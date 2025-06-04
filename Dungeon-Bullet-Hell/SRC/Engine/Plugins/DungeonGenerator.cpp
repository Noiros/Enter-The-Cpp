#include "DungeonGenerator.h"
#include <algorithm> // Pour std::shuffle, std::min, std::max
#include <iostream>  // Pour std::cout
#include <random>    // Pour std::mt19937 et std::random_device
#include <vector>    // Pour std::vector utilisé comme une pile

// Implémentation des fonctions utilitaires
glm::vec2 GetDirectionVector(Direction dir) {
    if (dir == Direction::NORTH) return {0, 1};
    if (dir == Direction::SOUTH) return {0, -1};
    if (dir == Direction::EAST) return {1, 0};
    if (dir == Direction::WEST) return {-1, 0};
    return {0, 0}; // Ne devrait pas arriver
}

Direction GetOppositeDirection(Direction dir) {
    if (dir == Direction::NORTH) return Direction::SOUTH;
    if (dir == Direction::SOUTH) return Direction::NORTH;
    if (dir == Direction::EAST) return Direction::WEST;
    if (dir == Direction::WEST) return Direction::EAST;
    return dir; // Ne devrait pas arriver, mais évite un avertissement du compilateur
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
    // Vous aviez cette fonction, je la laisse au cas où elle serait utilisée ailleurs.
    // Si elle n'est pas utilisée, vous pouvez la supprimer.
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
    rooms.clear();
    grid.clear();
    // pendingRoomsVector n'est plus un membre, il est local à GenerateDungeon
}

void DungeonGenerator::AddRoom(Room* room) {
    grid[room->position] = room;
    rooms.push_back(room);
}

void DungeonGenerator::GenerateDungeon(int desiredRoomCount) {
    // Nettoyer les données des exécutions précédentes
    for (Room* room : rooms) {
        delete room;
    }
    rooms.clear();
    grid.clear();

    if (desiredRoomCount <= 0) return;

    std::vector<Room*> roomExpansionStack; // Utilisée comme une pile (LIFO)

    // 1. Créer la salle de départ
    Room* startRoom = new Room({0, 0});
    AddRoom(startRoom); // Ajoute à 'grid' et 'rooms'
    roomExpansionStack.push_back(startRoom);

    int currentRoomCount = 1;

    while (currentRoomCount < desiredRoomCount && !roomExpansionStack.empty()) {
        Room* currentRoom = roomExpansionStack.back();

        std::vector<Direction> availableDirections = {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST};
        std::shuffle(availableDirections.begin(), availableDirections.end(), randomEngine);

        bool expandedThisIteration = false;
        for (Direction dir : availableDirections) {
            glm::vec2 neighborPos = currentRoom->position + GetDirectionVector(dir);
            auto it = grid.find(neighborPos);

            if (it == grid.end()) { // Pas de pièce à cette position
                if (currentRoomCount < desiredRoomCount) {
                    Room* newRoom = new Room(neighborPos);
                    currentRoom->connections[dir] = true;
                    newRoom->connections[GetOppositeDirection(dir)] = true;
                    AddRoom(newRoom);
                    roomExpansionStack.push_back(newRoom);
                    currentRoomCount++;
                    expandedThisIteration = true;
                    break; 
                }
            } else { // Une pièce existe déjà à cette position
                Room* existingNeighbor = it->second;
                if (!currentRoom->connections.at(dir) || !existingNeighbor->connections.at(GetOppositeDirection(dir))) {
                    currentRoom->connections[dir] = true;
                    existingNeighbor->connections[GetOppositeDirection(dir)] = true;
                }
            }
        }

        if (!expandedThisIteration) {
            roomExpansionStack.pop_back();
        }
    }
}
