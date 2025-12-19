#include "Game.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace sf;

//Asigno un valor a las ID de cada bloque
const int ID_ESPADA = 1;
const int ID_ESCUDO = 2;
const int ID_CORONA = 3;
const int ID_CETRO = 4;
const int ID_DRAGON = 5;
const int ID_EMBLEMA = 6;
const int ID_REYGUERRERO = 7;
const int ID_ESPADAENCANTADA = 8;
const int ID_CAZADORDEDRAGONES = 9;
const int ID_GUARDIANREAL = 10;
const int ID_BOLADECRISTAL = 11;
const int ID_ESCAMADEDRAGON = 12;
const int ID_HECHICEROREAL = 13;
const int ID_REYDRAGON = 14;
const int ID_DRAGONMAGICO = 15;
const int ID_PALADIN = 16;
const int ID_HEROELEGENDARIO = 17;
const int ID_DEFENSORDELREINO = 18;
const int ID_DRAGONDELACORONA = 19;
const int ID_SEÑORDELAGUERRA = 20;
const int ID_AVATARDELREINO = 21;
const int ID_DRAGONANCESTRAL = 22;
const int ID_TITANDEBATALLA = 23;
const int ID_CABALLERODRAGON = 24;
const int ID_ESPADACREPUSCULO = 25;


