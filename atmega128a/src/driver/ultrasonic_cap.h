#include "common/def.h"



#define TRIGGER_DDR     DDRD
#define TRIGGER_PORT    PORTD
#define TRIGGER_PIN     6

void ultraInit();
void ultraTrigger();
uint16_t ultraDistance();