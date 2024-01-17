/**
* @file servo .h
* @author Paco Rodriguez
* @date Spring 2021
*
* @brief Servo (0 to 180 ) management using the stick module
*
* Main characteristics of this module :
* - Servo signal is connected to P1 .7 ( fixed )
* - Timer clock frequency is 18 MHz ( fixed )
* - Servo angle ( taking a Parallax 900 -00005 as example ) ranges from 0 to 180
* - The generated PWM signal has a fixed frequency of 50 Hz (20 ms period )
* - The pulse width to get the servo 0 angle is 1 ms
* - The pulse width to get the servo 180 angle is 2 ms
* - The module offers the possibility to move the servo to an absolute position
* as well as to move the servo some degress relative to its current position
*
*/
# ifndef SERVO_H
#define SERVO_H
/* SECTION 1: Included header files to compile this file */
#include <stdint.h>
/* SECTION 2: Public macros */
/* SECTION 3: Public types */

/* SECTION 4: Public variables :: declarations , extern mandatory */
/* SECTION 5: Public functions :: declarations , extern optional
Rule exception ( callbacks ) :: declarations , extern recommended */

/**
* @brief Set a new servo absolute position
* @param [in] pos New absolute angle ( between 0 y 180)
* If the new angle is not in the valid range [0, 180] moves the servo
* to the closest valid position
* @return New servo angle
*/

uint32_t servoSetAbsPosition ( uint32_t pos);

/**
* @brief Set a new servo relative position
* @param [in] delta Angular relative increment / decrement [ -180 , +180]
* with respect the current servo position .
* If the resulting angle is not in the valid range [0, 180] moves the servo
* to the closest valid position
* @return New servo angle
*/

uint32_t servoSetRelPosition ( int32_t delta );

/**
* Initialize the servo module
* Configures pin P1 .7 as a GPIO output with an initial value 0 and
* moves the servo to the central position (90 )
* @return New servo angle (90 )
*/

uint32_t servoInit ( void );

# endif // SERVO_H
