#include "Game.h"
#include <iostream>

using namespace sf;

Game::Game() {
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

    // Cargar todas las texturas de bloques y almacenarlas en el vector
    // Asegúrate de tener estas imágenes en tu carpeta
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
    blockSprite.setScale(0.25f, 0.25f); // Escala inicial del bloque, a ajustar en tiempo real


    // Escalar el sprite del bloque al iniciar el programa
// (Esta es la versión del constructor, no la del evento Resized)
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
    while (window->isOpen()) {
        processEvents();
        render();
    }
}





// Procesa eventos de usuario
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
                // Añadir el nuevo bloque al vector de bloques colocados
                placedBlocks.push_back(newBlock);
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

            // --- NUEVO CÓDIGO: Alternar pantalla completa ---
            if (event.key.code == sf::Keyboard::P) {
                // Alternar el estado de pantalla completa
                if (is_fullscreen ) { 
                    // Cambiar a modo ventana
                    window->create(sf::VideoMode(1500, 852), "Mi Juego SFML con POO", sf::Style::Default);
                    is_fullscreen = false;
                }
                else {
                    // Cambiar a modo pantalla completa
                    window->create(sf::VideoMode::getDesktopMode(), "Mi Juego SFML con POO", sf::Style::Fullscreen);
                    is_fullscreen = true;
                }
                // Limitar los FPS y ajustar el escalado después de recrear la ventana
                window->setFramerateLimit(60);
                sf::FloatRect visibleArea(0, 0, static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
                window->setView(sf::View(visibleArea));

                scaleSpriteToWindow(backgroundSprite, backgroundTexture);

                // Recalcular la escala del bloque
                float originalBlockWidth = blockTextures[0].getSize().x;
                float windowWidth = window->getSize().x;
                float scale = (windowWidth / 1990.0f) * 0.25f;
                blockSprite.setScale(scale, scale);

                for (auto& block : placedBlocks) {
                    block.setScale(scale, scale);
                }

                std::cout << "Tamaño de la ventana: " << window->getSize().x << " x " << window->getSize().y << std::endl;
            }
            // ----------------------------------------------------
        }

        // Redimensionar sprites en tiempo real
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            window->setView(sf::View(visibleArea));

            scaleSpriteToWindow(backgroundSprite, backgroundTexture);

            float originalBlockWidth = blockTextures[0].getSize().x;
            float windowWidth = window->getSize().x;
            float scale = (windowWidth / 1990.0f) * 0.25f;
            blockSprite.setScale(scale, scale);

            for (auto& block : placedBlocks) {
                block.setScale(scale, scale);
            }
        }
    }
}


void Game::render() {
    window->clear();
    window->draw(backgroundSprite);

    // Dibuja todos los bloques colocados
    for (const auto& block : placedBlocks) {
        window->draw(block);
    }

    window->draw(blockSprite); // Dibuja el bloque que sigue al cursor
    window->draw(text);
    window->display();
}

// Nueva función reutilizable para escalar sprites
void Game::scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture) {
    float originalWidth = static_cast<float>(texture.getSize().x);
    float windowWidth = static_cast<float>(window->getSize().x);
    float scale = windowWidth / originalWidth;
    sprite.setScale(scale, scale);
}