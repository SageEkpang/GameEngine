#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

/*
    #include "PlayerComponent.h"
    #include "EnemyComponent.h"
    #include "CharacterComponent.h"
*/

// GAME OBJECTS(s)
#include "GameObject.h"


// GAME COMPONENTS(s)
#include "CameraComponent.h"
#include "ButtonComponent.h"
#include "TileSetComponent.h"
#include "UIComponent.h"
#include "RenderComponent.h"

class GameObjectManager
{
private:
    
    // PRIVATE VARIABLE(s)
    std::vector<GameObject*> m_GameObjects;
    std::vector<CameraComponent*> m_Cameras; int m_CameraIndex = 0;
    CameraComponent* m_Camera;

    // PRIVATE FUNCTION(s)
    void AddCamera(CameraComponent camera) { m_Cameras.push_back(&camera); } // Add Camera to Specific Screen (Takes in camera, takes in Game Screen)
    
    void AddGameScreen(); // Add Game Screen (GameScreen, Enum Screen Value (Might have to be a string))


    void ProcessGameObject(float deltaTime); // Update / Process Game Object
    void ProcessCharacter(float deltaTime); // Update / Process Character
    void ProcessPlayer(float deltaTime); // Update / Process Player
    void ProcessEnemy(float deltaTime); // Update / Process Enemy
    void ProcessComponents(float deltaTime); // Update / Process Components
    void ProcessGameScreen(float deltaTime); // Update / Process Game Screen


    void ShowcaseGameObject(); // Render / Showcase Game Object
    void ShowcaseCharacter(); // Render / Showcase Character
    void ShowcasePlayer(); // Render / Showcase Player
    void ShowcaseEnemy(); // Render / Showcase Enemy
    void ShowcaseComponents(); // Render / Showcase Components
    void ShowcaseGameScreen(); // Render / Showcase Game Screen

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameObjectManager();

    /// @brief Default Destructor for Class
    ~GameObjectManager();

    /// @brief Helper Destructor for Class
    void Destroy();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Process(float deltaTime);

    /// @brief Default Draw function for Class
    void Showcase();


    // CAMERA FUNCTION(s)
    void SetDefaultCamera(Camera2D* defaultCamera) { m_Camera->SetCamera2D(defaultCamera); }
    void IncrementCameraIndex();
    void DecrementCameraIndex();
    int CameraCount() { m_Cameras.size(); };
    Camera2D GetCurrentCamera() { return m_Cameras[m_CameraIndex]->GetCamera2D();}


    // SETTER FUNCTION(s)
    void AddGameObject(GameObject gameObject) { m_GameObjects.push_back(&gameObject); } // Add GameObject to Specific Screen, (Takes in Game Object, Takes in Screen it coresponds to)

    void AddCharacter(); // Add GameObject that acts like Character (Takes in Character) (Character, Level)
    void AddPlayer(); // Add GameObject that acts like Player (Takes in Player) (Player, Level)
    void AddEnemy(); // Add GameObject that acts like Enemy (Takes in Enemy) (Enemy, Level)

};

#endif