/**
 * Header file containing all register addresses
*/

#ifndef _HTU21d_H_
#define	_HTU21d_H_
#endif

// i2c address
#define ADDR            _u(0x40)

//Hardware Registers
#define TrigTempMeasurement_HM          _u(0xE3)        //Trigger Temperature Measurement 0xE3 Hold master
#define TrigHumidityMeasurement_HM      _u(0xE5)        //Trigger Humidity Measurement 0xE5 Hold master
#define TrigTempMeasurement_NHM         _u(0xF3)        //Trigger Temperature Measurement 0xF3 No Hold master
#define TrigHumidityMeasurement_NHM     _u(0xF5)        //Trigger Humidity Measurement 0xF5 No Hold master
#define WriteUserReg                    _u(0xE6)        //Wrie User Register
#define ReafUserReg                     _u(0xE7)        //Wrie User Register
#define SoftReset                       _u(0xFE)        //Soft Reset

