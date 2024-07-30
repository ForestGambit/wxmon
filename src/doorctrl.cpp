#include "doorctrl.h"

#include <modbus/modbus.h>

doorctrl::doorctrl(const char* addr, int port, float pulse_duration)
:   m_doorIP{addr}, 
    m_port{port},
    m_pulseDuration{pulse_duration}
{
    m_modbus = modbus_new_tcp(m_doorIP.c_str(), port);

    
}

doorctrl::~doorctrl()
{
    modbus_free(m_modbus);
}

//Return true if open
bool doorctrl::GetStatus()
{
    uint8_t inputreg;
    modbus_connect(m_modbus);
    int status = modbus_read_input_bits(m_modbus, 0, 1, &inputreg);
    modbus_close(m_modbus);

    if(inputreg == 1)
        m_status = false;
    else
        m_status = true;

    return m_status;
}

void doorctrl::Operate()
{
    uint16_t data[2];
    modbus_set_float_cdab(m_pulseDuration, data);
    int writeret = modbus_write_registers(m_modbus, 0x0010, 4, data);
}