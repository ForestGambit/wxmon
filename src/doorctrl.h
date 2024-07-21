#pragma once

#include <modbus/modbus.h>

#include <string>

class doorctrl
{
public:
    doorctrl(const char* addr, int port = 502, float pulse_duration = 0.5f);
    ~doorctrl();

    bool GetStatus();
    void Operate();

private:

    modbus_t* m_modbus;

    float m_pulseDuration;
    std::string m_doorIP;
    int m_port;
    bool m_status;
};