#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

// NOTE: NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include <iostream>

class AudioManager
{
private:


public:

	// CLASS FUNCTION(s)
	AudioManager();
	~AudioManager();

	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime);
	virtual void Draw();

};

#endif