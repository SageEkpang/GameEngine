#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(std::string tag, std::string name, Transform2D transform, float health, float damage, float speed, float maxJump, Texture2D spriteSheet, Level* level) 
: Character(tag = "Enemy", name, transform, health, damage, speed, maxJump, spriteSheet, level)
{
}

Enemy::Enemy(std::string tag, std::string name, Vector2 position, float rotation, Vector2 size, float health, float damage, float speed, float maxJump, Texture2D spriteSheet, Level* level) 
: Character(tag = "Enemy", name, position, rotation, size, health, damage, speed, maxJump, spriteSheet, level)
{
}

void Enemy::Update(float DeltaTime) 
{
    // BASE UPDATE
    Character::Update(DeltaTime);
    
    // m_LevelRef->GetCollisionTiles()[0]; // NEEDED THIS FOR ENEMIES RUNNING BACK AND FORTH

    m_Transform.position.x -= ENEMY_SPEED_HORIZONTAL * DeltaTime;

    // TODO: Enemy Collision with the Player
    // TODO: Enemy Attacking 

}

void Enemy::Draw() 
{
    
}
