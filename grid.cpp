#include <grid.hpp>
#include <sprite.hpp>

std::vector<sf::Vector2i> Map::targets;

const std::string floorSrc = "src/floor.png";
const std::string targetSrc = "src/target.png";
const float GRIDSIZE = 64.0f;

Map::Map(size_t x , size_t y)
:height(y),width(x),floorSprite(Sprite::getTexture(floorSrc)) , targetSprite(Sprite::getTexture(targetSrc))
{
    floorSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
    targetSprite.setPosition(sf::Vector2f(0.0f, 0.0f));

    const sf::Vector2u textureSize = floorSprite.getTexture().getSize();
    
    if (textureSize.x > 0 && textureSize.y > 0) {
        const float scaleX = this->gridSize / static_cast<float>(textureSize.x);
        const float scaleY = this->gridSize / static_cast<float>(textureSize.y);
        floorSprite.setScale(sf::Vector2f(scaleX, scaleY));
        targetSprite.setScale(sf::Vector2f(scaleX, scaleY));

    }
    this->grid.resize(y);
    for(int i = 0 ; i < y ; i++){
        grid[i].resize(x);
    }   
}

std::unique_ptr<Map> Map::create(const std::string& filepath){
    std::ifstream file(filepath);
    if (!file.is_open()) return nullptr;
    char tile;
    int x = 0;
    int y = 0;
    int height, width;

    if(!(file >> height >> width)){
        std::cerr << "dimensions cannot be read" << std::endl;
        return nullptr; 
    }
    auto temp =  Map::createMap(width, height);
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (file.get(tile)){
        if (tile == '\n'){
            y++;
            x = 0;
            continue;
        }
        if (tile == '\r') {
            continue;
        }
        if (y >= height || x >= width) {
            continue;
        }
        if (tile == '#') {
            temp->grid[y][x] = Object::createWall(*temp , x , y); 
        }
        else if(tile == 'o') { 
            temp->grid[y][x] = Object::createBox(*temp , x , y);
        }
        else if (tile == '!') {
            temp->grid[y][x] = Player::createPlayer(*temp , x , y);
        }
        else if (tile == '?') {
            targets.push_back(sf::Vector2i(x, y));
        }
        x++;
    }
    return temp;
}

bool Map::isOutOfBounds(int x, int y){
    return (x >= width || x < 0 || y >= height || y < 0) ? true : false;
}



Sprite* Map::getSprite(int x , int y){
    return grid[y][x].get();
}

Player* Map::getPlayer(){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == nullptr) continue;
            if (auto* player = dynamic_cast<Player*>(grid[y][x].get())) {
                return player;
            }
        }
    }
    return nullptr;
}

void Map::move(int x , int y , Sprite& sprite){
    if(isOutOfBounds(x,y)) return;
    std::swap(grid[sprite.posY][sprite.posX], grid[y][x]);
    sprite.posX = x;
    sprite.posY = y;
    sprite.m_sprite.setPosition(sf::Vector2f(x * gridSize , y * gridSize));
}

void Map::add(int x , int y , std::unique_ptr<Sprite> sprite){
    if(isOutOfBounds(x,y) || getSprite(x,y) != nullptr) return;
    grid[y][x] = std::move(sprite);
}

std::unique_ptr<Map> Map::createMap(int x , int y){
    auto ptr = std::make_unique<Map> (x,y);
    ptr->grid.resize(y);
    for (int i = 0 ; i<y ; i++){
        ptr->grid[i].resize(x);
    }
    ptr->height = y;
    ptr->width  = x;
    return ptr;
}

void Map::renderMap(sf::RenderWindow& window){
    for (int i = 0 ; i < this->height ; i++){
        for (int j = 0 ; j < this->width ; j++){
        
            floorSprite.setPosition(sf::Vector2f(j*gridSize , i*gridSize));
            window.draw(floorSprite);

            for(int k = 0 ; k < this->targets.size() ; k++){
                if(sf::Vector2i(j,i) == this->targets[k]){
                    targetSprite.setPosition(sf::Vector2f(j*gridSize , i*gridSize));
                    window.draw(targetSprite);
                }
            }

            if(this->grid[i][j] != nullptr){
                grid[i][j]->draw(window);   
            }
        }
    
    }
}
//lutfen 3 for looptan daha iyi bi yol bul
bool Map::isFinished(){
    if (targets.empty()) {
        return false;
    }
    for(const auto& target : targets){
        if(grid[target.y][target.x] == nullptr){
            return false;
        }
        if (grid[target.y][target.x]->isObjective == false) return false;
        
    }
    return true;
}