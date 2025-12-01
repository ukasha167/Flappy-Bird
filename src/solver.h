#ifndef SOLVER_H
#define SOLVER_H

#include <raylib.h>

class Bird;
class Pipe;
class Background;

#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 640
#define PIPES_COUNT 5
#define PIPE_GAP 110
#define GRAVITY 550.0f

enum GameState
{
    MENU = 0,
    PLAYING = 1,
    GAME_OVER = 2
};

class Solver
{
private:
    static constexpr float ROTATION_ANGLE = -20.0f;

    inline static float pipeSpeed = 100.0f;
    inline static float backGroundSpeed = 15.0f;

    inline static float jumpForce = -200.0f;

    inline static int First_Pipe = 0;
    inline static int Current_Pipe = First_Pipe;

    static bool PipeCollision();
    static void setPipesPositionX();
    static void setPipesPositionY(const int *const pipe);

public:
    static Bird bird;
    static Pipe topPipes[PIPES_COUNT];
    static Pipe bottomPipes[PIPES_COUNT];
    static Background background[2];

    inline static int score = 0;
    inline static GameState currentState = MENU;

    static void initGamePositions();
    static void updateState(const float &dt);
    static void updateScore();
    static void recyclePipes();
    static bool checkCollision();
    static void reset();
};

#endif
