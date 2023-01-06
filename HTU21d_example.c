/**
 *  Copyright (c) 2022 Milko van Valen
**/

#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include "HTU21d.h"

/**
 * Example codebase to read an hTU21d accelerometer
 * Standard address: 0x53
 * 
*/

#ifdef i2c_default
void hTU21d_init() {
    printf("Init, performing soft reset\n");
    uint8_t reg = SoftReset;
    i2c_write_blocking(i2c_default, ADDR, &reg, 1, false);   
}

uint16_t hTU21d_read_raw_Tempurature(void){
    printf("Reading...\n");
    uint16_t raw_Temp = 0;
    uint8_t reg_Temp = TrigTempMeasurement_HM;
    uint8_t buf_Temp[3];

    i2c_write_blocking(i2c_default, ADDR, &reg_Temp, 1, false);
    i2c_read_blocking(i2c_default, ADDR, buf_Temp, 3, false);

    raw_Temp = ((uint16_t) buf_Temp[0] << 8) | (uint16_t) buf_Temp[1];
    //raw_Temp = raw_Temp >> 2;


    return raw_Temp;
}

float hTU21d_Temperature_Conversion(void){
    uint16_t raw_Temp;
    float conversion;

    raw_Temp = hTU21d_read_raw_Tempurature();

    conversion =  (raw_Temp * 175.72 / 65536.0) - 46.85;

    return conversion;
}


#endif

int main(){
    stdio_init_all();

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / ADXL_example requires a board with I2C pins
        puts("Default I2C pins were not defined");
#else
    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    hTU21d_init();

    printf("Hello, HTU21d! Reading temperature and Humidity data from sensor...\n");

    
    int16_t Temp;
    //int16_t Humidity;
    

    sleep_ms(250); // sleep so that data polling and register update don't collide
    while (1) {
        Temp = hTU21d_Temperature_Conversion();
        printf("Temperature: %d °C\n", Temp);
        // poll every 500ms
        sleep_ms(500);
    }

#endif
    return 0;
}