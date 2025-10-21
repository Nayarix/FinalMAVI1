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
    
	//Combinaciones de tercer nivel
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





Game::Game() : gravity(500.f) {
    window = new RenderWindow(VideoMode::getDesktopMode(), "Mi Juego SFML con POO", Style::Fullscreen);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(true);
    is_fullscreen = true;

    if (!backgroundTexture.loadFromFile("BloquesMAVI1/fondoPrueba2.jpg")) {
        std::cerr << "Error al cargar el fondo" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    float originalWidth = backgroundTexture.getSize().x;
    float windowWidth = (float)window->getSize().x;
    float scale = windowWidth / originalWidth;
    backgroundSprite.setScale(scale, scale);

   
    if (!tutorialButtonTexture.loadFromFile("BloquesMAVI1/GuiaCombinaciones.png")) {
        std::cerr << "Error al cargar la textura del botón de tutorial" << std::endl;
        
    }
    tutorialButtonSprite.setTexture(tutorialButtonTexture);
    
    tutorialButtonSprite.setScale(0.1f, 0.1f);

    
    
    float margin = 20.f;
    float buttonWidth = tutorialButtonSprite.getGlobalBounds().width;

    if (!backgroundMusic.openFromFile("Musica/MedievalMusicwav.wav")) {
        std::cerr << "Error al cargar la musica" << std::endl;
    }
    backgroundMusic.setLoop(true); 
    backgroundMusic.play();        
    isMusicPlaying = true;

    if (!placeSoundBuffer.loadFromFile("Musica/SonidoColocarBloque.wav")) {
        std::cerr << "Error al cargar el efecto de sonido SonidoColocarBloque.wav" << std::endl;
    }
    placeSound.setBuffer(placeSoundBuffer);
    
    if (!musicButtonTexture.loadFromFile("BloquesMAVI1/SimboloMusica.png")) {
        std::cerr << "Error al cargar la textura del boton de musica" << std::endl;
    }
    musicButtonSprite.setTexture(musicButtonTexture);
    musicButtonSprite.setScale(0.1f, 0.1f);

    tutorialButtonSprite.setPosition(windowWidth - buttonWidth - margin, margin);

    float tutorialButtonHeight = tutorialButtonSprite.getGlobalBounds().height;
    musicButtonSprite.setPosition(windowWidth - buttonWidth - margin, margin + tutorialButtonHeight + margin);


    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
    }
    score = 0;
    scoreText.setFont(font); 
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(20.f, 60.f);


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
    initializeRules();


    currentTextureIndex = 0;
    blockSprite.setTexture(blockTextures[currentTextureIndex]);
    float originalBlockWidth = blockTextures[0].getSize().x;
    float windowWidth_initial = window->getSize().x;
    float scale_initial = (windowWidth_initial / 1990.0f) * 0.25f;
    blockSprite.setScale(scale_initial, scale_initial);

    

    currentColumnIndex = 3;
    isBlockLaunched = false;
    is_game_started = false;

    oldWindowSize = static_cast<sf::Vector2f>(window->getSize());

    grid.resize(GRID_ROWS, std::vector<int>(GRID_COLS, 0));

    recalculatePositions();
    spawnNewBlock();
}

Game::~Game() {
    delete window;
    window = nullptr;
}



void Game::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {


        if (!isBlockLaunched && cascadingBlocks.empty()) {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                currentColumnIndex = std::max(0, currentColumnIndex - 1);
                updateBlockPosition();
            }
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                currentColumnIndex = std::min(GRID_COLS - 1, currentColumnIndex + 1);
                updateBlockPosition();
            }

            if (event.key.code == sf::Keyboard::Space) {
                sf::Sprite newBlock = blockSprite;
                placedBlocks.push_back(newBlock);
                blockVelocities.push_back(sf::Vector2f(0.f, 0.f));
                isBlockLaunched = true;
                is_game_started = true;
            }

           
            /*if (event.key.code == sf::Keyboard::C) {
                currentTextureIndex++;
                if (currentTextureIndex >= blockTextures.size()) {
                    currentTextureIndex = 0;
                }
                blockSprite.setTexture(blockTextures[currentTextureIndex]);
            }
            */
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

