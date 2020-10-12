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
 * Description: The function displays an individual character only
 * @param character:
 * */
void display_character (char character);

/**
 * Description: It is a loop where the player selects either Rock, Papper,
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
 * @param player_selection: The current player's selection
 * @param other_selection: The other player's selection
 * @return an integer that is either 0,1,2 to indicate whether it is
 *         Loss/Tie/Win respectively
 * */
int find_winner(char* player_selection, char* other_selection);

/**
 * Description: Using find_winner(char* player_selection, char* other_selection),
 *              it can indicate on LED matrix if it is a Win/Loss/Tie
 * @param result: find_winner(char* player_selection, char* other_selection) is passed onto it
 * @param score: the current player's score
 * */
void display_winner(int result, int* score);

/**
 * Description: Displays the current player's score
 * @param score: It is the current player's score
 * */
void display_score(int* score);

/**
 * Description: Blocking code where it displays whether the player
 *              won or lost
 * @param score: Player's score
 * @param max_score: Max score for comparison
 * */
void game_won(int score, int max_score);

/**
 * Description: It is only true if the other player wins
 * @return returns 0 or 1, only ever returns 1 if the other player wins
 * */
bool game_lost(void);
