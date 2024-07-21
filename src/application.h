#pragma once
#include <memory>

#include "window.h"
#include "wxdata.h"
#include "doorctrl.h"

class Application
{
public:
    Application();
    ~Application();

    int Run();
    void Stop();

private:
    int m_exit_status{0};
    bool m_isrunning{true};
    bool m_show_panel{true};

    window* m_window{nullptr};
    wxdata* m_wxdata;
    doorctrl* m_doorctrl;
};