#include "common/def.h"


#define TRIGGER_DDR     DDRD
#define ECHO_DDR        DDRD
#define TRIGGER_PORT    PORTD
#define ECHO_PORT       PIND
#define TRIGGER_PIN     6
#define ECHO_PIN        3


void ultrasonicInit();
void ultrasonicTrigger();
uint16_t ultrasonicDistance();