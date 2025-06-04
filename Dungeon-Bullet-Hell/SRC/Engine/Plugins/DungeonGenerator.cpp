#include "DungeonGenerator.h"
#include <algorithm> // Pour std::shuffle, std::min, std::max
#include <iostream>  // Pour std::cout

// Implémentation des fonctions utilitaires
glm::vec2 GetDirectionVector(Direction dir) {
    if (dir == Direction::NORTH) return {0, 1};
    if (dir == Direction::SOUTH) return {0, -1};
    if (dir == Direction::EAST) return {1, 0};
    if (dir == Direction::WEST) return {-1, 0};
    return {0, 0}; // Should not happen
}

Direction GetOppositeDirection(Direction dir) {
    if (dir == Direction::NORTH) return Direction::SOUTH;
    if (dir == Direction::SOUTH) return Direction::NORTH;
    if (dir == Direction::EAST) return Direction::WEST;
    if (dir == Direction::WEST) return Direction::EAST;
    return dir;
}

// Implémentation de la classe Room
Room::Room(glm::vec2 pos) : position(pos) {
    connections[Direction::NORTH] = false;
    connections[Direction::SOUTH] = false;
    connections[Direction::EAST] = false;
    connections[Direction::WEST] = false;
}

int Room::GetDoorCount() const {
    int count = 0;
    for (const auto& pair : connections) {
        if (pair.second) {
            count++;
        }
    }
    return count;
}

int Room::GetComplexityCost() const {
    return GetDoorCount();
}

// Implémentation de Vec2Comparer
bool Vec2Comparer::operator()(const glm::vec2& a, const glm::vec2& b) const {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

// Implémentation de la classe DungeonGenerator
DungeonGenerator::DungeonGenerator() {
    std::random_device rd;
    randomEngine.seed(rd()); // Initialise le moteur aléatoire une seule fois
}

DungeonGenerator::~DungeonGenerator() {
    // Nettoyer la mémoire des salles allouées
    for (Room* room : rooms) {
        delete room;
    }
}

void DungeonGenerator::GenerateDungeon(int desiredRoomCount) {
    if (desiredRoomCount <= 0) return;

    // 1. Créer la salle de départ
    Room* startRoom = new Room({0, 0});
    AddRoom(startRoom);
    pendingRoomsVector.push_back(startRoom); // Ajouter à la nouvelle liste

    int currentRoomCount = 1;

    while (currentRoomCount < desiredRoomCount && !pendingRoomsVector.empty()) {
        // Sélectionner une salle aléatoire parmi celles en attente
        std::uniform_int_distribution<int> distribution(0, pendingRoomsVector.size() - 1);
        int randomIndex = distribution(randomEngine);
        Room* currentRoom = pendingRoomsVector[randomIndex];

        // Retirer la salle sélectionnée pour éviter de la traiter à nouveau immédiatement
        // et maintenir la "pile" de salles à explorer
        pendingRoomsVector.erase(pendingRoomsVector.begin() + randomIndex);

        std::vector<Direction> availableDirections;
        for (Direction dir : {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST}) {
            if (!currentRoom->connections.at(dir)) {
                glm::vec2 nextPos = currentRoom->position + GetDirectionVector(dir);
                if (grid.find(nextPos) == grid.end()) {
                    availableDirections.push_back(dir);
                }
            }
        }
        
        std::shuffle(availableDirections.begin(), availableDirections.end(), randomEngine);

        std::uniform_int_distribution<int> numNewDoorsDist(1, 2); 
        int doorsToOpen = numNewDoorsDist(randomEngine);

        int doorsOpened = 0;
        for (Direction dir : availableDirections) {
            if (currentRoomCount >= desiredRoomCount || doorsOpened >= doorsToOpen) break; 

            glm::vec2 newRoomPos = currentRoom->position + GetDirectionVector(dir);
            
            if (grid.find(newRoomPos) == grid.end()) {
                Room* newRoom = new Room(newRoomPos);

                currentRoom->connections[dir] = true;
                newRoom->connections[GetOppositeDirection(dir)] = true;

                AddRoom(newRoom);
                pendingRoomsVector.push_back(newRoom); // Ajouter à la nouvelle liste
                currentRoomCount++;
                doorsOpened++;
            }
        }
    }
}

void DungeonGenerator::AddRoom(Room* room) {
    grid[room->position] = room;
    rooms.push_back(room);
}

void DungeonGenerator::PrintDungeon() {
    if (rooms.empty()) {
        std::cout << "Donjon vide." << std::endl;
        return;
    }

    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (const auto& pair : grid) {
        minX = std::min(minX, static_cast<int>(pair.first.x));
        maxX = std::max(maxX, static_cast<int>(pair.first.x));
        minY = std::min(minY, static_cast<int>(pair.first.y));
        maxY = std::max(maxY, static_cast<int>(pair.first.y));
    }

    int displayWidth = (maxX - minX + 1) * 4 + 1;
    int displayHeight = (maxY - minY + 1) * 2 + 1;

    std::vector<std::vector<char>> displayGrid(displayHeight, std::vector<char>(displayWidth, ' '));

    for (int y = 0; y < displayHeight; ++y) {
        for (int x = 0; x < displayWidth; ++x) {
            if (y % 2 == 0) {
                if (x % 4 == 0) {
                    displayGrid[y][x] = '+';
                } else {
                    displayGrid[y][x] = '-';
                }
            } else {
                if (x % 4 == 0) {
                    displayGrid[y][x] = '|';
                } else {
                    displayGrid[y][x] = ' ';
                }
            }
        }
    }

    for (const auto& pair : grid) {
        const glm::vec2& roomPos = pair.first;
        const Room* room = pair.second;

        int gridX = (static_cast<int>(roomPos.x) - minX) * 4 + 1; 
        int gridY = (maxY - static_cast<int>(roomPos.y)) * 2 + 1;

        if (gridY >= 0 && gridY < displayHeight && gridX >= 0 && gridX < displayWidth) {
             displayGrid[gridY][gridX] = 'R';
        }

        if (room->connections.at(Direction::NORTH)) {
            if (gridY - 1 >= 0 && gridX >= 0 && gridX < displayWidth) {
                displayGrid[gridY - 1][gridX] = ' ';
            }
        }
        if (room->connections.at(Direction::SOUTH)) {
            if (gridY + 1 < displayHeight && gridX >= 0 && gridX < displayWidth) {
                displayGrid[gridY + 1][gridX] = ' ';
            }
        }
        if (room->connections.at(Direction::EAST)) {
            if (gridX + 2 < displayWidth && gridY >= 0 && gridY < displayHeight) {
                displayGrid[gridY][gridX + 2] = ' ';
            }
        }
        if (room->connections.at(Direction::WEST)) {
            if (gridX - 2 >= 0 && gridY >= 0 && gridY < displayHeight) {
                displayGrid[gridY][gridX - 2] = ' ';
            }
        }
    }

    for (int y = 0; y < displayHeight; ++y) {
        for (int x = 0; x < displayWidth; ++x) {
            std::cout << displayGrid[y][x];
        }
        std::cout << std::endl;
    }
}