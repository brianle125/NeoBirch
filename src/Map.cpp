#include "Map.h"
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "Game.h"
#include <fstream>

extern Manager manager;

namespace {
struct TerrainColliderSpec {
  int x;
  int y;
  int w;
  int h;
};

TerrainColliderSpec GetTerrainColliderSpec(int terrainType, int tileX, int tileY,
                                          int scaledSize) {
  const int halfSize = scaledSize / 2;

  switch (terrainType) {
  case 1:
    return {tileX * scaledSize, tileY * scaledSize, scaledSize, scaledSize};
  case 2:
    return {tileX * scaledSize, tileY * scaledSize, scaledSize, halfSize};
  case 3:
    return {tileX * scaledSize, tileY * scaledSize + halfSize, scaledSize,
            halfSize};
  case 4:
    return {tileX * scaledSize, tileY * scaledSize, halfSize, scaledSize};
  case 5:
    return {tileX * scaledSize + halfSize, tileY * scaledSize, halfSize,
            scaledSize};
  default:
    return {0, 0, 0, 0};
  }
}
} // namespace

Map::Map(TextureId tID, int ms, int ts)
    : texID(tID), mapScale(ms), tileSize(ts) {
  scaledSize = ms * ts;
}

Map::~Map() {}

void Map::LoadMap(const std::string &path, int sizeX, int sizeY) {
  char c;
  std::fstream mapFile;
  mapFile.open(path);

  int srcX, srcY;

  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      mapFile.get(c);
      srcY = (c - '0') * tileSize;
      mapFile.get(c);
      srcX = (c - '0') * tileSize;
      AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
      mapFile.ignore();
    }
  }

  mapFile.ignore();

  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      mapFile.get(c);
      const int terrainType = c - '0';
      if (terrainType > 0) {
        const auto spec = GetTerrainColliderSpec(terrainType, x, y, scaledSize);
        if (spec.w > 0 && spec.h > 0) {
          auto &tcol(manager.addEntity());
          tcol.addComponent<ColliderComponent>("terrain", spec.x, spec.y,
                                               spec.w, spec.h);
          tcol.addGroup(Game::groupColliders);
        }
      }
      mapFile.ignore();
    }
  }

  mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale,
                                   texID);
  tile.addGroup(Game::groupMap);
}