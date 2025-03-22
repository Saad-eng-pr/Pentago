#include "Pentago.h"


int zeros(int board[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                ++count;
            }
        }
    }
    return count;
}

int MAX(int a, int b) {
    return (a > b) ? a : b;
}

int MIN(int a, int b) {
    return (a < b) ? a : b;
}

void choisir_coup(int board[N][N], int *i, int *j, int *k) {
    int bestVal = INT_MIN;
    *i = -1;
    *j = -1;
    *k = -1;

    int z = zeros(board);
    int **coups = (int **)malloc(z * sizeof(int *));
    for (int m = 0; m < z; m++) {
        coups[m] = (int *)malloc(2 * sizeof(int));
    }
    genere_coups(board, coups, z);

    for (int l = 0; l < z; l++) {
        for (int m = 0; m < 8; m++) {
            applique(coups[l][0], coups[l][1], m, PLAYER_MAX, board);
            int moveVal = minmax(board, PLAYER_MIN, MAX_DEPTH, i, j, k);
            if (m % 2 == 0) {
                rotation(board, m + 1);
            } else {
                rotation(board, m - 1);
            }
            board[coups[l][0]][coups[l][1]] = 0;

            if (moveVal > bestVal) {
                *i = coups[l][0];
                *j = coups[l][1];
                *k = m;
                bestVal = moveVal;
            }
        }
    }

    for (int m = 0; m < z; m++) {
        free(coups[m]);
    }
    free(coups);
}

void genere_coups(int board[N][N], int **coups, int z) {
    int i = 0;
    for (int k = 0; k < N; k++) {
        for (int l = 0; l < N; l++) {
            if (board[k][l] == 0 && i < z) {
                coups[i][0] = k;
                coups[i][1] = l;
                i++;
            }
        }
    }
}

void applique(int i, int j, int k, int player, int board[N][N]) {
    board[i][j] = player;
    rotation(board, k);
}

int evaluation(int depth, int player, int board[N][N]) {
    if (checkwin(board, PLAYER_MAX)) return +10;
    if (checkwin(board, PLAYER_MIN)) return -10;

    int maxval = INT_MIN, minval = INT_MAX;

    if (depth == 0) {
        if (check_4_in_a_row(board, PLAYER_MAX)) return +3;
        if (check_4_in_a_row(board, PLAYER_MIN)) return -3;
        if (check_3_in_a_row(board, PLAYER_MAX)) return +1;
        if (check_3_in_a_row(board, PLAYER_MIN)) return -1;
        return 0;
    }

    int count = zeros(board);
    if (count == 0) return 0;

    int **coups = (int **)malloc(count * sizeof(int *));
    for (int k = 0; k < count; k++) {
        coups[k] = (int *)malloc(2 * sizeof(int));
    }
    genere_coups(board, coups, count);

    if (player == PLAYER_MAX) {
        for (int i = 0; i < count; i++) {
            for (int k = 0; k < 8; k++) {
                applique(coups[i][0], coups[i][1], k, player, board);
                maxval = MAX(maxval, evaluation(depth - 1, PLAYER_MIN, board));
                if (k % 2 == 0) {
                    rotation(board, k + 1);
                } else {
                    rotation(board, k - 1);
                }
                board[coups[i][0]][coups[i][1]] = 0;
            }
        }
        for (int k = 0; k < count; k++) {
            free(coups[k]);
        }
        free(coups);
        return maxval;
    } else {
        for (int i = 0; i < count; i++) {
            for (int k = 0; k < 8; k++) {
                applique(coups[i][0], coups[i][1], k, player, board);
                minval = MIN(minval, evaluation(depth - 1, PLAYER_MAX, board));
                if (k % 2 == 0) {
                    rotation(board, k + 1);
                } else {
                    rotation(board, k - 1);
                }
                board[coups[i][0]][coups[i][1]] = 0;
            }
        }
        for (int k = 0; k < count; k++) {
            free(coups[k]);
        }
        free(coups);
        return minval;
    }
}

int minmax(int board[N][N], int player, int depth, int *I, int *J, int *K) {
    if (depth == 0 || checkwin(board, PLAYER_MAX) || checkwin(board, PLAYER_MIN)) {
        return evaluation(depth, player, board);
    }

    int z = zeros(board);
    int **coups = (int **)malloc(z * sizeof(int *));
    for (int k = 0; k < z; k++) {
        coups[k] = (int *)malloc(2 * sizeof(int));
    }
    genere_coups(board, coups, z);

    int bestVal = (player == PLAYER_MAX) ? INT_MIN : INT_MAX;

    for (int l = 0; l < z; l++) {
        for (int m = 0; m < 8; m++) {
            applique(coups[l][0], coups[l][1], m, player, board);
            int moveVal = minmax(board, (player == PLAYER_MAX) ? PLAYER_MIN : PLAYER_MAX, depth - 1, I, J, K);
            if (m % 2 == 0) {
                rotation(board, m + 1);
            } else {
                rotation(board, m - 1);
            }
            board[coups[l][0]][coups[l][1]] = 0;

            if (player == PLAYER_MAX) {
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    if (depth == MAX_DEPTH) {
                        *I = coups[l][0];
                        *J = coups[l][1];
                        *K = m;
                    }
                }
            } else {
                if (moveVal < bestVal) {
                    bestVal = moveVal;
                    if (depth == MAX_DEPTH) {
                        *I = coups[l][0];
                        *J = coups[l][1];
                        *K = m;
                    }
                }
            }
        }
    }

    for (int k = 0; k < z; k++) {
        free(coups[k]);
    }
    free(coups);

    return bestVal;
}
