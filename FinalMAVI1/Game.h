#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();             // Constructor
    ~Game();            // Destructor
    void run();         // Bucle principal del juego

private:
    void processEvents();       // Maneja los eventos de entrada
    void render();              // Dibuja en pantalla

    sf::RenderWindow* window; // Puntero a la ventana de SFML
    sf::Font font;              // Fuente para el texto
    sf::Text text;              // Objeto de texto
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock clock;            // Reloj para calcular delta time
    sf::Sprite cursor;
    sf::Texture mat_cursor;

};

#endif // GAME_H