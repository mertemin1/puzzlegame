#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "grid.hpp"
#include "sprite.hpp"

enum gameState {
    CONTINUE, 
    FINISHED
};
void finishGame(sf::RenderWindow& w , std::unique_ptr<Map>& m){
    w.clear();
    m->renderMap(w);
    w.display();
}
int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cerr << "Usage : ./Sokoban levels/<levelname>.txt" << std::endl;
        return 1;
    }
    const std::string levelPath = argv[1];

    std::ifstream levelFile(levelPath);
    if (!levelFile.is_open()) {
        std::cerr << "Could not open level file: " << levelPath << '\n';
        return 1;
    }

    int levelHeight = 0;
    int levelWidth = 0;
    if (!(levelFile >> levelHeight >> levelWidth)) {
        std::cerr << "Could not read level dimensions from: " << levelPath << '\n';
        return 1;
    }

    const auto windowWidth = static_cast<unsigned int>(levelWidth * GRIDSIZE);
    const auto windowHeight = static_cast<unsigned int>(levelHeight * GRIDSIZE);
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Sokoban");
    window.setFramerateLimit(60);

    auto gameMap = Map::create(levelPath);
    if (!gameMap) {
        std::cerr << "Map could not be created from: " << levelPath << '\n';
        return 1;
    }
    
    sf::Clock moveClock;
    const sf::Time moveDelay = sf::milliseconds(120);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (Player* player = gameMap->getPlayer(); player != nullptr &&
            moveClock.getElapsedTime() >= moveDelay) {
            if (player->moveWithInput()) {
                if(gameMap->isFinished()){
                    std::cout << levelPath << " finished. Congratulations" << std::endl;
                    window.close();
                }
                moveClock.restart();
            }
        }

        window.clear();
        gameMap->renderMap(window);
        window.display();
    }

    return 0;
}