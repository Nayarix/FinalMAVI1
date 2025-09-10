#include "Game.h"
#include <iostream>

using namespace sf;

Game::Game() : gravity(500.f) {
    window = new RenderWindow(VideoMode::getDesktopMode(), "Mi Juego SFML con POO", Style::Fullscreen);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);
    is_fullscreen = true;

    if (!backgroundTexture.loadFromFile("BloquesMAVI1/fondoPrueba2.jpg")) {
        std::cerr << "Error al cargar el fondo" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    float originalWidth = backgroundTexture.getSize().x;
    float windowWidth = window->getSize().x;
    float scale = windowWidth / originalWidth;
    backgroundSprite.setScale(scale, scale);

    sf::Texture Espada, Escudo, Corona;
    if (!Espada.loadFromFile("BloquesMAVI1/Espada.png") ||
        !Escudo.loadFromFile("BloquesMAVI1/Escudo.png") ||
        !Corona.loadFromFile("BloquesMAVI1/Corona.png")) {
        std::cerr << "Error al cargar las texturas de bloques" << std::endl;
    }
    blockTextures.push_back(Espada);
    blockTextures.push_back(Escudo);
    blockTextures.push_back(Corona);

    currentTextureIndex = 0;
    blockSprite.setTexture(blockTextures[currentTextureIndex]);
    float originalBlockWidth = blockTextures[0].getSize().x;
    float windowWidth_initial = window->getSize().x;
    float scale_initial = (windowWidth_initial / 1990.0f) * 0.25f;
    blockSprite.setScale(scale_initial, scale_initial);

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString("Bienvenido a SFML!");
    text.setPosition(10.f, 10.f);

    // --- POSICIONES MANUALES DE LAS COLUMNAS ---
    columnPositions = {
        150.f, // Columna 1
        400.f, // Columna 2
        650.f, // Columna 3
        900.f, // Columna 4 (Centro)
        1150.f, // Columna 5
        1400.f, // Columna 6
        1650.f  // Columna 7
    };

    currentColumnIndex = 3; // Posición central inicial
    isBlockLaunched = false;
    spawnNewBlock();
}

Game::~Game() {
    delete window;
    window = nullptr;
}

void Game::run() {
    sf::Clock frameClock;
    while (window->isOpen()) {
        sf::Time deltaTime = frameClock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (!isBlockLaunched) {
                // Mover el bloque actual
                if (event.key.code == sf::Keyboard::Left) {
                    currentColumnIndex = std::max(0, currentColumnIndex - 1);
                    spawnNewBlock(); // Regenerar el bloque en la nueva posición
                }
                if (event.key.code == sf::Keyboard::Right) {
                    currentColumnIndex = std::min(static_cast<int>(columnPositions.size()) - 1, currentColumnIndex + 1);
                    spawnNewBlock(); // Regenerar el bloque en la nueva posición
                }
                // Lanzar el bloque
                if (event.key.code == sf::Keyboard::Space) {
                    sf::Sprite newBlock = blockSprite;
                    placedBlocks.push_back(newBlock);
                    blockVelocities.push_back(sf::Vector2f(0.f, 0.f));
                    isBlockLaunched = true;
                }
                // Cambiar la textura
                if (event.key.code == sf::Keyboard::C) {
                    currentTextureIndex++;
                    if (currentTextureIndex >= blockTextures.size()) {
                        currentTextureIndex = 0;
                    }
                    blockSprite.setTexture(blockTextures[currentTextureIndex]);
                }
            }

            // Alternar pantalla completa
            if (event.key.code == sf::Keyboard::P) {
                if (is_fullscreen) {
                    window->create(sf::VideoMode(1500, 852), "Mi Juego SFML con POO", sf::Style::Default);
                    is_fullscreen = false;
                }
                else {
                    window->create(sf::VideoMode::getDesktopMode(), "Mi Juego SFML con POO", sf::Style::Fullscreen);
                    is_fullscreen = true;
                }
                window->setMouseCursorVisible(!is_fullscreen);
                window->setFramerateLimit(60);
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    bool allBlocksStopped = true;

    for (size_t i = 0; i < placedBlocks.size(); ++i) {
        blockVelocities[i].y += gravity * deltaTime.asSeconds();

        sf::Vector2f currentPos = placedBlocks[i].getPosition();
        sf::Vector2f nextPos = currentPos;
        nextPos.y += blockVelocities[i].y * deltaTime.asSeconds();

        sf::FloatRect blockBounds = placedBlocks[i].getGlobalBounds();
        blockBounds.height *= 0.85f;
        blockBounds.width *= 0.85f;

        if (nextPos.y + blockBounds.height >= window->getSize().y) {
            nextPos.y = window->getSize().y - blockBounds.height;
            blockVelocities[i].y = 0.f;
        }

        for (size_t j = 0; j < placedBlocks.size(); ++j) {
            if (i == j) continue;

            sf::FloatRect otherBlockBounds = placedBlocks[j].getGlobalBounds();
            otherBlockBounds.height *= 0.85f;
            otherBlockBounds.width *= 0.85f;

            sf::FloatRect nextBounds = blockBounds;
            nextBounds.top = nextPos.y;

            if (nextBounds.intersects(otherBlockBounds)) {
                if (blockVelocities[i].y > 0 && currentPos.y < otherBlockBounds.top) {
                    nextPos.y = otherBlockBounds.top - blockBounds.height;
                    blockVelocities[i].y = 0.f;
                }
            }
        }

        placedBlocks[i].setPosition(placedBlocks[i].getPosition().x, nextPos.y);

        if (blockVelocities[i].y > 0.f) {
            allBlocksStopped = false;
        }
    }

    if (isBlockLaunched && allBlocksStopped) {
        spawnNewBlock();
        isBlockLaunched = false;
    }
}

void Game::render() {
    window->clear();
    window->draw(backgroundSprite);

    for (const auto& block : placedBlocks) {
        window->draw(block);
    }

    if (!isBlockLaunched) {
        window->draw(blockSprite);
    }

    window->draw(text);
    window->display();
}

void Game::scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture) {
    float originalWidth = static_cast<float>(texture.getSize().x);
    float windowWidth = static_cast<float>(window->getSize().x);
    float scale = windowWidth / originalWidth;
    sprite.setScale(scale, scale);
}

void Game::spawnNewBlock() {
    currentTextureIndex = rand() % blockTextures.size();
    blockSprite.setTexture(blockTextures[currentTextureIndex]);

    float blockWidth = blockSprite.getGlobalBounds().width;
    float posX = columnPositions[currentColumnIndex] - (blockWidth / 2.0f);
    float posY = 50.f;

    blockSprite.setPosition(posX, posY);
}