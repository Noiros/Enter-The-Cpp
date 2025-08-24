#include "DungeonGenerator.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

glm::vec2 GetDirectionVector(Direction dir) {
    if (dir == Direction::NORTH) return {0, 1};
    if (dir == Direction::SOUTH) return {0, -1};
    if (dir == Direction::EAST) return {1, 0};
    if (dir == Direction::WEST) return {-1, 0};
    return {0, 0};
}

Direction GetOppositeDirection(Direction dir) {
    if (dir == Direction::NORTH) return Direction::SOUTH;
    if (dir == Direction::SOUTH) return Direction::NORTH;
    if (dir == Direction::EAST) return Direction::WEST;
    if (dir == Direction::WEST) return Direction::EAST;
}

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

bool Vec2Comparer::operator()(const glm::vec2& a, const glm::vec2& b) const {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

DungeonGenerator::DungeonGenerator() {
    std::random_device rd;
    randomEngine.seed(rd());
}

DungeonGenerator::~DungeonGenerator() {
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
    for (Room* room : rooms) {
        delete room;
    }
    rooms.clear();
    grid.clear();

    if (desiredRoomCount <= 0) return;

    std::vector<Room*> roomExpansionStack;

    Room* startRoom = new Room({0, 0});

    int currentRoomCount = 1;

    if (currentRoomCount < desiredRoomCount) {
        glm::vec2 northNeighborPos = startRoom->position + GetDirectionVector(Direction::NORTH);
        Room* northRoom = new Room(northNeighborPos);
        startRoom->connections[Direction::NORTH] = true;
        northRoom->connections[GetOppositeDirection(Direction::NORTH)] = true;
        AddRoom(northRoom);
        roomExpansionStack.push_back(northRoom);
        currentRoomCount++;
    }

    while (currentRoomCount < desiredRoomCount && !roomExpansionStack.empty()) {
        Room* currentRoom = roomExpansionStack.back();

        std::vector<Direction> availableDirections = {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST};
        std::shuffle(availableDirections.begin(), availableDirections.end(), randomEngine);

        bool expandedThisIteration = false;
        for (Direction dir : availableDirections) {
            glm::vec2 neighborPos = currentRoom->position + GetDirectionVector(dir);
            auto it = grid.find(neighborPos);

            if (it == grid.end()) {
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
            } else {
                if (neighborPos == glm::vec2(0,0) && dir != Direction::NORTH) {
                    continue; 
                }

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