#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>
#include <string>

class Bird;
class Pipe;
class Background;
class Solver;

#define PIPES_COUNT 5

class Renderer
{
private:
    static Texture2D startGameTexture;
    static Texture2D gameOverTexture;

    static void drawMenuScreen();
    static void drawGameOverScreen(const int &score);

public:
    static void importAssets(Bird &bird, Background (&background)[2], Pipe (&topPipes)[PIPES_COUNT], Pipe (&bottomPipes)[PIPES_COUNT]);

    static void unloadAssets(Bird &bird, Background (&background)[2], Pipe (&topPipes)[PIPES_COUNT], Pipe (&bottomPipes)[PIPES_COUNT]);

    static void drawScene(const int &state, const int &score, const Bird &bird, const Background (&background)[2], const Pipe (&topPipes)[PIPES_COUNT], const Pipe (&bottomPipes)[PIPES_COUNT]);
};

#endif