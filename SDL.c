#include "Pentago.h"




SDL_Texture* load_texture_from_image(const char* file_image_name, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Surface* my_image = IMG_Load(file_image_name);
    if (my_image == NULL) {
        end_sdl(0, "Chargement de l'image impossible", window, renderer);
    }

    SDL_Texture* my_texture = SDL_CreateTextureFromSurface(renderer, my_image);
    SDL_FreeSurface(my_image);
    if (my_texture == NULL) {
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);
    }

    return my_texture;
}

void end_sdl(char ok, const char* msg, SDL_Window* window, SDL_Renderer* renderer) {
    char msg_formated[255];
    int l;

    if (!ok) {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();

    if (!ok) {
        exit(EXIT_FAILURE);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Pentago", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    afficherFenetreDemarrage(renderer,window);

    int board[GRID_SIZE][GRID_SIZE] = {0};
    int currentPlayer = 1;
    bool running = true;
    SDL_Event event;

    SDL_Texture* fleche[] = {load_texture_from_image("Pentago_sdl/fleche/1.jpg",window, renderer),load_texture_from_image("Pentago_sdl/fleche/2.jpg",window, renderer),
                            load_texture_from_image("Pentago_sdl/fleche/3.jpg",window, renderer),load_texture_from_image("Pentago_sdl/fleche/4.jpg",window, renderer),
                            load_texture_from_image("Pentago_sdl/fleche/5.jpg",window, renderer),load_texture_from_image("Pentago_sdl/fleche/6.jpg",window, renderer),
                            load_texture_from_image("Pentago_sdl/fleche/7.jpg",window, renderer),load_texture_from_image("Pentago_sdl/fleche/8.jpg",window, renderer)};
    
    SDL_Texture* rect_grid = load_texture_from_image("Pentago_sdl/Grid.png", window, renderer);


    int gridWidth = GRID_SIZE * CELL_SIZE;
    int gridHeight = GRID_SIZE * CELL_SIZE;
    int xOffset = (WINDOW_WIDTH - gridWidth) / 2;
    int yOffset = (WINDOW_HEIGHT - gridHeight) / 2;

    int mode = afficherSelectionMode(renderer);
    if (mode == 0)
    {
    while (running) {
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if click is on the rotateSubgrid buttons
                int quadrant = -1;
                int k;
                // First quadrant buttons (top-left)
                if (x > 260 && x < 320 && y > 70 && y < 130) {
                    quadrant = 0;
                    k = 1;
                } else if (x > 170 && x < 230 && y > 160 && y < 220) {
                    quadrant = 0;
                    k = 0;
                }

                // Second quadrant buttons (top-right)
                else if (x > 480 && x < 540 && y > 70 && y < 130) {
                    quadrant = 1;
                    k = 6;
                } else if (x > 570 && x < 630 && y > 160 && y < 220) {
                    quadrant = 1;
                    k = 7;
                }

                // Third quadrant buttons (bottom-left)
                else if (x > 170 && x < 230 && y > 370 && y < 430) {
                    quadrant = 2;
                    k = 2;
                } else if (x > 260 && x < 320 && y > 470 && y < 530) {
                    quadrant = 2;
                    k = 3;
                }

                // Fourth quadrant buttons (bottom-right)
                else if (x > 480 && x < 540 && y > 470 && y < 530) {
                    quadrant = 3;
                    k = 4;
                } else if (x > 570 && x < 630 && y > 370 && y < 430) {
                    quadrant = 3;
                    k = 5;
                }

                
                if (currentPlayer == 2)
                {
                    if (quadrant != -1) {
                    rotateSubgrid(board, k);
                    }
                    else {
                    int row2,col2,k2;
                    minmax(board,2,MAX_DEPTH,&row2,&col2,&k2);
                    if (row2 >= 0 && row2 < GRID_SIZE && col2 >= 0 && col2 < GRID_SIZE && board[row2][col2] == 0) {
                        placePiece(board, row2, col2, currentPlayer);
                        if (checkwin(board,currentPlayer))
                        {
                        printf("le joueur %d a gagne!!! \n", currentPlayer);
                        EndGame(renderer, window, 2);
                        running = 0;
                        break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                        rotateSubgrid(board, k2);
                        currentPlayer = 1;
                    }
                    if (checkwin(board,currentPlayer))
                        {
                        printf("le joueur %d a gagne!!! \n", currentPlayer);
                        EndGame(renderer, window, 2);
                        running = 0;
                        break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                    }
                }
         
                if (currentPlayer == 1) {
                    // Check if click is on the board

                    if (quadrant != -1) {
                    rotateSubgrid(board, k);
                    }
                    else{
                    int row1 = (y - yOffset) / CELL_SIZE;
                    int col1 = (x - xOffset) / CELL_SIZE;

                    if (row1 >= 0 && row1 < GRID_SIZE && col1 >= 0 && col1 < GRID_SIZE && board[row1][col1] == 0) {
                        placePiece(board, row1, col1, currentPlayer);
                        if (checkwin(board,currentPlayer)){
                            printf("le joueur %d a gagne!!! \n", currentPlayer);
                            EndGame(renderer, window, 1);
                            running = 0;
                            break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                        currentPlayer = 2;
                    }
                    if (checkwin(board,currentPlayer))
                        {
                        printf("le joueur %d a gagne!!! \n", currentPlayer);
                        EndGame(renderer, window, 1);
                        running = 0;
                        break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                    }
                    
                }
            }
        }
        
        // Set background color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White background
        SDL_RenderClear(renderer);

        SDL_Rect rect1 = {223,123,355,356};
        SDL_Rect rect_f1 = {260,70,60,60};
        SDL_Rect rect_f2 = {170,160,60,60};
        SDL_Rect rect_f3 = {570,160,60,60};
        SDL_Rect rect_f4 = {480,70,60,60};
        SDL_Rect rect_f5 = {170,370,60,60};
        SDL_Rect rect_f6 = {260,470,60,60};
        SDL_Rect rect_f7 = {480,470,60,60};
        SDL_Rect rect_f8 = {570,370,60,60}; 
        SDL_RenderCopy (renderer,rect_grid,NULL,&rect1);
        SDL_RenderCopy (renderer,fleche[0],NULL,&rect_f1);
        SDL_RenderCopy (renderer,fleche[1],NULL,&rect_f2);
        SDL_RenderCopy (renderer,fleche[2],NULL,&rect_f3);    
        SDL_RenderCopy (renderer,fleche[3],NULL,&rect_f4);
        SDL_RenderCopy (renderer,fleche[4],NULL,&rect_f5);
        SDL_RenderCopy (renderer,fleche[5],NULL,&rect_f6);
        SDL_RenderCopy (renderer,fleche[6],NULL,&rect_f7);
        SDL_RenderCopy (renderer,fleche[7],NULL,&rect_f8);
        //drawGrid(renderer, xOffset, yOffset);
        drawPieces(renderer, board, xOffset, yOffset);
        //drawrotateSubgridButtons(renderer, xOffset, yOffset);

        SDL_RenderPresent(renderer);
    }
    }
    else if (mode == 1){
        while (running) {
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if click is on the rotateSubgrid buttons
                int quadrant = -1;
                int k;
                // First quadrant buttons (top-left)
                if (x > 260 && x < 320 && y > 70 && y < 130) {
                    quadrant = 0;
                    k = 1;
                } else if (x > 170 && x < 230 && y > 160 && y < 220) {
                    quadrant = 0;
                    k = 0;
                }

                // Second quadrant buttons (top-right)
                else if (x > 480 && x < 540 && y > 70 && y < 130) {
                    quadrant = 1;
                    k = 6;
                } else if (x > 570 && x < 630 && y > 160 && y < 220) {
                    quadrant = 1;
                    k = 7;
                }

                // Third quadrant buttons (bottom-left)
                else if (x > 170 && x < 230 && y > 370 && y < 430) {
                    quadrant = 2;
                    k = 2;
                } else if (x > 260 && x < 320 && y > 470 && y < 530) {
                    quadrant = 2;
                    k = 3;
                }

                // Fourth quadrant buttons (bottom-right)
                else if (x > 480 && x < 540 && y > 470 && y < 530) {
                    quadrant = 3;
                    k = 4;
                } else if (x > 570 && x < 630 && y > 370 && y < 430) {
                    quadrant = 3;
                    k = 5;
                }

                
                if (currentPlayer == 2)
                {
                    if (quadrant != -1) {
                    rotateSubgrid(board, k);
                    }
                    else{
                    int row2 = (y - yOffset) / CELL_SIZE;
                    int col2 = (x - xOffset) / CELL_SIZE;

                    if (row2 >= 0 && row2 < GRID_SIZE && col2 >= 0 && col2 < GRID_SIZE && board[row2][col2] == 0) {
                        placePiece(board, row2, col2, 2);
                        if (checkwin(board,2)){
                            printf("le joueur %d a gagne!!! \n", 2);
                            EndGame(renderer, window, 1);
                            running = 0;
                            break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                        currentPlayer = 1;
                    }
                    if (checkwin(board,2))
                        {
                        printf("le joueur %d a gagne!!! \n", 2);
                        EndGame(renderer, window, 1);
                        running = 0;
                        break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                    }
                }
         
                if (currentPlayer == 1) {
                    // Check if click is on the board

                    if (quadrant != -1) {
                    rotateSubgrid(board, k);
                    }
                    else{
                    int row1 = (y - yOffset) / CELL_SIZE;
                    int col1 = (x - xOffset) / CELL_SIZE;

                    if (row1 >= 0 && row1 < GRID_SIZE && col1 >= 0 && col1 < GRID_SIZE && board[row1][col1] == 0) {
                        placePiece(board, row1, col1, 1);
                        if (checkwin(board,1)){
                            printf("le joueur %d a gagne!!! \n", 1);
                            EndGame(renderer, window, 1);
                            running = 0;
                            break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                        currentPlayer = 2;
                    }
                    if (checkwin(board,1))
                        {
                        printf("le joueur %d a gagne!!! \n", 1);
                        EndGame(renderer, window, 1);
                        running = 0;
                        break;
                        }
                        if (Is_draw(board)){
                            printf("la partie est nulle!!\n");
                            EndGame(renderer, window, 0);
                            running = 0;
                            break;
                        }
                    }
                    
                }
            }
        }
        
        // Set background color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White background
        SDL_RenderClear(renderer);

        SDL_Rect rect1 = {223,123,355,356};
        SDL_Rect rect_f1 = {260,70,60,60};
        SDL_Rect rect_f2 = {170,160,60,60};
        SDL_Rect rect_f3 = {570,160,60,60};
        SDL_Rect rect_f4 = {480,70,60,60};
        SDL_Rect rect_f5 = {170,370,60,60};
        SDL_Rect rect_f6 = {260,470,60,60};
        SDL_Rect rect_f7 = {480,470,60,60};
        SDL_Rect rect_f8 = {570,370,60,60}; 
        SDL_RenderCopy (renderer,rect_grid,NULL,&rect1);
        SDL_RenderCopy (renderer,fleche[0],NULL,&rect_f1);
        SDL_RenderCopy (renderer,fleche[1],NULL,&rect_f2);
        SDL_RenderCopy (renderer,fleche[2],NULL,&rect_f3);    
        SDL_RenderCopy (renderer,fleche[3],NULL,&rect_f4);
        SDL_RenderCopy (renderer,fleche[4],NULL,&rect_f5);
        SDL_RenderCopy (renderer,fleche[5],NULL,&rect_f6);
        SDL_RenderCopy (renderer,fleche[6],NULL,&rect_f7);
        SDL_RenderCopy (renderer,fleche[7],NULL,&rect_f8);

        drawPieces(renderer, board, xOffset, yOffset);

        SDL_RenderPresent(renderer);
    }

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int afficherFenetreDemarrage(SDL_Renderer *renderer, SDL_Window* window) {
    SDL_bool continuer = SDL_TRUE;
    SDL_Event evenement;
    SDL_Rect boutonDemarrer = {
        (WINDOW_WIDTH - 180) / 2, // Centrage en largeur
        (WINDOW_HEIGHT - 80) / 2, // Centrage en hauteur
        180, 80 };

    SDL_Texture* start_button = load_texture_from_image("Pentago_sdl/play2.jpg", window, renderer);
    if (!start_button) {
        fprintf(stderr, "Erreur lors du chargement de la texture du bouton démarrer: %s\n", SDL_GetError());
        return -1;
    }

    // Charger une texture pour l'arrière-plan
    SDL_Texture* Start_Background = load_texture_from_image("Pentago_sdl/Pentago2.jpg", window, renderer);
    if (!Start_Background) {
        fprintf(stderr, "Erreur lors du chargement de la texture de l'arrière-plan: %s\n", SDL_GetError());
        return -1;
    }

    while (continuer) {
        while (SDL_PollEvent(&evenement)) {
            switch (evenement.type) {
                case SDL_QUIT:
                    continuer = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evenement.button.x >= boutonDemarrer.x && evenement.button.x <= (boutonDemarrer.x + boutonDemarrer.w) &&
                        evenement.button.y >= boutonDemarrer.y && evenement.button.y <= (boutonDemarrer.y + boutonDemarrer.h)) {
                        continuer = SDL_FALSE; // L'utilisateur a cliqué sur démarrer
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, Start_Background, NULL, NULL); // Ajouter l'arrière-plan
        SDL_RenderCopy(renderer, start_button, NULL, &boutonDemarrer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(start_button);
    SDL_DestroyTexture(Start_Background);
    return 0;
}

// Fonction pour afficher la page de sélection de mode de jeu
int afficherSelectionMode(SDL_Renderer * renderer) {
    SDL_bool continuer = SDL_TRUE;
    SDL_Event event;
    int Mode; // Mode par défaut


    // Centrer les boutons sur l'écran
    int boutonWidth = 350;
    int boutonHeight = 250;
    int boutonSpacing = 10; // Espace entre les boutons
    int totalHeight = (2 * boutonHeight) + boutonSpacing;
    int startY = (WINDOW_HEIGHT - totalHeight) / 2;

    SDL_Rect boutonPvP = {(WINDOW_WIDTH - boutonWidth) / 2, startY, boutonWidth, boutonHeight};
    SDL_Rect boutonPvC = {(WINDOW_WIDTH - boutonWidth) / 2, startY + boutonHeight + boutonSpacing, boutonWidth, boutonHeight};


    // Charger les textures pour les boutons
    SDL_Texture* text_PvP = IMG_LoadTexture(renderer, "Pentago_sdl/PvP.jpg");
    SDL_Texture* text_PvC = IMG_LoadTexture(renderer, "Pentago_sdl/PvC.jpg");

    // Vérifier si les textures ont été chargées correctement
    if (!text_PvP || !text_PvC) {
        fprintf(stderr, "Erreur lors du chargement des textures des boutons: %s\n", SDL_GetError());
        return -1;
    }

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    continuer = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x >= boutonPvP.x && event.button.x <= (boutonPvP.x + boutonPvP.w) &&
                        event.button.y >= boutonPvP.y && event.button.y <= (boutonPvP.y + boutonPvP.h)) {
                        Mode= 1; //PvP
                        continuer = SDL_FALSE;
                    } else if (event.button.x >= boutonPvC.x && event.button.x <= (boutonPvC.x + boutonPvC.w) &&
                               event.button.y >= boutonPvC.y && event.button.y <= (boutonPvC.y + boutonPvC.h)) {
                        Mode= 0; //PvC
                        continuer = SDL_FALSE;
                    }
                    break;
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White background
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, text_PvP, NULL, &boutonPvP);
        SDL_RenderCopy(renderer, text_PvC, NULL, &boutonPvC);
        SDL_RenderPresent(renderer);
    }

    // Libérer les textures
    SDL_DestroyTexture(text_PvP);
    SDL_DestroyTexture(text_PvC);

    return Mode;
}

int EndGame(SDL_Renderer *renderer, SDL_Window* window, int win) {
    SDL_bool continuer = SDL_TRUE;
    SDL_Event event;
    
    // Charger une texture pour l'arrière-plan
    SDL_Texture* Game_over = load_texture_from_image("Pentago_sdl/gameover.jpg", window, renderer);
    if (!Game_over) {
        fprintf(stderr, "Erreur lors du chargement de la texture de l'arrière-plan: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Texture* You_win = load_texture_from_image("Pentago_sdl/you_win.jpg", window, renderer);
    if (!You_win) {
        fprintf(stderr, "Erreur lors du chargement de la texture de l'arrière-plan: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Texture* Draw = load_texture_from_image("Pentago_sdl/noWinner.jpg", window, renderer);
    if (!Draw) {
        fprintf(stderr, "Erreur lors du chargement de la texture de l'arrière-plan: %s\n", SDL_GetError());
        return -1;
    }

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                continuer = SDL_FALSE;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if(win == 1){
            SDL_RenderCopy(renderer, You_win, NULL, NULL); // Ajouter l'arrière-plan
        }
        else if (win == 2){
            SDL_RenderCopy(renderer, Game_over, NULL, NULL); 
        }
        else if (win == 0){
            SDL_RenderCopy(renderer, Draw, NULL, NULL);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(Game_over);
    SDL_DestroyTexture(You_win);
    SDL_DestroyTexture(Draw);
    return 0;
}

void drawGrid(SDL_Renderer *renderer, int xOffset, int yOffset) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // Black lines

    for (int i = 0; i <= GRID_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, xOffset + i * CELL_SIZE, yOffset, xOffset + i * CELL_SIZE, yOffset + GRID_SIZE * CELL_SIZE);
        SDL_RenderDrawLine(renderer, xOffset, yOffset + i * CELL_SIZE, xOffset + GRID_SIZE * CELL_SIZE, yOffset + i * CELL_SIZE);
    }

    SDL_Rect thickLine;

    SDL_SetRenderDrawColor(renderer, 30, 0, 0, SDL_ALPHA_OPAQUE); // Dark red thick lines

    // Vertical thick lines
    thickLine = (SDL_Rect){xOffset + SUBGRID_SIZE * CELL_SIZE - LINE_THICKNESS / 2, yOffset, LINE_THICKNESS, GRID_SIZE * CELL_SIZE};
    SDL_RenderFillRect(renderer, &thickLine);

    // Horizontal thick lines
    thickLine = (SDL_Rect){xOffset, yOffset + SUBGRID_SIZE * CELL_SIZE - LINE_THICKNESS / 2, GRID_SIZE * CELL_SIZE, LINE_THICKNESS};
    SDL_RenderFillRect(renderer, &thickLine);
}

void drawPieces(SDL_Renderer *renderer, int board[GRID_SIZE][GRID_SIZE], int xOffset, int yOffset) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (board[row][col] != 0) {
                int centerX = xOffset + col * CELL_SIZE + CELL_SIZE / 2;
                int centerY = yOffset + row * CELL_SIZE + CELL_SIZE / 2;
                int radius = CELL_SIZE / 2 - 6;

                if (board[row][col] == 1) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black pieces
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White pieces
                }

                drawFilledCircle(renderer, centerX, centerY, radius);
            }
        }
    }
}

void drawrotateSubgridButtons(SDL_Renderer *renderer, int xOffset, int yOffset) {
    SDL_Rect button;

    // First quadrant buttons (top-left)
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue for k
    button = (SDL_Rect){xOffset - 60, yOffset, 50, 40};
    SDL_RenderFillRect(renderer, &button);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red for counterk
    button = (SDL_Rect){xOffset - 60, yOffset + 40, 50, 40};
    SDL_RenderFillRect(renderer, &button);

    // Second quadrant buttons (top-right)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue for k
    button = (SDL_Rect){xOffset + GRID_SIZE * CELL_SIZE + 10, yOffset, 50, 40};
    SDL_RenderFillRect(renderer, &button);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red for counterk
    button = (SDL_Rect){xOffset + GRID_SIZE * CELL_SIZE + 10, yOffset + 40, 50, 40};
    SDL_RenderFillRect(renderer, &button);

    // Third quadrant buttons (bottom-left)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue for k
    button = (SDL_Rect){xOffset - 60, yOffset + GRID_SIZE * CELL_SIZE - 80, 50, 40};
    SDL_RenderFillRect(renderer, &button);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red for counterk
    button = (SDL_Rect){xOffset - 60, yOffset + GRID_SIZE * CELL_SIZE - 40, 50, 40};
    SDL_RenderFillRect(renderer, &button);

    // Fourth quadrant buttons (bottom-right)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue for k
    button = (SDL_Rect){xOffset + GRID_SIZE * CELL_SIZE + 10, yOffset + GRID_SIZE * CELL_SIZE - 80, 50, 40};
    SDL_RenderFillRect(renderer, &button);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red for counterk
    button = (SDL_Rect){xOffset + GRID_SIZE * CELL_SIZE + 10, yOffset + GRID_SIZE * CELL_SIZE - 40, 50, 40};
    SDL_RenderFillRect(renderer, &button);
}

void placePiece(int board[GRID_SIZE][GRID_SIZE], int row, int col, int player) {
    board[row][col] = player;
}

/*
void rotateSubgrid(int board[GRID_SIZE][GRID_SIZE], int quadrant, bool k) {
    int temp[SUBGRID_SIZE][SUBGRID_SIZE];
    int startRow = (quadrant / 2) * SUBGRID_SIZE;
    int startCol = (quadrant % 2) * SUBGRID_SIZE;

    // Copy the subgrid to temp
    for (int i = 0; i < SUBGRID_SIZE; ++i) {
        for (int j = 0; j < SUBGRID_SIZE; ++j) {
            temp[i][j] = board[startRow + i][startCol + j];
        }
    }

    // Rotate the subgrid in temp
    for (int i = 0; i < SUBGRID_SIZE; ++i) {
        for (int j = 0; j < SUBGRID_SIZE; ++j) {
            if (k) {
                board[startRow + j][startCol + SUBGRID_SIZE - 1 - i] = temp[i][j];
            } else {
                board[startRow + SUBGRID_SIZE - 1 - j][startCol + i] = temp[i][j];
            }
        }
    }
}
*/

void rotateSubgrid(int board[N][N], int k) //rotateSubgrid à faire apres chaque coup 
{                                   //8 rotateSubgrid en totale
    
    int temp, temp1;
        switch (k) {
        case 0:
            //rot1_270
            temp = board[0][0];
            board[0][0] = board[0][2];
            temp1 = board[2][0];
            board[2][0] = temp;
            board[0][2] = board[2][2];
            board[2][2] = temp1;
            //
            temp = board[1][0];
            board[1][0] = board[0][1];
            temp1 = board[2][1];
            board[2][1] = temp;
            board[0][1] = board[1][2];
            board[1][2] = temp1;

            break;
        case 1:
            //rot1_90
            temp = board[0][0];
            board[0][0] = board[2][0];
            temp1 = board[0][2];
            board[0][2] = temp;
            board[2][0] = board[2][2];
            board[2][2] = temp1;
            //
            temp = board[0][1];
            board[0][1] = board[1][0];
            temp1 = board[1][2];
            board[1][2] = temp;
            board[1][0] = board[2][1];
            board[2][1] = temp1;
            break;
        case 6:
            //rot2_270
            temp = board[0][3];
            board[0][3] = board[0][5];
            temp1 = board[2][3];
            board[2][3] = temp;
            board[0][5] = board[2][5];
            board[2][5] = temp1;
            //
            temp = board[0][4];
            board[0][4] = board[1][5];
            temp1 = board[1][3];
            board[1][3] = temp;
            board[1][5] = board[2][4];
            board[2][4] = temp1;
            break;
        case 7:
            //rot2_90
            temp = board[0][5];
            board[0][5] = board[0][3];
            temp1 = board[2][5];
            board[2][5] = temp;
            board[0][3] = board[2][3];
            board[2][3] = temp1;
            //
            temp = board[1][5];
            board[1][5] = board[0][4];
            temp1 = board[2][4];
            board[2][4] = temp;
            board[0][4] = board[1][3];
            board[1][3] = temp1;
            break;
        case 2:
            //rot3_90
            temp = board[3][2];
            board[3][2] = board[3][0];
            temp1 = board[5][2];
            board[5][2] = temp;
            board[3][0] = board[5][0];
            board[5][0] = temp1;
            //
            temp = board[5][1];
            board[5][1] = board[4][2];
            temp1 = board[4][0];
            board[4][0] = temp;
            board[4][2] = board[3][1];
            board[3][1] = temp1;
            break;
        case 3:
            //rot3_270
            temp = board[3][0];
            board[3][0] = board[3][2];
            temp1 = board[5][0];
            board[5][0] = temp;
            board[3][2] = board[5][2];
            board[5][2] = temp1;
            //
            temp = board[5][1];
            board[5][1] = board[4][0];
            temp1 = board[4][2];
            board[4][2] = temp;
            board[4][0] = board[3][1];
            board[3][1] = temp1;
            break;
        case 4:
            //rot4_90
            temp = board[3][5];
            board[3][5] = board[3][3];
            temp1 = board[5][5];
            board[5][5] = temp;
            board[3][3] = board[5][3];
            board[5][3] = temp1;
            //
            temp = board[4][5];
            board[4][5] = board[3][4];
            temp1 = board[5][4];
            board[5][4] = temp;
            board[3][4] = board[4][3];
            board[4][3] = temp1;
            break;
        case 5:
            //rot4_270
            temp = board[3][5];
            board[3][5] = board[5][5];
            temp1 = board[3][3];
            board[3][3] = temp;
            board[5][5] = board[5][3];
            board[5][3] = temp1;
            //
            temp = board[4][5];
            board[4][5] = board[5][4];
            temp1 = board[3][4];
            board[3][4] = temp;
            board[5][4] = board[4][3];
            board[4][3] = temp1;
            break;
        default:
            break;
    }
}

void drawFilledCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

