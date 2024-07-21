#include <modbus/modbus.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    modbus_t* mb;
    uint16_t tab_reg[32];
    uint8_t inputreg;

    mb = modbus_new_tcp("172.25.0.130", 502);

    modbus_connect(mb);

    //modbus_read_input_bits(mb, 0,1,&inputreg);
    printf("%d\n", inputreg);

    uint16_t data[2];
    modbus_set_float_cdab(1.0f, data);
    int writeret = modbus_write_registers(mb, 0x0010, 4, data);
    fprintf(stderr, "%d\n", writeret);
    
    modbus_close(mb);
    modbus_free(mb);
}

