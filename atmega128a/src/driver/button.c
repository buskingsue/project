#include "button.h"


// 인스턴스생성
void buttonInit(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber)
{
    button->ddr = ddr;
    button->pin = pin;
    button->btnPin = pinNumber;
    button->prevState = RELEASED; // PUSH 0 
    *button->ddr &= ~(1<<button->btnPin);
}
// DDR의 주소 넣고 / PIN의 주소넣고!

uint8_t buttonGetState(Button *button)
{           
    uint8_t curState = *button->pin & (1<<button->btnPin);
             // 0    <-  PINDx의 값 기본1 누르면0   1
             // 1    <-  PINDx의 값 떼면1          1   

    if ((curState == PUSHED) && (button->prevState == RELEASED))
    {               
        _delay_ms(50);
        button->prevState = PUSHED; //0
        return ACT_PUSH; 
    }                                       
    else if ((curState != PUSHED) && (button->prevState == PUSHED)) // 누르지 않고 &와 &&차이
    {           // 누른상태 아니고             전 상태가 누르는 상태면
        _delay_ms(50); 
        button->prevState = RELEASED; // 풀어진 상태
        return ACT_RELEASED;
    }
    return NO_ACT; // 누르고 있는상태 
}
