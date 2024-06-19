// NEEDED INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// CUSTOM INCLUDE(s)
#include "GameScreen.h"

class Title : public GameScreen
{
private:

    

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    Title();

    /// @brief Default Destructor for Class
    ~Title();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float DeltaTime);

    /// @brief Default Draw function for Class
    void Draw();

};