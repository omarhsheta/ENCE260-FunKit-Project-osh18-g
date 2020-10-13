/**
 * File:   game_logic.c
 * Author: Omar Sheta (osh18) and George Holden (gah83)
 * Date:   13 Oct 2020
 * Descr:  Contains functions which manage the calculation of game logic
 * 		   and handle input / output.
 * */
#include <stdbool.h>
#include <string.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"

void game_won(void);

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
 * Description: It is a loop where the player selects either Rock, Papper,
 *              Scissors. Once they select, it locks and blue LED light
 *              lights up to indicate that the player has made their
 *              selection, and waits for the other player to make their
 *              selection.
 * @param player_selection: The current player's selection
 * @param other_selection: The other player's selection
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
		if (ir_uart_read_ready_p()) {
            received = ir_uart_getc();
            if (strchr(options, received) != NULL) { // Checks if recieved character in "RPS"
                *other_selection = received;
                received = '\0';
            } else if (received == 'L') {
                game_lost();
            }
        }
        
        pacer_wait();
        tinygl_update();
        navswitch_update();
        if (!transmitted) {
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                    counter = (counter + 1) % 3;
            }

            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                counter = (counter + 2) % 3; // Same as -1 mod 3
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(options[counter]);
            *player_selection = options[counter];
            transmitted = true;
            led_set(LED1, 1);
        }

        if (*other_selection != '\0' && transmitted) {
            ready = true;
        }

        display_character(options[counter]);
    }
}

/**
 * Description: Evaluates if the current round is a Win/Loss/Tie
 * @param player_selection: The current player's selection (in "RPS")
 * @param other_selection: The other player's selection (in "RPS")
 * @return an integer that is either 0,1 or 2 to indicate a
 *         Loss/Tie/Win respectively
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
 * Description: Displays the result of the round as output and updates
 * 				the player's score if required.
 * @param result: an integer 0, 1 or 2 to represent a Loss, Tie or Win.
 * 				  Same as output from find_winner.
 * @param score: A pointer to the player's total score, updated in place 
 * 				 where appropriate.
 * */
void display_winner(int result, int* score)
{
    char status;
    if (result == 2) {
        status = 'W';
        *score = *score + 1;
    } else if (result == 1) {
        status = 'T';
    } else {
        status = 'L';
    }

    int counter = 0;
    while(counter < 1000)
    {
        display_character(status);
        pacer_wait();
        tinygl_update();
        counter++;
    }
}

/**
 * Description: Displays the current player's score as output. 
 * 				Assumed that score <= MAX_SCORE < 10 so that 
 * 				'0' + *score gives the correct character.
 * @param score: A pointer to the score value to be displayed
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
    led_set(LED1, 0);
}

/**
 * Description: Endlessly displays a victory message
 * */
void game_won(void)
{
    tinygl_text_speed_set(10);
	ir_uart_putc('L');
	tinygl_text("You won!\0");
	led_set(LED1, 1);
    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
}

/**
 * Description: Endlessly displays a defeat message
 * */
void game_lost(void)
{
    tinygl_text_speed_set(10);
    tinygl_text("You lost!\0");
    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
}
