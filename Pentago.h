#ifndef MINMAX_H
#define MINMAX_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define level 36
#define N 6
#define PLAYER_MAX 1
#define PLAYER_MIN 2
#define MAX_DEPTH 3
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRID_SIZE 6
#define CELL_SIZE 50
#define SUBGRID_SIZE 3
#define LINE_THICKNESS 5

//SDL
SDL_Texture* load_texture_from_image(const char* file_image_name, SDL_Window* window, SDL_Renderer* renderer);
void end_sdl(char ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer);
int afficherFenetreDemarrage(SDL_Renderer *renderer, SDL_Window* window);
int afficherSelectionMode(SDL_Renderer * renderer);
int EndGame(SDL_Renderer *renderer, SDL_Window* window, int win);
void drawGrid(SDL_Renderer *renderer, int xOffset, int yOffset);
void drawPieces(SDL_Renderer *renderer, int board[GRID_SIZE][GRID_SIZE], int xOffset, int yOffset);
void placePiece(int board[GRID_SIZE][GRID_SIZE], int row, int col, int player);
void rotateSubgrid(int board[GRID_SIZE][GRID_SIZE], int k);
void drawFilledCircle(SDL_Renderer *renderer, int x, int y, int radius);
void drawrotateSubgridButtons(SDL_Renderer *renderer, int xOffset, int yOffset);

//minmax
int zeros(int board[N][N]);
int MAX(int a, int b);
int MIN(int a, int b);
void choisir_coup(int board[N][N], int *i, int *j, int *k);
void genere_coups(int board[N][N], int **coups, int z);
void applique(int i, int j, int k, int player, int board[N][N]);
int evaluation(int depth, int player, int board[N][N]);
int minmax(int board[N][N], int player, int depth, int *I, int *J, int *K);

//GAME
void Init_board(int board[N][N]);
int checklignes(int board[N][N], int player);
int checkcolonnes(int board[N][N], int player);
int checkdiagonale(int board[N][N] ,int player);
int checkanti_diagonale(int board[N][N], int player);
int checkwin(int board[N][N], int player);
int check_3_in_a_row(int board[N][N], int player);
int check_4_in_a_row(int board[N][N], int player);
int Is_draw(int board[N][N]);
void rotation(int board[N][N], int k);
void affichage(int board[N][N]);


#endif
