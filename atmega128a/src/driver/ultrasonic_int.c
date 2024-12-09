#include "ultrasonic_int.h"

volatile uint16_t startCount;
volatile uint16_t endCount;
volatile uint16_t usTcnt;

ISR(INT3_vect)
{
    if(ECHO_PORT & (1<<ECHO_PIN))   // Echo핀이 Rising 이면
    {
        startCount = TCNT1;         // startCount에 현재의 값 저장

        EICRA &= ~(1<<ISC30);       // falling edge로 변경
        EICRA |= (1<<ISC31);
    }
    else
    {
        endCount = TCNT1;   
        usTcnt = endCount - startCount;

        EICRA |= (1<<ISC31) | (1<<ISC30);   // Rising Edge 인터럽트 발생
    }
}



void ultrasonicInit()
{
    TRIGGER_DDR |= (1<<TRIGGER_PIN);        // 출력
    ECHO_DDR &= ~(1<<ECHO_PIN);             // 입력

    EICRA |= (1<<ISC31) | (1<<ISC30);   // Rising Edge 인터럽트 발생
    EIMSK |= (1<<INT3);                 // 인터럽트 3번 인에이블

    TCCR1B |= (1<<CS11) | (1<<CS10);    // 64분주
}

void ultrasonicTrigger()
{
    TCNT1 = 0;

    TRIGGER_PORT &= ~(1<<TRIGGER_PIN);  // Low
    _delay_us(1);
    TRIGGER_PORT |= (1<<TRIGGER_PIN);   // High
    _delay_us(10);
    TRIGGER_PORT &= ~(1<<TRIGGER_PIN);  // Low
}

uint16_t ultrasonicDistance()
{
    uint16_t distance = (uint16_t)(usTcnt * 0.000004 * 34000) / 2;
    return distance;
}