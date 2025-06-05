#pragma once
#include "../Engine/Plugins/DungeonGenerator.h"

#include <vector>
#include <string>
#include <random>

class RoomList {
public:    
    std::vector<RoomResource> rooms = {
        RoomResource("./Assets/Maps/Rooms/1_Room_E_01", {Direction::EAST}),
        RoomResource("./Assets/Maps/Rooms/1_Room_S_01", {Direction::SOUTH}),
        RoomResource("./Assets/Maps/Rooms/1_Room_W_01", {Direction::WEST}),
        RoomResource("./Assets/Maps/Rooms/1_Room_N_01", {Direction::NORTH}),
        
        RoomResource("./Assets/Maps/Rooms/2_Room_EW_01", {Direction::EAST, Direction::WEST}),
        RoomResource("./Assets/Maps/Rooms/2_Room_NS_01", {Direction::NORTH, Direction::SOUTH}),
        RoomResource("./Assets/Maps/Rooms/2_Room_NE_01", {Direction::NORTH, Direction::EAST}),
        RoomResource("./Assets/Maps/Rooms/2_Room_NW_01", {Direction::NORTH, Direction::WEST}),
        RoomResource("./Assets/Maps/Rooms/2_Room_SW_01", {Direction::SOUTH, Direction::WEST}),
        RoomResource("./Assets/Maps/Rooms/2_Room_SE_01", {Direction::SOUTH, Direction::EAST}),
        
        RoomResource("./Assets/Maps/Rooms/3_Room_NSE_01", {Direction::NORTH, Direction::SOUTH, Direction::EAST}),
        RoomResource("./Assets/Maps/Rooms/3_Room_NSW_01", {Direction::NORTH, Direction::SOUTH, Direction::WEST}),
        RoomResource("./Assets/Maps/Rooms/3_Room_NEW_01", {Direction::NORTH, Direction::EAST, Direction::WEST}),
        RoomResource("./Assets/Maps/Rooms/3_Room_SEW_01", {Direction::SOUTH, Direction::EAST, Direction::WEST}),
        
        RoomResource("./Assets/Maps/Rooms/4_Room_NSWE_01", {Direction::SOUTH, Direction::EAST, Direction::WEST, Direction::NORTH}),
    };

    mutable std::mt19937 randomEngine;

    RoomList() {
        std::random_device rd;
        randomEngine.seed(rd());
    }

    const RoomResource* GetBestRoomResource(const Room* dungeonRoom) const;

private:
    std::vector<Direction> GetSortedDirections(const std::map<Direction, bool>& connections) const;
};
