#include "EnemyObject.h"

EnemyObject::EnemyObject(std::string tag, std::string name, Transform2Utility transform, float health, float damage, float speed, float maxJump, Texture2D spriteSheet) 
{
    
}

void EnemyObject::Update(float DeltaTime) 
{
    // BASE UPDATE
    // Character::Update(DeltaTime);
    
    // m_LevelRef->GetCollisionTiles()[0]; // NEEDED THIS FOR ENEMIES RUNNING BACK AND FORTH

    // m_Transform.position.x -= ENEMY_SPEED_HORIZONTAL * DeltaTime;

    // TODO: Enemy Collision with the Player
    // TODO: Enemy Attacking 

}

void EnemyObject::Draw() 
{
    
}

