#include "Level.h"
#include "Enemy.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <math.h>

Level::Level() {
  // Load tileset
  tileset = LoadTexture("assets/tiles.png");
  background = LoadTexture("assets/background.png");
  landmarks = LoadTexture("assets/landmarks.png");
  swordTexture = LoadTexture("assets/sword.png");

  // Initialize game timer (3 minutes = 180 seconds)
  gameTimer = 180.0f;
  gameOver = false;
  nextSwordId = 0;

  InitializeTiles();
}

void Level::InitializeTiles() {
  // Clear existing tiles and swords
  tiles.clear();
  swords.clear();

  // Random seed
  SetRandomSeed(GetTime());

  // Track all question blocks for sword assignment
  std::vector<int> questionBlockIndices;

  // Ground - Extended map like Mario Bros (3000 blocks = ~96,000 pixels)
  for (int i = 0; i < 3000; i++) {
    Tile tile;
    tile.rect = {(float)i * 32, 400, 32, 32};
    tile.type = 1; // Ground
    tile.hasSword = false;
    tile.hit = false;
    tile.hitAnimTimer = 0.0f;
    tile.spawningItem = false;
    tile.spawnAnimTimer = 0.0f;
    tile.spawnItemPos = {0, 0};
    tiles.push_back(tile);

    // Add bottom layer
    Tile tile2;
    tile2.rect = {(float)i * 32, 432, 32, 32};
    tile2.type = 1;
    tile2.hasSword = false;
    tile2.hit = false;
    tile2.hitAnimTimer = 0.0f;
    tile2.spawningItem = false;
    tile2.spawnAnimTimer = 0.0f;
    tile2.spawnItemPos = {0, 0};
    tiles.push_back(tile2);

    // Random obstacles (start after x=20 to give space)
    if (i > 20 && i < 2950) { // Leave space for castle at end
      int r = GetRandomValue(0, 100);

      // 5% chance of a pipe (Lower height)
      if (r < 5) {
        int height = GetRandomValue(1, 2);
        for (int h = 0; h < height; h++) {
          Tile pipe;
          pipe.rect = {(float)i * 32, (float)(368 - h * 32), 32, 32};
          pipe.type = 3;
          pipe.hasSword = false;
          pipe.hit = false;
          pipe.hitAnimTimer = 0.0f;
          pipe.spawningItem = false;
          pipe.spawnAnimTimer = 0.0f;
          pipe.spawnItemPos = {0, 0};
          tiles.push_back(pipe);
        }
      }
      // 10% chance of a floating platform
      else if (r < 15) {
        int height = 250;
        int length = GetRandomValue(3, 5);
        for (int l = 0; l < length; l++) {
          Tile plat;
          plat.rect = {(float)(i + l) * 32, (float)height, 32, 32};
          plat.type = 2;
          plat.hasSword = false;
          plat.hit = false;
          plat.hitAnimTimer = 0.0f;
          plat.spawningItem = false;
          plat.spawnAnimTimer = 0.0f;
          plat.spawnItemPos = {0, 0};
          tiles.push_back(plat);
        }
        i += length;
      }
      // 5% chance of stairs
      else if (r < 20) {
        int height = GetRandomValue(2, 3);
        for (int s = 0; s < height; s++) {
          for (int k = 0; k <= s; k++) {
            Tile stair;
            stair.rect = {(float)(i + s) * 32, (float)(368 - k * 32), 32, 32};
            stair.type = 2;
            stair.hasSword = false;
            stair.hit = false;
            stair.hitAnimTimer = 0.0f;
            stair.spawningItem = false;
            stair.spawnAnimTimer = 0.0f;
            stair.spawnItemPos = {0, 0};
            tiles.push_back(stair);
          }
        }
        i += height + 2;
      }
      // 8% chance of question blocks (increased from 5%)
      else if (r < 28) {
        Tile q;
        q.rect = {(float)i * 32, 250, 32, 32};
        q.type = 3; // Question block
        q.hasSword = false;
        q.hit = false;
        q.hitAnimTimer = 0.0f;
        q.spawningItem = false;
        q.spawnAnimTimer = 0.0f;
        q.spawnItemPos = {0, 0};
        questionBlockIndices.push_back((int)tiles.size());
        tiles.push_back(q);
      }
    }
  }

  // Fix: Add solid terrain at the start (first 30 blocks)
  for (int i = 0; i < 30; i++) {
    Tile tile;
    tile.rect = {(float)i * 32, 368, 32, 32};
    tile.type = 2; // Brick
    tile.hasSword = false;
    tile.hit = false;
    tile.hitAnimTimer = 0.0f;
    tile.spawningItem = false;
    tile.spawnAnimTimer = 0.0f;
    tile.spawnItemPos = {0, 0};
    tiles.push_back(tile);
  }

  // Add test question block with sword at the start (for testing - position x=400, above ground)
  Tile testBlock;
  testBlock.rect = {400.0f, 250.0f, 32, 32};
  testBlock.type = 3; // Question block (yellow)
  testBlock.hasSword = true; // This block contains a sword
  testBlock.hit = false;
  testBlock.hitAnimTimer = 0.0f;
  testBlock.spawningItem = false;
  testBlock.spawnAnimTimer = 0.0f;
  testBlock.spawnItemPos = {0, 0};
  tiles.push_back(testBlock);

  // Add castle at end (around x=94400, block 2950)
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 6; j++) {
      Tile castle;
      castle.rect = {94400.0f + i * 32, 400.0f - j * 32, 32, 32};
      castle.type = 2; // Brick
      castle.hasSword = false;
      castle.hit = false;
      castle.hitAnimTimer = 0.0f;
      castle.spawningItem = false;
      castle.spawnAnimTimer = 0.0f;
      castle.spawnItemPos = {0, 0};
      tiles.push_back(castle);
    }
  }

  // Randomly select 2 question blocks to have swords
  if (questionBlockIndices.size() >= 2) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questionBlockIndices.begin(), questionBlockIndices.end(), g);
    tiles[questionBlockIndices[0]].hasSword = true;
    tiles[questionBlockIndices[1]].hasSword = true;
  }

  // Spawn enemies after tiles are generated
  SpawnEnemies();
}

