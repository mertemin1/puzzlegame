#pragma once 
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
extern const std::string floorSrc;
extern const float GRIDSIZE;

//placeholder
class Sprite;
class Player;

class Map{
    public: 
        Map(size_t x, size_t y);
        ~Map() = default;
        float gridSize = GRIDSIZE;
        static std::unique_ptr<Map> create(const std::string& filepath);
        bool isOutOfBounds(int x , int y);
        Sprite* getSprite(int x , int y);
        Player* getPlayer();
        //if the grid is nullptr; render floorSprite
        sf::Sprite floorSprite;
        sf::Sprite targetSprite;
        static std::unique_ptr<Map> createMap(int x , int y);       
        void renderMap(sf::RenderWindow& window);
        //only checks if x,y is out of bounds then swaps sprite's coordinate with x and y
        void move(int x, int y , Sprite& sprite);
        void add(int x , int y , std::unique_ptr<Sprite> sprite);
        bool isFinished();
        protected:
        int height , width;
        std::vector<std::vector <std::unique_ptr <Sprite>>> grid;
        static std::vector<sf::Vector2i> targets;
    };

