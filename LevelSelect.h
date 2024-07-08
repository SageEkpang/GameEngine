#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// CUSTOM INCLUDE(s)
#include "GameScreen.h"
#include "GameObject.h"

class LevelSelect : public GameScreen
{
private:

    // std::vector<GameObject*> m_LevelSelectButtons;
    
public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    LevelSelect(std::string screenName);

    /// @brief Default Destructor for Class
    ~LevelSelect();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float DeltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;


    // HELPER FUNCTION(s)
    void LoadContent();

};

#endif