//Funcion para cargar al vector de reglas todas las posibles combinaciones
void Game::initializeRules() {
	combinationRules.clear();
	combinationRules.push_back({ ID_ESCUDO, ID_ESPADA, ID_EMBLEMA });
	combinationRules.push_back({ ID_ESPADA, ID_ESCUDO, ID_EMBLEMA });
	combinationRules.push_back({ ID_CORONA, ID_ESPADA, ID_REYGUERRERO });
	combinationRules.push_back({ ID_ESPADA, ID_CORONA, ID_REYGUERRERO });
	combinationRules.push_back({ ID_CETRO, ID_ESPADA, ID_ESPADAENCANTADA });
	combinationRules.push_back({ ID_ESPADA, ID_CETRO, ID_ESPADAENCANTADA });
	combinationRules.push_back({ ID_DRAGON, ID_ESPADA, ID_CAZADORDEDRAGONES });
	combinationRules.push_back({ ID_ESPADA, ID_DRAGON, ID_CAZADORDEDRAGONES });
	combinationRules.push_back({ ID_CORONA, ID_ESCUDO, ID_GUARDIANREAL });
	combinationRules.push_back({ ID_ESCUDO, ID_CORONA, ID_GUARDIANREAL });
	combinationRules.push_back({ ID_CETRO, ID_ESCUDO, ID_BOLADECRISTAL });
	combinationRules.push_back({ ID_ESCUDO, ID_CETRO, ID_BOLADECRISTAL });
	combinationRules.push_back({ ID_DRAGON, ID_ESCUDO, ID_ESCAMADEDRAGON });
	combinationRules.push_back({ ID_ESCUDO, ID_DRAGON, ID_ESCAMADEDRAGON });
	combinationRules.push_back({ ID_CETRO, ID_CORONA, ID_HECHICEROREAL });
	combinationRules.push_back({ ID_CORONA, ID_CETRO, ID_HECHICEROREAL });
	combinationRules.push_back({ ID_DRAGON, ID_CORONA, ID_REYDRAGON });
	combinationRules.push_back({ ID_CORONA, ID_DRAGON, ID_REYDRAGON });
	combinationRules.push_back({ ID_DRAGON, ID_CETRO, ID_DRAGONMAGICO });
	combinationRules.push_back({ ID_CETRO, ID_DRAGON, ID_DRAGONMAGICO });
	combinationRules.push_back({ ID_EMBLEMA, ID_HECHICEROREAL, ID_PALADIN });
	combinationRules.push_back({ ID_HECHICEROREAL, ID_EMBLEMA, ID_PALADIN });
	combinationRules.push_back({ ID_ESPADAENCANTADA, ID_REYDRAGON, ID_HEROELEGENDARIO });
	combinationRules.push_back({ ID_REYDRAGON, ID_ESPADAENCANTADA, ID_HEROELEGENDARIO });
	combinationRules.push_back({ ID_CAZADORDEDRAGONES, ID_BOLADECRISTAL, ID_DEFENSORDELREINO });
	combinationRules.push_back({ ID_BOLADECRISTAL, ID_CAZADORDEDRAGONES, ID_DEFENSORDELREINO });
	combinationRules.push_back({ ID_GUARDIANREAL, ID_DRAGONMAGICO, ID_DRAGONDELACORONA });
	combinationRules.push_back({ ID_DRAGONMAGICO, ID_GUARDIANREAL, ID_DRAGONDELACORONA });
	combinationRules.push_back({ ID_REYGUERRERO, ID_ESCAMADEDRAGON, ID_SEÑORDELAGUERRA });
	combinationRules.push_back({ ID_ESCAMADEDRAGON, ID_REYGUERRERO, ID_SEÑORDELAGUERRA });
	tripleCombinationRules.push_back({ ID_PALADIN, ID_HEROELEGENDARIO, ID_DEFENSORDELREINO, ID_AVATARDELREINO });
	tripleCombinationRules.push_back({ ID_DEFENSORDELREINO, ID_HEROELEGENDARIO, ID_PALADIN, ID_AVATARDELREINO });
	tripleCombinationRules.push_back({ ID_HEROELEGENDARIO, ID_PALADIN, ID_DEFENSORDELREINO, ID_AVATARDELREINO });
	tripleCombinationRules.push_back({ ID_PALADIN, ID_DEFENSORDELREINO, ID_HEROELEGENDARIO, ID_AVATARDELREINO });
	tripleCombinationRules.push_back({ ID_HEROELEGENDARIO, ID_DEFENSORDELREINO, ID_PALADIN, ID_AVATARDELREINO });
	tripleCombinationRules.push_back({ ID_DEFENSORDELREINO, ID_PALADIN, ID_HEROELEGENDARIO, ID_AVATARDELREINO });
	tripleCombinationRules.push_back({ ID_DRAGONDELACORONA, ID_SEÑORDELAGUERRA, ID_DRAGONMAGICO, ID_DRAGONANCESTRAL });
	tripleCombinationRules.push_back({ ID_DRAGONMAGICO, ID_SEÑORDELAGUERRA, ID_DRAGONDELACORONA, ID_DRAGONANCESTRAL });
	tripleCombinationRules.push_back({ ID_SEÑORDELAGUERRA, ID_DRAGONDELACORONA, ID_DRAGONMAGICO, ID_DRAGONANCESTRAL });
	tripleCombinationRules.push_back({ ID_DRAGONDELACORONA, ID_DRAGONMAGICO, ID_SEÑORDELAGUERRA, ID_DRAGONANCESTRAL });
	tripleCombinationRules.push_back({ ID_SEÑORDELAGUERRA, ID_DRAGONMAGICO, ID_DRAGONDELACORONA, ID_DRAGONANCESTRAL });
	tripleCombinationRules.push_back({ ID_DRAGONMAGICO, ID_DRAGONDELACORONA, ID_SEÑORDELAGUERRA, ID_DRAGONANCESTRAL });
	tripleCombinationRules.push_back({ ID_DEFENSORDELREINO, ID_SEÑORDELAGUERRA, ID_HEROELEGENDARIO, ID_TITANDEBATALLA });
	tripleCombinationRules.push_back({ ID_HEROELEGENDARIO, ID_SEÑORDELAGUERRA, ID_DEFENSORDELREINO, ID_TITANDEBATALLA });
	tripleCombinationRules.push_back({ ID_SEÑORDELAGUERRA, ID_DEFENSORDELREINO, ID_HEROELEGENDARIO, ID_TITANDEBATALLA });
	tripleCombinationRules.push_back({ ID_DEFENSORDELREINO, ID_HEROELEGENDARIO, ID_SEÑORDELAGUERRA, ID_TITANDEBATALLA });
	tripleCombinationRules.push_back({ ID_SEÑORDELAGUERRA, ID_HEROELEGENDARIO, ID_DEFENSORDELREINO, ID_TITANDEBATALLA });
	tripleCombinationRules.push_back({ ID_HEROELEGENDARIO, ID_DEFENSORDELREINO, ID_SEÑORDELAGUERRA, ID_TITANDEBATALLA });
	tripleCombinationRules.push_back({ ID_PALADIN, ID_DRAGONDELACORONA, ID_DRAGONMAGICO, ID_CABALLERODRAGON });
	tripleCombinationRules.push_back({ ID_DRAGONMAGICO, ID_DRAGONDELACORONA, ID_PALADIN, ID_CABALLERODRAGON });
	tripleCombinationRules.push_back({ ID_DRAGONDELACORONA, ID_PALADIN, ID_DRAGONMAGICO, ID_CABALLERODRAGON });
	tripleCombinationRules.push_back({ ID_PALADIN, ID_DRAGONMAGICO, ID_DRAGONDELACORONA, ID_CABALLERODRAGON });
	tripleCombinationRules.push_back({ ID_DRAGONMAGICO, ID_PALADIN, ID_DRAGONDELACORONA, ID_CABALLERODRAGON });
	tripleCombinationRules.push_back({ ID_DRAGONDELACORONA, ID_DRAGONMAGICO, ID_PALADIN, ID_CABALLERODRAGON });
	tripleCombinationRules.push_back({ ID_HEROELEGENDARIO, ID_DRAGONMAGICO, ID_PALADIN, ID_ESPADACREPUSCULO });
	tripleCombinationRules.push_back({ ID_PALADIN, ID_DRAGONMAGICO, ID_HEROELEGENDARIO, ID_ESPADACREPUSCULO });
	tripleCombinationRules.push_back({ ID_HEROELEGENDARIO, ID_PALADIN, ID_DRAGONMAGICO, ID_ESPADACREPUSCULO });
	tripleCombinationRules.push_back({ ID_DRAGONMAGICO, ID_HEROELEGENDARIO, ID_PALADIN, ID_ESPADACREPUSCULO });
	tripleCombinationRules.push_back({ ID_PALADIN, ID_HEROELEGENDARIO, ID_DRAGONMAGICO, ID_ESPADACREPUSCULO });
	tripleCombinationRules.push_back({ ID_DRAGONMAGICO, ID_PALADIN, ID_HEROELEGENDARIO, ID_ESPADACREPUSCULO });
}

