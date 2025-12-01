#include <raylib.h>

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 640
#define GRAVITY 550.0f
#define ROTATIONAL_GRAVITY 22.0f

struct Bird
{
    float width, height;

    float positionX = SCREEN_WIDTH / 5;
    float positionY = SCREEN_HEIGHT >> 1;
    float velocityY = 0.0f;
    float curr_rotation = 0.0f;

    Texture2D img;

    void setImage(const Image &srcImage)
    {
        float scale = 0.1f;
        Image imgCopy = ImageCopy(srcImage);
        ImageResize(&imgCopy,
                    (int)(imgCopy.width * scale),
                    (int)(imgCopy.height * scale));
        img = LoadTextureFromImage(imgCopy);
        UnloadImage(imgCopy);

        width = img.width;
        height = img.height;
    }

    void update(const float &dt, const float &jumpForce, const float &ROTATION_ANGLE)
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
        {
            velocityY = jumpForce;
            curr_rotation = ROTATION_ANGLE;
        }

        curr_rotation += ROTATIONAL_GRAVITY * dt;
        velocityY += GRAVITY * dt;
        positionY += velocityY * dt;

        if (positionY <= 0.0f)
        {
            velocityY = 0.0f;
            positionY = 0.0f;
        }
        if (curr_rotation >= 15.0f)
        {
            curr_rotation = 15.0f;
        }
    }
};