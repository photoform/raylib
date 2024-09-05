# include <iostream>
# include "raylib.h"

// TODO: more broadcast objects


const int windowHeight = 1024;
const int windowWidth = 1024;

class broadcast {
  private:
    int id;
    Texture2D bgi;
    Music bgm;
  public:
    broadcast(int id, const char *imageFile, const char *audioFile)
    {
      this->id = id;
      bgi = LoadTexture(imageFile);
      bgm = LoadMusicStream(audioFile);
      std::cout << "broadcast " << id << " created" << std::endl;
    }
    void playAudio()
    {
      PlayMusicStream(bgm);
    }
    void pauseAudio()
    {
      PauseMusicStream(bgm);
    }
    Music getAudio()
    {
      return bgm;
    }
    Texture2D getImage()
    {
      return bgi;
    }

    ~broadcast()
    {
      UnloadTexture(bgi);
      UnloadMusicStream(bgm);
    }
};

int main()
{
  InitWindow(windowHeight, windowWidth,"storm footage");
  SetTargetFPS(60);
  InitAudioDevice();
  Image noise;
  if(!IsAudioDeviceReady()) return -1;
  broadcast casts[] = {
	  broadcast(0, "./images/image0.png","./audio/audio0.wav"),
	  broadcast(1, "./images/image1.png","./audio/audio1.wav"),
	  broadcast(2, "./images/image2.png","./audio/audio2.wav"),
  };
  Sound acceptSwitch = LoadSound("./audio/switch-broadcast-true.wav");
  Sound declineSwitch = LoadSound("./audio/switch-broadcast-false.wav");
  Texture2D broadcast_frame = LoadTexture("./images/camera-frame.png");
  int index = 0;
  int scanlineY = 0;
  casts[index].playAudio();
  std::cout << "Press A or D to switch cameras" << std::endl;
  std::cout << "Press Q to quit" << std::endl;
  while(!WindowShouldClose())
  {
    noise = GenImageWhiteNoise(windowWidth / 8, windowHeight / 8, 1.0f);
    if(IsKeyPressed(68))
    {
      if(index < 2)
      {
        casts[index].pauseAudio();
        index++;
		PlaySound(acceptSwitch);
        casts[index].playAudio();
      }
	  else {PlaySound(declineSwitch);}
    }
    if(IsKeyPressed(65))
    {
      if(index > 0)
      {
        casts[index].pauseAudio();
        index--;
		PlaySound(acceptSwitch);
        casts[index].playAudio();
      }
	  else {PlaySound(declineSwitch);}
    }
    if(IsKeyPressed(81)) break;
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureEx(casts[index].getImage(), (Vector2){0, 0},0.0f,8.0f, GRAY);
    DrawTextureEx(broadcast_frame, (Vector2){0, 0},0.0f,8.0f, DARKGRAY);
    for (int i = 0; i <= 15; i++)
    {
        scanlineY = rand() % windowHeight;
        DrawLineV(Vector2{0,scanlineY},Vector2{windowWidth,scanlineY},DARKGRAY);  
    }
    
    
    UpdateMusicStream(casts[index].getAudio());
    EndDrawing();
    
  }
  
  casts[0].~broadcast();
  casts[1].~broadcast();
  casts[2].~broadcast();
  CloseWindow();
  return 0;

}


