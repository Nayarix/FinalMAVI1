#include "Game.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace sf;

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


void Game::initializeRules() {
    combinationRules.clear();

	//Combinaciones de primer nivel
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

    //Combinaciones de segundo nivel
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
    
   

    
}





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

   

       
    std::vector<std::string> texturePaths = {
        //Bloques de primer nivel
        "BloquesMAVI1/Espada.png",
        "BloquesMAVI1/Escudo.png",
        "BloquesMAVI1/Corona.png",
        "BloquesMAVI1/cetroMagico.png",
        "BloquesMAVI1/Dragon.png",

        //Bloques de segundo nivel
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

		//Bloques de tercer nivel
        "BloquesMAVI1/Paladin.png",
        "BloquesMAVI1/HeroeLegendario.png",
        "BloquesMAVI1/DefensorDelReino.png",
        "BloquesMAVI1/DragonDeLaCorona.png",
        "BloquesMAVI1/SeñorDeLaGuerra.png",

		//Bloques de cuarto nivel
        "BloquesMAVI1/AvatarDelReino.png",
        "BloquesMAVI1/DragonAncestral.png",
         "BloquesMAVI1/TitanDeBatalla.png",
        "BloquesMAVI1/CaballeroDragon.png",
        "BloquesMAVI1/EspadaDelCrepusculo.png",
    };

    
    for (const auto& path : texturePaths) {
        sf::Texture tempTexture;
        if (tempTexture.loadFromFile(path)) {
            
            blockTextures.push_back(std::move(tempTexture));
        }
        else {
            std::cerr << "Error al cargar la textura: " << path << std::endl;
        }
    }

    initializeRules();


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

    currentColumnIndex = 3;
    isBlockLaunched = false;

    oldWindowSize = static_cast<sf::Vector2f>(window->getSize());

    grid.resize(GRID_ROWS, std::vector<int>(GRID_COLS, 0));

    recalculatePositions();
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
                if (event.key.code == sf::Keyboard::Left) {
                    currentColumnIndex = std::max(0, currentColumnIndex - 1);
                    spawnNewBlock();
                }
                if (event.key.code == sf::Keyboard::Right) {
                    currentColumnIndex = std::min(GRID_COLS - 1, currentColumnIndex + 1);
                    spawnNewBlock();
                }
                if (event.key.code == sf::Keyboard::Space) {
                    if (!isBlockLaunched) {
                        sf::Sprite newBlock = blockSprite;
                        placedBlocks.push_back(newBlock);
                        blockVelocities.push_back(sf::Vector2f(0.f, 0.f));
                        isBlockLaunched = true;
                    }
                }
                if (event.key.code == sf::Keyboard::C) {
                    currentTextureIndex++;
                    if (currentTextureIndex >= blockTextures.size()) {
                        currentTextureIndex = 0;
                    }
                    blockSprite.setTexture(blockTextures[currentTextureIndex]);
                }
            }

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
                recalculatePositions();
            }
        }

        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            window->setView(sf::View(visibleArea));
            recalculatePositions();
        }
    }
}

void Game::update(sf::Time deltaTime) {
    if (!placedBlocks.empty() && isBlockLaunched) {
        size_t lastBlockIndex = placedBlocks.size() - 1;
        sf::Vector2f& currentVelocity = blockVelocities[lastBlockIndex];
        sf::Sprite& currentBlock = placedBlocks[lastBlockIndex];

        currentVelocity.y += gravity * deltaTime.asSeconds();
        currentBlock.move(currentVelocity * deltaTime.asSeconds());

        int col = currentColumnIndex;
        int targetRow = -1;

        for (int row = GRID_ROWS - 1; row >= 0; --row) {
            if (grid[row][col] == 0) {
                targetRow = row;
                break;
            }
        }

        if (targetRow != -1) {
            float targetPosY = getGridPosition(targetRow, col).y;

            if (currentBlock.getPosition().y >= targetPosY) {
                grid[targetRow][col] = currentTextureIndex + 1;

                checkAndProcessInteractions(targetRow, col);

                placedBlocks.pop_back();
                blockVelocities.pop_back();

                isBlockLaunched = false;
                spawnNewBlock();
            }
        }
        else {
            placedBlocks.pop_back();
            blockVelocities.pop_back();
            isBlockLaunched = false;
            spawnNewBlock();
        }
    }
}

