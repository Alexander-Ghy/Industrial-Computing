/**
* @file servo .c
* @author Paco Rodriguez
* @date Spring 2021
*
* @modified by Alexander Ghyoot, Michal kos
* @modified date December 2021
*
* @brief Servo (0° to 180° ) management using the stick module
*
* Main characteristics of this module :
* - Servo signal is connected to P1 .7 ( fixed )
* - Timer clock frequency is 18 MHz ( fixed )
* - Servo angle ( taking a Parallax 900 -00005 as example ) ranges from 0° to 180°
* - The generated PWM signal has a fixed frequency of 50 Hz (20 ms period )
* - The pulse width to get the servo 0° angle is 1 ms
* - The pulse width to get the servo 180° angle is 2 ms
* - The module offers the possibility to move the servo to an absolute position
* as well as to move the servo some degress relative to its current position
*
*/

/* SECTION 1: Included header files to compile this file */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "stick.h"
#include "servo.h"

/* SECTION 2: Private macros */
#define SERVO_PWM_PERIOD 360000 /**< Whole period clock cycles */
#define SERVO_PWM_MIN_PULSE 18000 /**< Clock cycles for the 0° pulse */
#define SERVO_PWM_1DEG_PULSE 100 /**< Clock cycles for a relative increment of 1° */
#define SERVO_ANG_MIN 0 /**< Absolute min angle */
#define SERVO_ANG_MED 90 /**< Absolute central angle */
#define SERVO_ANG_MAX 180 /**< Absolute max angle */

/**
* @brief Get the number of clock cycles from an absolute angle value
*/

#define SERVO_PWM_PULSE(x) ( SERVO_PWM_MIN_PULSE + x* SERVO_PWM_1DEG_PULSE )

/* SECTION 3: Private types */
/**
* @brief Structure with all the module 's private info
*/

typedef struct {
    uint32_t on_time ; /**< Positive semi - period clock cycles */
    uint32_t off_time ; /**< Negative semi - period clock cycles */
    uint32_t new_pos ; /**< New servo absolute position */
    uint32_t current_pos ; /**< Current servo absolute position */
    uint32_t state ; /**< State information to genertate the PWM signal
    0 => at the start of the positive semi - period
    1 => at the start of the negative semi - period */
} servo_pulse_t ;

/* SECTION 4: Public variables :: definitions , no extern
( must match declarations in header file ) */

/* SECTION 5: Private variables :: definitions , static mandatory
(no need to declare , definitions include declarations ) */

static servo_pulse_t _servo ;

/* SECTION 6: Private functions :: declarations , static mandatory
Rule exception ( ISRs ) :: declarations , no static */

/**
* @brief Callback executed from the timer ISR
*
* In fact this isn 't a private function (it 's invoked from the stick module ).
* But we don 't want the function to be visible (in the .H file ) as we don 't
* want any other code except the stick module to execute it.
* So we do our best here : " hide " the function declaration in the .C file
* ( pretending it is private ) with the hope the rest of the application
* don 't see it and thus forbidding others to call the function
* ( which is impossible , as it does not use static ).
*/

void stickCallback ( void );

/**
* @brief Prepare the servo for a new absolute position
* Sets the module information so that the next callback execution that
* corresponds to the start of the PWM period the new angle will be used .
*/

static void _servoSetPos ( void );

    /* SECTION 7: Private functions :: definitions , static mandatory
    Rule exception ( ISRs ) :: definitions , no static
    Public functions :: definitions , no extern
    Function definitions ( private & public ) written in any order */

static void _servoSetPos (void){
    _servo.current_pos = _servo.new_pos;
    _servo.on_time = SERVO_PWM_PULSE(_servo.current_pos);
    _servo.off_time = SERVO_PWM_PERIOD - _servo.on_time;
}

uint32_t servoSetAbsPosition ( uint32_t pos) {
    // Check input argument , applying saturation if needed
    if (pos > SERVO_ANG_MAX ){
        pos = SERVO_ANG_MAX;
    }
    // Set the new angle .
    // This will be effective used at the start of the next positive semi - period .
    _servo.new_pos = (uint32_t) pos;
    // Return the new angle
    return _servo.new_pos ;
}

uint32_t servoSetRelPosition ( int32_t delta ) {
    int32_t new_pos ;
    // Calculate the new absolute angle , applying saturation if needed
    new_pos = _servo.current_pos + delta ;
    if ( new_pos < SERVO_ANG_MIN ){
        new_pos = SERVO_ANG_MIN;
    }
    if ( new_pos > SERVO_ANG_MAX ){
        new_pos = SERVO_ANG_MAX;
    }
    // Set the new angle .
    // This will be effective used at the start of the next positive semi - period .
    _servo.new_pos = ( uint32_t ) new_pos ;
    // Return the new angle
    return _servo.new_pos ;
}

uint32_t servoInit ( void ) {
    // Configure P1.7 as GPIO output
    P1 -> SEL1 &= ~ BIT7 ;
    P1 -> SEL0 &= ~ BIT7 ;
    P1 ->DIR |= BIT7 ;
    P1 ->DS &= ~ BIT7 ;
    // Set the central servo position
    _servo.new_pos = SERVO_ANG_MED ;
    _servoSetPos ();
    // To start generating the PWM signal :
    // 1.- Set the output signal to 1
    P1 ->OUT |= BIT7 ;
    // 2.- Program the positive semi - period in the timer ( enabling interrupts )
    stickStop ();
    stickEnableInt ();
    stickSetPeriod (_servo.on_time);
    stickStart ();
    // 3.- Update state so the next callback execution the code moves
    // to the start of the negative semi - period
    _servo.state = 1;
    // Return the servo position
    return _servo.new_pos ;
}

void stickCallback ( void ) {
    // Check state to determine what to do
    if ( _servo.state == 0) {
        // 1.- Update absolute angle and calculations just in case
        // the application has set a new_pos angle since the last time
        // we got here .
        // At the start of the positive semi - period
        // 2.- Set the output signal to 1
        P1 ->OUT |= BIT7 ;
        // 3.- Program the positive semi - period in the timer
        _servoSetPos();
        stickStop ();
        stickSetPeriod(_servo.on_time);
        stickStart();
        // 3.- Update state so the next callback execution the code moves
        // to the start of the negative semi - period
        _servo.state = 1;

    } else {
        // At the start of the negative semi - period
        // 1.- Set the output signal to 0
        P1 ->OUT &= ~ BIT7 ;
        // 2.- Program the negative semi - period in the timer
        stickStop ();
        stickSetPeriod(_servo.off_time);
        stickStart ();
        // 3.- Update state so the next callback execution the code moves
        // to the start of the positive semi - period
        _servo.state = 0;

    }
}
