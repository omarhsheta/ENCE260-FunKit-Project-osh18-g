Authors: Omar Sheta (osh18) and George Holden (gah83)
Date: 13 Oct 2020
Description: Rock, Paper, Scissors game

Initializing gameplay:
    1- The game will display a message saying "Press when ready!"
    
    
    2- Once the player presses on the middle button of the navigation switch,
       The funkit will display a message saying "Waiting for player" while
       the blue LED light lights up.
    3- Once the other player joins, the game will start!
    

Gameplay
    1- The character 'R' (for Rock) will be displayed on the funkit, you can 
       toggle up/down for other characters; 'S' for Scissors, and 'P' for Paper.
    2- Once the player have selected their character, the blue LED light 
       will light up to indicate that the character is selected and locked, and
       the player waits for the other player to send over their character
    3- Once the 2nd player sends their character, the status of the round will
       show on the LED matrix indicating 'W' for win, 'L' for loss, and 'T' for
       tie. Then the score will display a bit later.
    4- Another round commences and the same loop goes on until one of the players
       reaches MAX_SCORE (which is set to 4 by default, but can be changed in
       game.c), and the winner will have a message saying "You won!" while blue
       LED lights up, and the loser will have a message saying "You lost!" without
       the blue LED lighting up.