#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

enum GameState {
    MENU,
    PLAYING
};

void createButton(const std::string& textStr, float yPos, sf::Text& text, sf::RectangleShape& rect, const sf::Font& font, sf::RenderWindow* window, bool isContinuing) {
    text.setFont(font);
    text.setCharacterSize(40);
    text.setString(textStr);

    text.setFillColor(isContinuing ? sf::Color(255, 200, 0) : sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    float windowWidth = (float)window->getSize().x;
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(windowWidth / 2.0f, yPos);

    rect.setSize(sf::Vector2f(300, 60));
    rect.setFillColor(sf::Color(0, 0, 0, 180)); 
    rect.setOrigin(150.f, 30.f);
    rect.setPosition(windowWidth / 2.0f, yPos);
}


int main() {
    Game game;
    GameState currentState = MENU;
    sf::RenderWindow* window = game.getWindow();
    window->setMouseCursorVisible(true);
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
        return -1;
    }
    sf::Text playText, newGameText, exitText;
    sf::RectangleShape playRect, newGameRect, exitRect;

    sf::Clock frameClock;

    while (window->isOpen()) {
        sf::Time deltaTime = frameClock.restart();
        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (currentState == PLAYING) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentState = MENU; 
                    window->setMouseCursorVisible(true);
                }
                else {
                    game.processEvents(event); 
                }
            }

            if (currentState == MENU) {
                
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

                    if (playRect.getGlobalBounds().contains(mousePos)) {
                        if (!game.isGameStarted()) {
                            game.resetGame();
                        }
                        currentState = PLAYING;
                        window->setMouseCursorVisible(false);
                    }
                    else if (newGameRect.getGlobalBounds().contains(mousePos)) {
                        game.resetGame(); 
                        currentState = PLAYING;
                        window->setMouseCursorVisible(false);
                    }
                    else if (exitRect.getGlobalBounds().contains(mousePos)) {
                        window->close();
                    }
                }
            }

        
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
                window->setView(sf::View(visibleArea));
              
            }
        } 

       
        if (currentState == PLAYING) {
            game.update(deltaTime);
            game.render();
        }
        else if (currentState == MENU) {
            game.renderBackground(); 

         
            bool isContinuing = game.isGameStarted();
            float windowHeight = (float)window->getSize().y;
            float center_y = windowHeight / 2.0f;

          
            createButton(isContinuing ? "Continuar" : "Jugar", center_y - 100.f, playText, playRect, font, window, isContinuing);
            createButton("Nueva Partida", center_y, newGameText, newGameRect, font, window, false);
            createButton("Salir", center_y + 100.f, exitText, exitRect, font, window, false);

         
            window->draw(playRect);
            window->draw(newGameRect);
            window->draw(exitRect);
            window->draw(playText);
            window->draw(newGameText);
            window->draw(exitText);

            window->display();
        }
    } 

    return 0;
}