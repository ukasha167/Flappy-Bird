#include <raylib.h>

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 640
#define PIPES_COUNT 5
#define PIPE_GAP 110
#define GRAVITY 550.0f

struct Background
{
    float width, height;
    float positionX = 0.0f;
    Texture2D img;

    void setImage(Image &image)
    {
        img = LoadTextureFromImage(image);

        width = img.width;
        height = img.height;
    }

    void update(const float &velocityX, const float &dt)
    {
        positionX -= velocityX * dt;

        if (positionX + SCREEN_WIDTH <= 0)
        {
            positionX = SCREEN_WIDTH;
        }
    }
};