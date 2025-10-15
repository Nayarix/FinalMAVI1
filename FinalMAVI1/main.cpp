#include "Game.h"
#include <SFML/Graphics.hpp> 
#include <iostream>

enum GameState {
    MENU,
    PLAYING,
    TUTORIAL
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

    rect.setSize(sf::Vector2f(300.f, 60.f));
    rect.setFillColor(sf::Color(0, 0, 0, 180));
    rect.setOrigin(150.f, 30.f);
    rect.setPosition(windowWidth / 2.0f, yPos);
}

int main() {
    Game game;
    GameState currentState = MENU;
    sf::RenderWindow* window = game.getWindow();
    GameState stateBeforeTutorial = MENU;
    float tutorialScrollY = 0.f;

    window->setMouseCursorVisible(true);

    std::vector<std::string> tutorialRules = game.getRulesForDisplay();

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
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
                window->setView(sf::View(visibleArea));
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
            if (currentState == TUTORIAL) {
                if (event.type == sf::Event::MouseWheelScrolled) {
                    tutorialScrollY += event.mouseWheelScroll.delta * 30.0f;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentState = stateBeforeTutorial;
                    if (currentState == PLAYING) {
                        window->setMouseCursorVisible(false);
                    }
                }
            }

            
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

                
                if (currentState == MENU) {
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

                
                if (game.getTutorialButtonBounds().contains(mousePos) && currentState != TUTORIAL) {
                    stateBeforeTutorial = currentState;
                    currentState = TUTORIAL;
                    window->setMouseCursorVisible(true);
                }
                if (game.getMusicButtonBounds().contains(mousePos)) {
                    if (game.isMusicPlaying) {
                        game.backgroundMusic.pause();
                        game.isMusicPlaying = false;
                    }
                    else {
                        game.backgroundMusic.play();
                        game.isMusicPlaying = true;
                    }
                }
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
            game.renderTutorialButton(); 
            game.renderMusicButton();    
            window->display();
        }
        else if (currentState == TUTORIAL) {
            game.renderBackground();
            sf::RectangleShape backgroundRect;
            float padding = 30.f;
            float rectWidth = (float)window->getSize().x - 2 * padding;
            float rectHeight = (float)window->getSize().y - 150.f;

            backgroundRect.setSize(sf::Vector2f(rectWidth, rectHeight));
            backgroundRect.setFillColor(sf::Color(0, 0, 0, 180));
            backgroundRect.setPosition(padding, 120.f);
            window->draw(backgroundRect);

            sf::Text titleText;
            titleText.setFont(font);
            titleText.setString("Guia de Combinaciones (Bloque IDs)");
            titleText.setCharacterSize(60);
            titleText.setFillColor(sf::Color::Yellow);
            titleText.setOrigin(titleText.getLocalBounds().width / 2.0f, titleText.getLocalBounds().height / 2.0f);
            titleText.setPosition((float)window->getSize().x / 2.0f, 50.f);
            window->draw(titleText);

            float contentStartX = padding + 20.f;
            float contentStartY = 140.f;
            float totalContentHeight = (float)tutorialRules.size() * 30.f;
            float visibleAreaHeight = rectHeight - (contentStartY - backgroundRect.getPosition().y) - 30.f;
            float maxScroll = totalContentHeight - visibleAreaHeight;
            if (maxScroll < 0) maxScroll = 0.f;
            if (tutorialScrollY > 0.f) tutorialScrollY = 0.f;
            if (tutorialScrollY < -maxScroll) tutorialScrollY = -maxScroll;
            float currentY = contentStartY + tutorialScrollY;

            for (const std::string& rule : tutorialRules) {
                sf::Text ruleText;
                ruleText.setFont(font);
                ruleText.setString(rule);
                ruleText.setCharacterSize(24);
                sf::Color textColor = sf::Color::White;

                if (rule.find("--- TUTORIAL") != std::string::npos) {
                    textColor = sf::Color(0, 255, 255);
                }
                else if (rule.find("--- COMBINACIONES NIVEL 1 (100 PUNTOS) ---") != std::string::npos) {
                    textColor = sf::Color(255, 165, 0);
                }
                else if (rule.find("--- COMBINACIONES NIVEL 2 (500 PUNTOS) ---") != std::string::npos) {
                    textColor = sf::Color(255, 0, 255);
                }
                else if (rule.find("--- COMBINACIONES NIVEL 3 (2500 PUNTOS) ---") != std::string::npos) {
                    textColor = sf::Color::Red;
                }

                ruleText.setFillColor(textColor);
                ruleText.setPosition(contentStartX, currentY);

                if (currentY > backgroundRect.getPosition().y + 10.f && currentY < backgroundRect.getPosition().y + rectHeight - 30.f) {
                    window->draw(ruleText);
                }
                currentY += 30.f;
            }
            game.renderTutorialButton();
            game.renderMusicButton();    
            window->display();
        }
    }
    return 0;
}