#include <SDL2/SDL.h>
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char *argv[]) {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      std::cerr << "FATAL: Cannot init SDL: " << SDL_GetError();
      return -1;
    }

    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();  // Store the results in a variable

    SDL_Quit();  // Quit SDL properly
    return result;  // Return the result, as required by google test
}