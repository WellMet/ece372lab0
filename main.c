/* 
 * File:   main.c
 * Author: Sheldon Ruiz
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3
} stateType;

volatile stateType stateCurrent;
volatile stateType stateNext;
//TODO: Use volatile variables that change within interrupts

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    //initTimer2();
    initTimer1();
    
    while(1){
        if(PORTDbits.RD6 != 0){
            switch(stateCurrent){
            case(led1):
                turnOnLED(1);
                stateNext = led2;
                break;
            case(led2):
                turnOnLED(2);
                stateNext = led3;
                break;
            case(led3):
                turnOnLED(3);
                stateNext = led1;
                break;
            default:
                stateCurrent = led1;
                break;
            }
        }
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0; //pull down interrupt flag
    T1CONbits.TON = 0; //stop timer
    switch(stateCurrent){
        case(led1):
            stateNext = led3;
            break;
        case(led2):
            stateNext = led1;
            break;
        case(led3):
            stateNext = led2;
            break;
    }
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL6SRS) _CNInterrupt(){
    IFS1bits.CNDIF = 0;
    TMR1 = 0;
    if(PORTDbits.RD6 == 0){
      T1CONbits.TON = 1; //Turn on timer
    }
    else if(PORTDbits.RD6 == 1){
        T1CONbits.TON = 0;
        stateCurrent = stateNext;
    }
}

