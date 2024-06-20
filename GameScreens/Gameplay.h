// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// CUSTOM INCLUDE(s)
#include "GameScreen.h"

// GAME INCLUDE(s)


class Gameplay : public GameScreen
{
private:

    // Player* m_Player;
    // LevelComponent* m_PlayLevel;

    bool m_IsLoaded;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    Gameplay();

    /// @brief Default Destructor for Class
    ~Gameplay();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;


    // HELPER FUNCTION(s)

    /// @brief Helper function to Load Content
    void LoadContent();

};