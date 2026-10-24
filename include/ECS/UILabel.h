#pragma once

#include "../AssetManager.h"
#include "../Game.h"
#include "ECS.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
public:
  UILabel(int xpos, int ypos, const std::string &text, FontId font,
          SDL_Color &colour);
  ~UILabel() override;

  void SetLabelText(const std::string &text, FontId font);
  void draw() override;

private:
  SDL_Rect position;
  std::string labelText;
  FontId labelFont;
  SDL_Color textColour;
  SDL_Texture *labelTexture;
};