Level::~Level() {
  // Clean up enemies
  for (auto *enemy : enemies) {
    delete enemy;
  }
  enemies.clear();

  UnloadTexture(tileset);
  UnloadTexture(background);
  UnloadTexture(landmarks);
  UnloadTexture(swordTexture);
}

void Level::Reset() {
  // Reset game state
  gameTimer = 180.0f;
  gameOver = false;
  nextSwordId = 0;
  
  // Clean up existing enemies
  for (auto *enemy : enemies) {
    delete enemy;
  }
  enemies.clear();
  
  // Regenerate tiles (this will also clear swords and spawn new enemies)
  InitializeTiles();
}

void Level::Update(float dt) {
  // Update game timer (countdown)
  if (!gameOver) {
    gameTimer -= dt;
    if (gameTimer <= 0.0f) {
      gameTimer = 0.0f;
      gameOver = true;
    }
  }

  // Update enemies (including dying ones for animation)
  for (auto *enemy : enemies) {
    if (enemy) {
      enemy->Update(*this, dt);
    }
  }

  // Remove dead enemies (only after death animation completes)
  enemies.erase(
    std::remove_if(enemies.begin(), enemies.end(),
      [](Enemy* e) {
        if (!e || (!e->IsAlive() && !e->IsDying())) {
          delete e;
          return true;
        }
        return false;
      }),
    enemies.end());

  // Update hit animations for all tiles
  for (auto &tile : tiles) {
    if (tile.hitAnimTimer > 0.0f) {
      tile.hitAnimTimer -= dt;
      if (tile.hitAnimTimer <= 0.0f) {
        tile.hitAnimTimer = 0.0f;
      }
    }

    // Update sword spawn animation
    if (tile.spawningItem) {
      tile.spawnAnimTimer += dt;
      // Continue animation for 0.8 seconds
      if (tile.spawnAnimTimer >= 0.8f) {
        // Animation complete, create the actual sword at final position
        float finalY = tile.rect.y - 40.0f;
        Sword sword;
        sword.rect = {tile.spawnItemPos.x, finalY, 32, 32};
        sword.id = nextSwordId++;
        sword.collected = false;
        swords.push_back(sword);
        tile.spawningItem = false;
        // Mark block as used after sword is spawned
        tile.hit = true;
      }
    }
  }
}

void Level::HitBox(Rectangle playerRect, float velocityY) {
  // Only check if player is moving upward (hitting from below)
  if (velocityY >= 0)
    return;

  for (auto &tile : tiles) {
    if (tile.type == 3 && tile.hitAnimTimer <= 0.0f &&
        CheckCollisionRecs(playerRect, tile.rect)) {
      // Check if player hit from below
      Rectangle collision = GetCollisionRec(playerRect, tile.rect);
      if (collision.height < collision.width) {
        // Vertical collision - player hit the block
        // Only mark as hit if it doesn't have a sword (blocks with sword can be hit multiple times)
        if (!tile.hasSword) {
          tile.hit = true;
        }
        tile.hitAnimTimer = 0.4f; // Bounce animation duration (increased for better visibility)

        // If block has sword, start spawn animation
        if (tile.hasSword && !tile.spawningItem) {
          tile.spawningItem = true;
          tile.spawnAnimTimer = 0.0f;
          // Spawn sword from center of the box
          tile.spawnItemPos = {tile.rect.x + tile.rect.width / 2.0f - 16.0f, tile.rect.y + tile.rect.height / 2.0f - 16.0f};
          // Debug: ensure spawn animation starts
        }
      }
    }
  }
}

void Level::DrawBackground(float cameraX) {
  // Parallax background
  float parallaxFactor = 0.5f;
  float bgX = -cameraX * parallaxFactor;

  // Draw background repeated
  float textureWidth = (float)background.width;
  if (textureWidth == 0)
    textureWidth = 800;

  float offset = fmod(bgX, textureWidth);
  if (offset > 0)
    offset -= textureWidth;

  DrawTexture(background, (int)offset, 0, WHITE);
  DrawTexture(background, (int)offset + (int)textureWidth, 0, WHITE);
  DrawTexture(background, (int)offset + (int)textureWidth * 2, 0, WHITE);

  // Draw landmarks
  DrawTexture(landmarks, 500 - (int)cameraX, 200, WHITE);
  DrawTexture(landmarks, 1500 - (int)cameraX, 300, WHITE);
}

