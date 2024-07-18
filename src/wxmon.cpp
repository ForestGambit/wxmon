#include <cstdlib>

//g++ wxmon.cpp -w -lSDL2 -o wxmon

#include "application.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320



int main(int argc, char** argv)
{
    Application app{};

    return app.Run();
}