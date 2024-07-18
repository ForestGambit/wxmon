 #include "window.h"
 
 
window::window(std::string title, int w, int h)
    :m_title(title), m_width(w), m_height(h) 
{
    m_window = SDL_CreateWindow(
        m_title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_width,
        m_height,
        SDL_WINDOW_FULLSCREEN
    );

    auto renderer_flags{static_cast<SDL_RendererFlags>(SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)};

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        renderer_flags
    );
}

window::~window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

SDL_Window* window::GetWindow() const
{
    return m_window;
}

SDL_Renderer* window::GetRenderer() const
{
    return m_renderer;
}