void Game::render() {
    window->clear();
    window->draw(backgroundSprite);

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
    float originalHeight = static_cast<float>(texture.getSize().y);
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    float scaleX = windowWidth / originalWidth;
    float scaleY = windowHeight / originalHeight;

    float finalScale = std::max(scaleX, scaleY);

    sprite.setScale(finalScale, finalScale);
}

void Game::spawnNewBlock() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, blockTextures.size() - 1);

    currentTextureIndex = distrib(gen);
    blockSprite.setTexture(blockTextures[currentTextureIndex]);

    float blockWidth = blockSprite.getGlobalBounds().width;
    float posX = columnPositions[currentColumnIndex] - (blockWidth / 2.0f);
    float posY = 50.f;

    blockSprite.setPosition(posX, posY);
}

void Game::recalculatePositions() {
    scaleSpriteToWindow(backgroundSprite, backgroundTexture);

    const int numColumns = GRID_COLS;
    float originalBlockWidth = static_cast<float>(blockTextures[0].getSize().x);
    float targetBlockWidth = (window->getSize().x / 1990.0f) * (originalBlockWidth * 0.25f);
    float blockWidth_scale = targetBlockWidth / originalBlockWidth;

    columnPositions.clear();
    float totalWidth = window->getSize().x;
    float effectiveBlockWidth = originalBlockWidth * blockWidth_scale;
    float offset = totalWidth * 0.075f;
    float availableWidth = totalWidth - (2 * offset);
    float spacing = (availableWidth - (effectiveBlockWidth * numColumns)) / (numColumns - 1);

    for (int i = 0; i < numColumns; ++i) {
        float position = offset + (i * (effectiveBlockWidth + spacing));
        columnPositions.push_back(position + effectiveBlockWidth / 2.0f);
    }

    blockSprite.setScale(blockWidth_scale, blockWidth_scale);
    spawnNewBlock();

    float newWindowWidth = static_cast<float>(window->getSize().x);
    float oldWindowWidth = oldWindowSize.x;
    if (oldWindowWidth > 0) {
        float scaleFactor = newWindowWidth / oldWindowWidth;
        for (auto& block : placedBlocks) {
            block.setPosition(block.getPosition().x * scaleFactor, block.getPosition().y);
            block.setScale(blockWidth_scale, blockWidth_scale);
        }
    }

    oldWindowSize = static_cast<sf::Vector2f>(window->getSize());
}

sf::Vector2f Game::getGridPosition(int row, int col) {
    float blockHeight = blockTextures[0].getSize().y * blockSprite.getScale().y;
    float blockWidth = blockTextures[0].getSize().x * blockSprite.getScale().x;

    float posX = columnPositions[col];
    float posY = window->getSize().y - (blockHeight * (GRID_ROWS - row));

    return sf::Vector2f(posX - blockWidth / 2.0f, posY);
}

void Game::applyCascadingGravity(int col) {
    int nextOpenRow = GRID_ROWS - 1; 

    for (int row = GRID_ROWS - 1; row >= 0; --row) {
        if (grid[row][col] != 0) {
            if (row != nextOpenRow) {
                grid[nextOpenRow][col] = grid[row][col];
                grid[row][col] = 0; 
            }
            nextOpenRow--;
        }
    }
}

void Game::checkAndProcessInteractions(int landedRow, int landedCol) {

    int currentBlockType = grid[landedRow][landedCol];

    std::vector<std::pair<int, int>> neighbors = {
        {landedRow - 1, landedCol}, 
        {landedRow + 1, landedCol}, 
        {landedRow, landedCol - 1}, 
        {landedRow, landedCol + 1}  
    };

    for (const auto& neighbor : neighbors) {
        int neighborRow = neighbor.first;
        int neighborCol = neighbor.second;

        if (neighborRow >= 0 && neighborRow < GRID_ROWS &&
            neighborCol >= 0 && neighborCol < GRID_COLS) {

            int adjacentBlockType = grid[neighborRow][neighborCol];

            if (adjacentBlockType != 0) {

                for (const auto& rule : combinationRules) {

                   
                    if (rule.BlockTypeA == adjacentBlockType && rule.BlockTypeB == currentBlockType) {


                        int resultRow = neighborRow;
                        int resultCol = neighborCol;

                        
                        grid[resultRow][resultCol] = rule.ResultBlockType; 
                        grid[landedRow][landedCol] = 0;                  

                     
                        applyCascadingGravity(landedCol);
                        
                        if (landedCol != neighborCol) {
                            applyCascadingGravity(neighborCol);
                        }

                        
                        return;
                    }
                }
            }
        }
    }
}
