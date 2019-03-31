/*
 * main.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: desta
 */

#include <prot.h>

void delay(void) {
    volatile unsigned loops = 50000; // Start the delay counter at 50,000
    while (--loops > 0);             // Count down until the delay counter reaches 0
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1REN |= BIT1;            // Connect resistor on P1.1 to P1OUT
    P1OUT |= BIT1;            // Set output register for P1.1 to '1'
    P2DIR |= BIT0 | BIT1 | BIT2;            // Make P1.0 an output
    P2OUT &= ~(BIT0 | BIT1);
    PM5CTL0 &= ~LOCKLPM5;    // Unlock ports from power manager

    for (;;) {
        delay();             // Run the delay sub-routine
        if (!(P1IN & BIT1))  // Read the input from P1.1 and check its state
            P2OUT |= BIT2;   // If the button was pressed, turn on the LED
        else
            P2OUT &= ~BIT2;  // If the button wasn't pressed, turn off the LED.
    }
}
