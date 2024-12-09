#include "ultrasonic_cap.h"


volatile uint16_t startCount = 0;
volatile uint16_t endCount = 0;
volatile uint8_t risingEdge = 1;

ISR(TIMER3_CAPT_vect)
{
    if(risingEdge)
    {
        startCount = ICR3;
        TCCR3B &= ~(1<<ICES3);  // 폴링으로 변경
        risingEdge = 0;
    }
    else
    {
        endCount = ICR3;
        TCCR3B |= (1<<ICES3);   // 라이징으로 변경
        risingEdge = 1;
    }
}



void ultraInit()
{
    TRIGGER_DDR |= (1 << TRIGGER_PIN);
    DDRE &= ~(1 << PINE7);

    // Timer3 설정 -> Input Capture 상승 엣지 / 64분주
    TCCR3B |= (1 << ICES3) | (1 << CS31) | (1 << CS30);

    // Input Capture Enable
    ETIMSK |= (1 << TICIE3);
}

void ultraTrigger()
{
    TCNT1 = 0;

    TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // Low
    _delay_us(1);
    TRIGGER_PORT |= (1 << TRIGGER_PIN); // High
    _delay_us(10);
    TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // Low
}

uint16_t ultraDistance()
{
    uint16_t pulseWidth = endCount - startCount;
    uint32_t timeUs = pulseWidth * 4;
    uint16_t distance = (timeUs * 34) / 2000;
    return distance;
}