#include "Player.h"
#include "Enemy.h"

Player::Player() {
  position = {100, 300};
  velocity = {0, 0};
  texture = LoadTexture("assets/alan_garcia.png");
  animTexture = LoadTexture("assets/police_animations.png");
  swordTexture = LoadTexture("assets/sword.png");
  isGrounded = false;
  isShieldActive = false;
  hasSword = false;
  isAttacking = false;
  currentFrame = 0;
  animTimer = 0.0f;
  attackTimer = 0.0f;
  jumpCount = 0;
  facingRight = true;
  health = 3;
  maxHealth = 3;

  // Note: No shield texture to load - we'll draw it programmatically
}

Player::~Player() {
  UnloadTexture(texture);
  UnloadTexture(animTexture);
  UnloadTexture(swordTexture);
}

void Player::Reset() {
  position = {100, 300};
  velocity = {0, 0};
  isGrounded = false;
  isShieldActive = false;
  hasSword = false;
  isAttacking = false;
  currentFrame = 0;
  animTimer = 0.0f;
  attackTimer = 0.0f;
  jumpCount = 0;
  facingRight = true;
  health = 3;
  maxHealth = 3;
  bullets.clear(); // Clear all bullets
}

void Player::Update(Level &level) {
  float dt = GetFrameTime();

  // Horizontal movement
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    velocity.x = speed;
    facingRight = true;
  } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    velocity.x = -speed;
    facingRight = false;
  } else {
    velocity.x = 0;
  }

  // Jumping
  if (IsKeyPressed(KEY_SPACE)) {
    if (isGrounded) {
      velocity.y = -jumpForce;
      isGrounded = false;
      jumpCount = 1;
    } else if (jumpCount < maxJumps) {
      velocity.y = -jumpForce;
      jumpCount++;
    }
  }

  // Gravity
  velocity.y += gravity * dt;

  // Apply movement
  position.x += velocity.x * dt;
  position.y += velocity.y * dt;

  // Collision detection
  isGrounded = false;
  Rectangle playerRect = {position.x, position.y, 32, 64};

  for (const auto &tile : level.GetTiles()) {
    if (CheckCollisionRecs(playerRect, tile.rect)) {
      Rectangle collision = GetCollisionRec(playerRect, tile.rect);

      if (collision.width > collision.height) {
        // Vertical collision
        if (velocity.y > 0) {
          position.y = tile.rect.y - 64;
          velocity.y = 0;
          isGrounded = true;
          jumpCount = 0;
        } else if (velocity.y < 0) {
          position.y = tile.rect.y + tile.rect.height;
          velocity.y = 0;
        }
      } else {
        // Horizontal collision
        if (velocity.x > 0) {
          position.x = tile.rect.x - 32;
        } else if (velocity.x < 0) {
          position.x = tile.rect.x + tile.rect.width;
        }
      }
    }
  }

  // Check sword pickup
  for (const auto &sword : level.GetSwords()) {
    if (!sword.collected && CheckCollisionRecs(playerRect, sword.rect)) {
      hasSword = true;
      level.CollectSword(sword.id);
    }
  }

  // Check surprise box hits (when moving upward)
  level.HitBox(playerRect, velocity.y);

  // Check enemy collisions
  for (auto *enemy : level.GetEnemies()) {
    if (!enemy || !enemy->IsAlive()) continue;

    Rectangle enemyRect = enemy->GetCollisionRect();
    if (CheckCollisionRecs(playerRect, enemyRect)) {
      // Check if player is attacking
      if (isAttacking && hasSword) {
        // Player kills enemy
        enemy->Kill();
      } else if (!isShieldActive) {
        // Enemy damages player (only if not using shield)
        // Add simple cooldown to prevent rapid damage
        static float lastDamageTime = 0.0f;
        float currentTime = (float)GetTime();
        if (currentTime - lastDamageTime > 1.0f) { // 1 second cooldown
          if (health > 0) {
            health--;
            lastDamageTime = currentTime;
            // Push player back slightly
            position.x += (facingRight ? -30.0f : 30.0f);
          }
        }
      }
    }
  }

  // Keep within bounds
  if (position.y > 1000) {
    // Game over - fell off map
    health = 0;
  }

  // Combat Logic
  isShieldActive = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

  // Sword attack (E key or Left Click if has sword)
  if (hasSword &&
      (IsKeyPressed(KEY_E) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
    isAttacking = true;
    attackTimer = 0.3f; // Attack duration
  }

  if (attackTimer > 0) {
    attackTimer -= dt;
    if (attackTimer <= 0)
      isAttacking = false;
  }

  // Shooting (player always has gun)
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isAttacking) {
    Projectile p;
    p.position = {position.x + 32, position.y + 20};
    p.velocity = {10.0f, 0.0f};
    if (!facingRight) {
      p.velocity.x = -10.0f;
      p.position.x = position.x;
    }
    p.active = true;
    bullets.push_back(p);
  }

  // Update Bullets
  for (auto &b : bullets) {
    if (b.active) {
      b.position.x += b.velocity.x;
      if (b.position.x < position.x - 800 || b.position.x > position.x + 800) {
        b.active = false;
      }
    }
  }

  // Animation logic
  animTimer += dt;

  if (!isGrounded) {
    // Jumping animation (frame 3)
    currentFrame = 3;
  } else if (velocity.x != 0) {
    // Walking animation (frames 1-2)
    if (animTimer >= animSpeed) {
      currentFrame = (currentFrame == 1) ? 2 : 1;
      animTimer = 0.0f;
    }
  } else {
    // Idle animation (frame 0)
    currentFrame = 0;
  }
}

void Player::Draw() {
  // Calculate source rectangle from animation sheet
  Rectangle source = {(float)(currentFrame * 32), 0, 32, 64};

  // Flip sprite if moving left
  if (!facingRight)
    source.width = -32;

  DrawTexturePro(animTexture, source, {position.x, position.y, 32, 64}, {0, 0},
                 0.0f, WHITE);

  // Draw sword if equipped and attacking
  if (hasSword && isAttacking) {
    float swordX = (!facingRight) ? position.x - 32 : position.x + 32;
    // Add rotation animation during attack
    float rotation = (attackTimer / 0.3f) * 90.0f;
    if (!facingRight)
      rotation = -rotation;

    Vector2 origin = {16, 16};
    Rectangle swordDest = {swordX + 16, position.y + 32, 32, 32};
    Rectangle swordSrc = {0, 0, (float)swordTexture.width,
                          (float)swordTexture.height};
    DrawTexturePro(swordTexture, swordSrc, swordDest, origin, rotation, WHITE);
  }

  // Draw simple black riot shield
  if (isShieldActive) {
    int shieldX = (!facingRight) ? (int)position.x - 20 : (int)position.x + 40;
    int shieldY = (int)position.y + 10;

    // Shield body (black rectangle)
    Rectangle shieldRect = {(float)shieldX, (float)shieldY, 16, 40};
    DrawRectangleRec(shieldRect, BLACK);
    DrawRectangleLinesEx(shieldRect, 2, DARKGRAY);

    // Handle (gray)
    Rectangle handle = {(float)shieldX + 4, (float)shieldY + 15, 8, 10};
    DrawRectangleRec(handle, DARKGRAY);
  }

  // Draw Bullets
  for (const auto &b : bullets) {
    if (b.active) {
      DrawCircle((int)b.position.x, (int)b.position.y, 5, YELLOW);
    }
  }
}
