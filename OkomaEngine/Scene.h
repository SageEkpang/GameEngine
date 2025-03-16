#ifndef SCENE_H
#define SCENE_H

#include "HeaderManager.h"

class Scene
{
protected: // PROTECTED VARIABLE(s)

	char* m_Name;
	Camera2D m_Camera;

public:

	// CLASS FUNCTION(s)
	Scene(char* name) { strcpy_s(m_Name, strlen(name), name); }
	virtual ~Scene() { }


	// BASE FUNCTION(s)
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	// GETTER FUNCTION(s)
	inline char* GetName() const { return m_Name; } 

	// SETTER FUNCTION(s)
	inline void SetName(char* name) const { strcpy_s(m_Name, strlen(name), name); }

};

#endif
