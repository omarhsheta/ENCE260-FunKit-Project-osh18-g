#include <stdbool.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"

/**
 * Description: this void function sets up all the necessary tools for
 *              this Rock, Papper, Scissors game
 * @param message_rate: selects the rate of the messages
 * @param pacer_rate: selects the pacer's rate
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
 * Description: The start up of the game. When player is ready, the player
 *              waits for the 2nd player to be ready
 * */
void inital_loop(void)
{
    tinygl_text("Press when ready!\0");
    bool ready = false;
    bool player_ready = false;
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
    led_set(LED1, 1);
    while (!player_ready)
    {
        pacer_wait();
        tinygl_update();
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == '1') {
                player_ready = true;
            }
        }
    }

}
