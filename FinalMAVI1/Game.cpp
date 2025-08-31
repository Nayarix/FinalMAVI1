#include "Game.h"
#include <iostream>

using namespace sf;

Game::Game() : gravity(500.f) { // Se usa un valor mayor para una caída más visible
    window = new RenderWindow(VideoMode::getDesktopMode(), "Mi Juego SFML con POO", Style::Fullscreen);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);
    is_fullscreen = true;

    // Cargar la imagen de fondo
    if (!backgroundTexture.loadFromFile("BloquesMAVI1/fondoPrueba2.jpg")) {
        std::cerr << "Error al cargar el fondo" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Ajustar la imagen de fondo al tamaño de la ventana al iniciar el programa
    float originalWidth = backgroundTexture.getSize().x;
    float windowWidth = window->getSize().x;
    float scale = windowWidth / originalWidth;
    backgroundSprite.setScale(scale, scale);

    // Cargar todas las texturas de bloques
    sf::Texture Espada, Escudo, Corona;
    if (!Espada.loadFromFile("BloquesMAVI1/Espada.png") ||
        !Escudo.loadFromFile("BloquesMAVI1/Escudo.png") ||
        !Corona.loadFromFile("BloquesMAVI1/Corona.png")) {
        std::cerr << "Error al cargar las texturas de bloques" << std::endl;
    }
    blockTextures.push_back(Espada);
    blockTextures.push_back(Escudo);
    blockTextures.push_back(Corona);

    // Inicializar el sprite del bloque que sigue al mouse
    currentTextureIndex = 0;
    blockSprite.setTexture(blockTextures[currentTextureIndex]);
    float originalBlockWidth = blockTextures[0].getSize().x;
    float windowWidth_initial = window->getSize().x;
    float scale_initial = (windowWidth_initial / 1990.0f) * 0.25f;
    blockSprite.setScale(scale_initial, scale_initial);

    // Cargar fuente y texto
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString("Bienvenido a SFML!");
    text.setPosition(10.f, 10.f);
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

        // Mover el sprite del bloque con el mouse
        if (event.type == sf::Event::MouseMoved) {
            blockSprite.setPosition(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
        }

        // Colocar un bloque en la pantalla al hacer clic
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Crear un nuevo sprite y configurarlo
                sf::Sprite newBlock = blockSprite;
                newBlock.setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                // Añadir el nuevo bloque y su velocidad inicial
                placedBlocks.push_back(newBlock);
                blockVelocities.push_back(sf::Vector2f(0.f, 0.f));
            }
        }

        // Cambiar la textura del bloque con la tecla 'Espacio'
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                currentTextureIndex++;
                if (currentTextureIndex >= blockTextures.size()) {
                    currentTextureIndex = 0;
                }
                blockSprite.setTexture(blockTextures[currentTextureIndex]);
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

        // Redimensionar sprites en tiempo real
        if (event.type == sf::Event::Resized || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)) {
            sf::FloatRect visibleArea(0, 0, static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
            window->setView(sf::View(visibleArea));

            scaleSpriteToWindow(backgroundSprite, backgroundTexture);

            float originalBlockWidth = blockTextures[0].getSize().x;
            float windowWidth = window->getSize().x;
            float scale = (windowWidth / 1990.0f) * 0.25f;
            blockSprite.setScale(scale, scale);

            for (auto& block : placedBlocks) {
                sf::Vector2f oldPos = block.getPosition();
                sf::Vector2f oldScale = block.getScale();

                float newPosX = oldPos.x * (scale / oldScale.x);
                float newPosY = oldPos.y * (scale / oldScale.y);

                block.setScale(scale, scale);
                block.setPosition(newPosX, newPosY);
            }
            std::cout << "Tamaño de la ventana: " << window->getSize().x << " x " << window->getSize().y << std::endl;
        }
    }
}


void Game::update(sf::Time deltaTime) {
    for (size_t i = 0; i < placedBlocks.size(); ++i) {
        // Aplica la gravedad a la velocidad (MRUV)
        blockVelocities[i].y += gravity * deltaTime.asSeconds();

        // Obtiene la posición actual y calcula la siguiente
        sf::Vector2f currentPos = placedBlocks[i].getPosition();
        sf::Vector2f nextPos = currentPos;
        nextPos.y += blockVelocities[i].y * deltaTime.asSeconds();

        // --- Detección de colisiones con los bordes de la pantalla ---
        // Se crea un área de colisión más pequeña para evitar el espacio
        sf::FloatRect blockBounds = placedBlocks[i].getGlobalBounds();

        // Ajusta la altura y el ancho del área de colisión
        blockBounds.height *= 0.85f;
        blockBounds.width *= 0.85f;

        if (nextPos.y + blockBounds.height >= window->getSize().y) {
            nextPos.y = window->getSize().y - blockBounds.height;
            blockVelocities[i].y = 0.f; // Detiene la caída
        }

        // --- Detección de colisiones entre bloques ---
        for (size_t j = 0; j < placedBlocks.size(); ++j) {
            if (i == j) continue;

            sf::FloatRect otherBlockBounds = placedBlocks[j].getGlobalBounds();

            // Ajusta la altura y el ancho del área de colisión del otro bloque
            otherBlockBounds.height *= 0.85f;
            otherBlockBounds.width *= 0.85f;

            sf::FloatRect nextBounds = blockBounds;
            nextBounds.top = nextPos.y;

            if (nextBounds.intersects(otherBlockBounds)) {
                // Si el bloque que cae está encima del otro
                if (blockVelocities[i].y > 0 && currentPos.y < otherBlockBounds.top) {
                    // Ajusta la posición del bloque para que se "asiente" perfectamente
                    nextPos.y = otherBlockBounds.top - blockBounds.height;
                    blockVelocities[i].y = 0.f;
                }
            }
        }

        // Finalmente, actualiza la posición del bloque a la posición calculada
        placedBlocks[i].setPosition(placedBlocks[i].getPosition().x, nextPos.y);
    }
}


void Game::render() {
    window->clear();
    window->draw(backgroundSprite);

    // Dibuja todos los bloques colocados
    for (const auto& block : placedBlocks) {
        window->draw(block);
    }

    window->draw(blockSprite);
    window->draw(text);
    window->display();
}

void Game::scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture) {
    float originalWidth = static_cast<float>(texture.getSize().x);
    float windowWidth = static_cast<float>(window->getSize().x);
    float scale = windowWidth / originalWidth;
    sprite.setScale(scale, scale);
}