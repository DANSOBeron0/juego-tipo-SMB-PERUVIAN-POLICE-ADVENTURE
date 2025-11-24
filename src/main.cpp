#include "Level.h"
#include "Player.h"
#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Alan Garcia Platformer");

  SetTargetFPS(60);

  Player player;
  Level level;

  Camera2D camera = {0};
  camera.target = {player.GetPosition().x + 20.0f,
                   player.GetPosition().y + 20.0f};
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  while (!WindowShouldClose()) {
    // Update
    float dt = GetFrameTime();

    // Check if player is dead (health = 0)
    bool playerDead = (player.GetHealth() <= 0);

    if (!playerDead && !level.IsGameOver()) {
      level.Update(dt);
      player.Update(level);

      // Camera follows player
      camera.target = {player.GetPosition().x + 20,
                       player.GetPosition().y + 20};
      // Clamp camera to ground
      if (camera.target.y > 200)
        camera.target.y = 200;
    }

    // Draw
    BeginDrawing();
    ClearBackground(SKYBLUE); // Sky color

    // Draw background (parallax)
    level.DrawBackground(camera.target.x - screenWidth / 2.0f);

    BeginMode2D(camera);
    level.Draw(); // This now draws enemies too
    player.Draw();
    EndMode2D();

    // Draw health hearts (left side)
    for (int i = 0; i < player.GetMaxHealth(); i++) {
      int heartX = 10 + i * 35;
      int heartY = 10;

      if (i < player.GetHealth()) {
        // Full heart (red)
        DrawCircle(heartX + 10, heartY + 8, 8, RED);
        DrawCircle(heartX + 20, heartY + 8, 8, RED);
        DrawTriangle({(float)heartX + 5, (float)heartY + 10},
                     {(float)heartX + 25, (float)heartY + 10},
                     {(float)heartX + 15, (float)heartY + 25}, RED);
      } else {
        // Empty heart (gray outline)
        DrawCircleLines(heartX + 10, heartY + 8, 8, DARKGRAY);
        DrawCircleLines(heartX + 20, heartY + 8, 8, DARKGRAY);
        DrawTriangleLines({(float)heartX + 5, (float)heartY + 10},
                          {(float)heartX + 25, (float)heartY + 10},
                          {(float)heartX + 15, (float)heartY + 25}, DARKGRAY);
      }
    }

    // Draw timer UI (center)
    float timeLeft = level.GetGameTimer();
    int minutes = (int)(timeLeft / 60.0f);
    int seconds = (int)(timeLeft) % 60;
    const char *timerText = TextFormat("Time: %02d:%02d", minutes, seconds);
    int timerWidth = MeasureText(timerText, 30);
    DrawText(timerText, screenWidth / 2 - timerWidth / 2, 10, 30,
             level.IsGameOver() ? RED : WHITE);

    // Game Over Screen
    if (playerDead || level.IsGameOver()) {
      // Black semi-transparent overlay
      DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));

      // Game Over Text
      const char *gameOverText = playerDead ? "GAME OVER" : "TIME'S UP!";
      int textWidth = MeasureText(gameOverText, 60);
      DrawText(gameOverText, screenWidth / 2 - textWidth / 2,
               screenHeight / 2 - 80, 60, RED);

      // Menu Options
      DrawText("REINICIAR - Presiona R", screenWidth / 2 - 150,
               screenHeight / 2 + 20, 20, WHITE);
      DrawText("SALIR - Presiona ESC", screenWidth / 2 - 140,
               screenHeight / 2 + 50, 20, WHITE);

      // Handle input
      if (IsKeyPressed(KEY_R)) {
        // Restart game - reset everything to initial state
        player.Reset();
        level.Reset();
        // Reset camera to start position
        camera.target = {player.GetPosition().x + 20.0f,
                         player.GetPosition().y + 20.0f};
        camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
