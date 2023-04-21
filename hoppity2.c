#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void imprimir_tablero(char tablero[10][10])
{
    int i, j;
    printf("  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |\n");
    printf("-------------------------------------------\n");
    for (i = 0; i < 10; i++)
    {
        //		printf(" %c |", 'A' + i); // para imprimir filas con letras
        printf(" %d |", i+1); //para imprimir filas con numeros
        for (j = 0; j < 10; j++)
        {
            printf(" %c |", tablero[i][j]);
        }
        printf("\n-------------------------------------------\n");
    }
}

int iniciar_tablero(char tablero[10][10])
{
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<10; j++)
        {
            tablero[i][j] = ' ';
        }
    }

    //Número aleatorio para definir en que esquinan van las piezas
    int num_aleatorio = rand() % 1;
    char bon[2] = {'B','N'};

    //piezas blancas -> B
    tablero[0][0] = bon[num_aleatorio];
    tablero[0][1] = bon[num_aleatorio];
    tablero[0][2] = bon[num_aleatorio];
    tablero[0][3] = bon[num_aleatorio];
    tablero[0][4] = bon[num_aleatorio];
    tablero[1][0] = bon[num_aleatorio];
    tablero[1][1] = bon[num_aleatorio];
    tablero[1][2] = bon[num_aleatorio];
    tablero[1][3] = bon[num_aleatorio];
    tablero[2][0] = bon[num_aleatorio];
    tablero[2][1] = bon[num_aleatorio];
    tablero[2][2] = bon[num_aleatorio];
    tablero[3][0] = bon[num_aleatorio];
    tablero[3][1] = bon[num_aleatorio];
    tablero[4][0] = bon[num_aleatorio];

    //piezas negras -> N
    if (num_aleatorio == 1)
        num_aleatorio = 0;
    else num_aleatorio++;
    tablero[5][9] = bon[num_aleatorio];
    tablero[6][9] = bon[num_aleatorio];
    tablero[7][9] = bon[num_aleatorio];
    tablero[8][9] = bon[num_aleatorio];
    tablero[9][9] = bon[num_aleatorio];
    tablero[6][8] = bon[num_aleatorio];
    tablero[7][8] = bon[num_aleatorio];
    tablero[8][8] = bon[num_aleatorio];
    tablero[9][8] = bon[num_aleatorio];
    tablero[7][7] = bon[num_aleatorio];
    tablero[8][7] = bon[num_aleatorio];
    tablero[9][7] = bon[num_aleatorio];
    tablero[8][6] = bon[num_aleatorio];
    tablero[9][6] = bon[num_aleatorio];
    tablero[9][5] = bon[num_aleatorio];

    return num_aleatorio;
    
}




void movimiento(char tablero[10][10], int origen_fila, int origen_col){
    int mov_fila, mov_col;
    printf("Ingrese la fila a la que se quiere mover: ");
    scanf("%d", &mov_fila);
    printf("Ingrese la columna a la que se quiere mover: ");
    scanf("%d", &mov_col);

    if(pow((mov_fila-origen_fila),2)+pow((mov_col-origen_col),2) <=2){
        tablero[origen_fila-1][origen_col-1] = ' ';
        tablero[mov_fila-1][mov_col-1] = 'B';
    }



}


int main(int argc, char const *argv[])
{
    int origen_fila, origen_col, turno;
    char tablero[10][10];
    printf("Bienvenido al juego Hoppity!\n\n");
    iniciar_tablero(tablero);
    
    imprimir_tablero(tablero);
    printf("Ingrese la fila de la pieza que quiere mover: ");
    scanf("%d", &origen_fila);
    printf("Ingrese la columna de la pieza que quiere mover: ");
    scanf("%d", &origen_col);
    movimiento(tablero, origen_fila, origen_col);
    imprimir_tablero(tablero);

    return 0;
}


// Movimiento: pow((mov_fila-origen_fila),2)+pow((mov_col-origen_col),2) <=2