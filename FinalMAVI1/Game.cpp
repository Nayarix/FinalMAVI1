#include "Game.h"
#include <iostream>

using namespace sf;

// Constructor: Inicializa la ventana y los objetos del juego
Game::Game() {
    //  Crear la ventana de SFML
    window = new RenderWindow(VideoMode(1500, 750), "Mi Juego SFML con POO");
    window->setFramerateLimit(60); // Limita FPS para control
    
    

    //  Cargar la imagen en la textura miembro de la clase
    if (!backgroundTexture.loadFromFile("BloquesMAVI1/fondoPrueba2.jpg")) {
        std::cerr << "Error al cargar el fondo" << std::endl;
        // Dependiendo de tu lógica, podrías cerrar la ventana o cargar un fondo de fallback
    }

    // Asignar la textura al sprite miembro de la clase
    backgroundSprite.setTexture(backgroundTexture);  

	// Establecer el tamaño del sprite al tamaño de la ventana
    float originalWidth = backgroundTexture.getSize().x;
    float originalHeight = backgroundTexture.getSize().y;

    // Obtener las dimensiones de la ventana
    float windowWidth = window->getSize().x;
    float windowHeight = window->getSize().y;

    // Calcular la escala para que la imagen se ajuste al ancho de la ventana
    float scale = windowWidth / originalWidth;

    // Aplicar la escala al sprite
    backgroundSprite.setScale(scale, scale);

	 // Oculta el cursor del sistema
     
    window->setMouseCursorVisible(false);

    // Carga la imagen y la asigna al sprite del cursor
    
    mat_cursor.loadFromFile("BloquesMAVI1/Escudo.png");
    cursor.setTexture(mat_cursor);
    cursor.setPosition(0, 0);
    cursor.setScale(0.5, 0.5);


    // Cargar fuente para texto
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString("Bienvenido a SFML!");
    text.setPosition(10.f, 10.f);
}

// Destructor: Libera la memoria asignada dinámicamente
Game::~Game() {
    delete window;
    window = nullptr;
}

// Bucle principal del juego
void Game::run() {
    while (window->isOpen()) {
        sf::Time deltaTime = clock.restart();
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
        if (event.type == sf::Event::MouseMoved) {
            // Actualizamos la posición del sprite con la información del evento
            cursor.setPosition(event.mouseMove.x, event.mouseMove.y);
        }

        // --- Nuevo código para redimensionar el fondo en tiempo real ---
        if (event.type == sf::Event::Resized) {
            // Recalcula y aplica la escala del fondo
            float originalWidth = backgroundTexture.getSize().x;
            float windowWidth = window->getSize().x;
            float scale = windowWidth / originalWidth;
            backgroundSprite.setScale(scale, scale);

            // Opcional: ajustar la vista para mantener la proporción de la ventana
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
        }
        // -----------------------------------------------------------------
    }
}

// Dibuja en pantalla
void Game::render() {
    window->clear(); // Limpia la pantalla
    window->draw(backgroundSprite);
    window->draw(text);
    window->draw(cursor);
    window->display();
}