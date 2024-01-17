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
     /* LP_S1 on P1.1 , internal pull-up */
     {.odd = P1, .port_is_odd = 1, .mask = BIT1, .use_pullup = 1, .use_interrupt = 0, .int_num = 0},
     /* LP_S2 on P1 .4 , internal pull-up  */
     {.odd = P1, .port_is_odd = 1, .mask = BIT4, .use_pullup = 1, .use_interrupt = 0, .int_num = 0},

     /* BP_S1 on P5 .1 , no internal pull-up  */
     {.odd = P5, .port_is_odd = 1, .mask = BIT1, .use_pullup = 0, .use_interrupt = 1, .int_num = INT_PORT5},

     /* BP_S2 on P3 .5 , no internal pull-up  */
     {.odd = P3, .port_is_odd = 1, .mask = BIT5, .use_pullup = 0, .use_interrupt = 1, .int_num = INT_PORT3},
};

/* ----------- Definition of private variables (with static) -------------- */

/* ----------------- Definition of public variables --------------------- */

/* ---------- Declaration of private functions (with static) -------------- */

/* A function that returns the bitmask for a specific port */
static int _IVBitmask(int port);
static void _buttonInit(const input_pinref_t *ref);
static int _buttonInverseSearch(uint16_t int_num, uint8_t mask);
void buttonCallback(int button_index) __attribute__((weak));

/* --------- Implementation of private functions (with static) ------------ */
static int _IVBitmask(int port){
    switch(port){
    case 0x00:
        return -1;
        break;
    case 0x02:
        return BIT0;
        break;
    case 0x04:
        return BIT1;
        break;
    case 0x06:
        return BIT2;
        break;
    case 0x08:
        return BIT3;
        break;
    case 0x0A:
        return BIT4;
        break;
    case 0x0C:
        return BIT5;
        break;
    case 0x0E:
        return BIT6;
        break;
    case 0x10:
        return BIT7;
        break;
    default:
        return -1;
        break;
    }
}

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
        if(ref->use_interrupt)
        {
            ref->odd->IES |= ref->mask;
            ref->odd->IE |= ref->mask;
            ref->odd->IFG &= ~(ref->mask);
            Interrupt_enableInterrupt(ref->int_num);
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
        if(ref->use_interrupt)
        {
            ref->even->IES |= ref->mask;
            ref->even->IE |= ref->mask;
            ref->even->IFG &= ~(ref->mask);
            Interrupt_enableInterrupt(ref->int_num);
        }
    }
}

static int _buttonInverseSearch(uint16_t int_num, uint8_t mask)
{
    int i;
    for(i = 0; i < NUM_BUTTONS; i++){
        if((buttonsPinRef[i].int_num == int_num) && (buttonsPinRef[i].mask == mask))
            return i;
    }
    return -1;
}

void PORT1_IRQHandler(void){
    uint16_t int_num = INT_PORT1;
    uint16_t port = P1->IV;
    int bitmask = _IVBitmask(port);
    int button_num = _buttonInverseSearch(int_num,bitmask);
    if(button_num > 0){
        buttonCallback(button_num);
    }
}
void PORT2_IRQHandler(void){
    uint16_t int_num = INT_PORT2;
    uint16_t port = P2->IV;
    int bitmask = _IVBitmask(port);
    int button_num = _buttonInverseSearch(int_num,bitmask);
    if(button_num > 0){
        buttonCallback(button_num);
    }
}
void PORT3_IRQHandler(void){
    uint16_t int_num = INT_PORT3;
    uint16_t port = P3->IV;
    int bitmask = _IVBitmask(port);
    int button_num = _buttonInverseSearch(int_num,bitmask);
    if(button_num > 0){
        buttonCallback(button_num);
    }
}
void PORT4_IRQHandler(void){
    uint16_t int_num = INT_PORT4;
    uint16_t port = P4->IV;
    int bitmask = _IVBitmask(port);
    int button_num = _buttonInverseSearch(int_num,bitmask);
    if(button_num > 0){
        buttonCallback(button_num);
    }
}
void PORT5_IRQHandler(void){
    uint16_t int_num = INT_PORT5;
    uint16_t port = P5->IV;
    int bitmask = _IVBitmask(port);
    int button_num = _buttonInverseSearch(int_num,bitmask);
    if(button_num > 0){
        buttonCallback(button_num);
    }
}
void PORT6_IRQHandler(void){
    uint16_t int_num = INT_PORT6;
    uint16_t port = P6->IV;
    int bitmask = _IVBitmask(port);
    int button_num = _buttonInverseSearch(int_num,bitmask);
    if(button_num > 0){
        buttonCallback(button_num);
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
