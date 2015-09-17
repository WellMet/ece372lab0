
/* 
 * File:   timer.c
 * Author: Sheldon Ruiz
 *
 * Created on September 8, 2015, 10:19 AM
 */

#include <xc.h>


void initTimer1(){
    TMR1 = 0;// clear TMR1
    PR1 = 1221*2;// Initialize PR1
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator
    IEC0bits.T1IE = 1;// Enable the interrupt
    IFS0bits.T1IF = 0;// Put the flag down
    IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    T1CONbits.TON = 1;// Turn the timer on
}

initTimer2(){
    TMR2 = 0;// clear TMR1
    T2CONbits.TCKPS = 0; // Initialize pre-scalar
    T2CONbits.TCS = 0; // Setting the oscillator
    IFS0bits.T2IF = 0;// Put the flag down
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
    TMR2 = 0;
    PR2 = delay*624;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    
    while(IFS0bits.T2IF == 0){
        T2CONbits.ON = 0;
    }
}