#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector> // Necesitas incluir la cabecera para std::vector

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

    // Bloques del juego
    sf::Sprite blockSprite; // Sprite del bloque que sigue al cursor
    std::vector<sf::Texture> blockTextures; // Vector para almacenar todas las texturas de bloques
    int currentTextureIndex; // Índice de la textura actual
    bool is_fullscreen;
    // Vector para almacenar todos los bloques colocados
    std::vector<sf::Sprite> placedBlocks;
};

#endif // GAME_H