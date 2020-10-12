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
 * Description: this void function sets up all the necessary tools for
 *              this Rock, Papper, Scissors game
 * @param message_rate: selects the rate of the messages
 * @param pacer_rate: selects the pacer's rate
 * */
void setup_all(int message_rate, int pacer_rate);

/**
 * Description: The start up of the game. When player is ready, the player
 *              waits for the 2nd player to be ready
 * */
void inital_loop(void);
