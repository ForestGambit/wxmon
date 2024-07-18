#include "application.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>

#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "imgui/imgui.h"

extern const unsigned int font_futura_compressed_size;
extern const unsigned int font_futura_compressed_data[];

Application::Application()
{
    unsigned int init_flags{SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER};
    if(SDL_Init(init_flags) != 0)
    {
        m_exit_status = 1;
    }

    m_window = new window(std::string{"Application"}, 480, 320);
    m_wxdata = new wxdata();
}

Application::~Application()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}

int Application::Run()
{
    if(m_exit_status == 1)
        return m_exit_status;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io{ImGui::GetIO()}; (void)io;

    //io.Fonts->AddFontFromFileTTF("futura.ttf", 80.0f);
    io.Fonts->AddFontFromMemoryCompressedTTF(font_futura_compressed_data, font_futura_compressed_size, 60.0f);

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplSDL2_InitForSDLRenderer(m_window->GetWindow(), m_window->GetRenderer());
    ImGui_ImplSDLRenderer2_Init(m_window->GetRenderer());

    m_isrunning = true;
    bool first_run = true;

    //m_wxdata->Refresh();

    constexpr unsigned long dispRefreshRate = 1000;
    constexpr unsigned long wxRefreshRate = 100000;
    unsigned long dispExpTime = SDL_GetTicks64() + dispRefreshRate;
    unsigned long wxExpTime = SDL_GetTicks64() + wxRefreshRate; 

    //std::cout << m_wxdata->GetBuffer().c_str();

    while(m_isrunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) == 1)
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_q)
                    Stop();
            }
            else if (event.type == SDL_QUIT)
            {
                Stop();
            }
        }

        std::string errStr{};

        unsigned long currentTime = SDL_GetTicks64();

        if((currentTime >= wxExpTime) || (first_run))
        {
            wxExpTime = currentTime + wxRefreshRate;

            int status = m_wxdata->Refresh();       
            if(status < 0)
            {
                errStr = "Error" + std::to_string(status) + "\n";
            }
        }

        if((currentTime >= dispExpTime) || (first_run))
        {
            dispExpTime = currentTime + dispRefreshRate;
            errStr.clear();

            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            
            //std::time_t time = std::time({});
            //char timestring[25];
            //std::strftime(std::data(timestring), std::size(timestring), "%X", std::localtime(&time));

            ImGui::Begin("TempPanel", &m_show_some_panel, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings);
            //ImGui::Text("%ld    %ld", dispExpTime, wxExpTime);
            //ImGui::Button("Button!", {100,50});
            ImGui::Text(" ");
            ImGui::Text("%sF  %s%%", m_wxdata->GetTemp().c_str(), m_wxdata->GetRH().c_str());
            //ImGui::Text("%s%% RH", m_wxdata->GetRH().c_str());
            ImGui::Text("%s", errStr.c_str());
            ImGui::End();
        

            ImGui::Render();
        
            SDL_SetRenderDrawColor(m_window->GetRenderer(), 100,100,100,255);
            SDL_RenderClear(m_window->GetRenderer());

            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_window->GetRenderer());

            SDL_RenderPresent(m_window->GetRenderer());
        }

        first_run = false;

    }

    return m_exit_status;
}

void Application::Stop()
{
    m_isrunning = false;
}