#include <stdbool.h>
#include <string.h>
#include "navswitch.h"
#include "ir_uart.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"

void display_character (char character);

void selection_loop(char* player_selection, char* other_selection);

int find_winner(char* player_selection, char* other_selection);

void display_winner(int result, int* score);

void display_score(int* score);

void game_won(int score, int max_score);

bool game_lost(void);