//Funcion Principal
//Declaro gravedad del juego
Game::Game() : gravity(500.f) {
	//Creo la ventana
	window = new RenderWindow(VideoMode::getDesktopMode(), "Mi Juego SFML con POO", Style::Fullscreen);
	window->setFramerateLimit(60);
	window->setMouseCursorVisible(true);
	is_fullscreen = true;

	//Cargo textura del fondo
	if (!backgroundTexture.loadFromFile("BloquesMAVI1/fondoPrueba2.jpg")) {
		std::cerr << "Error al cargar el fondo" << std::endl;
	}

	//Establezco la textura del fondo y sus atributos
	backgroundSprite.setTexture(backgroundTexture);
	float originalWidth = backgroundTexture.getSize().x;
	float windowWidth = (float)window->getSize().x;
	float scale = windowWidth / originalWidth;
	backgroundSprite.setScale(scale, scale);

	//Cargo textura del boton de tutorial
	if (!tutorialButtonTexture.loadFromFile("BloquesMAVI1/GuiaCombinaciones.png")) {
		std::cerr << "Error al cargar la textura del botón de tutorial" << std::endl;
	}

	//Establezco la textura del boton del tutorial y sus atributos
	tutorialButtonSprite.setTexture(tutorialButtonTexture);
	tutorialButtonSprite.setScale(0.1f, 0.1f);
	float margin = 20.f;
	float buttonWidth = tutorialButtonSprite.getGlobalBounds().width;

	//Cargo la musica de fondo
	if (!backgroundMusic.openFromFile("Musica/MedievalMusicwav.wav")) {
		std::cerr << "Error al cargar la musica" << std::endl;
	}
	//Establezco la musica de fondo
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	isMusicPlaying = true;


	//Cargo el sonido de caida de los bloques
	if (!placeSoundBuffer.loadFromFile("Musica/SonidoColocarBloque.wav")) {
		std::cerr << "Error al cargar el efecto de sonido SonidoColocarBloque.wav" << std::endl;
	}
	//Establezco el sonido de caida de los bloques
	placeSound.setBuffer(placeSoundBuffer);


	//Cargo textura del boton de musica
	if (!musicButtonTexture.loadFromFile("BloquesMAVI1/SimboloMusica.png")) {
		std::cerr << "Error al cargar la textura del boton de musica" << std::endl;
	}
	//Establezco la textura del boton del misica y sus atributos
	musicButtonSprite.setTexture(musicButtonTexture);
	musicButtonSprite.setScale(0.1f, 0.1f);
	tutorialButtonSprite.setPosition(windowWidth - buttonWidth - margin, margin);
	float tutorialButtonHeight = tutorialButtonSprite.getGlobalBounds().height;
	musicButtonSprite.setPosition(windowWidth - buttonWidth - margin, margin + tutorialButtonHeight + margin);
	
	
	//Cargo la fuente para los textos 
	if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
	}
	//Establezco los atributos del texto de puntuacion
	score = 0;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setPosition(20.f, 60.f);


	//Cargo las texturas de los bloques y sus nombres, a travez de un vector de strings
	std::vector<std::string> texturePaths = {
	"BloquesMAVI1/Espada.png",
	"BloquesMAVI1/Escudo.png",
	"BloquesMAVI1/Corona.png",
	"BloquesMAVI1/cetroMagico.png",
	"BloquesMAVI1/Dragon.png",
	"BloquesMAVI1/Emblema.png",
	"BloquesMAVI1/ReyGuerrero.png",
	"BloquesMAVI1/EspadaEncantada.png",
	"BloquesMAVI1/CazadorDeDragones.png",
	"BloquesMAVI1/GuardianReal.png",
	"BloquesMAVI1/BolaDeCristal.png",
	"BloquesMAVI1/EscamaDeDragon.png",
	"BloquesMAVI1/HechiceroReal.png",
	"BloquesMAVI1/ReyDragon.png",
	"BloquesMAVI1/DragonMagico.png",
	"BloquesMAVI1/Paladin.png",
	"BloquesMAVI1/HeroeLegendario.png",
	"BloquesMAVI1/DefensorDelReino.png",
	"BloquesMAVI1/DragonDeLaCorona.png",
	"BloquesMAVI1/SeñorDeLaGuerra.png",
	"BloquesMAVI1/AvatarDelReino.png",
	"BloquesMAVI1/DragonAncestral.png",
	"BloquesMAVI1/TitanDeBatalla.png",
	"BloquesMAVI1/CaballeroDragon.png",
	"BloquesMAVI1/EspadaDelCrepusculo.png",
	};

	//Cargo las texturas de los bloques en el vector blockTextures (Explicar como funcionana los vectores)
	//Bucle "Range-based for" (For de Rango)
	for (const auto& path : texturePaths) {
		sf::Texture tempTexture;
		if (tempTexture.loadFromFile(path)) {
			blockTextures.push_back(std::move(tempTexture));
		}
		else {
			std::cerr << "Error al cargar la textura: " << path << std::endl;
		}
	}
	//Asigno los nombres a cada bloque en el mapa blockNames, a travez de sus ID. (Explicar como funcionana los mapas)
	blockNames[ID_ESPADA] = "Espada";
	blockNames[ID_ESCUDO] = "Escudo";
	blockNames[ID_CORONA] = "Corona";
	blockNames[ID_CETRO] = "Cetro";
	blockNames[ID_DRAGON] = "Dragón";
	blockNames[ID_EMBLEMA] = "Emblema";
	blockNames[ID_REYGUERRERO] = "Rey Guerrero";
	blockNames[ID_ESPADAENCANTADA] = "Espada Encantada";
	blockNames[ID_CAZADORDEDRAGONES] = "Cazador de Dragones";
	blockNames[ID_GUARDIANREAL] = "Guardián Real";
	blockNames[ID_BOLADECRISTAL] = "Bola de Cristal";
	blockNames[ID_ESCAMADEDRAGON] = "Escama de Dragón";
	blockNames[ID_HECHICEROREAL] = "Hechicero Real";
	blockNames[ID_REYDRAGON] = "Rey Dragón";
	blockNames[ID_DRAGONMAGICO] = "Dragón Mágico";
	blockNames[ID_PALADIN] = "Paladín";
	blockNames[ID_HEROELEGENDARIO] = "Héroe Legendario";
	blockNames[ID_DEFENSORDELREINO] = "Defensor del Reino";
	blockNames[ID_DRAGONDELACORONA] = "Dragón de la Corona";
	blockNames[ID_SEÑORDELAGUERRA] = "Señor de la Guerra";
	blockNames[ID_AVATARDELREINO] = "Avatar del Reino";
	blockNames[ID_DRAGONANCESTRAL] = "Dragón Ancestral";
	blockNames[ID_TITANDEBATALLA] = "Titán de Batalla";
	blockNames[ID_CABALLERODRAGON] = "Caballero Dragón";
	blockNames[ID_ESPADACREPUSCULO] = "Espada Crepúsculo";

	//Inicializo las reglas de combinacion
	initializeRules();

	//Inicializo la variable currentTextureIndex para seleccionar la textura del bloque actual 
	currentTextureIndex = 0;

	//Establezco la textura del bloque actual y sus atributos
	blockSprite.setTexture(blockTextures[currentTextureIndex]);
	float originalBlockWidth = blockTextures[0].getSize().x;
	float windowWidth_initial = window->getSize().x;
	float scale_initial = (windowWidth_initial / 1990.0f) * 0.25f;
	blockSprite.setScale(scale_initial, scale_initial);
	currentColumnIndex = 3;
	isBlockLaunched = false;
	is_game_started = false;

	//Guardo el tamaño inicial de la ventana
	oldWindowSize = static_cast<sf::Vector2f>(window->getSize());
	
	//Inicializo la grilla del juego
	grid.resize(GRID_ROWS, std::vector<int>(GRID_COLS, 0));

	//Calculo las posiciones de las columnas
	recalculatePositions();
	//Lanzo el nuevo bloque
	spawnNewBlock();
}

