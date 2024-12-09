#include "ap.h"

void apInit()
{
    
}

void apMain(void)
{
  

    // DDRA |= (1<<PORTA0) | (1<<PORTA1) | (1<<PORTA2);//0x07; // PA0, PA1, PA2 출력 설정
    LED_PORT = 0x00; // LED 초기화 (모두 끄기)

    // 버튼 초기화
    Button btnOn, btnOff, btnStart, btnStop;

    buttonInit(&btnOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);
    buttonInit(&btnOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
    buttonInit(&btnStart, &BUTTON_DDR, &BUTTON_PIN, BUTTON_START);
    buttonInit(&btnStop, &BUTTON_DDR, &BUTTON_PIN, BUTTON_STOP);

    // denamuInit(); // PWM 초기화
    // uint8_t dutyCycle = 0;  // 초기 듀티 사이클 0 (최소 속도)

    pwm16Init();

    // PWM 초기화
    denamuInit();

    LCD_Init();
    uint8_t buff[30];
    LCD_WriteStringXY(0,0,"DORAZO ROBOT");


    //초음파 
    uint16_t distance = 0;
    ultraInit();
    //sei();

    while (1)
    {
       // ON 버튼을 눌렀을 때: LED 블루 점등 및 메인 pwm 정위치
        if (buttonGetState(&btnOn) == ACT_PUSH)
        {
            
            // LCD 출력
            LCD_WriteStringXY(1, 0, "POWER ON        ");
            denamuRun(0);  // 속도 PWM 0 출력
            DDRA = 0x04;
            LED_PORT = 0x04;
            // LED_PORT |=  (1<<PORTA0) | (1<<PORTA3);    // 0x04 | 0x01  = 0x05;

            // LED_PORT &= 0xf0;

            OCR3A = 220;  // OC3A 듀티 사이클 설정 (PE3 핀)
            //오류가 뜰 수도 있는데 문제없이 그냥 빌드 됨
            
        }

        
        // OFF 버튼을 눌렀을 때: LED 끄기 및 PWM 정위치
        if (buttonGetState(&btnOff) == ACT_PUSH)
        {

            // LCD 출력
            LCD_WriteStringXY(1, 0, "POWER OFF        ");
            denamuRun(0);  // 속도 PWM 0 출력
            LED_PORT = 0x00;
            OCR3A = 220;
        }


        // START 버튼을 눌렀을 때: LED 켜기 및 보안 작동
        if (buttonGetState(&btnStart) == ACT_PUSH)
        {   
            // LCD 출력
            LCD_WriteStringXY(1, 0, "Security START");
            denamuRun(255);  // 최대 속도로 PWM 출력
            DDRA = 0x02;
            LED_PORT = 0x02;

            // denamuRun(255);
            while(1)
            {            
                // ultraTrigger();
                //     //초음파센서 거리측정
                // ultraDistance();
                
                OCR3A = 160;  // OC3A 듀티 사이클 설정 (PE3 핀)
                OCR3B = 125;  // OC3A 듀티 사이클 설정 (PE3 핀)
                OCR3C = 125;  // OC3C 듀티 사이클 설정 (PE5 핀)
                _delay_ms(500);

                
                // // 초음파 센서 값이 20 미만이면 멈춤
                // if(ultraDistance < 20)
                // {
                    
                //     LCD_WriteStringXY(1, 0, "ANERMY        ");
                //     DDRA = 0x01;
                //     LED_PORT = 0x01;    // LED 상태 변경
                //     denamuRun(0);  // 속도 PWM 0 출력
                //     break;
                    
                // }

                if (buttonGetState(&btnStop) == ACT_PUSH)
                {
                    //LCD 출력                  
                    LCD_WriteStringXY(1, 0, "Security STOP  ");
                    DDRA = 0x05;
                    LED_PORT |=  (1<<PORTA0) | (1<<PORTA2);    // 0x04 | 0x01  = 0x05;
                    denamuRun(0);  // 속도 PWM 0 출력
                    break;
                }
                if (buttonGetState(&btnOff) == ACT_PUSH)
                {
                    // LCD 출력
                    LCD_WriteStringXY(1, 0, "POWER OFF        ");
                    LED_PORT = 0x00;
                    OCR3A = 220;
                    denamuRun(0);  // 속도 PWM 0 출력
                    break;
                }
                OCR3A = 300; // OC3C 듀티 사이클 변경
                OCR3B = 620; // OC3C 듀티 사이클 변경
                OCR3C = 620; // OC3C 듀티 사이클 변경
                _delay_ms(500);

            // STOP 버튼으로 루프 종료
                if (buttonGetState(&btnStop) == ACT_PUSH)
                {
                    // LCD 출력
                    LCD_WriteStringXY(1, 0, "Security STOP  ");
                    DDRA = 0x05;
                    LED_PORT |=  (1<<PORTA0) | (1<<PORTA2);    // 0x04 | 0x01  = 0x05;
                    denamuRun(0);  // 속도 PWM 0 출력
                    break;
                }

                // OFF 버튼 동작 우선 처리
                if (buttonGetState(&btnOff) == ACT_PUSH)
                {
                    // LCD 출력
                    LCD_WriteStringXY(1, 0, "POWER OFF        ");
                    LED_PORT = 0x00;
                    OCR3A = 220;
                    denamuRun(0);  // 속도 PWM 0 출력
                    break;
                }
            }
            
        }


        // STOP 버튼을 눌렀을 때: LED 빨간색 및 PWM 그자리에서 멈춤
        if (buttonGetState(&btnStop) == ACT_PUSH)
        {

            // LCD 출력
            LCD_WriteStringXY(1, 0, "Security STOP  ");
            DDRA = 0x05;
            LED_PORT |=  (1<<PORTA0) | (1<<PORTA2);    // 0x04 | 0x01  = 0x05;
            denamuRun(0);  // 속도 PWM 0 출력
            
        }
    }
}
