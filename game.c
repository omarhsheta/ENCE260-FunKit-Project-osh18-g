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
#define MAX_SCORE 10

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

int find_winner(char* player_selection, char* other_selection)
{
    if (*player_selection == 'R') {
        if (*other_selection == 'S') {
            return 2;
        } else if (*other_selection == 'R') {
            return 1;
        } else {
            return 0;
        }
    } else if (*player_selection == 'P') {
        if (*other_selection == 'R') {
            return 2;
        } else if (*other_selection == 'P') {
            return 1;
        } else {
            return 0;
        }
    } else if (*player_selection == 'S' && *other_selection == 'P') {
        if (*other_selection == 'P') {
            return 2;
        } else if (*other_selection == 'S') {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

void display_winner(int result, int* score)
{
    if (result == 2) {
        display_character('W');
        *score = *score + 1;
    } else if (result == 1) {
        display_character('T');
    } else {
        display_character('L');
    }

    int counter = 0;
    while(counter < 1000)
    {
        pacer_wait();
        tinygl_update();
        counter++;
    }
}

void display_score(int* score)
{
    display_character('0' + *score);
}

int main (void)
{
    setup_all();
    inital_loop();
    int score = 0;

    char player_selection = '\0';
    char other_selection = '\0';
    selection_loop(&player_selection, &other_selection);
    display_winner(find_winner(&player_selection, &other_selection), &score);
    display_score(&score);
    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
    return 0;
}