void Level::Draw() {
  for (const auto &tile : tiles) {
    Rectangle source = {0, 0, 32, 32};
    if (tile.type == 1)
      source.x = 0; // Ground
    else if (tile.type == 2)
      source.x = 32; // Brick
    else if (tile.type == 3) {
      if (tile.hit)
        source.x = 32; // Used block (brick)
      else
        source.x = 64; // Question block
    }

    // Apply hit animation (bounce up and return)
    Rectangle destRect = tile.rect;
    Color tint = WHITE;

    if (tile.hitAnimTimer > 0.0f) {
      // Smooth bounce animation: goes up then returns to original position
      float maxBounceHeight = 8.0f; // Maximum bounce height
      float progress = tile.hitAnimTimer / 0.4f; // Normalize to 0-1
      
      // Create a bounce effect: up then down (using a sine-like curve)
      float bounceHeight;
      if (progress < 0.5f) {
        // First half: going up
        bounceHeight = maxBounceHeight * (progress * 2.0f);
      } else {
        // Second half: coming down
        bounceHeight = maxBounceHeight * (1.0f - (progress - 0.5f) * 2.0f);
      }
      
      destRect.y -= bounceHeight;

      // Yellow flash when hit (first 0.15 seconds)
      if (tile.hitAnimTimer > 0.25f) {
        tint = YELLOW;
      }
    }

    DrawTexturePro(tileset, source, destRect, {0, 0}, 0.0f, tint);

    // Draw spawning sword animation (sword comes out from inside the box)
    if (tile.spawningItem) {
      float progress = tile.spawnAnimTimer / 0.8f; // Match animation duration
      if (progress > 1.0f) progress = 1.0f;
      
      // Start from center of box, move upward
      float startY = tile.rect.y + tile.rect.height / 2.0f - 16.0f;
      float endY = tile.rect.y - 40.0f;
      float currentY = startY - (startY - endY) * progress;
      
      // Add slight horizontal wobble for effect
      float wobble = sinf(progress * 3.14159f * 4.0f) * 2.0f;
      float currentX = tile.spawnItemPos.x + wobble;
      
      // Draw sword with slight scale effect
      float scale = 0.8f + (progress * 0.2f); // Grow from 80% to 100%
      Rectangle swordRect = {currentX, currentY, 32.0f * scale, 32.0f * scale};
      Rectangle swordSrc = {0, 0, (float)swordTexture.width, (float)swordTexture.height};
      DrawTexturePro(swordTexture, swordSrc, swordRect, {0, 0}, 0.0f, WHITE);
    }
  }

  // Draw swords
  for (const auto &sword : swords) {
    if (!sword.collected) {
      DrawTexture(swordTexture, (int)sword.rect.x, (int)sword.rect.y, WHITE);
    }
  }

  // Draw enemies
  for (auto *enemy : enemies) {
    if (enemy && enemy->IsAlive()) {
      enemy->Draw();
    }
  }
}

const std::vector<Tile> &Level::GetTiles() const { return tiles; }

const std::vector<Sword> &Level::GetSwords() const { return swords; }

std::vector<Enemy*> &Level::GetEnemies() { return enemies; }
const std::vector<Enemy*> &Level::GetEnemies() const { return enemies; }

void Level::CollectSword(int id) const {
  for (auto &sword : swords) {
    if (sword.id == id) {
      sword.collected = true;
      break;
    }
  }
}

void Level::SpawnEnemies() {
  // Spawn enemies at strategic locations throughout the map
  // Enemies spawn on ground platforms
  std::vector<float> spawnPositions = {
    500.0f,   // Early game
    1200.0f,  // 
    2000.0f,  //
    3500.0f,  //
    5000.0f,  //
    7000.0f,  //
    9000.0f,  //
    12000.0f, //
    15000.0f, //
    20000.0f, //
    25000.0f, //
    30000.0f, //
    40000.0f, //
    50000.0f, //
    60000.0f, //
    70000.0f, //
    80000.0f, //
    90000.0f  // Near end
  };

  for (float x : spawnPositions) {
    // Spawn enemy on ground level (y = 368, which is ground level)
    // Enemy constructor will adjust Y position to align bottom with ground
    enemies.push_back(new Enemy(x, 368.0f));
  }
}

void Level::CheckEnemyCollisions(Rectangle playerRect, bool isAttacking) {
  for (auto *enemy : enemies) {
    if (!enemy || !enemy->IsAlive()) continue;

    Rectangle enemyRect = enemy->GetCollisionRect();
    
    if (CheckCollisionRecs(playerRect, enemyRect)) {
      if (isAttacking) {
        // Player attacks enemy - kill enemy
        enemy->Kill();
      } else {
        // Enemy touches player - damage player (handled in Player::Update)
        // We'll return a flag or handle it differently
      }
    }
  }
}
