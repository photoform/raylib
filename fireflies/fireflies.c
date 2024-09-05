# include <raylib.h>
# include <stdio.h>
# include <time.h>

const int windowHeight = 600;
const int windowWidth = 800;

Vector2 walk(Vector2 ff)
{   
        switch (rand() % 4) {
            case 0:
            ff.x = ff.x < windowWidth ? ++ff.x : --ff.x;
            break;
            case 1:
            ff.x = ff.x > 0 ? --ff.x : ++ff.x;
            break;
            case 2:
            ff.y = ff.y < windowHeight ? ++ff.y : --ff.y;
            break;
            case 3:
            ff.y > 0 ? --ff.y : ++ff.y;
            break;
        }
    
    return ff;
}

Vector2 setDefault(Vector2 ff)
{
    ff.x = rand() % windowWidth;
    ff.y = rand() % windowHeight;
    return ff;
}

int main(void)
{
    srand(time(NULL));
    InitWindow(windowWidth,windowHeight,"fireflies");
	SetTargetFPS(60);
    InitAudioDevice();
    Vector2 fireflies[100];
    Music mu = LoadMusicStream("fireflies-001.wav");
    PlayMusicStream(mu);
    for (int i = 0; i < 100; i++)
    {
        fireflies[i] = setDefault(fireflies[i]);
    }
	while(!WindowShouldClose())
	{
        UpdateMusicStream(mu);
		BeginDrawing();
        ClearBackground((Color){ 0, 12, 25, 255 } );
        for (int i = 0; i<=100;i++)
        {
            fireflies[i] = walk(fireflies[i]);
            DrawCircleV(fireflies[i], 3, (Color){ 253, 249, 0, 63});
            DrawPixelV(fireflies[i], (Color){ 253, 249, 0, 255 });
        }
		EndDrawing();
	}
}


