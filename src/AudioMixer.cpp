#include "AudioMixer.h"
#include "AssetManager.h"
#include "Config.h"
#include <stdio.h>

using namespace Config;

AudioMixer::AudioMixer() : musicVolume(DEFAULT_VOLUME), gMusic(nullptr) {
  // Initialize SDL_mixer
  if (Mix_OpenAudio(MIX_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
           Mix_GetError());
  }

  // Load music and sfx
  gMusic = Mix_LoadMUS("assets/audio/placeholder.mp3");
  if (gMusic == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }

  // Load sound effects into map
  soundEffects[GAME_OVER] = Mix_LoadWAV("assets/audio/snoring_sfx.mp3");

  if (Mix_PlayingMusic() == 0) {
    // Play the music; commenting this out until I get a better track on loop
    Mix_PlayMusic(gMusic, -1);
  }
}

AudioMixer::~AudioMixer() {
  for (auto &[name, chunk] : soundEffects) {
    if (chunk != nullptr) {
      Mix_FreeChunk(chunk);
    }
  }
  soundEffects.clear();
  Mix_FreeMusic(gMusic);
  Mix_Quit();
}

// Play a sound from the list of sound effects.
// TODO: Designate a channel
void AudioMixer::playSound(SoundEffect sound) {
  // Only works on SDL_mixer-2.6.0 and above:
  // int setVol = Mix_MasterVolume(10);
  int setVol = Mix_Volume(1, 10);
  auto it = soundEffects.find(sound);
  if (it != soundEffects.end()) {
    Mix_Chunk *gSound = it->second;
    if (gSound == NULL)
      return;
    Mix_PlayChannel(CHANNEL_SOUNDS, gSound, 0);
  }
}