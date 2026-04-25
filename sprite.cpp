#include <sprite.hpp>
#include <grid.hpp>

std::unordered_map<std::string, sf::Texture> Sprite::textureMap;

const std::string playerSrc = "src/character.png";
const std::string boxSrc = "src/box.png";
const std::string wallSrc = "src/wall.png";


sf::Texture& Sprite::getTexture(const std::string& path){
    if(textureMap.find(path) == textureMap.end()){

        if(!textureMap[path].loadFromFile(path)) { 
            std::cerr << "ERROR: Texture image could not load\n" << path << std::endl;

        }
    }
    return textureMap[path];
}

Sprite::Sprite(Map& g , int x , int y ,  bool iC , bool iM , const std::string& texturePath)
: isColliding(iC), isMoveable(iM), m_sprite(Sprite::getTexture(texturePath)), grid(g), posX(x), posY(y) 
{
    m_sprite.setPosition(sf::Vector2f(x * g.gridSize, y * g.gridSize));

    const sf::Vector2u textureSize = m_sprite.getTexture().getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        const float scaleX = g.gridSize / static_cast<float>(textureSize.x);
        const float scaleY = g.gridSize / static_cast<float>(textureSize.y);
        m_sprite.setScale(sf::Vector2f(scaleX, scaleY));
    }
}


//assuming player can only go in one direction at a time
void Sprite::move(int x , int y){
    if(this->grid.isOutOfBounds(x,y)) return;

    Sprite* target = grid.getSprite(x, y);
    if(target == nullptr){
        grid.move(x , y , *this);
        return;
    }

    if (!target->isMoveable) {
        return;
    }

    const int dx = x - this->posX;
    const int dy = y - this->posY;
    const int pushX = x + dx;
    const int pushY = y + dy;

    if (this->grid.isOutOfBounds(pushX, pushY)) return;
    if (grid.getSprite(pushX, pushY) != nullptr) return;

    grid.move(pushX, pushY, *target);
    grid.move(x, y, *this);
}

void Sprite::draw(sf::RenderWindow &window){
    window.draw(m_sprite);
}



Player::Player(Map& g , int x , int y)
:Sprite(g , x , y , true , true , playerSrc)
{
    //will add later
}

std::unique_ptr<Player> Player::createPlayer(Map& g , int x , int y){
    return std::make_unique<Player>(g,x,y);
}

Object::Object(Map& g , int x , int y , bool iC , bool iM ,const std::string& textureSrc)
:Sprite(g, x ,y ,iC ,iM , textureSrc)
{}

std::unique_ptr<Object> Object::createBox(Map& g , int x , int y){
    auto ptr = std::make_unique<Object>(g, x, y, true, true, boxSrc);
    ptr->isObjective = true;
    return ptr;
}
std::unique_ptr<Object> Object::createWall(Map& g , int x , int y){
    auto ptr = std::make_unique<Object>(g, x, y, true, false, wallSrc);
    return ptr;
}
bool Player::moveWithInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        this->move(this->posX , this->posY - 1);
        return true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        this->move(this->posX - 1 , this->posY);
        return true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        this->move(this->posX , this->posY + 1);
        return true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        this->move(this->posX + 1 , this->posY);
        return true;
    }
    return false;
}