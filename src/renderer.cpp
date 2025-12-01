#include <raylib.h>
#include <string>

#include "renderer.h"
#include "solver.h"
#include "bird.cpp"
#include "pipe.cpp"
#include "background.cpp"

#define BIRD_PATH "../assets/flappybird.png"
#define TOP_PIPE_PATH "../assets/toppipe.png"
#define BOT_PIPE_PATH "../assets/bottompipe.png"
#define BG_PATH "../assets/flappybirdbg.png"
#define MENU_IMG_PATH "../assets/menu.png"
#define GAMEOVER_IMG_PATH "../assets/gameovermenu.png"

Texture2D Renderer::startGameTexture;
Texture2D Renderer::gameOverTexture;

void Renderer::importAssets(Bird &bird, Background (&background)[2], Pipe (&topPipes)[PIPES_COUNT], Pipe (&bottomPipes)[PIPES_COUNT])
{

    Image birdImg = LoadImage(BIRD_PATH);
    Image topPipesImg = LoadImage(TOP_PIPE_PATH);
    Image lowPipeImg = LoadImage(BOT_PIPE_PATH);
    Image bgImg = LoadImage(BG_PATH);
    Image menuImg = LoadImage(MENU_IMG_PATH);
    Image overImg = LoadImage(GAMEOVER_IMG_PATH);

    bird.setImage(birdImg);

    background[0].setImage(bgImg);
    background[1].setImage(bgImg);

    background[0].positionX = 0;
    background[1].positionX = SCREEN_WIDTH;

    for (unsigned char i = 0; i < PIPES_COUNT; i++)
    {
        topPipes[i].setImage(topPipesImg);
        bottomPipes[i].setImage(lowPipeImg);
    }

    UnloadImage(birdImg);
    UnloadImage(topPipesImg);
    UnloadImage(lowPipeImg);
    UnloadImage(bgImg);

    if (menuImg.data)
        startGameTexture = LoadTextureFromImage(menuImg);
    if (overImg.data)
        gameOverTexture = LoadTextureFromImage(overImg);

    if (menuImg.data)
        UnloadImage(menuImg);
    if (overImg.data)
        UnloadImage(overImg);
}

void Renderer::unloadAssets(Bird &bird, Background (&background)[2], Pipe (&topPipes)[PIPES_COUNT], Pipe (&bottomPipes)[PIPES_COUNT])
{
    UnloadTexture(background[0].img);

    UnloadTexture(background[1].img);
    UnloadTexture(bird.img);

    for (unsigned char i = 0; i < PIPES_COUNT; i++)
    {
        UnloadTexture(topPipes[i].img);
        UnloadTexture(bottomPipes[i].img);
    }

    UnloadTexture(startGameTexture);
    UnloadTexture(gameOverTexture);
}

void Renderer::drawMenuScreen()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.3f));

    if (startGameTexture.id > 0)
    {
        DrawTexture(startGameTexture, 0, 0, WHITE);
    }
    else
    {
        DrawText("FLAPPY BIRD", 80, 150, 40, WHITE);
    }

    char *prompt = "PRESS";
    int promptWidth = MeasureText(prompt, 20);
    DrawText(prompt, (SCREEN_WIDTH - promptWidth) >> 1, (SCREEN_HEIGHT * 0.75) + 80, 20, WHITE);

    prompt = "SPACE OR ARROW-UP";
    promptWidth = MeasureText(prompt, 20);
    DrawText(prompt, (SCREEN_WIDTH - promptWidth) >> 1, (SCREEN_HEIGHT * 0.75) + 100, 20, WHITE);

    prompt = "TO START";
    promptWidth = MeasureText(prompt, 20);
    DrawText(prompt, (SCREEN_WIDTH - promptWidth) >> 1, (SCREEN_HEIGHT * 0.75) + 120, 20, WHITE);
}

void Renderer::drawGameOverScreen(const int &score)
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));

    if (gameOverTexture.id > 0)
    {
        DrawTexture(gameOverTexture, 0, 0, WHITE);
    }
    else
    {
        DrawText("GAME OVER", 90, 150, 40, RED);
    }

    int scoreWidth = MeasureText(TextFormat("Score : %02i", score), 40);
    DrawText(TextFormat("Score : %02i", score), (SCREEN_WIDTH - scoreWidth) >> 1, SCREEN_HEIGHT >> 1, 40, {255, 216, 0, 255});

    char *prompt = "PRESS";
    int promptWidth = MeasureText(prompt, 20);
    DrawText(prompt, (SCREEN_WIDTH - promptWidth) >> 1, (SCREEN_HEIGHT * 0.75) + 80, 20, WHITE);

    prompt = "SPACE OR ARROW-UP";
    promptWidth = MeasureText(prompt, 20);
    DrawText(prompt, (SCREEN_WIDTH - promptWidth) >> 1, (SCREEN_HEIGHT * 0.75) + 100, 20, WHITE);

    prompt = "TO RESTART";
    promptWidth = MeasureText(prompt, 20);
    DrawText(prompt, (SCREEN_WIDTH - promptWidth) >> 1, (SCREEN_HEIGHT * 0.75) + 120, 20, WHITE);
}

void Renderer::drawScene(const int &state, const int &score, const Bird &bird, const Background (&background)[2], const Pipe (&topPipes)[PIPES_COUNT], const Pipe (&bottomPipes)[PIPES_COUNT])
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background[0].img, background[0].positionX, 0, WHITE);
    DrawTexture(background[1].img, background[1].positionX, 0, WHITE);

    if (state == MENU)
    {
        DrawTexture(bird.img, (SCREEN_WIDTH >> 1) - ((int)bird.width >> 1), bird.positionY, WHITE);
    }
    else
    {
        DrawTexturePro(bird.img, {0.0f, 0.0f, (float)bird.img.width, (float)bird.img.height}, {SCREEN_WIDTH / 5, bird.positionY, (float)bird.img.width, (float)bird.img.height}, {0.0f, 0.0f}, bird.curr_rotation, WHITE);
    }

    for (unsigned char i = 0; i < PIPES_COUNT; i++)
    {
        DrawTexture(topPipes[i].img, topPipes[i].positionX, topPipes[i].positionY, WHITE);
        DrawTexture(bottomPipes[i].img, bottomPipes[i].positionX, bottomPipes[i].positionY, WHITE);
    }

    switch (state)
    {
    case MENU:
        drawMenuScreen();
        break;
    case PLAYING:
        DrawText(TextFormat("%02i", score), (SCREEN_WIDTH >> 1) - 40, 10, 50, WHITE);
        DrawText(TextFormat("FPS: %02i", GetFPS()), 10, 10, 14, WHITE);
        break;
    case GAME_OVER:
        drawGameOverScreen(score);
        break;
    }

    /*  DEBUG: Display Hitboxs
        DrawRectangleLinesEx({SCREEN_WIDTH / 5, bird.positionY, (float)bird.img.width, (float)bird.img.height}, 2.0f, RED);

        for (unsigned char i = 0; i < PIPES_COUNT; i++)
        {
            DrawRectangleLinesEx({topPipes[i].positionX, topPipes[i].positionY, (float)topPipes[i].img.width, (float)topPipes[i].img.height}, 2.0f, RED);
            DrawRectangleLinesEx({bottomPipes[i].positionX, bottomPipes[i].positionY, (float)bottomPipes[i].img.width, (float)bottomPipes[i].img.height}, 2.0f, RED);
        }
    */

    EndDrawing();
}