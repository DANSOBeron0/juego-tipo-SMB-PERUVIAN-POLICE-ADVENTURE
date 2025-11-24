#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(float x, float y) {
  // Position enemy so bottom aligns with ground level
  // y is the ground level (368), enemy height is 51.2, so position.y = y - 51.2
  position = {x, y - 51.2f};
  velocity = {0, 0};
  animTexture = LoadTexture("assets/police_animations.png"); // Reuse police sprite as thief
  isGrounded = false;
  facingRight = true;
  alive = true;
  currentFrame = 0;
  animTimer = 0.0f;
  patrolDistance = 200.0f; // Patrol 200 pixels from spawn
  startX = x;
  movingRight = true;
  isDying = false;
  deathTimer = 0.0f;
}

Enemy::~Enemy() {
  UnloadTexture(animTexture);
}

void Enemy::Update(Level &level, float dt) {
  if (!alive && !isDying) return;

  // Handle death animation
  if (isDying) {
    deathTimer += dt;
    // Apply gravity for falling animation
    velocity.y += gravity * dt;
    position.y += velocity.y * dt;
    position.x += velocity.x * dt * 0.5f; // Slow horizontal movement
    
    // Rotate while falling
    // After 1 second, mark as dead
    if (deathTimer >= 1.0f) {
      alive = false;
      isDying = false;
    }
    return; // Don't process normal AI during death
  }

  // Simple AI: patrol back and forth
  float distanceFromStart = position.x - startX;
  
  if (movingRight) {
    if (distanceFromStart >= patrolDistance) {
      movingRight = false;
      facingRight = false;
    } else {
      velocity.x = speed;
      facingRight = true;
    }
  } else {
    if (distanceFromStart <= -patrolDistance || distanceFromStart <= 0) {
      movingRight = true;
      facingRight = true;
    } else {
      velocity.x = -speed;
      facingRight = false;
    }
  }

  // Gravity
  velocity.y += gravity * dt;

  // Apply movement
  position.x += velocity.x * dt;
  position.y += velocity.y * dt;

  // Collision detection with tiles
  isGrounded = false;
  Rectangle enemyRect = {position.x, position.y, 25.6f, 51.2f};

  for (const auto &tile : level.GetTiles()) {
    if (CheckCollisionRecs(enemyRect, tile.rect)) {
      Rectangle collision = GetCollisionRec(enemyRect, tile.rect);

      if (collision.width > collision.height) {
        // Vertical collision
        if (velocity.y > 0) {
          position.y = tile.rect.y - 51.2f;
          velocity.y = 0;
          isGrounded = true;
        } else if (velocity.y < 0) {
          position.y = tile.rect.y + tile.rect.height;
          velocity.y = 0;
        }
      } else {
        // Horizontal collision - turn around
        if (velocity.x > 0) {
          position.x = tile.rect.x - 25.6f;
          movingRight = false;
          facingRight = false;
        } else if (velocity.x < 0) {
          position.x = tile.rect.x + tile.rect.width;
          movingRight = true;
          facingRight = true;
        }
        velocity.x = 0;
      }
    }
  }

  // Keep within bounds (fall off = death)
  if (position.y > 1000) {
    alive = false;
  }

  // Animation logic
  animTimer += dt;
  if (isGrounded && velocity.x != 0) {
    // Walking animation (frames 1-2)
    if (animTimer >= animSpeed) {
      currentFrame = (currentFrame == 1) ? 2 : 1;
      animTimer = 0.0f;
    }
  } else if (!isGrounded) {
    // Jumping animation (frame 3)
    currentFrame = 3;
  } else {
    // Idle animation (frame 0)
    currentFrame = 0;
  }
}

void Enemy::Draw() {
  if (!alive && !isDying) return;

  // Calculate source rectangle from animation sheet
  Rectangle source = {(float)(currentFrame * 32), 0, 32, 64};

  // Flip sprite if facing left (unless dying)
  if (!facingRight && !isDying)
    source.width = -32;

  // During death animation, rotate and fade
  float rotation = 0.0f;
  Color tint = WHITE;
  if (isDying) {
    rotation = deathTimer * 360.0f; // Rotate while falling
    float alpha = 1.0f - (deathTimer / 1.0f); // Fade out
    tint = Fade(WHITE, alpha);
  }

  // Draw enemy at 80% size of player (32x64 -> 25.6x51.2)
  Vector2 origin = {12.8f, 25.6f}; // Center of enemy for rotation
  DrawTexturePro(animTexture, source, {position.x, position.y, 25.6f, 51.2f}, origin,
                 rotation, tint);
}

