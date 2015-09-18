/* 
 * File:   switch.c
 * Author: Sheldon Ruiz
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>
#define OUTPUT 0
#define INPUT 1

//setup the button rd6 for input
void initSwitch1(){
    //Configure the switch as an input
    TRISDbits.TRISD6 = INPUT;
    
    //enable interrupt
    CNCONDbits.ON = 1;
    CNENDbits.CNIED6 = 1;
    IEC1bits.CNDIE = 1;
    
    //flag and pull up resistor
    CNPUDbits.CNPUD6 = 1;
    IFS1bits.CNDIF = 0;
}