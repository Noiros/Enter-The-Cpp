#include "RoomList.h"
#include <iostream> // Pour débogage

#include "../Engine/Logger.h"

// Assurez-vous d'inclure les headers nécessaires pour RoomResource, Direction, etc.
// #include "DungeonGenerator.h" // Si RoomResource n'est pas déjà inclus via RoomList.h
// #include <algorithm> // Pour std::sort

const RoomResource* RoomList::GetBestRoomResource(const Room* dungeonRoom) const {
    // Obtenir les directions triées de la salle du donjon
    std::vector<Direction> targetConnections = GetSortedDirections(dungeonRoom->connections);

    std::vector<const RoomResource*> matchingResources;

    // Parcourir toutes les RoomResources disponibles
    for (const auto& resource : rooms) {
        // CORRECTION: Utiliser 'resource.doors' au lieu de 'resource.connections'
        std::vector<Direction> resourceConnections = resource.doors; 
        
        // Trier les directions de la ressource pour comparaison
        std::sort(resourceConnections.begin(), resourceConnections.end());

        // Comparer les connexions. Si elles correspondent, cette ressource est "propice".
        if (resourceConnections == targetConnections) {
            matchingResources.push_back(&resource);
        }
    }

    // Si des ressources correspondantes sont trouvées, en choisir une aléatoirement
    if (!matchingResources.empty()) {
        // NOTE: Si randomEngine n'est pas mutable, cela provoquera une erreur.
        // Assurez-vous que 'randomEngine' est déclaré comme 'mutable std::mt19937 randomEngine;' dans RoomList.h
        std::uniform_int_distribution<int> distribution(0, static_cast<int>(matchingResources.size() - 1));
        return matchingResources[distribution(randomEngine)];
    }

    // Aucun RoomResource correspondant trouvé
    Logger::Err("No RoomResource found for connections");
    return nullptr; // Ou un RoomResource par défaut pour gérer l'erreur
}

std::vector<Direction> RoomList::GetSortedDirections(const std::map<Direction, bool>& connections) const {
    std::vector<Direction> sortedDirs;
    for (const auto& pair : connections) {
        if (pair.second) { // Si la connexion existe
            sortedDirs.push_back(pair.first);
        }
    }
    std::sort(sortedDirs.begin(), sortedDirs.end()); // Trier pour une comparaison canonique
    return sortedDirs;
}