#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

//Useful constants below
#define PACER_RATE 500
#define MESSAGE_RATE 20

int main (void)
{

    system_init();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text("Rock Papper Scissors 2: Electric Boogaloo\0");


    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        tinygl_update(); //Calling tinygl update function

    }
    return 0;
}
