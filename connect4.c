/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

enum {
    EMPTY = 0,
    R,
    B,
};

typedef char board_t[4][5];
typedef char player_t;

void init_board(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            board[row][col] = '0';
        }
    }
}

player_t other_player(player_t player)
{
    switch (player) {
    case 'R': return 'B';
    case 'B': return 'R';
    default: assert(0);
    }
}

int has_won(board_t board, player_t player)
{
    for(int row=0; row < 4; row++) {
        int count = 0;
        for (int col=0 ; col < 5;col++) {
            if (board[row][col]!=player) {
                count++;
                if (col == 1 || col == 2 || col == 3 ){
                    goto next_row;
                }
            }
            if (count == 2){
                goto next_row;
            }
        }
        return 1;
        next_row:{
          
        }
    }

    for (int col=0; col < 5; col++) {    
        int count =0;
        for (int row=0 ; row < 4; row++) {
            if (board[row][col]!=player) {
                goto next_col;
            }
            else {
                count++;
            }
        }
        if (count == 4) {
        return 1;
        }
        next_col:{
          
        }
    }

    for (int i=0; i<4;i++){
        if (board[i][i]!=player) {
            goto next_diag1;
        }
    }
    return 1;

    next_diag1:
    for (int i=0; i < 4;i++) {
        if (board[i][i+1]!=player) {
            goto next_diag2;
        }
    }
    return 1;

    next_diag2:
    for (int i=0;i<4;i++) {
        if (board[i][3-i]!=player) {
            goto next_diag3;
        }
    }
    return 1;

    next_diag3:
    for (int i=0;i<4;i++) {
        if (board[i][4-i]!=player) {
            return 0;
        }
    }
    return 1;

}

int is_full(board_t board)
{
    for (int row =0; row < 4; row++) {
        for (int col=0; col <5; col++) {
            if (board[row][col]=='0') {
                return 0;
            }
        }
    }
    return 1;
}

typedef struct {
    int col;
    int score;
} move_t;

move_t best_move(board_t board, player_t player)
{
    move_t candiate;
    move_t response;
    int no_candiate=1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));

    for (int col=0; col<5; col++) {
        for (int row=3; row>=0; row--) {
            if (board[row][col]=='0' && (row==3 || board[row+1][col]!='0' ) ){
                board[row][col]=player;
                if (has_won(board,player)){
                    board[row][col]='0';
                    candiate=(move_t){
                        .col=col,
                        .score=1,
                    };
                    return candiate;
                }
                board[row][col]='0';
            }
        }
    }

    for (int col = 0; col < 5; col++) {
        for (int row = 3; row >=0; row--) {
            if (board[row][col]=='0' && (row==3 || board[row+1][col]!='0' )) {
                board[row][col] = player;
                if (is_full(board)) {
                    board[row][col] = '0';
                    candiate = (move_t) {
                        .col = col,
                        .score = 0
                        };
                    return candiate;
                }
                response = best_move(board, other_player(player));
                board[row][col] = '0';
                if (response.score == -1) {
                    candiate = (move_t) {
                        .col = col,
                        .score = 1
                        };
                    return candiate;
                } else if (response.score == 0) {
                    candiate = (move_t) {
                    
                        .col = col,
                        .score = 0
                    };
                    no_candiate = 0;
                } else { /* response.score == +1 */
                    if (no_candiate) {
                        candiate = (move_t) {
                        
                            .col = col,
                            .score = -1
                        };
                        no_candiate = 0;
                    }
                }
            }
        }
    }
    
    return candiate;





}

void print_board(board_t board)
{
    for (int row = 0; row <4 ; ++row) {
        for (int col = 0; col < 5; ++col) {
            printf("%3c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");


}

void print_key()
{
    int i = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            printf("%3d ", i++);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */

 board_t board;
  init_board(board);
  int move,  col;
  move_t response;

  // Select the player.
  player_t player;
  player_t user;
  printf("Select your player (R/B): ");
  char c = getchar();
  if (c == 'R' || c == 'r') {
    player = 'R';
    user='R';
  } else if (c == 'B' || c == 'b') {
    player = 'B';
    user='B';
  } else {
    printf("Invalid selection.\n");
    return 1;
  }

  while(1) {
    //printf("a");
    print_board(board);
    //printf("c");
    if (player==user) {
        printf("  0   1   2   3   4\n");
        printf("Enter your move: ");
        scanf("%d", &move);
        int Row;    
        for (int row=3;row >= 0;row--) {
            if (board[row][move]=='0' ) {
                Row=row;
                break;
            }
        }
        assert(board[Row][move] == '0');
        board[Row][move]=player;
    }else {
        //printf("cc\n");
        response = best_move(board, player);
        int Col=response.col;
        int Row;
        for (int row=3; row>=0; row--) {
            if (board[row][Col]=='0' ) {
                Row=row;
                break;
            }
        }
        board[Row][response.col] = player;
    }

    if (has_won(board, player)) {
    print_board(board);
    printf("Player %c has won!\n", player);
    break;
    } else if (is_full(board)) {
        print_board(board);
        printf("Draw.\n");
        break;
    }
    player = other_player(player);
  }
    return 0;
}
