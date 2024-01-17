/**
 * @file leds.c
 * @author Alexander Ghyoot, Michal Kos
 * @date October 2021
 *
 * @brief A source file for the leds module.
 *
 * A source file to be to be used by the user to control the leds on a msp432p401r Launchpad board.
 * This contains the implementation for the private and public functions for the leds module.
 *
 * @{
 */

/* ---------------- #includes needed for this file ----------------- */
#include "leds.h"

/* --------------------------- Private macros ----------------------------- */
#define NUM_LEDS (sizeof(ledsPinRef) / sizeof(output_ref_t))

/* ----------------------- Private data types ------------------------- */

/* ----------- Definition of private variables (with static) -------------- */
/* Private constant with references to the led pins */
static output_ref_t ledsPinRef[] = {
    {.odd = P1, .port_is_odd = 1, .mask = BIT0},  /* LP_LED1 on P1 .0 */
    {.even = P2, .port_is_odd = 0, .mask = BIT0}, /* LP_LED2_RED on P2 .0 */
    {.even = P2, .port_is_odd = 0, .mask = BIT1}, /* LP_LED 2_ GREEN on P2 .1 */
    {.even = P2, .port_is_odd = 0, .mask = BIT2}, /* LP_LED2_BLUE on P2 .2 */
    {.even = P2, .port_is_odd = 0, .mask = BIT6}, /* BP_LED1_RED on P2 .6 */
    {.even = P2, .port_is_odd = 0, .mask = BIT4}, /* BP_LED 1_ GREEN on P2 .4 */
    {.odd = P5, .port_is_odd = 1, .mask = BIT6},  /* BP_LED1_BLUE on P5 .6 */
};

/* Private variable with the status of the LEDs */
static uint8_t ledsStatus[NUM_LEDS];

/* ----------------- Definition of public variables --------------------- */

/* ---------- Declaration of private functions (with static) -------------- */
static void _ledEvenInit(DIO_PORT_Even_Interruptable_Type *port, uint16_t pin);
static void _ledOddInit(DIO_PORT_Odd_Interruptable_Type *port, uint16_t pin);
static void _ledInit(const output_ref_t *ref);

/* --------- Implementation of private functions (with static) ------------ */
static void _ledEvenInit(DIO_PORT_Even_Interruptable_Type *port, uint16_t pin)
{
    port->SEL0 &= ~(pin);
    port->SEL1 &= ~(pin);
    port->DIR |= pin;
    port->DS &= ~(pin);
}

static void _ledOddInit(DIO_PORT_Odd_Interruptable_Type *port, uint16_t pin)
{
    port->SEL0 &= ~(pin);
    port->SEL1 &= ~(pin);
    port->DIR |= pin;
    port->DS &= ~(pin);
}

static void _ledInit(const output_ref_t *ref)
{
    if (ref->port_is_odd)
    {
        _ledOddInit(ref->odd, ref->mask);
    }
    else
    {
        _ledEvenInit(ref->even, ref->mask);
    }
}

/* ---------------- Implementation of public functions ------------------ */
void ledsInit(void)
{
    led_ref_t i;
    for (i = 0; i < NUM_LEDS; i++)
    {
        _ledInit(&(ledsPinRef[i]));
        ledOff(i);
        ledsStatus[i] = 0;
    }
}

void ledOn(led_ref_t led_ref)
{
    if (led_ref < NUM_LEDS)
    {
        if (ledsPinRef[led_ref].port_is_odd)
        {
            ledsPinRef[led_ref].odd->OUT |= ledsPinRef[led_ref].mask;
        }
        else
        {
            ledsPinRef[led_ref].even->OUT |= ledsPinRef[led_ref].mask;
        }
        ledsStatus[led_ref] = 1;
    }
}

void ledOff(led_ref_t led_ref)
{
    if (led_ref < NUM_LEDS)
    {
        if (ledsPinRef[led_ref].port_is_odd)
        {
            ledsPinRef[led_ref].odd->OUT &= ~(ledsPinRef[led_ref].mask);
        }
        else
        {
            ledsPinRef[led_ref].even->OUT &= ~(ledsPinRef[led_ref].mask);
        }
        ledsStatus[led_ref] = 0;
    }
}

void ledToggle(led_ref_t led_ref)
{
    if (led_ref < NUM_LEDS)
    {
        if (ledsStatus[led_ref])
        {
            ledOff(led_ref);
        }
        else
        {
            ledOn(led_ref);
        }
    }
}

uint8_t ledGet(led_ref_t led_ref)
{
    if (led_ref < NUM_LEDS)
    {
        return ledsStatus[led_ref];
    }
    return 0;
}

int ledsGetNum(void)
{
    return NUM_LEDS;
}

/* @} */
