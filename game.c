#include "system.h"
#include <stdio.h>
#include <string.h>
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "stdbool.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20
#define OPTIONS

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void setup_all(void)
{
    system_init();
    tinygl_init(PACER_RATE);
    navswitch_init();
    ir_uart_init();

    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init(PACER_RATE);
}

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


void selection_loop(char* player_selection, char* other_selection)
{
    const char options[] = "RPS";
    int counter = 0;
    display_character(options[counter]);
    bool transmitted = false;
    bool ready = false;
    char received = '\0';
    while(!ready)
    {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            counter = (counter + 1) % 3;
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            counter = (counter + 2) % 3; // Same as -1 mod 3
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(options[counter]);
            *player_selection = options[counter];
            transmitted = true;
        }

        if (ir_uart_read_ready_p()) {
            received = ir_uart_getc();
            if (strchr(options, received) != NULL) { // Checks if recieved character in "RPS"
                *other_selection = received;
                received = '\0';
            }
        }

        if (*other_selection != '\0' && transmitted) {
            ready = true;
        }

        display_character(options[counter]);
    }
}

int main (void)
{
    setup_all();
    inital_loop();

    char player_selection = '\0';
    char other_selection = '\0';
    selection_loop(&player_selection, &other_selection);
    display_character(other_selection);
    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
    return 0;
}

