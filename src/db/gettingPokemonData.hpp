#include <unordered_map>
#include <string>
#include <optional>
#include <fstream>
#include <stdexcept>
#include "json.hpp"
#include "../pokemon.h"
#include "../deck.h"
#include <set>

using json = nlohmann::json;

std::unordered_map<std::string, std::string> prefixToFile = {
    {"A1", "./src/db/data/geneticApex.json"}
};

std::string getPrefix(const std::string& cardID) {
    size_t separatorPosition = cardID.find('#');
    if (separatorPosition != std::string::npos) {
        return cardID.substr(0, separatorPosition);
    }
    throw std::invalid_argument("cardID mal formaté : " + cardID);
}

energyList parseEnergyList(const json& energyJson) {
    std::vector<typeEnergy> parsedEnergy;
    for (const auto& energy : energyJson) {
        std::string energyStr = energy.get<std::string>();
        parsedEnergy.push_back(stringToTypeEnergy(energyStr));
    }
    return energyList(parsedEnergy);
}

pokemonData findPokemonInFile(const std::string& filename, const std::string& cardID) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filename);
    }

    json jsonData;
    file >> jsonData;

    for (const auto& item : jsonData) {
        if (item["cardID"] == cardID) {
            pokemonData data;

            // Champs de base
            data.cardID = item["cardID"];
            data.name = item["name"];
            data.hp = item["hp"];
            data.type = stringToTypeEnergy(item["type"]);
            data.weakness = stringToTypeEnergy(item["weakness"]);
            data.evolveFrom = item.contains("evolvesFrom") ? std::optional<std::string>(item["evolvesFrom"].get<std::string>()) : std::nullopt;

            // Coût de retraite
            data.retreatCost = parseEnergyList(item["retreatCost"]);
            // Moves
            for (const auto& move : item["moves"]) {
                data.moves.push_back(Move{
                    move["name"],
                    move["power"],
                    energyList(parseEnergyList(move["cost"]))
                });
            }

            return data;
        }
    }

    throw std::runtime_error("Pokémon non trouvé : " + cardID); // Si le Pokémon n'est pas trouvé
}

pokemonData getPokemonData(const std::string& cardID) {
    std::string prefix = getPrefix(cardID);
    return findPokemonInFile(prefixToFile[prefix], cardID);
}

Deck getDeck(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + filename);
    }

    json jsonData;
    file >> jsonData;

    std::vector<std::unique_ptr<Card>> cards;
    std::set<typeEnergy> energySet;

    // Parse energy types
    for (const auto& energy : jsonData["energyType"]) {
        energySet.insert(stringToTypeEnergy(energy.get<std::string>()));
    }

    // Convert set to vector
    std::vector<typeEnergy> energyTypes(energySet.begin(), energySet.end());

    // Parse cards
    for (const auto& cardEntry : jsonData["cardsList"]) {
        std::string cardID = cardEntry["cardID"].get<std::string>();
        int count = cardEntry["count"].get<int>();

        pokemonData data = getPokemonData(cardID);
        for (int i = 0; i < count; ++i) {
            cards.push_back(std::make_unique<Pokemon>(data));
        }
    }

    return Deck(std::move(cards), energyTypes);
}