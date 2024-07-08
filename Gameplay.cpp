#include "Gameplay.h"

Gameplay::Gameplay(std::string screenName) 
: GameScreen(screenName) 
{
    m_Camera.zoom = 1.0f;
}

Gameplay::~Gameplay() 
{
    // m_PlayLevel = nullptr;
    // delete m_PlayLevel;
    
    // m_Player = nullptr;
    // delete m_Player;
}

void Gameplay::Update(float DeltaTime) 
{
    // LOAD GAME CONTENT

    // LoadContent();

    // MAIN UPDATE

    // m_Player->Update(DeltaTime);
    
    // Vector2 CameraTargetPosition = Vector2{Lerp(m_Camera.target.x, m_Player->GetPosition().x - (SCREEN_WIDTH / 2), 0.05), Lerp(m_Camera.target.y, m_Player->GetPosition().y - (SCREEN_HEIGHT / 2), 0.05)};
    // m_Camera.target = CameraTargetPosition;

    // if (IsKeyReleased(KEY_ENTER))
    // {
    //     // m_GameInfo.State = GameState::STATE_END;
    //     m_GameInfo.ScState = ScreenState::SCREEN_NEXT;
    //     m_IsLoaded = false;
    //     // m_GameInfo.ScState = ScreenState::SCREEN_NEXT;
    // }
}

void Gameplay::Draw() 
{
    // if (m_IsLoaded == true)
    // {
    //     m_PlayLevel->Draw();
    //     m_Player->Draw(); 
    // }
}

void Gameplay::LoadContent() 
{
    // // LOADS THE LEVEL
    // if (m_IsLoaded == false)
    // {

    //     // LOAD PLAYER CONTENT

    //     m_PlayLevel = new Level(m_GameCopy.LevelIndex);

    //     // If there are size problems, check the character base class
    //     Texture2D m_PlayerSprite = LoadTexture("Images/Player/PlayerSpriteSheet.png");
    //     // Transform2D PlayerTransform(Vector2{100, 600}, Vector2{100, 100}, 0);
        
    //     m_Player = new Player("Player", "Chief", PlayerTransform, 100, 50, 10, 2, m_PlayerSprite, m_PlayLevel);


    //     // LOAD ENEMY CONTENT




    //     // LOAD ENVIRONMENT CONTENT



    //     m_IsLoaded = true;
    // }
}
