#include "Pentago.h"

void Init_board(int board[N][N]) //initialisation de la table avec des zeros
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            board[i][j] = 0;
        }
    }
}

int checklignes(int board[N][N],int player) //recherche de suite de n-1 boules de meme couleur dans les lignes
{
    int answer = 0;
    for (int i=0;i<N;i++)
    {
        int j = 0;
        while(j < N && board[i][j] != player )
        {
            j++;
        }
        int count = 0;
        while(board[i][j] == player && j < N)
        {
            count ++;
            j++;
        }
        if ((count == 5) || (count == 6))
        {
            answer = 1;
        }
        
    }
    return answer;
}

int checkcolonnes(int board[N][N],int player) //recherche de suite de n-1 boules de meme couleur dans les colonnes
{
    int answer = 0;
    for (int j=0;j<N;j++)
    {
        int i = 0;
        while(i < N && board[i][j] != player )
        {
            i++;
        }
        int count = 0;
        while(board[i][j] == player && i < N)
        {
            count ++;
            i++;
        }
        if ((count == 5) || (count == 6))
        {
            answer = 1;
        }
        
    }
    return answer;
}

int checkdiagonale(int board[N][N],int player) //recherche de suite de n-1 boules de meme couleur dans la diagonale
{
    int answer = 0;
    int i = 0;
    while(i < N && board[i][i] != player )
    {
        i++;
    }
    int count = 0;
    while(board[i][i] == player && i < N)
    {
        count ++;
        i++;
    }
    if ((count == 5) || (count == 6))
    {
        answer = 1;
    }
    return answer;
}

int checkanti_diagonale(int board[N][N],int player) //recherche de suite de n-1 boules de meme couleur dans l'anti-diagonale
{
    int answer = 0;
    int i = 0;
    while(i < N && board[i][N-i-1] != player )
    {
        i++;
    }
    int count = 0;
    while(board[i][N-i-1] == player && i < N)
    {
        count ++;
        i++;
    }
    if ((count == 5) || (count == 6))
    {
        answer = 1;
    }
    return answer;
}

int checkwin(int board[N][N],int player)
{
    return checkcolonnes(board,player) || checklignes(board,player) || checkdiagonale(board,player) || checkanti_diagonale(board,player);
}

int Is_draw(int board[N][N])
{
    return (zeros(board) == 0) && (checkwin(board,1) == 0) && (checkwin(board,2) == 0);
}

int check_3_in_a_row(int board[N][N], int player) //recherche de suite de 3 boules de meme couleur dans la table
{
    int answer = 0;
    int i = 0;
    //ligne
    for (i=0;i<N;i++)
    {
        int j = 0;
        while(j < N && board[i][j] != player )
        {
            j++;
        }
        int count = 0;
        while(board[i][j] == player && j < N)
        {
            count ++;
            j++;
        }
        if (count == 3)
        {
            answer = 1;
        }
    }

    //colonne
    for (int j=0;j<N;j++)
    {
        int i = 0;
        while(i < N && board[i][j] != player )
        {
            i++;
        }
        int count = 0;
        while(board[i][j] == player && i < N)
        {
            count ++;
            i++;
        }
        if (count == 3)
        {
            answer = 1;
        }
    }

    //diagonale
    i = 0;
    while(i < N && board[i][i] != player )
    {
        i++;
    }
    int count = 0;
    while(board[i][i] == player && i < N)
    {
        count ++;
        i++;
    }
    if (count == 3)
    {
        answer = 1;
    }

    //anti_diagonale
    i = 0;
    while(i < N && board[i][N-i-1] != player )
    {
        i++;
    }
    count = 0;
    while(board[i][N-i-1] == player && i < N)
    {
        count ++;
        i++;
    }
    if (count == 3)
    {
        answer = 1;
    }
    return answer;
}

int check_4_in_a_row(int board[N][N],int player) //recherche de suite de 4 boules de meme couleur dans la table
{
    int answer = 0;
    int i = 0;
    //ligne
    for (i=0;i<N;i++)
    {
        int j = 0;
        while(j < N && board[i][j] != player )
        {
            j++;
        }
        int count = 0;
        while(board[i][j] == player && j < N)
        {
            count ++;
            j++;
        }
        if (count == 4)
        {
            answer = 1;
        }
    }

    //colonne
    for (int j=0;j<N;j++)
    {
        int i = 0;
        while(i < N && board[i][j] != player )
        {
            i++;
        }
        int count = 0;
        while(board[i][j] == player && i < N)
        {
            count ++;
            i++;
        }
        if (count == 4)
        {
            answer = 1;
        }
    }

    //diagonale
    i = 0;
    while(i < N && board[i][i] != player )
    {
        i++;
    }
    int count = 0;
    while(board[i][i] == player && i < N)
    {
        count ++;
        i++;
    }
    if (count == 4)
    {
        answer = 1;
    }

    //anti_diagonale
    i = 0;
    while(i < N && board[i][N-i-1] != player )
    {
        i++;
    }
    count = 0;
    while(board[i][N-i-1] == player && i < N)
    {
        count ++;
        i++;
    }
    if (count == 4)
    {
        answer = 1;
    }
    return answer;
}

void rotation(int board[N][N], int k) //rotation à faire apres chaque coup 
{                                   //8 rotation en totale
    
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
        case 2:
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
        case 3:
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
        case 4:
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
        case 5:
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
        case 6:
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
        case 7:
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

void affichage(int board[N][N])
{
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            printf("%d ",board[i][j]);
            if (j == 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i == 2)
        {
            for (int k=0;k<N;k++)
            {
                printf("--");
            }
            printf("\n");
        }
    }
}
