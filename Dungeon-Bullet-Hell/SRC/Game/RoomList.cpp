#include "RoomList.h"
#include <iostream> // Pour débogage

#include "../Engine/Logger.h"

const RoomResource* RoomList::GetBestRoomResource(const Room* dungeonRoom) const {
    std::vector<Direction> targetConnections = GetSortedDirections(dungeonRoom->connections);
    std::vector<const RoomResource*> matchingResources;

    for (const auto& resource : rooms) {
        std::vector<Direction> resourceConnections = resource.doors; 
        
        std::sort(resourceConnections.begin(), resourceConnections.end());

        if (resourceConnections == targetConnections) {
            matchingResources.push_back(&resource);
        }
    }

    if (!matchingResources.empty()) {
        std::uniform_int_distribution<int> distribution(0, static_cast<int>(matchingResources.size() - 1));
        return matchingResources[distribution(randomEngine)];
    }

    Logger::Err("No RoomResource found for connections");
    return nullptr;
}

std::vector<Direction> RoomList::GetSortedDirections(const std::map<Direction, bool>& connections) const {
    std::vector<Direction> sortedDirs;
    for (const auto& pair : connections) {
        if (pair.second) {
            sortedDirs.push_back(pair.first);
        }
    }
    std::sort(sortedDirs.begin(), sortedDirs.end());
    return sortedDirs;
}