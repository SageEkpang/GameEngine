#ifndef TILE_SET_COMPONENT_H
#define TILE_SET_COMPONENT_H

#include "Component.h"

#define LEVEL_LENGTH 40
#define LEVEL_HEIGHT 15

#define TILE_SIZE 100.0f

// E - EMPTY
// G - GROUND

typedef struct Tile
{
    std::string tag;
    Vector2 position;
    Texture2D texture;

    Tile(std::string tag = " ", Vector2 position = Vector2(), Texture2D texture = Texture2D())
    {
        this->tag = tag;
        this->position = position;
        this->texture = texture;
    }

} Tile2D;

class TileSetComponent : public Component
{
private: 

    // PRIVATE FUNCTION

    /// @brief Private Function to Load Level 
    void LoadLevel(std::string levelName);

    /// @brief
    void CheckCollisionTiles();

protected:

    // FILE VARIABLE(s)
    ifstream m_InFile;
    std::string m_LevelName;

    Texture2D m_GroundTile;
    Texture2D m_EmptyTile;

    // CHARACTER/LEVEL VARIABLE(s)
    Vector2 m_PlayerStartPosition;
    std::vector<Vector2> m_SpawnPositions;

    std::vector<Tile> m_TileArray; // Drawing Tiles
    std::vector<Rectangle> m_CollisionArray; // Cache tile collisions

    // EXTRA LEVEL VARIABLE(s)
    Vector2 m_TilePosition;
    const float m_TileSize;
    const Vector2 m_TileDemnsion{LEVEL_HEIGHT, LEVEL_LENGTH}; // NOTE: How Long and How High the level is 
    
    // ARRAY LEVEL VARIABLE(s)
    char m_LevelArray[LEVEL_HEIGHT][LEVEL_LENGTH];
    int m_LevelIterator;

public:

    // CLASS FUNCTION(s)

    /// @brief Custom Constructor for Class 
    TileSetComponent(int level);

    /// @brief Default Destructor for Class
    virtual ~TileSetComponent() { };


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    virtual void Draw() override;


    // EXTRA FUNCTION(s)

    /// @brief Extra function for unloads texture of tile map
    void UnloadTextureVariables();


    // GETTER FUNCTION(s)
    
    /// @brief Getter function for the Collidable tiles 
    std::vector<Rectangle> GetCollisionTiles() { return m_CollisionArray; }

    /// @brief Getter function for All tiles 
    std::vector<Tile> GetAllTiles() { return m_TileArray; }

};

#endif