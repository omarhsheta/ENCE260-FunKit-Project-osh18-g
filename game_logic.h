/**
 * File:   game_logic.h
 * Author: Omar Sheta (osh18) and George Holden (gah83)
 * Date:   12 Oct 2020
 * Descr:  Header for game_logic.c
 * */

#include <stdbool.h>
#include <string.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"

/**
 * Description: Endlessly displays a victory message
 * */
void game_won(void);

/**
 * Description: Endlessly displays a defeat message
 * */
void game_lost(void);

/**
 * Description: The function displays an individual character only
 * @param character:
 * */
void display_character (char character);

/**
 * Description: It is a loop where the player selects either Rock, Paper,
 *              Scissors. Once they select, it locks and blue LED light
 *              lights up to indicate that the player has made their
 *              selection, and waits for the other player to make their
 *              selection.
 * @param player_selection: The current player's selection
 * @param other_selection: The other player's selection
 * */
void selection_loop(char* player_selection, char* other_selection);

/**
 * Description: Evaluates if the current round is a Win/Loss/Tie
 * @param player_selection: The current player's selection (in "RPS")
 * @param other_selection: The other player's selection (in "RPS")
 * @return an integer that is either 0,1 or 2 to indicate a
 *         Loss/Tie/Win respectively
 * */
int find_winner(char* player_selection, char* other_selection);

/**
 * Description: Displays the result of the round as output and updates
 *              the player's score if required.
 * @param result: an integer 0, 1 or 2 to represent a Loss, Tie or Win.
 *                Same as output from find_winner.
 * @param score: A pointer to the player's total score, updated in place
 *               where appropriate.
 * */
void display_winner(int result, int* score);

/**
 * Description: Displays the current player's score as output.
 *              Assumed that score <= MAX_SCORE < 10 so that
 *              '0' + *score gives the correct character.
 * @param score: A pointer to the score value to be displayed
 * */
void display_score(int* score);

