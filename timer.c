
/* 
 * File:   timer.c
 * Author: Sheldon Ruiz
 *
 * Created on September 8, 2015, 10:19 AM
 */

#include <xc.h>

//setup the timer for the program
void initTimer1(){
    TMR1 = 0;// clear TMR1
    PR1 = 1221*2;// Initialize PR1
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator
    IEC0bits.T1IE = 1;// Enable the interrupt
    IFS0bits.T1IF = 0;// Put the flag down
    IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    T1CONbits.TON = 0;// Turn the timer on
}

//timer 2 setup. not used
initTimer2(){
    TMR2 = 0;// clear TMR2
    T2CONbits.TCKPS = 0; // Initialize pre-scalar
    T2CONbits.TCS = 0; // Setting the oscillator
    IFS0bits.T2IF = 0;// Put the flag down
}

//delay setup. not used
delayMs(int delay){
    TMR2 = 0;
    PR2 = delay*624;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    
    while(IFS0bits.T2IF == 0){
        T2CONbits.ON = 0;
    }
}