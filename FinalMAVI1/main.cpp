#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string> 


//Enumero una lista de los difrentes estados en los que se encuentra el juego
enum GameState {
    MENU,
    PLAYING,
    TUTORIAL,
    GAME_OVER 
};



//Funcion auxiliar para crear botones, se usa para crear cada boton

//Paso en la funcion valores por referencia como su texto y su rectangulo delcarandos afuera de la funcion. Junto con las demas variabalesles necesarias para crear el boton
void createButton(const std::string& textStr, float yPos, sf::Text& text, sf::RectangleShape& rect, const sf::Font& font, sf::RenderWindow* window, bool isContinuing) {
    //Explicar logica de manejo de textos
    text.setFont(font);
    text.setCharacterSize(40);
    text.setString(textStr);
    //Un interruptor para saber si el botón debe tener un color especial(dorado) o normal(blanco).
    text.setFillColor(isContinuing ? sf::Color(255, 200, 0) : sf::Color::White);

    //Obtiene el rectángulo invisible que rodea al texto antes de aplicarle transformaciones. Nos dice cuánto mide de ancho y alto la palabra exacta
    sf::FloatRect textBounds = text.getLocalBounds();
    //Obtiene el ancho actual de la ventana a través del puntero window. Lo necesitamos para calcular el centro de la pantalla.
    float windowWidth = (float)window->getSize().x;
    //Aquí estamos moviendo ese punto de anclaje al centro exacto del texto.
    //"Calculo el centro geométrico del texto y muevo su Origen (Pivot Point) a esa posición. Esto es crucial para que, al posicionarlo en el centro de la pantalla, el texto quede perfectamente alineado y no desplazado hacia la derecha."
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    //Coloca el objeto en la coordenada X (mitad de la ventana) y Y (yPos recibida por parámetro). Como ya ajustamos el Origen al centro del texto, el texto queda centrado.
    text.setPosition(windowWidth / 2.0f, yPos);
    //Define el tamaño fijo de la caja negra detrás del texto
    rect.setSize(sf::Vector2f(300.f, 60.f));
    //Pinta el rectángulo de negro
    rect.setFillColor(sf::Color(0, 0, 0, 180));
	//Ajusta el punto de origen del rectángulo al centro (150, 30) para que quede centrado detrás del texto
    rect.setOrigin(150.f, 30.f);
    //Mueve el rectángulo a la misma posición que el texto. Como ambos tienen su Origen en el centro, quedan perfectamente superpuestos y centrados en la pantalla.
    rect.setPosition(windowWidth / 2.0f, yPos);
}