void Game::update(sf::Time deltaTime) {

    if (!placedBlocks.empty() && isBlockLaunched && cascadingBlocks.empty()) {
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
                placeSound.play();
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
    if (!cascadingBlocks.empty()) {
        std::vector<FallingBlock> nextCascadingBlocks;

        for (FallingBlock& fBlock : cascadingBlocks) {
            float distanceToTravel = fBlock.velocity * deltaTime.asSeconds();
            float currentY = fBlock.sprite.getPosition().y;

            if (currentY + distanceToTravel >= fBlock.targetY) {

                fBlock.sprite.setPosition(fBlock.sprite.getPosition().x, fBlock.targetY);

                grid[fBlock.targetRow][fBlock.col] = fBlock.blockID;
                placeSound.play();
                checkAndProcessInteractions(fBlock.targetRow, fBlock.col);
                
            }
            else {
                fBlock.sprite.move(0.f, distanceToTravel);
                nextCascadingBlocks.push_back(fBlock);
            }
        }

        cascadingBlocks = std::move(nextCascadingBlocks);
    }
}

void Game::render() {
    window->clear();
    window->draw(backgroundSprite);
    window->setMouseCursorVisible(true);

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

    for (const auto& fBlock : cascadingBlocks) {
        window->draw(fBlock.sprite);
    }
    for (const auto& block : placedBlocks) {
        window->draw(block);
    }


    if (!isBlockLaunched && cascadingBlocks.empty()) {
        window->draw(blockSprite);
    }

    window->draw(scoreText);
    window->draw(text);
    window->draw(tutorialButtonSprite);
    renderMusicButton();
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
    const size_t MAX_SPAWN_INDEX = 14;
    std::uniform_int_distribution<size_t> distrib(0, MAX_SPAWN_INDEX);

    currentTextureIndex = distrib(gen);
    blockSprite.setTexture(blockTextures[currentTextureIndex]);
    updateBlockPosition();
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
    updateBlockPosition();

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
    std::vector<FallingBlock> blocksToFall;

    for (int row = GRID_ROWS - 1; row >= 0; --row) {
        if (grid[row][col] != 0) {
            if (row != nextOpenRow) {
               

                sf::Vector2f startPos = getGridPosition(row, col);
                sf::Vector2f targetPos = getGridPosition(nextOpenRow, col);

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
            nextOpenRow--;
        }
    }

    
    if (!blocksToFall.empty()) {
        cascadingBlocks.insert(cascadingBlocks.end(), blocksToFall.begin(), blocksToFall.end());
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

                        int points = 0;
                        if (rule.ResultBlockType >= 6 && rule.ResultBlockType <= 15) {
                            points = 100; 
                        }
                        else if (rule.ResultBlockType >= 16 && rule.ResultBlockType <= 20) {
                            points = 500; 
                        }
                        score += points;


                        int resultRow = neighborRow;
                        int resultCol = neighborCol;

                        
                        grid[resultRow][resultCol] = rule.ResultBlockType; 
                        grid[landedRow][landedCol] = 0;                  

                     
                        applyCascadingGravity(landedCol);
                        
                        if (landedCol != neighborCol) {
                            applyCascadingGravity(neighborCol);
                        }

                        scoreText.setString("Puntos: " + std::to_string(score));
                        return;
                    }
                }
            }
        }
    }
    checkTripleInteractions(landedRow, landedCol);
}

