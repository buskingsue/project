#include "common/def.h"
// #include "driver/led.h"

// #include "driver/pwm8.h"
// #include "driver/uart0.h"
// #include "driver/i2c_lcd.h"
#include "driver/i2c.h"
// #include "driver/ultrasonic_int.h"
// #include "driver/ultrasonic_cap.h"

// #include <avr/interrupt.h>
// #include <driver/pwm16.h>

// void apInit();
// void apMain();
#include "driver/button.h"
// #include "driver/eyeled.h"
#include "driver/display.h"
#include "driver/denamu.h"
#include "driver/pwm16.h"
#include "driver/ultrasonic.h"
#include "driver/ultrasonic_int.h"
#include "driver/ultrasonic_cap.h"

void motor_forward(void);
void motor_reverse(void);
void motor_stop(void);



void apInit();
void apMain();