//Destructor 
Game::~Game() {
	delete window;
	window = nullptr;
}

//Funcion para procesar los eventos del juego 
void Game::processEvents(sf::Event& event) {	

	//Cierro la ventana si se recibe el evento de cierre
	if (event.type == sf::Event::Closed) {
		window->close();
	}

	//Ajusto la vista si se redimensiona la ventana 
	if (event.type == sf::Event::Resized) {
		sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
		window->setView(sf::View(visibleArea));
		recalculatePositions();
	}

	//Controlo el movimiento del bloque actual y el lanzamiento del mismo 
	if (event.type == sf::Event::KeyPressed) {

		//Solo permito mover o lanzar el bloque si no hay un bloque en caida libre y no hay bloques en cascada
		if (!isBlockLaunched && cascadingBlocks.empty()) {

			//Muevo los bloques a la izquierda 
			if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
				int startCol = currentColumnIndex;
				int nextCol = startCol;
				//Busco la siguiente columna no llena hacia la izquierda
				do {
					nextCol--;
				} while (nextCol >= 0 && isColumnFull(nextCol));
				if (nextCol >= 0 && !isColumnFull(nextCol) || (nextCol == 0 && startCol == 1 && !isColumnFull(0))) {
					currentColumnIndex = nextCol;
					updateBlockPosition();
				}
			}

			//Muevo los bloques a la derecha
			if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
				int startCol = currentColumnIndex;
				int nextCol = startCol;
				//Busco la siguiente columna no llena hacia la derecha
				do {
					nextCol++;
				} while (nextCol < GRID_COLS && isColumnFull(nextCol));
				if (nextCol < GRID_COLS && !isColumnFull(nextCol)) {
					currentColumnIndex = nextCol;
					updateBlockPosition();
				}
			}

			//Lanzo el bloque actual
			if (event.key.code == sf::Keyboard::Space) {

				//Solo lanzo el bloque si la columna no esta llena
				if (!isColumnFull(currentColumnIndex)) {

					//Creo una copia del bloque actual
					sf::Sprite newBlock = blockSprite;
					//Agrego el bloque a la lista de bloques colocados 
					placedBlocks.push_back(newBlock);
					//establezco su su velocidad inicial
					blockVelocities.push_back(sf::Vector2f(0.f, 0.f));

					//Marco que el bloque ha sido lanzado
					isBlockLaunched = true;
					is_game_started = true;
				}
			}
		}

		//Cambio entre modo ventana y pantalla completa al presionar la tecla P
		if (event.key.code == sf::Keyboard::P) {
			if (is_fullscreen) {
				window->create(sf::VideoMode(1500, 852), "Mi Juego SFML con POO", sf::Style::Default);
				is_fullscreen = false;
			}
			else {
				window->create(sf::VideoMode::getDesktopMode(), "Mi Juego SFML con POO", sf::Style::Fullscreen);
				is_fullscreen = true;
			}
			// Ajusto la visibilidad del cursor y el limite de frames segun el modo de pantalla 
			window->setMouseCursorVisible(!is_fullscreen);
			window->setFramerateLimit(60);
			recalculatePositions();
		}
	}
}

