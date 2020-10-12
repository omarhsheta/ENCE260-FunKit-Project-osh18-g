/**
 * File:   game.c
 * Author: Omar Sheta (osh18) and George Holden (gah83)
 * Date:   12 Oct 2020
 * Descr:  Runs the game
 * */
#include "system.h"
#include "game_logic.h"
#include "game_init.h"
#include <stdio.h>
#include "pacer.h"

/* Constants*/
#define PACER_RATE 500
#define MESSAGE_RATE 20
#define MAX_SCORE 5

/* The game runs below */
int main (void)
{
    setup_all(MESSAGE_RATE, PACER_RATE); //Sets up all necessary settings to run the game
    inital_loop(); //Waits for both players to be ready

    /* Gameplay commences */
    int score = 0;
    while (score < MAX_SCORE)
    {
        char player_selection = '\0';
        char other_selection = '\0';
        selection_loop(&player_selection, &other_selection); //Where the player selects Rock, Papper, or Scissors
        display_winner(find_winner(&player_selection, &other_selection), &score); //Displays whether it is a Win/Loss/Tie for this round
        display_score(&score); //Displays the current score
        if (game_lost())
        {
            game_won(score, MAX_SCORE); //If the player loses to the 2nd player, they always go to that function
        }
    }
    game_won(score, MAX_SCORE);
    return 0;
}
