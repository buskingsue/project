#include "i2c.h"


void I2C_Init()
{
    I2C_DDR |= (1<<I2C_SCL) | (1<< I2C_SDA); // 출력 설정
    TWBR = 72;    // 100KHz
    //TWBR = 32;    // 200KHz
    //TWBR = 12;    // 400KHz
}

void I2C_Start()
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // TWINT에 1을 셋트하여 인터럽트를 발생시키는 것 같지만
    // 소프트웨어적으로 1을 셋트히여 플래그를 클리어 함 !!
    while(!(TWCR & (1<<TWINT))); // 하드웨어적으로TWINT 시점을 결정
}

void I2C_Stop()
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<< TWSTO);    //stop 비트 설정
}

void I2C_TxData(uint8_t data) // data 1바이트 전송
{
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));    //전송 완료 대기
}

void I2C_TxByte(uint8_t devAddrRW, uint8_t data)
{
    I2C_Start();
    I2C_TxData(devAddrRW);
    I2C_TxData(data);
    I2C_Stop();
}