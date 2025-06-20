#ifndef AUDIO_COMPONENT_H
#define AUDIO_COMPONENT_H

#include "ComponentEntity.h"
#include <iostream>

class AudioComponent : public ComponentEntity
{
private:





public:

	// CLASS FUNCTION(s)
	AudioComponent();
	~AudioComponent();


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw();


	// ADDITIONAL FUNCTION(s)	
	void PlayAudio();
	void StopAudio();
	void PlaySoundTrack();

};

#endif