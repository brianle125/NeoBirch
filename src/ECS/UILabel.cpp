#include "ECS/UILabel.h"

UILabel::UILabel(int xpos, int ypos, const std::string &text, FontId font,
                 SDL_Color &colour)
    : labelText(text), labelFont(font), textColour(colour) {
  position.x = xpos;
  position.y = ypos;

  SetLabelText(labelText, labelFont);
}

UILabel::~UILabel() = default;

void UILabel::SetLabelText(const std::string &text, FontId font) {
  SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(
      Game::assets->GetFont(font), text.c_str(), textColour, 0);
  labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
  SDL_FreeSurface(surf);

  SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
}

void UILabel::draw() {
  SDL_RenderCopy(Game::renderer, this->labelTexture, nullptr, &position);
  SDL_DestroyTexture(this->labelTexture);
}