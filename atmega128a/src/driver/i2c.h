#include "common/def.h"

#define I2C_DDR        DDRD
#define I2C_SCL        PORTD0
#define I2C_SDA        PORTD1

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_TxData(uint8_t data);
void I2C_TxByte(uint8_t devAddrRW, uint8_t data);