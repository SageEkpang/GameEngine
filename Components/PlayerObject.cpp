#include "PlayerObject.h"

PlayerObject::PlayerObject(std::string tag, std::string name, Transform2D transform, float health, float damage, float speed, float maxJump, Texture2D spriteSheet, Level* level) 
: Character(tag = "Player")
{
    m_IsGrounded = false;
}

PlayerObject::PlayerObject(std::string tag, std::string name, Vector2 position, float rotation, Vector2 size, float health, float damage, float speed, float maxJump, Texture2D spriteSheet, Level* level) 
: Character(tag = "Player")
{
    m_IsGrounded = false;
}

void PlayerObject::Update(float DeltaTime) 
{
    // PLAYER INPUT(s)

    // MOVEMENT
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
    { 
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
    { 
 
    }
    else
    {
    }

    // JUMP
    if (m_JumpCount == m_MaxJumps) { m_CanJump = false; }

    if (IsKeyPressed(KEY_SPACE)) 
    { 
        m_Speed = -PLAYER_JUMP_SPEED;
    }
    else
    {
    }

}

void PlayerObject::Draw() 
{
    // Flip sprite by manipulating the source rect
    Rectangle Source = Rectangle{m_Animate, (float)(16.7 * m_MoveDown), (float)(25 * Flip), 16.7}; // Rectangle Source = Rectangle{0, 0, m_Transform.size.x, m_Transform.size.y}; // x = 25, y = 16.5 (nth number of 4.25)
    Rectangle Destination = Rectangle{m_Transform.position.x, m_Transform.position.y, m_Transform.size.x, m_Transform.size.y};
    DrawTexturePro(m_CharacterSpriteSheet, Source, Destination, Vector2{0, 0}, 0, WHITE);
}