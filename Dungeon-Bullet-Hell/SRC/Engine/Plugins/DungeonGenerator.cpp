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
    // Nous n'ajoutons PAS startRoom à la pile d'expansion, pour éviter toute expansion future à partir d'elle.

    int currentRoomCount = 1;

    // Forcer la première extension vers le nord
    if (currentRoomCount < desiredRoomCount) {
        glm::vec2 northNeighborPos = startRoom->position + GetDirectionVector(Direction::NORTH);
        Room* northRoom = new Room(northNeighborPos);
        startRoom->connections[Direction::NORTH] = true;
        northRoom->connections[GetOppositeDirection(Direction::NORTH)] = true;
        AddRoom(northRoom);
        roomExpansionStack.push_back(northRoom); // Seule la salle du nord est ajoutée à la pile
        currentRoomCount++;
    }

    // Itérer à travers la pile d'expansion des salles
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
                // Si la pièce voisine est la salle de départ, et que la connexion n'est pas déjà établie vers le nord
                // alors nous ne créons pas de connexion, pour maintenir la salle de départ avec une seule porte.
                if (neighborPos == glm::vec2(0,0) && dir != Direction::NORTH) {
                    continue; 
                }

                // Si la connexion n'existe pas déjà, ou si les deux côtés ne sont pas connectés, créer la connexion
                if (!currentRoom->connections.at(dir) || !it->second->connections.at(GetOppositeDirection(dir))) {
                    currentRoom->connections[dir] = true;
                    it->second->connections[GetOppositeDirection(dir)] = true;
                }
            }
        }

        if (!expandedThisIteration) {
            roomExpansionStack.pop_back();
        }
    }
}