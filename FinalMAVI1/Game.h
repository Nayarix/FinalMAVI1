#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <vector>
#include <string>
#include <map>

const int GRID_ROWS = 4;
const int GRID_COLS = 7;

const float BASE_BLOCK_SCALE_FACTOR = 0.25f;

struct CombinationRule {
    int BlockTypeA;
    int BlockTypeB;
    int ResultBlockType;
};

struct TripleCombinationRule {
    int BlockTypeA;
    int BlockTypeB;
    int BlockTypeC;
    int ResultBlockType;
};

struct FallingBlock {
    sf::Sprite sprite;
    float targetY;
    float velocity;
    int col;
    int targetRow;
    int blockID;
};

class Game {
public:
    Game();
    ~Game();

    void processEvents(sf::Event& event);
    void update(sf::Time deltaTime);
    void render();

    void resetGame();
    void renderBackground();
    void renderTutorialButton();
    void renderMusicButton();
    std::vector<std::string> getRulesForDisplay() const;

    sf::RenderWindow* getWindow() const { return window; }
    bool isGameStarted() const { return is_game_started; }
    sf::FloatRect getTutorialButtonBounds() const { return tutorialButtonSprite.getGlobalBounds(); }
    sf::FloatRect getMusicButtonBounds() const { return musicButtonSprite.getGlobalBounds(); }

    
    sf::Music backgroundMusic;
    bool isMusicPlaying;


private:
    void scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture);
    void spawnNewBlock();
    void recalculatePositions();
    void initializeRules();
    void checkAndProcessInteractions(int landedRow, int landedCol);
    void checkTripleInteractions(int landedRow, int landedCol);
    void applyCascadingGravity(int col);
    void updateBlockPosition();

    const float MRU_FALL_SPEED = 800.0f;
    const float gravity;

    std::vector<CombinationRule> combinationRules;
    std::vector<TripleCombinationRule> tripleCombinationRules;
    std::vector<FallingBlock> cascadingBlocks;

    sf::Vector2f getGridPosition(int row, int col);
    std::vector<std::vector<int>> grid;

    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock clock;

    sf::Sprite blockSprite;
    std::vector<sf::Texture> blockTextures;
    int currentTextureIndex;
    bool is_fullscreen;
    bool is_game_started;

    sf::Texture tutorialButtonTexture;
    sf::Sprite tutorialButtonSprite;
    sf::Texture musicButtonTexture;
    sf::Sprite musicButtonSprite;

    std::vector<sf::Sprite> placedBlocks;
    std::vector<sf::Vector2f> blockVelocities;

    std::vector<float> columnPositions;
    int currentColumnIndex;
    bool isBlockLaunched;

    sf::Vector2f oldWindowSize;
    std::map<int, std::string> blockNames;
    std::string getBlockName(int id) const;

    sf::SoundBuffer placeSoundBuffer;
    sf::Sound placeSound;

    long score; 
    sf::Text scoreText;
};

#endif