void Game::checkTripleInteractions(int landedRow, int landedCol) {

    int blockA = 0, blockB = 0, blockC = 0;


    auto checkSequence = [&](int rA, int cA, int rB, int cB, int rC, int cC) {
        if (grid[rA][cA] == 0 || grid[rB][cB] == 0 || grid[rC][cC] == 0) return false;


        blockA = grid[rA][cA];
        blockB = grid[rB][cB];
        blockC = grid[rC][cC];

        for (const auto& rule : tripleCombinationRules) {
         
            if (rule.BlockTypeA == blockA && rule.BlockTypeB == blockB && rule.BlockTypeC == blockC) {

                int points = 2500;
                score += points;

                grid[rA][cA] = 0;
                grid[rC][cC] = 0;
                grid[rB][cB] = rule.ResultBlockType;

               
                applyCascadingGravity(cA);
                if (cA != cB) applyCascadingGravity(cB);
                if (cA != cC && cB != cC) applyCascadingGravity(cC);

                scoreText.setString("Puntos: " + std::to_string(score));
                return true;
            }
        }
        return false;
        };


  
    for (int col = 0; col <= GRID_COLS - 3; ++col) {
     
        if (checkSequence(landedRow, col, landedRow, col + 1, landedRow, col + 2)) return;
    }


    if (landedRow <= GRID_ROWS - 3) {
        int col = landedCol;
       
        if (checkSequence(landedRow, col, landedRow + 1, col, landedRow + 2, col)) return;
    }
}


void Game::resetGame() {
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

void Game::renderBackground() {
    window->clear();
    window->draw(backgroundSprite);
}

void Game::renderTutorialButton() {
    window->draw(tutorialButtonSprite);
}

std::vector<std::string> Game::getRulesForDisplay() const {
    std::vector<std::string> rules;

   
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
    for (const auto& rule : combinationRules) {
        
        if (rule.BlockTypeA < rule.BlockTypeB && rule.ResultBlockType >= ID_EMBLEMA && rule.ResultBlockType <= ID_DRAGONMAGICO) {
            std::string ruleStr = getBlockName(rule.BlockTypeA) + " + " +
                getBlockName(rule.BlockTypeB) + " = " +
                getBlockName(rule.ResultBlockType);
            rules.push_back(ruleStr);
        }
    }
    rules.push_back(" ");

    
    rules.push_back("COMBINACIONES NIVEL 2 (500 PUNTOS)");
    for (const auto& rule : combinationRules) {
        
        if (rule.BlockTypeA < rule.BlockTypeB && rule.ResultBlockType >= ID_PALADIN && rule.ResultBlockType <= ID_SEÑORDELAGUERRA) {
            std::string ruleStr = getBlockName(rule.BlockTypeA) + " + " +
                getBlockName(rule.BlockTypeB) + " = " +
                getBlockName(rule.ResultBlockType);
            rules.push_back(ruleStr);
        }
    }
    rules.push_back(" ");


    
    rules.push_back("COMBINACIONES NIVEL 3 (2500 PUNTOS)");
    for (const auto& rule : tripleCombinationRules) {
        
        if (rule.BlockTypeA < rule.BlockTypeB && rule.BlockTypeB < rule.BlockTypeC && rule.ResultBlockType >= ID_AVATARDELREINO && rule.ResultBlockType <= ID_ESPADACREPUSCULO) {
            std::string ruleStr = getBlockName(rule.BlockTypeA) + " + " +
                getBlockName(rule.BlockTypeB) + " + " +
                getBlockName(rule.BlockTypeC) + " = " +
                getBlockName(rule.ResultBlockType);
            rules.push_back(ruleStr);
        }
    }

    return rules;
}

std::string Game::getBlockName(int id) const {
    auto it = blockNames.find(id);
    if (it != blockNames.end()) {
        return it->second; 
    }
  
    return "ID Desconocido (" + std::to_string(id) + ")";
}


void Game::renderMusicButton() {
    window->draw(musicButtonSprite);
}

void Game::updateBlockPosition() {
    float blockWidth = blockSprite.getGlobalBounds().width;
    float posX = columnPositions[currentColumnIndex] - (blockWidth / 2.0f);
    float posY = 50.f; 

    blockSprite.setPosition(posX, posY);
}