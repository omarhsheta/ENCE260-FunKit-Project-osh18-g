/**
 * File:   game_init.h
 * Author: Omar Sheta (osh18) and George Holden (gah83)
 * Date:   12 Oct 2020
 * Descr:  Header for game_init.c
 * */

#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "stdbool.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"

/**
 * Description: this function initialises all other modules used throughout
 *              the program and sets some basic tinygl options.
 * @param message_rate: an integer to be passed as the tinygl_text_speed
 * @param pacer_rate: an integer used to set the pacer rate
 * */
void setup_all(int message_rate, int pacer_rate);

/**
 * Description: This function handles the start up phase of the game
 * */
void inital_loop(void);
