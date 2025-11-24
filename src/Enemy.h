#pragma once
#include "raylib.h"
#include <vector>

class Level; // Forward declaration

class Enemy {
public:
  Enemy(float x, float y);
  ~Enemy();

  void Update(Level &level, float dt);
  void Draw();
  Rectangle GetCollisionRect() const { return {position.x, position.y, 25.6f, 51.2f}; }
  bool IsAlive() const { return alive && !isDying; }
  bool IsDying() const { return isDying; } // Check if enemy is in death animation
  void Kill() { isDying = true; deathTimer = 0.0f; velocity.y = -200.0f; } // Start death animation
  Vector2 GetPosition() const { return position; }

private:
  Vector2 position;
  Vector2 velocity;
  Texture2D animTexture; // Animation sprite sheet
  bool isGrounded;
  bool facingRight;
  bool alive;
  bool isDying; // Death animation state
  float deathTimer; // Timer for death animation

  // Animation
  int currentFrame;
  float animTimer;
  static constexpr float animSpeed = 0.15f; // Time per frame

  // Constants
  static constexpr float speed = 80.0f; // Slower than player (player is 200.0f)
  static constexpr float gravity = 1000.0f;
  
  // AI - simple patrol behavior
  float patrolDistance;
  float startX;
  bool movingRight;
};

