#include <raylib.h>
#include <time.h>
#include "solver.h"
#include "renderer.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "1.67");
    SetRandomSeed((u_int32_t)time(NULL));
    SetTargetFPS(144);

    Renderer::importAssets(Solver::bird, Solver::background, Solver::topPipes, Solver::bottomPipes);

    Solver::initGamePositions();
    Solver::currentState = MENU;

    float dt;
    while (WindowShouldClose() == false)
    {
        dt = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
        {
            if (Solver::currentState == MENU)
            {
                Solver::currentState = PLAYING;
            }
            else if (Solver::currentState == GAME_OVER)
            {
                Solver::reset();
                Solver::currentState = PLAYING;
            }
        }

        if (Solver::currentState == PLAYING)
        {
            Solver::updateState(dt);
            Solver::updateScore();

            if (Solver::checkCollision())
            {
                Solver::currentState = GAME_OVER;
            }
            else
            {
                Solver::recyclePipes();
            }
        }

        Renderer::drawScene(Solver::currentState, Solver::score, Solver::bird, Solver::background, Solver::topPipes, Solver::bottomPipes);
    }

    Renderer::unloadAssets(Solver::bird, Solver::background, Solver::topPipes, Solver::bottomPipes);
    CloseWindow();

    return 0;
}
