/*
assets used
https://toppng.com/free-image/door-png-open-door-closed-door-PNG-free-PNG-Images_185993
https://www.youtube.com/watch?v=4XSi1XL-wnU
https://www.youtube.com/watch?v=pDh7aMPp6N8
*/

# include <raylib.h>
# include <stdio.h>

int main(void)
{
  InitWindow(1280, 1280, "door simulator");
  InitAudioDevice();
  SetTargetFPS(60);
  Texture2D doors[] = {
  LoadTexture("door1.png"),
  LoadTexture("door2.png")
  };
  Sound sounds[] = {
      LoadSound("open.mp3"),
      LoadSound("close.mp3")
  };
  while(!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    if(IsMouseButtonDown(0))
    {
      DrawTexture(doors[1], 445, 268, WHITE);
      PlaySound(sounds[1]);
    }
    else
    {
      DrawTexture(doors[0], 446, 266, WHITE);
      PlaySound(sounds[0]);
    }
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
