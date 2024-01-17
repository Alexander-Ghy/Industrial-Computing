/**
* @file stick .c
* @author Paco Rodriguez
* @date Spring 2021
*
* @brief Basic module to manage the SysTick timer
*
*/
/* SECTION 1: Included header files to compile this file */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
# include "stick.h"
/* SECTION 2: Private macros */
/* SECTION 3: Private types */
/* SECTION 4: Public variables :: definitions , no extern
( must match declarations in header file ) */
/* SECTION 5: Private variables :: definitions , static mandatory
(no need to declare , definitions include declarations ) */
/* SECTION 6: Private functions :: declarations , static mandatory
Rule exception ( ISRs ) :: declarations , no static */

/**
* @brief SysTick interrupt handler
*/
void SysTick_Handler ( void );

/**
* @brief Empty weak implementation of the callback
* @remarks This function is expected to be replaced with another ,
* non - weak implementation in a higher level module
*/

void stickCallback(void) __attribute__((weak));

/* SECTION 7: Private functions :: definitions , static mandatory
Rule exception ( ISRs ) :: definitions , no static
Public functions :: definitions , no extern
Function definitions ( private & public ) written in any order */
/**
* @brief SysTick interrupt handler
*
* Clear the timer interrupt flag and call the callback .
* It is the callback where the functionality is to be added
*/

void stickISR ( void ) {
    stickClearIntFlag ();
    stickCallback ();
}

/**
* @brief Empty weak implementation of the callback
* @remarks This function is expected to be replaced with another ,
* non - weak implementation in a higher level module
*
* This implementation offers no functionality (it is empty ).
* It is created with the sole purpose to be able to compile this module
* before the development of the higher level module that will use it
*/

void stickCallback(void) {

}

/**
* @brief Stop the timer
* @remarks The interrupt flag is cleared ( side effect )
*/

void stickStop ( void ) {
SysTick -> CTRL &= ~ SysTick_CTRL_ENABLE_Msk ;
}

/**
* @brief Start the timer
* @remarks The interrupt flag is cleared ( side effect )
* @note This function ensures the clock source bit is 1
*/

void stickStart ( void ) {
    SysTick -> CTRL |= ( SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk );
}

/**
* @brief Determine if the timer is running or not
* @remarks The interrupt flag is cleared ( side effect )
* @return 1 if the timer is running , 0 otherwise
*/

uint32_t stickIsStarted ( void ) {
    return ( SysTick -> CTRL & SysTick_CTRL_ENABLE_Msk ) >> SysTick_CTRL_ENABLE_Pos ;
}

/**
* @brief Enable timer interrupts
* @remarks The interrupt flag is cleared ( side effect )
*/

void stickEnableInt ( void ) {
    SysTick -> CTRL |= SysTick_CTRL_TICKINT_Msk ;
}

/**
* @brief Disable timer interrupts
* @remarks The interrupt flag is cleared ( side effect )
*/

void stickDisableInt ( void ) {
    SysTick -> CTRL &= ~ SysTick_CTRL_TICKINT_Msk ;
}

/**
* @brief Determine if the timer interrupts are enabled or not
* @remarks The interrupt flag is cleared ( side effect )
* @return 1 if the interrupts are enabled , 0 otherwise
*/

uint32_t stickIsIntEnabled ( void ) {
    return ( SysTick -> CTRL & SysTick_CTRL_TICKINT_Msk ) >> SysTick_CTRL_TICKINT_Pos ;
}

/**
* @brief Program a new timer period
* @param [in] p New period (in clock cycles )
* @remarks Only the 24 LSBs of p are used
*/

void stickSetPeriod ( uint32_t p) {
    SysTick -> LOAD = ((p -1) & SysTick_LOAD_RELOAD_Msk );
}

/**
* @brief Get the current timer period
* @return Current period (in clock cycles )
* @remarks The result is actually a 24 bits value
*/

uint32_t stickGetPeriod ( void ) {
    return (( SysTick -> LOAD & SysTick_LOAD_RELOAD_Msk ) + 1);
}

/**
* @brief Get the current timer value
* @return Current timer value (in clock cycles )
*/

uint32_t stickGetCount ( void ) {
    return ( SysTick ->VAL & SysTick_VAL_CURRENT_Msk );
}

/**
* @brief Clear the timer interrupt flag
*/

void stickClearIntFlag ( void ) {
    SysTick -> CTRL &= ~ SysTick_CTRL_COUNTFLAG_Msk ;
}

/**
* @brief Determine if the interrupt flag is set or not
* @remarks The interrupt flag is cleared ( side effect )
* @return 1 if the flag is set , 0 otherwise
*/

uint32_t stickIsIntFlagActive ( void ) {
    return ( SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk ) >>  - SysTick_CTRL_COUNTFLAG_Pos ;
}


