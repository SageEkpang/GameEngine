// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// CUSTOM INCLUDE(s)
#include "GameScreen.h"

class End : public GameScreen
{
private:
public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    End(std::string screenName);

    /// @brief Default Destructor for Class
    ~End();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float DeltaTime);

    /// @brief Default Draw function for Class
    void Draw();

};
