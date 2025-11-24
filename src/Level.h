#pragma once
#pragma once
#include "raylib.h"
#include <vector>

// Forward declaration
class Enemy;

struct Tile {
  Rectangle rect;
  int type; // 0: empty, 1: ground, 2: brick, 3: question
  bool hasSword;
  bool hit;
  float hitAnimTimer;
  bool spawningItem;
  float spawnAnimTimer;
  Vector2 spawnItemPos;
};

struct Sword {
  Rectangle rect;
  int id;
  bool collected;
};

class Level {
public:
  Level();
  ~Level();

  void Update(float dt);
  void Draw();
  void DrawBackground(float cameraX);
  void Reset(); // Reset level to initial state
  const std::vector<Tile> &GetTiles() const;
  const std::vector<Sword> &GetSwords() const;
  std::vector<Enemy*> &GetEnemies();
  const std::vector<Enemy*> &GetEnemies() const;
  void CollectSword(int id) const;
  void HitBox(Rectangle playerRect, float velocityY);
  void CheckEnemyCollisions(Rectangle playerRect, bool isAttacking);
  float GetGameTimer() const { return gameTimer; }
  bool IsGameOver() const { return gameOver; }

private:
  std::vector<Tile> tiles;
  mutable std::vector<Sword> swords;
  std::vector<Enemy*> enemies;
  Texture2D tileset;
  Texture2D background;
  Texture2D landmarks;
  Texture2D swordTexture;

  float gameTimer; // Countdown from 180 seconds
  bool gameOver;
  int nextSwordId;

  void InitializeTiles(); // Helper method to initialize tiles
  void SpawnEnemies(); // Spawn enemies at specific locations
};
