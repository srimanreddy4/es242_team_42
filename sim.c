#include <stdio.h>
#include <assert.h>

#include "test.h"

/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

int triangles[60] = {
    0,1,5,
    0,2,6,
    0,3,7,
    0,4,8,
    1,2,9,
    1,3,10,
    1,4,11,
    2,3,12,
    2,4,13,
    3,4,14,
    5,6,9,
    5,7,10,
    5,8,11,
    6,7,12,
    6,8,13,
    7,8,14,
    9,10,12,
    9,11,13,
    10,11,14,
    12,13,14
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12 
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

player_t other_player(player_t player)
{
    switch (player) {
    case RED : return BLUE;
    case BLUE : return RED;
    default: assert(0);
    }
}

int has_lost(board_t board, player_t player)
{
    for (int i = 0; i < 20; i++) {
        if (board[triangles[3*i]] == player &&
            board[triangles[(3*i) + 1]] == player &&
            board[triangles[(3*i) + 2]] == player) {
          return 1;
        }
    }
    return 0;
}

int is_full(board_t board)
{
    for (int i = 0;i < 15;i++){
        if (board[i] == NO){return 0;}
    }
    return 1;
}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        case NO: printf(".  ");break;
        }
    }
}

void init_board(board_t board)
{
    for (int i = 0; i < 15; i++){
        board[i] = NO;
    }
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 1 for win. */
} move_t;

move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;

    assert(!is_full(board));
    assert(!has_lost(board, player));
    assert(!has_lost(board, other_player(player)));


    for (int i = 0;i < 15;i++){
        if (board[i] == NO){
            board[i] = player;
            if (has_lost(board,player)){
                board[i] = NO;
                candidate = (move_t){
                    .line = i,
                    .score = -1
                };
            }else{
                response = best_move(board, other_player(player));
                board[i] = NO;
                if (response.score == -1){
                    return (move_t){
                        .line = i,
                        .score = 1
                    };
                }else {
                    candidate = (move_t){
                        .line = i,
                        .score = -1
                    };
                }
            
            }
        }
    }
    return candidate;

}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */

    int move, line;
    board_t board;
    move_t response;
    player_t current;
    printf("Choose your colour(1 for 'RED',2 for'BLUE'):");
    scanf("%d", &current);
    init_board(board);
    while (1)
    {
        print_board(board); printf("\n\n");
        printf("0  1  2  3  4  5  6  7  8  9  10 11 12 13 14\n");
        printf("Enter your move: ");
        scanf("%d", &move);

        assert(board[move] == NO);
        board[move] = current;

        if (has_lost(board,current)){
            print_board(board);
            if (current == 1){
                printf("Player BLUE has won!\n");
            }else{
                printf("Player RED has won!\n");
            }
            break;
        }
        
        current = other_player(current);

        print_board(board); printf("\n\n");
        response = best_move(board, current);
        board[response.line] = current;

        if (has_lost(board,current)){
            print_board(board);
            if (current == 1){
                printf("Player BLUE has won!\n");
            }else{
                printf("Player RED has won!\n");
            }
            break;
        }
        current = other_player(current);

    }
    return 0;
}