//Manejador Principal de eventos
int main() {

    //Instancio la clase Game. Esto invoca su constructor, cargando todos los recursos necesarios en memoria e inicializando la ventana.
    Game game;

    //Inicializo la Máquina de Estados Finitos en MENU, lo que asegura que el bucle principal comience renderizando la interfaz de usuario en lugar de la lógica del juego
    //Crea la variable que controlará qué pantalla ve el usuario
    GameState currentState = MENU;
    //Obtengo un puntero a la ventana creada dentro de la clase Game. Esto me permite consultar sus eventos y estado desde el main sin romper el encapsulamiento, ya que no accedo a la variable directa, sino a través de un getter
    sf::RenderWindow* window = game.getWindow();
    //Declaro una variable de respaldo para almacenar el estado previo antes de entrar al tutorial, permitiendo una navegación fluida al regresar
    GameState stateBeforeTutorial = MENU;
	//Herramienta para el scroll en el estado de tutorial, declara una variable float en 0 para determinar la posicion en Y del texto en el tutorial
    float tutorialScrollY = 0.f;
    //Activo la visibilidad del Mouse
    window->setMouseCursorVisible(true);

	//Recupero las reglas de juego formateadas desde la clase Game. Esto mantiene separado el contenido (lógica interna) de la presentación (interfaz en main)
    std::vector<std::string> tutorialRules = game.getRulesForDisplay();
	//Cargo la fuente arial.ttf 
    sf::Font font;
    //Cargo la tipografía necesaria para la interfaz. Incluyo una validación de error
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
        return -1;
    }

	//Declaro los objetos gráficos de la interfaz (Textos y Formas). Inicialmente están vacíos y serán configurados dinámicamente en el bucle de renderizado
    sf::Text playText, newGameText, exitText;
    sf::RectangleShape playRect, newGameRect, exitRect;
    sf::Text gameOverText, finalScoreText, menuButtonText;
    sf::RectangleShape menuButtonRect;

	//Instancio un reloj de alta precisión (sf::Clock). Este objeto será el responsable de medir el tiempo transcurrido entre cada iteración del bucle para garantizar un movimiento fluido e independiente de la velocidad del procesador
    sf::Clock frameClock;


	//Bucle principal del juego
	//Mientras la ventana esta abierta... Todo dento de este bucle se repite constantemente
    while (window->isOpen()) {
		// Obtengo el tiempo transcurrido desde el ultimo frame, gracias a la instancia previamente creada del reloj
        sf::Time deltaTime = frameClock.restart();
		// Creo un evento de SFML para manejar los eventos del juego, como entradas del usuario y cambios en la ventana
        sf::Event event;

		//Bucle para manejar los eventos de la ventana 
        while (window->pollEvent(event)) {
          
            //Cierre de la ventana
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::Resized) {
                // 1. Definimos un rectángulo que coincida EXACTAMENTE con el nuevo tamaño de la ventana
                // (0, 0) es la esquina superior izquierda.
                // event.size.width/height son las dimensiones nuevas (ej: 1920x1080).
                sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);

                // 2. Le decimos a la ventana: "Ajusta tu cámara (View) a este nuevo rectángulo".
                window->setView(sf::View(visibleArea));
            }

			//Manejo de eventos segun el estado actual del juego. Eventos modo Buffer

			//Si el estado actual es PLAYING...
            if (currentState == PLAYING) {
				//Si se presiona la tecla Escape se vuelve al menu principal
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentState = MENU;
                    window->setMouseCursorVisible(true);
                }
                else {
					//Si no, proceso los eventos del juego normalmente
                    game.processEvents(event);
                }
            }
			//Si el estado actual es TUTORIAL...
            if (currentState == TUTORIAL) {
				//Manejo del scroll con la rueda del mouse
				if (event.type == sf::Event::MouseWheelScrolled) {// Porque es diferente la declaraciond este evento 
					//Modifico la posicion del scroll segun la direccion de la rueda del mouse 
                    tutorialScrollY += event.mouseWheelScroll.delta * 30.0f;
                }
				//Con Escape vuelvo al estado anterior al tutorial
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentState = stateBeforeTutorial;

                }
            }

			//Manejo de clicks del mouse
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				//Obtengo la posicion del mouse en coordenadas de la ventana 
                sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*window);

				//si el estado actual es MENU...
                if (currentState == MENU) {
					//Manejo de los clicks en los botones del menu principal

					//Boton del juego
                    if (playRect.getGlobalBounds().contains(mousePos)) {
						//Si el juego ya habia comenzado, continuo la partida
                        if (!game.isGameStarted()) {
                            game.resetGame();
                        }
                        //Nuevo estado
                        currentState = PLAYING;
                       
                    }
					//Boton de nueva partida
                    else if (newGameRect.getGlobalBounds().contains(mousePos)) {
                        game.resetGame();
                        //Nuevo estado
                        currentState = PLAYING;
                        
                    }
					//Boton de salir
                    else if (exitRect.getGlobalBounds().contains(mousePos)) {
						//Cierra la ventana
                        window->close();
                    }
                }
				//Si el estado actual es GAME OVER...
                else if (currentState == GAME_OVER) {
					//Manejo del boton de volver al menu principal
                    if (menuButtonRect.getGlobalBounds().contains(mousePos)) {
                        currentState = MENU; 
                    }
                }

				//Manejo de los botones de tutorial y musica en todos los estados
				
                //Boton de tutorial
                if (game.getTutorialButtonBounds().contains(mousePos) && currentState != TUTORIAL) {
					
                    stateBeforeTutorial = currentState;
                    currentState = TUTORIAL;
                    window->setMouseCursorVisible(true);
                }
				//Boton de musica
                if (game.getMusicButtonBounds().contains(mousePos)) {
					//Alterno la musica de fondo
                    //Pauso la Musica
                    if (game.isMusicPlaying) {
                        game.backgroundMusic.pause();
                        game.isMusicPlaying = false;
                    }
					//Reanudo la Musica
                    else {
                        game.backgroundMusic.play();
                        game.isMusicPlaying = true;
                    }
                }
            }
        } 
		///// LÓGICA DE RENDERIZADO SEGÚN ESTADO ACTUAL////

		//Si el estado el PLAYING... 
        if (currentState == PLAYING) {
			//Actualizo las fisicas del juego 
            game.update(deltaTime);
			//Dibujo todo lo necesario en la ventana 
            game.render();


			//Verifico si la grilla esta llena para cambiar al estado de GAME OVER
            if (game.isGridFull()) {
                currentState = GAME_OVER;
                window->setMouseCursorVisible(true); 
            }
        }

		//Si el estado actual es GAME OVER...
        else if (currentState == GAME_OVER) {
			//Limpio la ventna y Dibujo el fondo del juego 
            game.renderBackground();

			//calculo el punto exacto (X, Y) del centro de la ventana en este preciso momento
            float windowHeight = (float)window->getSize().y;
            float center_x = (float)window->getSize().x / 2.f;
            float center_y = windowHeight / 2.f;

			//Texto de Juego Terminado, Explicar mas a detalle 
            gameOverText.setFont(font);
            gameOverText.setString("Juego Terminado");
            gameOverText.setCharacterSize(80);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2.f, gameOverText.getLocalBounds().height / 2.f);
            gameOverText.setPosition(center_x, center_y - 100.f);
            window->draw(gameOverText);

			//Texto de Puntaje Final
            finalScoreText.setFont(font);
            finalScoreText.setString("Puntaje Final: " + std::to_string(game.getScore()));
            finalScoreText.setCharacterSize(50);
            finalScoreText.setFillColor(sf::Color::Yellow);
            finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2.f, finalScoreText.getLocalBounds().height / 2.f);
            finalScoreText.setPosition(center_x, center_y);
            window->draw(finalScoreText);

			//Boton de Volver al Menu, lo creo asignandole valores a la funcion createButton
            createButton("Menu", center_y + 100.f, menuButtonText, menuButtonRect, font, window, false);
            window->draw(menuButtonRect);
            window->draw(menuButtonText);

			//Dibujo los botones de tutorial y musica 
            game.renderTutorialButton();
            game.renderMusicButton();
            window->display(); 
        }


		//Si el estado actual es MENU...
        else if (currentState == MENU) {
			//Dibujo el fondo del juego
            game.renderBackground();
			//Determino si el juego ya habia comenzado para cambiar el texto del boton de jugar/continuar 
            bool isContinuing = game.isGameStarted();
			//Centro los botones en la ventana 
            float windowHeight = (float)window->getSize().y;
            float center_y = windowHeight / 2.0f;

			//Creo los botones del menu principal
            createButton(isContinuing ? "Continuar" : "Jugar", center_y - 100.f, playText, playRect, font, window, isContinuing);
            createButton("Nueva Partida", center_y, newGameText, newGameRect, font, window, false);
            createButton("Salir", center_y + 100.f, exitText, exitRect, font, window, false);

			//Dibujo los botones y textos en la ventana 
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

		//Si el estado actual es TUTORIAL...
        else if (currentState == TUTORIAL) {
			//Dibujo el fondo del juego
            game.renderBackground();
            
			// Dibujo el recuadro de fondo del tutorial 
            sf::RectangleShape backgroundRect;
            float padding = 30.f;
            float rectWidth = (float)window->getSize().x - 2 * padding;
            float rectHeight = (float)window->getSize().y - 150.f;

            backgroundRect.setSize(sf::Vector2f(rectWidth, rectHeight));
            backgroundRect.setFillColor(sf::Color(0, 0, 0, 180));
            backgroundRect.setPosition(padding, 120.f);
            window->draw(backgroundRect);

			//Dibujo el titulo del tutorial 
            sf::Text titleText;
            titleText.setFont(font);
            titleText.setString("Guia de Combinaciones");
            titleText.setCharacterSize(60);
            titleText.setFillColor(sf::Color(0, 150, 0));
			//Establezco el origen y la posicion del texto del titulo 
            titleText.setOrigin(titleText.getLocalBounds().width / 2.0f, titleText.getLocalBounds().height / 2.0f);
            titleText.setPosition((float)window->getSize().x / 2.0f, 50.f);
            window->draw(titleText);

			//Control de scroll
            //Calcula cuanto texto cabe en la pantalla y ponerle un "freno" al usuario para que no pueda scrollear hacia el vacío infinito
            
            //Establece las coordenadas donde empezará a dibujarse la primera línea de texto
            float contentStartX = padding + 20.f;
            float contentStartY = 140.f;
            //Calcula la altura total que ocuparía el tutorial si lo imprimiéramos todo en una hoja gigante
            float totalContentHeight = (float)tutorialRules.size() * 30.f;
            //Calcula cuántos píxeles hay disponibles para mostrar texto dentro del recuadro del tutorial
            float visibleAreaHeight = rectHeight - (contentStartY - backgroundRect.getPosition().y) - 30.f;
            //Determina cuánto "sobra" de texto. 
            float maxScroll = totalContentHeight - visibleAreaHeight;
            //Si el texto es tan corto que cabe entero, el maxScroll se clava en 0 para que no se mueva
            if (maxScroll < 0) maxScroll = 0.f;
            //Tope Superior: Impide que scrollees hacia abajo cuando ya estás en la primera línea
            if (tutorialScrollY > 0.f) tutorialScrollY = 0.f;
			//Tope Inferior: Impide que scrollees hacia arriba cuando ya estás en la última línea
            if (tutorialScrollY < -maxScroll) tutorialScrollY = -maxScroll;
            //Calcula la coordenada Y real donde se dibujará el primer renglón en este frame
            float currentY = contentStartY + tutorialScrollY;

			//Dibujo las reglas del tutorial con el formato adecuado 
            for (const std::string& rule : tutorialRules) {
                sf::Text ruleText;
                ruleText.setFont(font);
                ruleText.setString(rule);
                ruleText.setCharacterSize(24);
                sf::Color textColor = sf::Color::White;

				//Asignacion de colores segun el tipo de regla 

				//Si el Texto dice TUTORIAL
                if (rule.find("TUTORIAL") != std::string::npos) {
                    textColor = sf::Color(0, 255, 255);
                }
                //Si el Texto dice COMBINACIONES NIVEL 1 (100 PUNTOS) 
                else if (rule.find("COMBINACIONES NIVEL 1 (100 PUNTOS)") != std::string::npos) {
                    textColor = sf::Color(255, 165, 0);
                }
                //Si el Texto dice COMBINACIONES NIVEL 2 (500 PUNTOS) 
                else if (rule.find("COMBINACIONES NIVEL 2 (500 PUNTOS)") != std::string::npos) {
                    textColor = sf::Color(255, 0, 255);
                }
                //Si el Texto dice COMBINACIONES NIVEL 3 (2500 PUNTOS) 
                else if (rule.find("COMBINACIONES NIVEL 3 (2500 PUNTOS)") != std::string::npos) {
                    textColor = sf::Color::Red;
                }

				//Establezco el color y la posicion de el texto de reglas 
                ruleText.setFillColor(textColor);
                ruleText.setPosition(contentStartX, currentY);

				//Dibujo el texto solo si esta dentro del area visible del recuadro 
				//Si la posicion Y actual es mayor a la posicion Y del recuadro + un margen de 10 pixeles y 
                //menor a la posicion Y del recuadro + la altura del recuadro - un margen de 30 pixeles
                if (currentY > backgroundRect.getPosition().y + 10.f && currentY < backgroundRect.getPosition().y + rectHeight - 30.f) {
                    window->draw(ruleText);
                }
				// Incremento la posicion Y para la siguiente regla, siguiente renglon
                currentY += 30.f;
            }
			//Dibujo los botones de tutorial y musica
            game.renderTutorialButton();
            game.renderMusicButton();
            window->display();
        }
    } 
	//Final del programa
    return 0;
}