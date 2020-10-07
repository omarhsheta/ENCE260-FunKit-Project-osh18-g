#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "button.h"
#include "stdbool.h"
#include "pio.h"

//Useful constants below
#define PACER_RATE 500
#define MESSAGE_RATE 20

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

static const uint8_t scissors[] =
{
    0b1110011, 0b0001011, 0b0000100, 0b0001011, 0b1110011
};

static const uint8_t paper[] =
{
    0b1111111, 0b1111111, 0b1111111, 0b1111111, 0b1111111
};

static const uint8_t rock[] =
{
    0b0011100, 0b0111110, 0b1111111, 0b0111110, 0b0011100
};


static void display_column (uint8_t row_pattern, uint8_t current_column)
{
    if (current_column > 0) {
        pio_output_high(cols[current_column-1]);
    } else {
        pio_output_high(cols[4]);
    }
    for (int current_row = 0; current_row < 7; current_row++) {
        if ((row_pattern >> current_row) & 1)
        {
            pio_output_low(rows[current_row]);
        }
        else
        {
            pio_output_high(rows[current_row]);
        }
    }
        pio_output_low(cols[current_column]);
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

    static const uint8_t *options[] =
    {
        rock, paper, scissors
    };


    pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);

    pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);
    int counter = 0;
    uint8_t current_column = 0;
    //display_character(options[counter]);
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

        display_column (options[counter][current_column], current_column);

        current_column++;

        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }

    }
    return 0;
}
