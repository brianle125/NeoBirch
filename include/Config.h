#pragma once

#include "SDL.h"

namespace Config {
// Window
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 640;
constexpr bool FULLSCREEN = false;
constexpr const char *WINDOW_TITLE = "BirchEngine Revamped";

// Performance
constexpr int FPS = 60;

// Camera
constexpr int CAMERA_WIDTH = 1600;
constexpr int CAMERA_HEIGHT = 1280;
constexpr SDL_Rect CAMERA_CONFIG = {0, 0, CAMERA_WIDTH, CAMERA_HEIGHT};

constexpr int CAMERA_OFFSET_X = 400; // Half of WINDOW_WIDTH
constexpr int CAMERA_OFFSET_Y = 320; // Half of WINDOW_HEIGHT

// Map
constexpr int TILE_SIZE = 32;
constexpr int MAP_SCALE = 3;
constexpr int MAP_WIDTH = 25;
constexpr int MAP_HEIGHT = 20;

// Player
constexpr float PLAYER_START_X = 800.0f;
constexpr float PLAYER_START_Y = 640.0f;
constexpr int PLAYER_WIDTH = 32;
constexpr int PLAYER_HEIGHT = 32;
constexpr int PLAYER_SCALE = 3;

constexpr int PLAYER_HEALTH = 50;

// Fonts
constexpr int FONT_SIZE_SMALL = 16;

// Audio
constexpr int MIX_FREQUENCY = 44100;
constexpr int CHANNEL_MUSIC = -1;
constexpr int CHANNEL_SOUNDS = 0;
} // namespace Config