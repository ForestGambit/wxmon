#pragma once

#include <string>
#include <SDL2/SDL.h>

class window
{
public:
    window(std::string title, int w, int h);
    ~window();

    SDL_Window* GetWindow() const;
    SDL_Renderer* GetRenderer() const;

private:
    std::string m_title;
    const int m_width{480};
    const int m_height{320};
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
};