#include <stdio.h>
#include "minmax.h"

int main() {
    int board[N][N] = {0};
    int i, j, k;
    int player = PLAYER_MAX;

    while (1) {
        affichage(board);
        printf("Choisir les indices de la case choisit :\n");
        scanf("%d %d", &i, &j);

        // Apply player move
        if (board[i][j] == 0) {
            board[i][j] = player;
        } else {
            printf("Case occupée, choisissez une autre case.\n");
            continue;
        }

        // Check for win or draw
        if (checkwin(board, player)) {
            printf("Joueur %d gagne!\n", player);
            break;
        }

        // Player rotation
        printf("choisit une rotation de 0 a 7\n");
        scanf("%d", &k);
        rotation(board, k);
        affichage(board);

        // Switch player
        player = (player == PLAYER_MAX) ? PLAYER_MIN : PLAYER_MAX;

        // Computer move
        minmax(board,player,MAX_DEPTH,&i,&j,&k);
        board[i][j] = player;
        rotation(board, k);
        affichage(board);

        // Check for win or draw
        if (checkwin(board, player)) {
            printf("Joueur %d gagne!\n", player);
            break;
        }
        if(Is_draw(board)){
            printf("la partie est nulle");
            break;
        }
        // Switch player
        player = (player == PLAYER_MAX) ? PLAYER_MIN : PLAYER_MAX;
    }

    return 0;
}
