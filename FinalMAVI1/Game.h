#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

const int GRID_ROWS = 4;
const int GRID_COLS = 7;


struct CombinationRule {
    int BlockTypeA;      
    int BlockTypeB;      
    int ResultBlockType; 
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void scaleSpriteToWindow(sf::Sprite& sprite, const sf::Texture& texture);
    void spawnNewBlock();
    void recalculatePositions();
    void initializeRules();
    void checkAndProcessInteractions(int landedRow, int landedCol);
    void applyCascadingGravity(int col);

    sf::Vector2f getGridPosition(int row, int col);

    std::vector<CombinationRule> combinationRules;
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

    std::vector<sf::Sprite> placedBlocks;
    std::vector<sf::Vector2f> blockVelocities;
    const float gravity;

    std::vector<float> columnPositions;
    int currentColumnIndex;
    bool isBlockLaunched;

    sf::Vector2f oldWindowSize;
};

#endif 