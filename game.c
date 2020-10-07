#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
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

int main (void)
{

    system_init();
    tinygl_init (PACER_RATE);
    navswitch_init();
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text("Rock Papper Scissors 2: Electric Boogaloo\0");


    pacer_init (PACER_RATE);
    bool ready = false;

    while(!ready)
    {
        pacer_wait();
        tinygl_update();

        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ready = true;
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