//Funcion para actualizar el estado del juego
void Game::update(sf::Time deltaTime) {

	//si hay un bloque en caida libre y no hay bloques en cascada, actualizo la posicion del bloque lanzado
	if (!placedBlocks.empty() && isBlockLaunched && cascadingBlocks.empty()) {

		//Obtengo el ultimo bloque lanzado  (Explicar MRUV)
		//size_t es un tipo de dato especial para tamaños. Es como un int, pero nunca puede ser negativo (porque una lista no puede tener -1 elementos)
		size_t lastBlockIndex = placedBlocks.size() - 1;
		//Declaro un vector local para la velocidad actual, esta determinado por el vector de blocks blockVelocities. (Actualemnte 0)
		sf::Vector2f& currentVelocity = blockVelocities[lastBlockIndex];
		//Delcaro el Sprite local del bloque actual, tomandolo del cector de placedBlocks
		sf::Sprite& currentBlock = placedBlocks[lastBlockIndex];

		//Aplico MRUV. El bloque ira aumentando de velocida en cada frame, calculado por deltatime 
		//VelocidadActual = VelocidadInicial + Gravedad * Tiempo
		currentVelocity.y += gravity * deltaTime.asSeconds();
		//Muevo el bloque con la velocidad actual, multiplicado por el tiempo
		//Todo esto se realiza cada frame, por o que la velocicidad va ena aumento 
		currentBlock.move(currentVelocity * deltaTime.asSeconds());

		//Verifico si el bloque ha llegado a su posicion final en la grilla
		int col = currentColumnIndex;
		//Busco la fila mas baja disponible en la columna seleccionada 
		int targetRow = -1;

		//Busco la fila mas baja disponible en la columna seleccionada
		for (int row = GRID_ROWS - 1; row >= 0; --row) {
			if (grid[row][col] == 0) {
				targetRow = row;
				break;
			}
		}
		//Si encontre una fila disponible, verifico si el bloque ha llegado a su posicion final
		if (targetRow != -1) {
			//Obtengo la posicion Y de la fila objetivo
			float targetPosY = getGridPosition(targetRow, col).y;
			//Si el bloque ha llegado o superado la posicion Y objetivo
			if (currentBlock.getPosition().y >= targetPosY) {
				//coloco al bloque en la grilla
				grid[targetRow][col] = currentTextureIndex + 1;
				//sonido del bloque
				placeSound.play();
				//chuequeo interacciones
				checkAndProcessInteractions(targetRow, col);
				placedBlocks.pop_back();
				blockVelocities.pop_back();
				
				isBlockLaunched = false;
				spawnNewBlock();
			}
		}
		else {
			//Esta parte en realidad no deberia ejecutarse, porque ya verifique que la columna no esta llena antes de lanzar el bloque
			placedBlocks.pop_back();
			blockVelocities.pop_back();

			isBlockLaunched = false;
			spawnNewBlock();
		}
	}
	//si hay bloques cayendo b
	if (!cascadingBlocks.empty()) {

		//Creo el vector para los bloques que esten cayendo. 
		//Solo paso a esta lista los bloques que aún no han llegado al suelo. Los que llegan, mueren.
		//Lo hago porque es peligroso borrar elementos de una lista mientras la estás leyendo.
		//Al recorrer con un for each, no puedo borrar elementos de la lista original sin romper el bucle.
		//El bloque 1 se mueve al lugar del 0.
		//El bloque 2 se mueve al lugar del 1.
		//El bucle for termina la vuelta 0 y pasa a la vuelta 1.
		//Resultado: ¡Se salto el bloque que antes era el 1 y el juego nunca revisó si ese bloque debía aterrizar.
		std::vector<FallingBlock> nextCascadingBlocks;

		// Actualizo la posicion de cada bloque en caida (Explicar MRU)
		for (FallingBlock& fBlock : cascadingBlocks) {
			//En MRU, la posicion se actualiza sumando la velocidad * tiempo
			//Posición = Posición + Velocidad * Tiempo
			float distanceToTravel = fBlock.velocity * deltaTime.asSeconds();
			float currentY = fBlock.sprite.getPosition().y;
			//Si llego a la meta, lo coloco en su posicion objetivo
			if (currentY + distanceToTravel >= fBlock.targetY) {
				fBlock.sprite.setPosition(fBlock.sprite.getPosition().x, fBlock.targetY);
				//Aquí muere el objeto FallingBlock y nace el dato en la grid
				grid[fBlock.targetRow][fBlock.col] = fBlock.blockID;
				placeSound.play();	
				checkAndProcessInteractions(fBlock.targetRow, fBlock.col);
			}
			//Si el bloque no ha llegado a su posicion objetivo, sigo moviendolo hacia abajo
			else {
				fBlock.sprite.move(0.f, distanceToTravel);
				nextCascadingBlocks.push_back(fBlock);
			}
		}
		//Actualizo la lista de bloques en caida
		cascadingBlocks = std::move(nextCascadingBlocks);
	}
}

//Funcion para renderizar el juego
void Game::render() {

	//Limpio la ventana y dibujo todos los elementos del juego
	window->clear();
	window->draw(backgroundSprite);
	window->setMouseCursorVisible(true);

	//Dibujo la grilla de bloques 
	for (int row = 0; row < GRID_ROWS; ++row) {
		for (int col = 0; col < GRID_COLS; ++col) {
			if (grid[row][col] != 0) {
				int blockType = grid[row][col];
				sf::Texture& texture = blockTextures[blockType - 1];
				sf::Sprite block(texture);
				block.setScale(blockSprite.getScale());
				block.setPosition(getGridPosition(row, col));
				window->draw(block);
			}
		}
	}

	//Dibujo los bloques en caida 
	for (const auto& fBlock : cascadingBlocks) {
		window->draw(fBlock.sprite);
	}
	//Dibujo los bloques colocados 
	for (const auto& block : placedBlocks) {
		window->draw(block);
	}

	//Dibujo el bloque actual si no esta en caida libre y no hay bloques en cascada
	if (!isBlockLaunched && cascadingBlocks.empty()) {
		window->draw(blockSprite);
	}

	//Actualizo y dibujo el texto de puntuacion
	window->draw(scoreText);
	window->draw(text);
	renderTutorialButton();
	renderMusicButton();
	window->display();
}


//Funcion para escalar sprites al tamaño de la ventana  (Explicar a detalle)
void Game::scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture) {
	float originalWidth = static_cast<float>(texture.getSize().x);
	float originalHeight = static_cast<float>(texture.getSize().y);
	float windowWidth = static_cast<float>(window->getSize().x);
	float windowHeight = static_cast<float>(window->getSize().y);
	float scaleX = windowWidth / originalWidth;
	float scaleY = windowHeight / originalHeight;
	float finalScale = std::max(scaleX, scaleY);
	sprite.setScale(finalScale, finalScale);
}

