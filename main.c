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
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

volatile stateType state;
//TODO: Use volatile variables that change within interrupts

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
    while(1){
        switch(state){
            case wait:
                if(IFS1bits.CNDIF == 1){
                    state = wait2;
                }
                break;
            case wait2:
                if(IFS1bits.CNDIF == 1){
                    //turn on previous LED
                }
            case debounceRelease:
                if(IFS1bits.CNDIF == 1){
                    turnOnLED(1);
                    state = led1;
                }
                break;
        }
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    //After two seconds timer 1 interrupt goes high.  Reverse to previous LED
    IFS0bits.T1IF = 0;
    state = wait2;

}

