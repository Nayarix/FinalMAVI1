#ifndef GAME_H
#define GAME_H

// Librerias de SFML para Gráficos y Audio
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Librerias estándar de C++ (STL)
#include <vector> // Para listas dinámicas (reglas, texturas, bloques)
#include <string> // Para manejo de texto (nombres, rutas)
#include <map>    // Para el diccionario ID -> Nombre

// Constantes globales para definir las dimensiones lógicas del tablero
const int GRID_ROWS = 4; // Filas de la matriz
const int GRID_COLS = 7; // Columnas de la matriz
const float BASE_BLOCK_SCALE_FACTOR = 0.25f; // Factor de escala visual

// Estructura para definir una regla de combinación simple (A + B = C)
struct CombinationRule {
	int BlockTypeA;      // ID del bloque vecino
	int BlockTypeB;      // ID del bloque actual
	int ResultBlockType; // ID del bloque resultante
};

// Estructura para definir una regla de combinación triple (A + B + C = D)
struct TripleCombinationRule {
	int BlockTypeA;
	int BlockTypeB;
	int BlockTypeC;
	int ResultBlockType;
};

// Estructura para representar un bloque en caída automática (Cascada/MRU)
struct FallingBlock {
	sf::Sprite sprite; // Su representación visual
	float targetY;     // Hasta qué píxel debe caer
	float velocity;    // Velocidad constante (MRU)
	int col;           // En qué columna lógica está
	int targetRow;     // A qué fila lógica va
	int blockID;       // Qué tipo de bloque es
};

class Game {
public:
	// Constructor y Destructor (Gestión de memoria y carga inicial)
	Game();
	~Game();

	// --- CICLO PRINCIPAL DEL JUEGO ---
	void processEvents(sf::Event& event); // Maneja inputs (Teclado/Mouse)
	void update(sf::Time deltaTime);      // Actualiza físicas y lógica (MRU/MRUV)
	void render();                        // Dibuja todo en pantalla

	// --- CONTROL DE ESTADO ---
	void resetGame(); // Reinicia variables para nueva partida

	// --- RENDERIZADO ESPECÍFICO (Para UI y Estados) ---
	void renderBackground();     // Dibuja fondo (usado en Menu/GameOver)
	void renderTutorialButton(); // Dibuja botón de ayuda
	void renderMusicButton();    // Dibuja botón de música

	// --- GETTERS (Acceso de lectura desde main.cpp) ---
	std::vector<std::string> getRulesForDisplay() const; // Devuelve textos para el tutorial
	sf::RenderWindow* getWindow() const { return window; } // Devuelve puntero a la ventana
	bool isGameStarted() const { return is_game_started; } // Bandera de estado

	// Getters para colisión del mouse con botones (UI)
	sf::FloatRect getTutorialButtonBounds() const { return tutorialButtonSprite.getGlobalBounds(); }
	sf::FloatRect getMusicButtonBounds() const { return musicButtonSprite.getGlobalBounds(); }

	// --- LÓGICA DE JUEGO (Consultas) ---
	bool isColumnFull(int col) const; // Verifica si una columna está llena (tope lógico)
	bool isGridFull() const;          // Verifica si todo el tablero está lleno (Game Over)
	long getScore() const { return score; } // Devuelve puntaje actual

	// --- AUDIO PÚBLICO ---
	// Son públicos para poder pausarlos desde main.cpp al hacer clic en botones
	sf::Music backgroundMusic;
	bool isMusicPlaying;

private:
	// --- MÉTODOS INTERNOS (Auxiliares) ---
	void scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture); // Ajuste de resolución
	void spawnNewBlock();       // Generación aleatoria de bloques
	void recalculatePositions(); // Recálculo visual al redimensionar ventana
	void initializeRules();     // Carga de las reglas en los vectores

	// Lógica de Colisiones e Interacciones
	void checkAndProcessInteractions(int landedRow, int landedCol); 
	void checkTripleInteractions(int landedRow, int landedCol);     // (Usa una funcion Lambda)
	void applyCascadingGravity(int col); // Lógica de caída tras fusión
	void updateBlockPosition(); // Sincroniza Sprite con Columna lógica

	// --- CONSTANTES FÍSICAS ---
	const float MRU_FALL_SPEED = 800.0f; // Velocidad para cascada (Constante)
	const float gravity;                 // Aceleración para caída del jugador (MRUV)

	// --- ESTRUCTURAS DE DATOS (Lógica) ---
	std::vector<CombinationRule> combinationRules;             // Lista de reglas dobles
	std::vector<TripleCombinationRule> tripleCombinationRules; // Lista de reglas triples
	std::vector<FallingBlock> cascadingBlocks;                 // Lista de bloques cayendo (MRU)

	//Vector para obtener la posicon de un bloque en la grilla
	//Utilidad: convertir Coordenadas Matriciales a Píxeles en Pantalla
	sf::Vector2f getGridPosition(int row, int col);

	// LA GRILLA: Representación lógica del tablero (Matriz de enteros)
	//Vector de vectores (filas x columnas)
	std::vector<std::vector<int>> grid;

	// --- RECURSOS SFML ---
	sf::RenderWindow* window; // Puntero a la ventana (gestión dinámica)
	sf::Font font;            // Fuente para textos
	sf::Text text;            // Objeto texto genérico

	// Recursos Gráficos (Fondo)
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


	// Recursos del Bloque Activo
	sf::Sprite blockSprite; // El "pincel" que dibuja el bloque actual

	// EL ALMACÉN DE TEXTURAS: Vector que guarda todas las imágenes en RAM
	std::vector<sf::Texture> blockTextures;
	int currentTextureIndex; // Índice de la textura actual

	// Variables de Estado
	bool is_fullscreen;
	bool is_game_started;

	// Recursos UI (Botones)
	sf::Texture tutorialButtonTexture;
	sf::Sprite tutorialButtonSprite;
	sf::Texture musicButtonTexture;
	sf::Sprite musicButtonSprite;

	// Vectores para la física del bloque controlado por el jugador
	std::vector<sf::Sprite> placedBlocks;      // Vector para el bloque en caída libre antes de tocar suelo
	std::vector<sf::Vector2f> blockVelocities; // Vector de velocidad (cambia con gravedad)

	// Posiciones precalculadas de las columnas (Optimización visual)
	std::vector<float> columnPositions;
	int currentColumnIndex; // En qué columna está el jugador (0-6)
	bool isBlockLaunched;   // Bandera: ¿Ya se soltó el bloque?

	// Gestión de resolución
	sf::Vector2f oldWindowSize;

	// DICCIONARIO: Mapa para traducir ID (int) a Nombre (string)
	std::map<int, std::string> blockNames;
	std::string getBlockName(int id) const; // Función auxiliar de búsqueda en el mapa

	// Audio (Efectos cortos)
	sf::SoundBuffer placeSoundBuffer; // El archivo en memoria RAM
	sf::Sound placeSound;             // El reproductor

	// Puntuación
	long score;
	sf::Text scoreText;
};

#endif