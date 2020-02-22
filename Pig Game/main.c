// CSC 240
// 02-20-2020
// Taylor Kelly

// This program allows two players to play a dice game called "Pig".
// The player that reaches 100 first wins.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rollDice(int* d1Ptr, int* d2Ptr) {
    
    // random value between 1-6 using (mod 6) + 1.
    *d1Ptr = (rand() % 6) + 1;
    *d2Ptr = (rand() % 6) + 1;
}

int calcPoints(int die1, int die2) {
    return die1 + die2;
}

// handles player functionality until a single 1 is rolled or 'n' is entered.
void playerTurn(int* playerPtr, int* p1ScorePtr, int* p2ScorePtr) {
    
    int die1;
    int die2;
    char answer;
    int tempScore = 0;
    
    // do-while loop: execute this until player enters 'n'.
    do {
        
        rollDice(&die1, &die2);
        printf("\nPLAYER%d rolls a %d and %d. ", *playerPtr, die1, die2);
        
        // logic for dice scenarios, update tempScore accordingly.
        if (die1 == 1 && die2 == 1) tempScore += 25;
        else if (die1 == die2) tempScore += 2 * calcPoints(die1, die2);
        else if (die1 == 1 || die2 == 1) tempScore = 0;
        else tempScore += calcPoints(die1, die2);
        
        printf("Score this round: %d\n", tempScore);
        
        // only prompt player if they scored points on roll (have not rolled a single 1).
        if (tempScore > 0) {
            printf("Do you want to roll again? (y/n)\n");
            scanf(" %c", &answer);
            
            // only accept 'y' or 'n' as inputs
            while (answer != 'y' && answer != 'n') {
                printf("\nInvalid Input '%c'\n", answer);
                printf("Do you want to roll again? (y/n)\n");
                scanf(" %c", &answer);
            }
            
        } else {
            // tempScore is 0, player rolled a 1, automatically switch turns.
            answer = 'n';
        }
        
    } while (answer != 'n');
    
    
    // after player turn, switch to other player.
    // Update respective scores.
    if (*playerPtr == 1) {
        *p1ScorePtr += tempScore;
        *playerPtr = 2;
    } else {
        *p2ScorePtr += tempScore;
        *playerPtr = 1;
    }
    
}

//      ---------------------------MAIN-----------------------------------

int main() {

    srand( (unsigned)time(NULL) );
    
    int player = 1;
    
    int p1Score = 0;
    int p2Score = 0;
    
    // do-while: execute while a player score has not reached 100.
    do {
        
        // switch: alternate player turns
        switch (player) {
                
            case 1:
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("   PLAYER 1 score: %d \n", p1Score);
                printf("   PLAYER 2 score: %d \n", p2Score);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
                playerTurn(&player, &p1Score, &p2Score);
                break;
                
            case 2:
                printf("\n");
                playerTurn(&player, &p1Score, &p2Score);
                
        }
        
    } while (p1Score < 100 && p2Score < 100);
    
        printf("-------------------------------------------------\n");
        printf("PLAYER 1 score: %d\n", p1Score);
        printf("PLAYER 2 score: %d\n", p2Score);
        printf("-------------------------------------------------\n");
    
}
