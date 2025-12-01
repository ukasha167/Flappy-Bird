#include <raylib.h>
#include "solver.h"
#include "bird.cpp"
#include "pipe.cpp"
#include "background.cpp"

Bird Solver::bird;
Pipe Solver::topPipes[PIPES_COUNT];
Pipe Solver::bottomPipes[PIPES_COUNT];
Background Solver::background[2];

void Solver::initGamePositions()
{
    setPipesPositionX();
    setPipesPositionY(nullptr);
}

void Solver::setPipesPositionX()
{
    const int MIN_GAP_X = 200;
    const int MAX_GAP_X = 250;

    for (unsigned char i = 1; i < PIPES_COUNT; i++)
    {
        int randomGap = GetRandomValue(MIN_GAP_X, MAX_GAP_X);
        topPipes[i].positionX = topPipes[i - 1].positionX + topPipes[i - 1].width + randomGap;
        bottomPipes[i].positionX = bottomPipes[i - 1].positionX + bottomPipes[i - 1].width + randomGap;
    }
}

void Solver::setPipesPositionY(const int *const pipe)
{
    constexpr int pipeStart = (SCREEN_HEIGHT >> 1) - 130;
    constexpr int pipeEnd = (SCREEN_HEIGHT >> 1) + 100;
    int randomNum;

    if ((pipe != nullptr) && (*pipe >= 0 && *pipe < PIPES_COUNT))
    {
        randomNum = GetRandomValue(pipeStart, pipeEnd);
        topPipes[*pipe].positionY = randomNum - topPipes[*pipe].height;
        bottomPipes[*pipe].positionY = randomNum + PIPE_GAP;
        return;
    }

    for (unsigned char i = 0; i < PIPES_COUNT; i++)
    {
        randomNum = GetRandomValue(pipeStart, pipeEnd);
        topPipes[i].positionY = randomNum - topPipes[i].height;
        bottomPipes[i].positionY = randomNum + PIPE_GAP;
    }
}

void Solver::updateState(const float &dt)
{
    bird.update(dt, jumpForce, ROTATION_ANGLE);
    background[0].update(backGroundSpeed, dt);
    background[1].update(backGroundSpeed, dt);

    for (unsigned char i = 0; i < PIPES_COUNT; i++)
    {
        topPipes[i].update(pipeSpeed, dt);
        bottomPipes[i].update(pipeSpeed, dt);
    }
}

void Solver::updateScore()
{
    if (topPipes[Current_Pipe].positionX + topPipes[Current_Pipe].width > bird.positionX)
    {
        return;
    }

    score++;
    Current_Pipe = (Current_Pipe + 1) % PIPES_COUNT;
    pipeSpeed += 1.5f;
    jumpForce -= 0.1f;
    backGroundSpeed += 0.5f;
}

bool Solver::PipeCollision()
{
    Pipe &topPipe = topPipes[Current_Pipe];
    Pipe &bottomPipe = bottomPipes[Current_Pipe];

    Rectangle birdRect = {bird.positionX, bird.positionY, (float)bird.width, (float)bird.height};
    Rectangle topRect = {topPipe.positionX, topPipe.positionY, (float)topPipe.width, (float)topPipe.height};
    Rectangle bottomRect = {bottomPipe.positionX, bottomPipe.positionY, (float)bottomPipe.width, (float)bottomPipe.height};

    if (CheckCollisionRecs(birdRect, topRect) || CheckCollisionRecs(birdRect, bottomRect))
    {
        return true;
    }

    return false;
}

bool Solver::checkCollision()
{
    if (PipeCollision() || bird.positionY + bird.height > SCREEN_HEIGHT)
    {
        return true;
    }

    return false;
}

void Solver::recyclePipes()
{
    if (topPipes[First_Pipe].positionX + topPipes[First_Pipe].width > 0)
    {
        return;
    }

    const int MIN_GAP_X = 200;
    const int MAX_GAP_X = 250;
    int randomGap;

    randomGap = GetRandomValue(MIN_GAP_X, MAX_GAP_X);
    topPipes[First_Pipe].positionX = topPipes[(First_Pipe + PIPES_COUNT - 1) % PIPES_COUNT].positionX + randomGap;
    bottomPipes[First_Pipe].positionX = bottomPipes[(First_Pipe + PIPES_COUNT - 1) % PIPES_COUNT].positionX + randomGap;

    setPipesPositionY(&First_Pipe);
    First_Pipe = (First_Pipe + 1) % PIPES_COUNT;
}

void Solver::reset()
{
    bird.velocityY = 0.0f;
    bird.positionY = SCREEN_HEIGHT >> 1;

    background[0].positionX = 0;
    background[1].positionX = SCREEN_WIDTH;

    for (unsigned char i = 0; i < PIPES_COUNT; i++)
    {
        topPipes[i].positionX = SCREEN_WIDTH;
        bottomPipes[i].positionX = SCREEN_WIDTH;
    }

    score = 0;
    backGroundSpeed = 15.0f;
    pipeSpeed = 100.0f;
    jumpForce = -200.0f;
    Current_Pipe = First_Pipe = 0;

    initGamePositions();
}
