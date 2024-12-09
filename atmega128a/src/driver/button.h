#include "common/def.h"

#define LED_DDR			DDRA
#define LED_PORT		PORTA
#define BUTTON_DDR    DDRA
#define BUTTON_PIN    PINA
#define BUTTON_ON     4
#define BUTTON_OFF    5
#define BUTTON_START  6
#define BUTTON_STOP   7


enum {PUSHED, RELEASED}; // 0, 1
enum {NO_ACT, ACT_PUSH, ACT_RELEASED}; // 0, 1 ,2

typedef struct 
{
    volatile uint8_t *ddr; 
    volatile uint8_t *pin;
    uint8_t           btnPin;
    uint8_t           prevState;
}Button;

void buttonInit(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber);
uint8_t buttonGetState(Button *button);