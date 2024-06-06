#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() 
{
}

CollisionComponent::~CollisionComponent() 
{
}

void CollisionComponent::Update(float deltaTime) 
{ 

    // // FIXME: Need to change this to the interpentration tests
    // // TODO: NEED TO PUT IN OWN COLLIDER CLASS

    // // CHECK POSITIONS (Default Positions)
    // Vector2 HeadPosition = Vector2{m_Transform->GetPosition().x + (m_Transform->GetScale().x / 2), m_Transform->GetPosition().y}; // Centre of the Head
    // Vector2 LeftPosition = Vector2{m_Transform->GetPosition().x, m_Transform->GetPosition().y + (m_Transform->GetScale().y / 2)}; // Centre of the Left Side
    // Vector2 RightPosition = Vector2{m_Transform->GetPosition().x + m_Transform->GetScale().x,  m_Transform->GetPosition().y + (m_Transform->GetScale().y / 2)}; // Centre of the Right Side
    // Vector2 BottomPosition = Vector2{m_Transform->GetPosition().x + (m_Transform->GetScale().x / 2),  m_Transform->GetPosition().y + m_Transform->GetScale().y}; // Centre of the Bottom


    // // CHECK POSITIONS (Corner Positions)

    // // TOP
    // Vector2 TopRightPosition = Vector2{m_Transform->GetPosition().x + m_Transform->GetScale().x - (float)(m_Transform->GetScale().x / 4), m_Transform->GetPosition().y};
    // Vector2 TopLeftPosition = Vector2{m_Transform->GetPosition().x + (float)(m_Transform->GetScale().x / 4), m_Transform->GetPosition().y};

    // // LEFT
    // Vector2 LeftTopPosition = Vector2{m_Transform->GetPosition().x, m_Transform->GetPosition().y + (m_Transform->GetScale().y / 2) - (float)(m_Transform->GetScale().y / 4)};
    // Vector2 LeftBottomPosition = Vector2{m_Transform->GetPosition().x, m_Transform->GetPosition().y + (m_Transform->GetScale().y / 2) + (float)(m_Transform->GetScale().y / 4)};

    // // RIGHT
    // Vector2 RightTopPosition = Vector2{m_Transform->GetPosition().x + m_Transform->GetScale().x, m_Transform->GetPosition().y + (m_Transform->GetScale().y / 2) - (float)(m_Transform->GetScale().y / 4)};
    // Vector2 RightBottomPosition = Vector2{m_Transform->GetPosition().x + m_Transform->GetScale().x, m_Transform->GetPosition().y + (m_Transform->GetScale().y / 2) + (float)(m_Transform->GetScale().y / 4)};

    // // BOTTOM
    // Vector2 BottomRightPosition = Vector2{m_Transform->GetPosition().x + m_Transform->GetScale().x - (float)(m_Transform->GetScale().x / 4), m_Transform->GetPosition().y + m_Transform->GetScale().y};
    // Vector2 BottomLeftPosition = Vector2{m_Transform->GetPosition().x + (float)(m_Transform->GetScale().x / 4), m_Transform->GetPosition().y + m_Transform->GetScale().y};

    // // COLLISION CHECKS
    // for (size_t i = 0; i < m_LevelRef->GetCollisionTiles().size(); ++i)
    // {

    //     // HEAD CHECK(s)
    //     if (CheckCollisionCircleRec(HeadPosition, 3, m_LevelRef->GetCollisionTiles()[i]) ||
    //         CheckCollisionCircleRec(TopRightPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(TopLeftPosition, 3, m_LevelRef->GetCollisionTiles()[i])) 
    //     { 
    //         m_Speed = +GRAVITY_DOWNFORCE;
    //     }
    //     else
    //     {
    //     }

    //     // RIGHT CHECK
    //     if (CheckCollisionCircleRec(RightPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(RightTopPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(RightBottomPosition, 3, m_LevelRef->GetCollisionTiles()[i])) 
    //     { 
    //         m_Transform->SetPosition(
    //             Vector2{
    //             m_LevelRef->GetCollisionTiles()[i].x - m_Transform->GetScale().x - 1, 
    //             m_Transform->GetPosition().y
    //         }
    //         );
    //     }
    //     else
    //     {
    //     }
    
    //     // LEFT CHECK
    //     if (CheckCollisionCircleRec(LeftPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(LeftTopPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(LeftBottomPosition, 3, m_LevelRef->GetCollisionTiles()[i]))
    //     { 
    //         m_Transform->SetPosition(
    //             Vector2{
    //             m_LevelRef->GetCollisionTiles()[i].x + m_Transform->GetScale().x + 1,
    //             m_Transform->GetPosition().y
    //         }
    //         );
    //     }
    //     else
    //     {
    //     }

    //     // BOTTOM CHECK
    //     if ((CheckCollisionCircleRec(BottomPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(BottomRightPosition, 3, m_LevelRef->GetCollisionTiles()[i]) || 
    //         CheckCollisionCircleRec(BottomLeftPosition, 3, m_LevelRef->GetCollisionTiles()[i])))
    //     {
    //         m_Speed = 0.0f;
    //         m_Transform->SetPosition(
    //             Vector2{
    //                 m_Transform->GetPosition().x,
    //                 m_LevelRef->GetCollisionTiles()[i].y - m_Transform->GetScale().y
    //             }
    //         );
    //     }
    //     else
    //     {
    //         m_Transform->MoveDown(m_Speed * DeltaTime);
    //         m_Speed += GRAVITY_DEFAULT * DeltaTime;
    //     }
    // }
}

void CollisionComponent::Draw() 
{
}
