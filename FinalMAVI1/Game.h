#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector> 

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void render();
    void scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture);


    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock clock;
    sf::Sprite cursor;
    sf::Sprite blockSprite; 
    std::vector<sf::Texture> blockTextures; 
    int currentTextureIndex; 
    bool is_fullscreen;
   
    std::vector<sf::Sprite> placedBlocks;
};

#endif // GAME_H