//Funcion para generar un nuevo bloque  (Explicar el sistema de aleatoriedad utilizado)
void Game::spawnNewBlock() {
	std::random_device rd;
	std::mt19937 gen(rd());
	const size_t MAX_SPAWN_INDEX = 14;
	std::uniform_int_distribution<size_t> distrib(0, MAX_SPAWN_INDEX);
	currentTextureIndex = distrib(gen);
	blockSprite.setTexture(blockTextures[currentTextureIndex]);
	updateBlockPosition();
}


//Funcion para recalcurar el tamaño de los bloques y sus posiciones en la ventana al redimensionarla (Explicar a detalle)
void Game::recalculatePositions() {
	// Ajusta el fondo para cubrir el nuevo Viewport de la ventana
	scaleSpriteToWindow(backgroundSprite, backgroundTexture);

	const int numColumns = GRID_COLS;

	// Obtengo la métrica base de la textura para calcular transformaciones
	float originalBlockWidth = static_cast<float>(blockTextures[0].getSize().x);

	// Determino el tamaño objetivo del bloque basado en la resolución actual (Proporcional a 1920p)
	float targetBlockWidth = (window->getSize().x / 1990.0f) * (originalBlockWidth * 0.25f);

	// Calculo el factor de escala relativo para aplicar al objeto Sprite
	float blockWidth_scale = targetBlockWidth / originalBlockWidth;

	// Limpia el contenedor de posiciones para regenerar la grilla lógica
	columnPositions.clear();

	float totalWidth = window->getSize().x;
	float effectiveBlockWidth = originalBlockWidth * blockWidth_scale; // Ancho real tras escalado

	// Defino márgenes laterales (7.5% del ancho total)
	float offset = totalWidth * 0.075f;
	float availableWidth = totalWidth - (2 * offset);

	// Calculo el espaciado uniforme entre columnas (Distribución Justificada)
	float spacing = (availableWidth - (effectiveBlockWidth * numColumns)) / (numColumns - 1);

	// Calculo el centro de cada columna para el alineamiento del proyectil
	for (int i = 0; i < numColumns; ++i) {
		float position = offset + (i * (effectiveBlockWidth + spacing));
		columnPositions.push_back(position + effectiveBlockWidth / 2.0f);
	}

	// Sincronizo el bloque activo con las nuevas métricas de la ventana
	blockSprite.setScale(blockWidth_scale, blockWidth_scale);
	updateBlockPosition();

	float newWindowWidth = static_cast<float>(window->getSize().x);
	float oldWindowWidth = oldWindowSize.x;

	// Aplico el factor de reescalado a los bloques ya existentes en la escena
	if (oldWindowWidth > 0) {
		float scaleFactor = newWindowWidth / oldWindowWidth;

		for (auto& block : placedBlocks) {
			// Reposicionamiento horizontal relativo y actualización de escala
			block.setPosition(block.getPosition().x * scaleFactor, block.getPosition().y);
			block.setScale(blockWidth_scale, blockWidth_scale);
		}
	}

	// Actualizo el registro del tamaño de ventana para el próximo frame
	oldWindowSize = static_cast<sf::Vector2f>(window->getSize());
}


//Funcion para actualizar la posicion del bloque actual segun la columna seleccionada 
sf::Vector2f Game::getGridPosition(int row, int col) {
	float blockHeight = blockTextures[0].getSize().y * blockSprite.getScale().y;
	float blockWidth = blockTextures[0].getSize().x * blockSprite.getScale().x;
	float posX = columnPositions[col];
	float posY = window->getSize().y - (blockHeight * (GRID_ROWS - row));
	return sf::Vector2f(posX - blockWidth / 2.0f, posY);
}


//Funcion para aplicar la gravedad  y reposicionar a los bloques colocados.
//Ocurre UNA SOLA VEZ justo después de que explotan los bloques.
//Su trabajo es calcular destinos y llenar la lista cascadingBlocks.
//update ocurre 60 VECES POR SEGUNDO. Revisa la lista cascadingBlocks y, si tiene cosas, las mueve un poco cada vez (frame) hasta que llegan a su destino "targetY".
void Game::applyCascadingGravity(int col) {

	//variable para la siguiente fila abierta (abajo)
	int nextOpenRow = GRID_ROWS - 1;
	//Vector para almacenar los bloques que van a caer
	std::vector<FallingBlock> blocksToFall;

	//Recorro la columna desde abajo hacia arriba
	for (int row = GRID_ROWS - 1; row >= 0; --row) {
		//Si encuentro un bloque en la fila actual 
		if (grid[row][col] != 0) {
			//Si la fila actual no es la siguiente fila abierta, el bloque debe caer
			if (row != nextOpenRow) {
				//Obtengo la posicion inicial del bloque 
				sf::Vector2f startPos = getGridPosition(row, col);
				//Obtengo la posicion objetivo del bloque 
				sf::Vector2f targetPos = getGridPosition(nextOpenRow, col);
				//Creo el bloque en caida y lo agrego a la lista de bloques que van a caer 
				//contenedor de datos temporal para el bloque en caida
				FallingBlock fBlock;
				fBlock.col = col;
				fBlock.targetRow = nextOpenRow;
				fBlock.velocity = MRU_FALL_SPEED;
				fBlock.targetY = targetPos.y;
				fBlock.blockID = grid[row][col];
				fBlock.sprite.setTexture(blockTextures[fBlock.blockID - 1]);
				fBlock.sprite.setScale(blockSprite.getScale());
				fBlock.sprite.setPosition(startPos.x, startPos.y);
				blocksToFall.push_back(fBlock);
				grid[row][col] = 0;
			}
			//Actualizo la siguiente fila abierta 
			nextOpenRow--;
		}
	}
	//Agrego los bloques que van a caer a la lista de bloques en caida 
	if (!blocksToFall.empty()) {
		cascadingBlocks.insert(cascadingBlocks.end(), blocksToFall.begin(), blocksToFall.end());
	}
}



