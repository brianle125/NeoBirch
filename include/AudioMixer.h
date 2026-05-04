#pragma once
#include <SDL_mixer.h>
#include <map>
#include <memory>

typedef enum { GAME_WON, GAME_OVER } SoundEffect;
static constexpr int DEFAULT_VOLUME = 20;

class AudioMixer {
public:
  AudioMixer();
  ~AudioMixer();
  void playSound(SoundEffect sound);

private:
  int musicVolume;
  Mix_Music *gMusic;
  std::map<SoundEffect, Mix_Chunk *> soundEffects;
};