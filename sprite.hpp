#pragma once
#include <grid.hpp>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

extern const std::string playerSrc;
extern const std::string boxSrc;
extern const std::string wallSrc;

class Map;

class Sprite{
    friend class Map;
    public:    
        Sprite(Map& g , int x , int y , bool iC , bool iM , const std::string& path);
        virtual ~Sprite() = default;
        bool isColliding;
        bool isMoveable;
        bool isObjective = false;
        void draw(sf::RenderWindow &window);
        static sf::Texture& getTexture(const std::string& path);
    protected:
        static std::unordered_map<std::string , sf::Texture> textureMap; //map of textures for sprites to use
        sf::Sprite m_sprite;
        Map& grid;
        int posX;
        int posY;
    bool canMove(size_t x, size_t y, int counter);// counter counts recursion to ensure either the player moves by itself or pushes a single box
    void move(int x, int y);//calls grid.move() 
};

class Player : public Sprite{
    public:    
        Player(Map& g , int x , int y);
        ~Player() = default;
        bool moveWithInput();
        static std::unique_ptr<Player> createPlayer(Map& g , int x , int y );
};

class Object : public Sprite{
    public:
        Object(Map& g , int x , int y, bool iC, bool iM ,const std::string& textureSrc);
        ~Object() = default; 
        
        static std::unique_ptr<Object> createBox(Map& g , int x , int y);
        static std::unique_ptr<Object> createWall(Map& g , int x , int y);
    
};