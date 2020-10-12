#include <stdbool.h>
#include <string.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"

/**
 * Description: The function displays an individual character only
 * @param character:
 * */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/**
 * Description:
 * @param player_selection:
 * @param other_selection:
 * */
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

/**
 * Description:
 * @param player_selection:
 * @param other_selection:
 * @return
 * */
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
    } else if (*player_selection == 'S') {
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

/**
 * Description:
 * @param result:
 * @param score:
 * */
void display_winner(int result, int* score)
{
    int counter = 0;
    while(counter < 1000)
    {
        if (result == 2) {
            display_character('W');
            *score = *score + 1;
        } else if (result == 1) {
            display_character('T');
        } else {
            display_character('L');
        }
            pacer_wait();
            tinygl_update();
            counter++;
    }
}

/**
 * Description:
 * @param score
 * */
void display_score(int* score)
{
    int counter = 0;
    while(counter < 1000)
    {
        display_character('0' + *score);
        pacer_wait();
        tinygl_update();
        counter++;
    }
}
