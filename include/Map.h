#pragma once
#include <string>
#include "AssetManager.h"

class Map {
public:
  Map(TextureId tID, int ms, int ts);
  ~Map();

  void LoadMap(const std::string &path, int sizeX, int sizeY);
  void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
  TextureId texID;
  int mapScale;
  int tileSize;
  int scaledSize;
};
