#include <raylib.h>

#define SCREEN_WIDTH 360

struct Pipe
{
    float width, height;
    float positionX = SCREEN_WIDTH;
    float positionY;

    Texture2D img;

    void setImage(const Image &srcImage)
    {
        float scale = 0.15f;
        Image imgCopy = ImageCopy(srcImage);
        ImageResize(&imgCopy,
                    (int)(imgCopy.width * scale),
                    (int)(imgCopy.height * scale));
        img = LoadTextureFromImage(imgCopy);
        UnloadImage(imgCopy);

        width = img.width;
        height = img.height;
    }

    void update(const float &velocityX, const float &dt)
    {
        positionX -= velocityX * dt;
    }
};