#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

#include <typeinfo>
#include <typeindex>
#include <cassert>

using namespace std;

// GAME STATE ENUMS
enum GameState{ // TODO:: Need a way to handle the screen exiting out of application
    STATE_NONE = 0,
    STATE_TITLE = 1,
    STATE_MENU  = 2,
    STATE_LEVEL_SELECT = 3,
    STATE_GAME = 4,
    STATE_END = 5
};

// GAME CURRENT SCREEN STATE ENUMS
enum ScreenState
{
    SCREEN_NEXT = 1,
    SCREEN_CURRENT = 0,
    SCREEN_PREVIOUS = -1
};

// DATA VARIABLE STRUCT(s)

typedef struct Vector2Utility
{
    float x;
    float y;

    // Conversions
    Vector2 vec2 = Vector2{x, y};

    Vector2Utility(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Vector2Utility &value) const
    {
        return (this->x == value.x && this->y == value.y);
    }

    Vector2Utility operator++()
    {
        ++this->x;
        ++this->y;
        return *this;
    }

    Vector2Utility operator--()
    {
        --this->x;
        --this->y;
        return *this;
    }

    Vector2Utility operator=(const Vector2Utility &value)
    {
        this->x = value.x;
        this->y = value.y;
        return *this;
    }

    Vector2Utility operator+=(const Vector2Utility &value)
    {
        this->x += value.x;
        this->y += value.y;
        return *this;
    }

    Vector2Utility operator+=(const float &value)
    {
        this->x += value;
        this->y += value;
        return *this;
    }

    Vector2Utility operator-=(const Vector2Utility &value)
    {
        this->x -= value.x;
        this->y -= value.y;
        return *this;
    }

    Vector2Utility operator-=(const float &value)
    {
        this->x -= value;
        this->y -= value;
        return *this;
    }

    // Vector2Utility Normalise()
    // {

    // }

    // Operator Overloads (default)

    Vector2Utility operator/(const Vector2Utility &value)
    {
        return Vector2Utility(this->x / value.x, this->y / value.y);
    }

    Vector2Utility operator+(const Vector2Utility &value)
    {
        return Vector2Utility(value.x + this->x, value.y + this->y);
    }

    Vector2Utility operator+(const float &value)
    {
        return Vector2Utility(value + this->x, value + this->y);
    }

    Vector2Utility operator-(const Vector2Utility &value)
    {
        return Vector2Utility(this->x - value.x, this->y - value.y);
    }

    Vector2Utility operator-(const float &value)
    {
        return Vector2Utility(this->x - value, this->y - value);
    }

    Vector2Utility operator*(const Vector2Utility &value)
    {
        return Vector2Utility( value.x * this->x, value.y * this->y);
    }

    Vector2Utility operator*(const float &value)
    {
        return Vector2Utility( value * this->x, value * this->y);
    }

} Vector2Utility;

typedef struct Vector3Utility
{
    float x;
    float y;
    float z;

    Vector3Utility(float x = 0, float y = 0, float z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

} Vector3Utility;

typedef struct Transform2Utility
{
    Transform2Utility* parent;
    Vector2Utility position;
    Vector2Utility scale;
    float rotation;

    Transform2Utility(Transform2Utility* parent = nullptr, Vector2Utility position = Vector2Utility(), Vector2Utility scale = Vector2Utility(), float rotation = 0)
    {
        parent = new Transform2Utility();
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }

} Transform2Utility;

typedef struct Transform3Utility
{
    Transform3Utility* parent;
    Vector3Utility position;
    Vector3Utility scale;
    Vector3Utility rotation;

    Transform3Utility(Transform3Utility* parent = nullptr, Vector3Utility position = Vector3Utility(), Vector3Utility scale = Vector3Utility(), Vector3Utility rotation = Vector3Utility())
    {
        parent = new Transform3Utility();
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }

} Transform3Utility;

#endif