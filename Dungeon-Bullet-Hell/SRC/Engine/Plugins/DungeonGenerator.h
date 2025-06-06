#pragma once

#include <glm.hpp>
#include <map>
#include <random>
#include <vector>

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

class Room {
public:
    glm::vec2 position;
    std::map<Direction, bool> connections;

    Room(glm::vec2 pos);

    int GetDoorCount() const;
    int GetComplexityCost() const;
};

struct Vec2Comparer {
    bool operator()(const glm::vec2& a, const glm::vec2& b) const;
};

class DungeonGenerator {
public:
    std::map<glm::vec2, Room*, Vec2Comparer> grid;
    std::vector<Room*> rooms;
    std::vector<Room*> pendingRoomsVector;

    std::mt19937 randomEngine;

    DungeonGenerator();
    ~DungeonGenerator();

    void GenerateDungeon(int desiredRoomCount);
    void AddRoom(Room* room);
    void PrintDungeon();
};