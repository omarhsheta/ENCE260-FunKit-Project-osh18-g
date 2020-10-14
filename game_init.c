/**
 * File:   game_init.c
 * Author: Omar Sheta (osh18) and George Holden (gah83)
 * Date:   13 Oct 2020
 * Descr:  Contains functions that handle the initialisation of other
 *         modules and the initial setup phase of the game.
 * */
#include <stdbool.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"

/**
 * Description: this function initialises all other modules used throughout
 *              the program and sets some basic tinygl options.
 * @param message_rate: an integer to be passed as the tinygl_text_speed
 * @param pacer_rate: an integer used to set the pacer rate
 * */
void setup_all(int message_rate, int pacer_rate)
{
    system_init();
    tinygl_init(pacer_rate);
    navswitch_init();
    ir_uart_init();
    led_init();
    led_set(LED1, 0);

    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(message_rate);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init(pacer_rate);
}

/**
 * Description: This function handles the start up phase of the game
 * */
void inital_loop(void)
{
    tinygl_text("Press when ready!\0");
    bool ready = false; //Is true when player is ready
    bool player_ready = false; //Is true when 2nd player is ready
    while(!ready)
    {
        pacer_wait();
        tinygl_update();

        navswitch_update();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc('1');
            ready = true;
        }
    }

    tinygl_text("Waiting for player\0");
    led_set(LED1, 1); //Turns on the blue LED
    while (!player_ready)
    {
        pacer_wait();
        tinygl_update();
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == '1') {
                player_ready = true;
                led_set(LED1, 0); //Turns off the blue LED
                tinygl_text_speed_set(2); //fixes the jitter bug with TinyGL
            }
        }
    }

}