//Funcion para chequear y procesar las interacciones entre bloques despues de colocar uno nuevo 
void Game::checkAndProcessInteractions(int landedRow, int landedCol) {

	//Obtengo el tipo de bloque que acabo de colocar
	int currentBlockType = grid[landedRow][landedCol];

	//Chequeo las interacciones con los bloques adyacentes (arriba, abajo, izquierda, derecha)
	std::vector<std::pair<int, int>> neighbors = {
	{landedRow - 1, landedCol},
	{landedRow + 1, landedCol},
	{landedRow, landedCol - 1},
	{landedRow, landedCol + 1}
	};

	//Reviso cada bloque adyacente, recorriendo el vector de vecinos
	for (const auto& neighbor : neighbors) {
		int neighborRow = neighbor.first;
		int neighborCol = neighbor.second;

		//Verifico que el vecino este dentro de los limites de la grilla
		if (neighborRow >= 0 && neighborRow < GRID_ROWS &&
			neighborCol >= 0 && neighborCol < GRID_COLS) {

			//Obtengo el tipo de bloque del vecino
			int adjacentBlockType = grid[neighborRow][neighborCol];

			//Si el bloque adyacente no es vacio, chequeo las reglas de combinacion
			if (adjacentBlockType != 0) {

				//Reviso cada regla de combinacion, recorriendo el vector de reglas
				for (const auto& rule : combinationRules) {
					if (rule.BlockTypeA == adjacentBlockType && rule.BlockTypeB == currentBlockType) {
						int points = 0;

						//Asigno puntos segun el tipo de bloque resultante
						if (rule.ResultBlockType >= 6 && rule.ResultBlockType <= 15) {
							points = 100;
						}
						else if (rule.ResultBlockType >= 16 && rule.ResultBlockType <= 20) {
							points = 500;
						}
						//Actualizo la puntuacion
						score += points;

						//Realizo la combinacion de bloques
						int resultRow = neighborRow;
						int resultCol = neighborCol;
						grid[resultRow][resultCol] = rule.ResultBlockType;
						grid[landedRow][landedCol] = 0;

						//Aplico la gravedad en cascada a las columnas afectadas
						applyCascadingGravity(landedCol);

						//Si la columna del vecino es diferente a la del bloque aterrizado, aplico gravedad en cascada ahi tambien
						if (landedCol != neighborCol) {
							applyCascadingGravity(neighborCol);
						}

						//Actualizo el texto de puntuacion
						scoreText.setString("Puntos: " + std::to_string(score));
						return;
					}
				}
			}
		}
	}
	//Chequeo interacciones triples
	checkTripleInteractions(landedRow, landedCol);
}



//Funcion para chequear y procesar interacciones triples entre bloques despues de colocar uno nuevo (Explicar funcion a fondo)
void Game::checkTripleInteractions(int landedRow, int landedCol) {

	//Creo una variable para almacenar los tipos de bloques involucrados en la secuencia
	int blockA = 0, blockB = 0, blockC = 0;


	//Funcion lambda para chequear una secuencia de tres bloques en las posiciones dadas (explicar las funciones lambda)
	auto checkSequence = [&](int rA, int cA, int rB, int cB, int rC, int cC) {
		//Verifico que las posiciones esten dentro de los limites de la grilla
		if (grid[rA][cA] == 0 || grid[rB][cB] == 0 || grid[rC][cC] == 0) return false;

		//Obtengo los VALORES de bloques en las posiciones dadas
		blockA = grid[rA][cA];
		blockB = grid[rB][cB];
		blockC = grid[rC][cC];

		//Reviso cada regla de combinacion triple, recorriendo el vector de reglas triples
		for (const auto& rule : tripleCombinationRules) {
			//Si los tipos de bloques coinciden con una regla, realizo la combinacion
			if (rule.BlockTypeA == blockA && rule.BlockTypeB == blockB && rule.BlockTypeC == blockC) {
				//Asigno puntos 
				int points = 2500;
				score += points;
				//Realizo la combinacion de bloques, desaparezco los bloques originales y creo el bloque resultante
				grid[rA][cA] = 0;
				grid[rC][cC] = 0;
				grid[rB][cB] = rule.ResultBlockType;

				//Aplico la gravedad en cascada a las columnas afectadas
				//Evito que el juego intente aplicar gravedad varias veces en la misma columna
				applyCascadingGravity(cA);
				if (cA != cB) applyCascadingGravity(cB);
				//Para combinacion en L, ej: dos bloques están en la columna 2 y uno en la columna 3
				if (cA != cC && cB != cC) applyCascadingGravity(cC);

				//Actualizo el texto de puntuacion
				scoreText.setString("Puntos: " + std::to_string(score));
				return true;
			}
		}
		return false;
		};
	//Chequeo todas las posibles secuencias de tres bloques que incluyan la posicion del bloque aterrizado, recorriendo la grilla de 3 en 3 
	for (int col = 0; col <= GRID_COLS - 3; ++col) {
		if (checkSequence(landedRow, col, landedRow, col + 1, landedRow, col + 2)) return;
	}
	if (landedRow <= GRID_ROWS - 3) {
		int col = landedCol;
		if (checkSequence(landedRow, col, landedRow + 1, col, landedRow + 2, col)) return;
	}
}


