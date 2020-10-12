#include "system.h"
#include "game_logic.h"
#include "game_init.h"
#include <stdio.h>
#include "pacer.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20
#define MAX_SCORE 10


int main (void)
{
    setup_all(MESSAGE_RATE, PACER_RATE);
    inital_loop();
    int score = 0;

    while (score < MAX_SCORE)
    {
        char player_selection = '\0';
        char other_selection = '\0';
        selection_loop(&player_selection, &other_selection);
        display_winner(find_winner(&player_selection, &other_selection), &score);
        display_score(&score);
    }

    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
    return 0;
}
