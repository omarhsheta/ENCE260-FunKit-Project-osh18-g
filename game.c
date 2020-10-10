#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "stdbool.h"

//Useful constants below
#define PACER_RATE 500
#define MESSAGE_RATE 20


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

int main (void)
{
    setup_all();
    tinygl_text("Press when ready!\0");
    bool ready = false;
    while(!ready)
    {
        pacer_wait();
        tinygl_update();

        navswitch_update();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc('S');
        }

        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == 'S') {
                ready = true;
                ir_uart_putc('S');
           }
        }
    }

    char options[] = "RPS";
    int counter = 0;
    display_character(options[counter]);
    while(1)
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

        display_character(options[counter]);

    }
    return 0;
}
