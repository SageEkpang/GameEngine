// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// CUSTOM INCLUDE(s)
#include "GameScreen.h"

class Gameplay : public GameScreen
{
private:

    // Player* m_Player;
    // LevelComponent* m_PlayLevel;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    Gameplay(std::string screenName);

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