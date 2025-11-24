#pragma once
#include "Level.h"
#include "raylib.h"
#include <vector>

class Player {
public:
  Player();
  ~Player();

  void Update(Level &level);
  void Draw();
  void Reset(); // Reset player to initial state
  Vector2 GetPosition() const { return position; }
  int GetHealth() const { return health; }
  int GetMaxHealth() const { return maxHealth; }
  bool HasSword() const { return hasSword; }
  void PickupSword() { hasSword = true; }

private:
  Vector2 position;
  Vector2 velocity;
  Texture2D texture;
  Texture2D animTexture; // Animation sprite sheet
  Texture2D swordTexture;
  Texture2D shieldTexture;
  bool isGrounded;

  // Animation
  int currentFrame;
  float animTimer;
  static constexpr float animSpeed = 0.1f; // Time per frame

  // Combat
  struct Projectile {
    Vector2 position;
    Vector2 velocity;
    bool active;
  };
  std::vector<Projectile> bullets;
  bool isShieldActive;
  bool hasSword;
  bool isAttacking;
  float attackTimer;

  // Constants
  static constexpr float speed = 200.0f;
  static constexpr float jumpForce = 450.0f;
  static constexpr float gravity = 1000.0f;
  static constexpr int maxJumps = 2;

  int jumpCount;
  bool facingRight;

  // Health system
  int health;
  int maxHealth;
};