//Funcion para reiniciar el juego
void Game::resetGame() {
	//Reinicio la grilla, los bloques colocados, las velocidades, la puntuacion y el bloque actual
	grid.assign(GRID_ROWS, std::vector<int>(GRID_COLS, 0));
	placedBlocks.clear();
	blockVelocities.clear();
	cascadingBlocks.clear();
	score = 0;
	scoreText.setString("Puntos: 0");
	isBlockLaunched = false;
	currentColumnIndex = 3;
	is_game_started = true;
	spawnNewBlock();
}


//Funcion para renderizar el fondo del juego, usado en main.cpp (revisar en donde mas)
void Game::renderBackground() {
	window->clear();
	window->draw(backgroundSprite);
}


//Funcion para renderizar el boton de tutorial
void Game::renderTutorialButton() {
	window->draw(tutorialButtonSprite);
}


//Funcion para obtener las reglas de combinacion para mostrarlas en pantalla, zona del tutorial 


std::vector<std::string> Game::getRulesForDisplay() const {
	//Vector para almacenar las reglas en formato de texto
	std::vector<std::string> rules;
	//Agrego las instrucciones del tutorial, cargo el vector recien creado
	rules.push_back("TUTORIAL DE JUEGO (COMO COMBINAR)");
	rules.push_back(" ");
	rules.push_back("Lanza bloques desde la parte superior de la grilla.");
	rules.push_back("Utiliza las flechas de tu teclado, o los botones A o D, para alternar entre las diferentes columnas.");
	rules.push_back("Utiliza la barra espaciadora para lanzar el bloque en la columna donde se encuentre.");
	rules.push_back("Combina bloques adyacentes (horizontal o vertical) en");
	rules.push_back("secuencias de dos o tres tipos para crear un bloque de mayor nivel.");
	rules.push_back("Las combinaciones son fijas y se listan abajo.");
	rules.push_back(" ");
	rules.push_back("COMBINACIONES NIVEL 1 (100 PUNTOS)");

	//recorro las reglas de combinacion y las agrego al vector en formato de texto
	for (const auto& rule : combinationRules) {
		//Solo agrego las reglas de nivel 1 
		if (rule.BlockTypeA < rule.BlockTypeB && rule.ResultBlockType >= ID_EMBLEMA && rule.ResultBlockType <= ID_DRAGONMAGICO) {
			std::string ruleStr = getBlockName(rule.BlockTypeA) + " + " +
				getBlockName(rule.BlockTypeB) + " = " +
				getBlockName(rule.ResultBlockType);
			rules.push_back(ruleStr);
		}	
	}
	//Agrego un espacio y las reglas de nivel 2
	rules.push_back(" ");
	rules.push_back("COMBINACIONES NIVEL 2 (500 PUNTOS)");
	//Recorro las reglas de combinacion y las agrego al vector en formato de texto (mismo que el anterior pero de nivel 2)
	for (const auto& rule : combinationRules) {
		if (rule.BlockTypeA < rule.BlockTypeB && rule.ResultBlockType >= ID_PALADIN && rule.ResultBlockType <= ID_SEÑORDELAGUERRA) {
			std::string ruleStr = getBlockName(rule.BlockTypeA) + " + " +
				getBlockName(rule.BlockTypeB) + " = " +
				getBlockName(rule.ResultBlockType);
			rules.push_back(ruleStr);
		}
	}
	//Agrego un espacio y las reglas de nivel 3
	rules.push_back(" ");
	rules.push_back("COMBINACIONES NIVEL 3 (2500 PUNTOS)");
	//Recorro las reglas de combinacion triple y las agrego al vector en formato de texto, mismo que el anterior pero nivel 3
	for (const auto& rule : tripleCombinationRules) {
		if (rule.BlockTypeA < rule.BlockTypeB && rule.BlockTypeB < rule.BlockTypeC && rule.ResultBlockType >= ID_AVATARDELREINO && rule.ResultBlockType <= ID_ESPADACREPUSCULO) {
			std::string ruleStr = getBlockName(rule.BlockTypeA) + " + " +
				getBlockName(rule.BlockTypeB) + " + " +
				getBlockName(rule.BlockTypeC) + " = " +
				getBlockName(rule.ResultBlockType);
			rules.push_back(ruleStr);
		}
	}

	//Retorno el vector con las reglas en formato de texto
	return rules;
}


//Funcion para obtener el nombre de un bloque a partir de su ID 
std::string Game::getBlockName(int id) const {
	auto it = blockNames.find(id);
	if (it != blockNames.end()) {
		return it->second;
	}
	return "ID Desconocido (" + std::to_string(id) + ")";
}

//Funcion para renderizar el boton de musica
void Game::renderMusicButton() {
	window->draw(musicButtonSprite);
}

//Funcion para actualizar la posicion del bloque actual segun la columna seleccionada 
void Game::updateBlockPosition() {
	float blockWidth = blockSprite.getGlobalBounds().width;
	float posX = columnPositions[currentColumnIndex] - (blockWidth / 2.0f);
	float posY = 50.f;
	blockSprite.setPosition(posX, posY);
}


//Funciones para verificar si una columna o la grilla estan llenas 
bool Game::isColumnFull(int col) const {
	if (col < 0 || col >= GRID_COLS) return true;
	return grid[0][col] != 0;
}
bool Game::isGridFull() const {
	for (int col = 0; col < GRID_COLS; ++col) {
		if (!isColumnFull(col)) {
			return false;
		}
	}
	return true;
}