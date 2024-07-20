#include "TileSetComponent.h"

TileSetComponent::TileSetComponent(int level, int layerIndex) 
: m_TileSize(TILE_SIZE)
{
    m_LayerIndex = layerIndex;

    m_ID = "Level";
    std::string Temp = to_string(level);
    m_LevelName = "Levels/Level" + Temp + ".txt";

    std::string TempLevelGround = "\0";

    // Load Different Tiles for Levels
    switch (level)
    {
        case 1 :
        case 2 :
        case 3 :
            TempLevelGround = "Images/Tile/GroundTile.png";
        break;

        case 4 :
        case 5 :
        case 6 :
            TempLevelGround = "Images/Tile/EmberGroundTile.png";
        break;

        case 7 :
        case 8 : 
        case 9 :
            TempLevelGround = "Images/Tile/SnowGroundTile.png";
        break;

    default:
            TempLevelGround = "Images/Tile/Default.png";
        break;
    }

    m_GroundTile = LoadTexture(TempLevelGround.c_str());
    m_GroundTile.mipmaps = 2;
    m_GroundTile.width = m_TileSize;
    m_GroundTile.height = m_TileSize;

    m_EmptyTile = LoadTexture("Images/Tile/EmptyTile.png");
    m_EmptyTile.width = m_TileSize;
    m_EmptyTile.height = m_TileSize;

    LoadLevel(m_LevelName);
    CheckCollisionTiles();
}

void TileSetComponent::Update(float DeltaTime) 
{
    
}

void TileSetComponent::Draw() 
{
    for (size_t i = 0; i < m_TileArray.size(); ++i)
    {
        DrawTextureV(m_TileArray[i].texture, m_TileArray[i].position, WHITE);
    }

    // DEBUG
    // if (IsKeyDown(KEY_U))
    // {
    //     for (size_t i = 0; i < m_CollisionArray.size(); ++i)
    //     {
    //         DrawRectangle(m_CollisionArray[i].x, m_CollisionArray[i].y, m_CollisionArray[i].width, m_CollisionArray[i].height, RED);
    //     }
    // }
}

void TileSetComponent::LoadLevel(std::string levelName) 
{
    // LOAD CHARS FROM FILE
    m_InFile.open(m_LevelName, ios::in);

    if (m_InFile.is_open())
    {
        for (int i = 0; i < LEVEL_HEIGHT; ++i)
        {
            for (int j = 0; j < LEVEL_LENGTH; ++j)
            {
                char TempChar = '\0';
                m_InFile >> TempChar;
                m_LevelArray[i][j] = TempChar;
            }
        }
    }
    else
    {
        DrawText("File is Not Open", 100, 100, 40, RED);
    }
    m_InFile.close();

    // LOAD POSITIONS OF TILES INTO DYNAMIC ARRAYS
    for (int i = 0; i < m_TileDemnsion.x; ++i)
    {
        for (int j = 0; j < m_TileDemnsion.y; ++j)
        {
            m_TilePosition = Vector2{(float)j * m_TileSize, (float)i * m_TileSize}; 

            switch (m_LevelArray[i][j])
            {
                case 'E': m_TileArray.push_back(Tile("Empty", m_TilePosition, m_EmptyTile)); break;
                case 'G': m_TileArray.push_back(Tile("Ground", m_TilePosition, m_GroundTile)); break;
                default: m_TileArray.push_back(Tile("Empty", m_TilePosition, m_EmptyTile)); break;
            }
        }
    }
}

void TileSetComponent::CheckCollisionTiles() 
{
    Vector2Utility Point = Vector2Utility();
    Vector2Utility PointPositions[4] = 
    {
        Vector2Utility{0, -1}, // Up
        Vector2Utility{1, 0}, // Right
        Vector2Utility{0, 1}, // Down
        Vector2Utility{-1, 0} // Left
    };

    for (size_t i = 0; i < m_TileArray.size(); ++i)
    {
        // Check if tile is empty
        if (m_TileArray[i].tag == "Empty") continue;

        Vector2 TempPosition = Vector2{m_TileArray[i].position.x + (m_TileSize / 2), m_TileArray[i].position.y + (m_TileSize / 2)};

        // Cache tiles that SHOULD have collision on them
        for (int j = 0; j < 4;)
        {
            Vector2 TempPoint = Vector2{Point.x, Point.y};
            // Set Point to Intersect with tiles
            TempPoint = Vector2Add(TempPosition, Vector2{PointPositions[j].x * m_TileSize, PointPositions[j].y * m_TileSize});

            // Check if there is a collision
            if (CheckCollisionPointRec(TempPoint, Rectangle{TempPosition.x, TempPosition.y, m_TileSize, m_TileSize}))
            {
                ++j;
            }
            else
            {
                // Set Collision to true if there are no other collidable tiles around it
                m_CollisionArray.push_back(Rectangle{TempPosition.x - (m_TileSize / 2), TempPosition.y - 50, m_TileSize, m_TileSize});
                break;
            }
        }
    }
}

void TileSetComponent::UnloadTextureVariables() 
{
    UnloadTexture(m_EmptyTile);
    UnloadTexture(m_GroundTile);
}
