#include "pwm16.h"

void pwm16Init()
{
    // PWM 출력 핀 설정 (포트 E)
    DDRE |= (1 << PORTE3); // OC3A 핀 (포트 E, 핀 3) - MAIN PWM 출력
    DDRE |= (1 << PORTE4); // OC3B 핀 (포트 E, 핀 4) - LEFT PWM 출력
    DDRE |= (1 << PORTE5); // OC3C 핀 (포트 E, 핀 5) - RIGHT PWM 출력

    // 타이머/카운터3 제어 레지스터 A 설정
    TCCR3A |= (1 << COM3A1) | (1 << WGM31); // OC3A 비반전 모드, Fast PWM 설정
    TCCR3A |= (1 << COM3B1);                // OC3B 비반전 모드 설정
    TCCR3A |= (1 << COM3C1);                // OC3C 비반전 모드 설정

    // 타이머/카운터3 제어 레지스터 B 설정
    TCCR3B |= (1 << WGM33) | (1 << WGM32);  // Fast PWM 모드 (WGM 모드 14)
    TCCR3B |= (1 << CS31) | (1 << CS30);    // 64분주 설정

    // PWM 주기 설정 (ICR3: Top 값)
    ICR3 = 4999; // 20ms 주기 (16MHz 클럭, 64분주 기준)
}
//usart 통신할때 싱크로너스 동기 통신
//uarto 비동기 통신 전이중방식 전화기
//isp 프로그램 업로드
//lsb부터 보냄