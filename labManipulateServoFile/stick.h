/**
* @file stick .h
* @author Paco Rodriguez
* @date Spring 2021
*
* @brief Basic module to manage the SysTick timer
*
*/
# ifndef STICK_H
#define STICK_H
/* SECTION 1: Included header files to compile this file */
#include <stdint.h>
/* SECTION 2: Public macros */
/* SECTION 3: Public types */
/* SECTION 4: Public variables :: declarations , extern mandatory */
/* SECTION 5: Public functions :: declarations , extern optional
Rule exception ( callbacks ) :: declarations , extern recommended */
/**
* @brief Stop the timer
* @remarks The interrupt flag is cleared ( side effect )
*/
void stickStop ( void );
/**
* @brief Start the timer
* @remarks The interrupt flag is cleared ( side effect )
* @note This function ensures the clock source bit is 1
*/
void stickStart ( void );
/**
* @brief Determine if the timer is running or not
* @remarks The interrupt flag is cleared ( side effect )
* @return 1 if the timer is running , 0 otherwise
*/
uint32_t stickIsStarted ( void );
/**
* @brief Enable timer interrupts
* @remarks The interrupt flag is cleared ( side effect )
*/
void stickEnableInt ( void );
/**
* @brief Disable timer interrupts
* @remarks The interrupt flag is cleared ( side effect )
*/
void stickDisableInt ( void );
/**
* @brief Determine if the timer interrupts are enabled or not
* @remarks The interrupt flag is cleared ( side effect )
* @return 1 if the interrupts are enabled , 0 otherwise
*/
uint32_t stickIsIntEnabled ( void );
/**
* @brief Program a new timer period
* @param [in] p New period (in clock cycles )
* @remarks Only the 24 LSBs of p are used
*/
void stickSetPeriod ( uint32_t p);
/**
* @brief Get the current timer period
* @return Current period (in clock cycles )
* @remarks The result is actually a 24 bits value
*/
uint32_t stickGetPeriod ( void );
/**
* @brief Get the current timer value
* @return Current timer value (in clock cycles )
*/
uint32_t stickGetCount ( void );
/**
* @brief Clear the timer interrupt flag
*/
void stickClearIntFlag ( void );
/**
* @brief Determine if the interrupt flag is set or not
* @remarks The interrupt flag is cleared ( side effect )
* @return 1 if the flag is set , 0 otherwise
*/
uint32_t stickIsIntFlagActive ( void );
/**
* @brief Callback function executed from the timer interrupt handler
* @note The extern keyword is not mandatory but we use it here to reinforce
* the idea this function must be implemented elsewhere
* (it is extern , it actually belongs to the higher level module using this one)
*/
extern void stickCallback ( void );
# endif // STICK_H

