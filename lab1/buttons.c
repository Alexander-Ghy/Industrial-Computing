/**
 * @file buttons.c
 * @author Alexander Ghyoot, Michal Kos
 * @date October 2021
 *
 * @brief A source file for the buttons module.
 *
 *A source file to be to be used by the user to control the buttons on a msp432p401r Launchpad board.
 *This contains the implementation for the private and public functions for the buttons module.
 *
 * @{
 */

/* ---------------- #includes needed for this file ----------------- */
#include "buttons.h"

/* --------------------------- Private macros ----------------------------- */
#define NUM_BUTTONS (sizeof(buttonsPinRef) / sizeof(input_pinref_t))

/* ----------------------- Private data types ------------------------- */
/* Private constant with references to button pins */
static const input_pinref_t buttonsPinRef[] =
    {
        {.odd = P1, .port_is_odd = 1, .mask = BIT1, .use_pullup = 1, .use_interrupt = 0, .int_num = 0},
        {.odd = P1, .port_is_odd = 1, .mask = BIT4, .use_pullup = 1, .use_interrupt = 0, .int_num = 0},
};

/* ----------- Definition of private variables (with static) -------------- */

/* ----------------- Definition of public variables --------------------- */

/* ---------- Declaration of private functions (with static) -------------- */
static void _buttonInit(const input_pinref_t *ref);

/* --------- Implementation of private functions (with static) ------------ */
static void _buttonInit(const input_pinref_t *ref)
{
    if (ref->port_is_odd)
    {
        ref->odd->SEL0 &= ~(ref->mask);
        ref->odd->SEL1 &= ~(ref->mask);
        ref->odd->DIR &= ~(ref->mask);
        if (ref->use_pullup)
        {
            ref->odd->REN |= ref->mask;
            ref->odd->OUT |= ref->mask;
        }
    }
    else
    {
        ref->even->SEL0 &= ~(ref->mask);
        ref->even->SEL1 &= ~(ref->mask);
        ref->even->DIR &= ~(ref->mask);
        if (ref->use_pullup)
        {
            ref->even->REN |= ref->mask;
            ref->even->OUT |= ref->mask;
        }
    }
}

/* ---------------- Implementation of public functions ------------------ */
void buttonsInit()
{
    button_ref_t i;
    for (i = 0; i < NUM_BUTTONS; i++)
    {
        _buttonInit(&(buttonsPinRef[i]));
    }
}

button_val_t buttonGet(button_ref_t button_ref)
{
    if (button_ref < NUM_BUTTONS)
    {
        if (buttonsPinRef[button_ref].port_is_odd)
        {
            uint8_t inputPin = (buttonsPinRef[button_ref].odd)->IN & buttonsPinRef[button_ref].mask;
            return inputPin > 0x00 ? BUTTON_RELEASED : BUTTON_PRESSED;
        }
        else
        {
            uint8_t inputPin = (buttonsPinRef[button_ref].even)->IN & buttonsPinRef[button_ref].mask;
            return inputPin > 0x00 ? BUTTON_RELEASED : BUTTON_PRESSED;
        }
    }
    else
    {
        return BUTTON_RELEASED;
    }
}

int buttonsGetNum(void)
{
    return NUM_BUTTONS;
}

/* @} */
