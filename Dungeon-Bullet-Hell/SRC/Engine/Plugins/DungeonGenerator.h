#pragma once

#include <glm.hpp> // Assurez-vous que c'est le bon chemin pour glm::vec2
#include <map>
#include <random>
#include <vector>

// Définitions de directions pour la grille
enum class Direction { NORTH, SOUTH, EAST, WEST };
glm::vec2 GetDirectionVector(Direction dir);
Direction GetOppositeDirection(Direction dir);

class RoomResource
{
public:
    RoomResource(std::string_view csv, std::vector<Direction> d) : csvPath(csv), doors(d) {};

    std::string_view csvPath;
    std::vector<Direction> doors;
};


// Classe Room
class Room {
public:
    glm::vec2 position;
    std::map<Direction, bool> connections; // True if there's a door in that direction

    Room(glm::vec2 pos);

    int GetDoorCount() const;
    int GetComplexityCost() const;
};

// --- Comparateur pour glm::vec2, nécessaire pour std::map ---
struct Vec2Comparer {
    bool operator()(const glm::vec2& a, const glm::vec2& b) const;
};

// Classe DungeonGenerator
class DungeonGenerator {
public:
    std::map<glm::vec2, Room*, Vec2Comparer> grid;
    std::vector<Room*> rooms;
    std::vector<Room*> pendingRoomsVector; // Utilisé pour la sélection aléatoire

    std::mt19937 randomEngine; // Moteur de nombres aléatoires

    DungeonGenerator();
    ~DungeonGenerator();

    void GenerateDungeon(int desiredRoomCount);
    void AddRoom(Room* room);
    void PrintDungeon(); // Gardée ici pour l'affichage de débogage de la génération
};