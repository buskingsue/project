#include "denamu.h"

void denamuInit(void)
{
    DDRB |= (1<<PORTB4);
    TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS02) |(1<<CS01);
}

void denamuRun(uint8_t duty)
{
    OCR0 = duty;
}
