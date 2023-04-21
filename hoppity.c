/*
 ============================================================================
 Name        : .c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Define el tamaño del tablero, se usa el define por si quieras jugar con un tablero de diferente tamaño.
#define N 16

/*Se define la estructura de las coordenadas, el cual consta de un valor para la fila y otro para la columna, 
funciona porque usaremos ambos valores en todo el programa.*/
struct coordFicha {
		int fila;
		int columna;
	};

/*Funcion para dar el mensaje de bienvenida al programa por formalidad. */
void bienvenida(){
    printf("Bienvenido al juego Hoppity!\n");
    printf("El objetivo del juego es llevar tus fichas a la esquina del rival.\n");
    printf("Puedes escoger la cantidad de movimientos que deseas realizar.\n");
    printf("Puedes saltar entre ficha y ficha para llegar al destino. Salta y gana!\n\n");
}   

/*
Se inicializa el tablero vacio, para luego empezar a rellenarlo. 
Parametros: tablero(tamaño del tablero), la struct declarada anteriormente para las coordenadas de las fichas, y el valor random que genera el programa
para definir que fichas son las tuyas.
Return: void. Solamente introduce al tablero las fichas.
*/
void inicializarTab (char tablero[N][N], struct coordFicha fichasMaquina[19], int sorteo){
	int c, i, j, k;
	// se carga el tablero con guion bajos
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			tablero[i][j] = '_';
		}
	}
	// se carga las fichas X en la esquina superior izquierda
	for (j = 0; j < 5; j++){
		tablero[0][j] = 'X';
	}
	for (i = 1; i < 5; i++){
		for(j = 0; j < 6 - i; j++){
			tablero[i][j] = 'X';
		}
	}
	// se carga las fichas O en la esquina inferior derecha
	for(i = 11, k = 4; i < 15; i++, k--){
		for(j = 10 + k; j < 16; j++){
			tablero[i][j] = 'O';
		}
	}
	for (j = 11; j < 16; j++){
		tablero[15][j] = 'O';
	}
	// se cargan las posiciones iniciales de las fichas de la maquina
	if (sorteo == 0){
		for (c = 0, j = 0; j < 5; j++, c++){
			fichasMaquina[c].fila = 0;
			fichasMaquina[c].columna = j;
		}
		for (i = 1; i < 5; i++){
			for(j = 0; j < 6 - i; j++){
				fichasMaquina[c].fila = i;
				fichasMaquina[c].columna = j;
				c += 1;
			}
		}
	} else {
		c = 0;
		for(i = 11, k = 4; i < 15; i++, k--){
			for(j = 10 + k; j < 16; j++){
				fichasMaquina[c].fila = i;
				fichasMaquina[c].columna = j;
				c++;
			}
		}
		for (j = 11; j < 16; j++){
			fichasMaquina[c].fila = 15;
			fichasMaquina[c].columna = j;
			c += 1;
		}
	}
}

/*Se imprime el tablero del juego, con las fichas en cada esquina. */
void imprimirTab (char tablero[N][N]){
	int i, j;
	// se imprimen los numeros de las columnas
	for(i = 0; i < 16; i++){
		printf("\t%d", i + 1);
	}
	printf("\n\n");
	// se imprime el tablero
	for (i = 0; i < 16; i++){
		printf("%d\t", i + 1); // imprime el numero de las filas
		for (j = 0; j < 16; j++){
			printf("%c\t", tablero[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");
}

/*
La funcion mas importante del programa, ya que controla el flujo del juego.
Parametros: 
tablero: La matriz del tablero.
tipoFicha: El tipo de ficha que te toco(O o X).
fInic, cInic, Ffinal, cFinal: Punteros a las los valores que introduce el usuario, que serian las coordenadas de las fichas en el tablero (a seleccionar o a donde mover)
Return: void. Por medios de punteros, cambia las coordenadas de las fichas dependiendo de a donde las muevas. 
Parentesis: En esta funcion tambien se validan las coordenadas, si no pones coordenadas correctas, la funcion se repite.
*/
void jugadaUsuario (char tablero[N][N], char tipoFicha, int *fInic, int *cInic, int *fFinal, int *cFinal){
	int k, movimientos, validacion;
	    do{
			printf("Ingrese el numero de fila de la ficha a mover: ");
			scanf("%d", fInic);
            *fInic -= 1;
            printf("Ingrese el numero de columna de la ficha a mover: ");
			scanf("%d", cInic);
            *cInic -= 1;
            validacion=1;
            if(*fInic < 0 || *fInic > 16 || *cInic < 0 || *cInic > 16 || (tablero[*fInic][*cInic] != 'O' && tipoFicha == 'O')|| (tablero[*fInic][*cInic] != 'X' && tipoFicha == 'X')){
                printf("No hay una ficha en esa posicion\n");
                validacion = 0;
            }
			} while (validacion==0);
			
        printf("Ingrese la cantidad de movimientos: ");
		scanf("%d", &movimientos);
        do {
		for (k = 1, validacion = 1; k <= movimientos && validacion == 1; k++){
			do {
				printf("Ingrese el numero de fila de la posicion de destino: ");
				scanf("%d", fFinal);
				*fFinal -= 1;
			} while (*fFinal < 0 || *fFinal > 16);
			do {
				printf("Ingrese el numero de columna de la posicion de destino: ");
				scanf("%d", cFinal);
				*cFinal -= 1;
			} while (*cFinal < 0 || *cFinal > 16);
					// se verifica si la posicion de destino esta vacia
					if (tablero[*fFinal][*cFinal] == '_'){
						// se verifica si la posicion de desstino es adyacente a la posicion de origen
						if ((*fFinal == *fInic - 1 && *cFinal == *cInic - 1)
						|| (*fFinal == *fInic - 1 && *cFinal == *cInic)
						|| (*fFinal == *fInic - 1 && *cFinal == *cInic + 1)
						|| (*fFinal == *fInic && *cFinal == *cInic - 1)
						|| (*fFinal == *fInic && *cFinal == *cInic + 1)
						|| (*fFinal == *fInic + 1 && *cFinal == *cInic - 1)
						|| (*fFinal == *fInic + 1 && *cFinal == *cInic)
						|| (*fFinal == *fInic + 1 && *cFinal == *cInic + 1)){
							validacion = 1;
                            
                            tablero[*fInic][*cInic] = '_';
                            if (tipoFicha == 'O')
                                tablero[*fFinal][*cFinal] = 'O';
                            else
                                tablero[*fFinal][*cFinal] = 'X';
                            imprimirTab (tablero);
                            printf("Has movido una ficha de la posicion (%d, %d) a la posicion (%d, %d)\n", *fInic + 1, *cInic + 1, *fFinal + 1, *cFinal + 1);
                            *fInic = *fFinal;
                            *cInic = *cFinal;
						} else {
							// se verifica si hay una ficha entre la posicion de origen y la posicion de destino
							if ((*fFinal == *fInic - 2 && *cFinal == *cInic - 2 && tablero[*fInic - 1][*cInic - 1] != '_')
							|| (*fFinal == *fInic - 2 && *cFinal == *cInic && tablero[*fInic - 1][*cInic] != '_')
							|| (*fFinal == *fInic - 2 && *cFinal == *cInic + 2 && tablero[*fInic - 1][*cInic + 1] != '_' )
							|| (*fFinal == *fInic && *cFinal == *cInic - 2 && tablero[*fInic][*cInic - 1] != '_')
							|| (*fFinal == *fInic && *cFinal == *cInic + 2 && tablero[*fInic][*cInic + 1] != '_' )
							|| (*fFinal == *fInic + 2 && *cFinal == *cInic - 2 && tablero[*fInic + 1][*cInic - 1] != '_' )
							|| (*fFinal == *fInic + 2 && *cFinal == *cInic && tablero[*fInic + 1][*cInic] != '_')
							|| (*fFinal == *fInic + 2 && *cFinal == *cInic + 2 && tablero[*fInic + 1][*cInic + 1] != '_')){
								validacion = 1;
                                tablero[*fInic][*cInic] = '_';
                                if (tipoFicha == 'O')
                                    tablero[*fFinal][*cFinal] = 'O';
                                else
                                    tablero[*fFinal][*cFinal] = 'X';

                                *fInic = *fFinal;
                                *cInic = *cFinal;
							} else {
								printf("Movimiento no valido\n");
								validacion = 0;
                                
							}
						}
					} else {
						printf("La casilla destino esta ocupada\n");
						validacion = 0;
                        
					}
				}

	} while (validacion == 0);
	
}

/*
Esta funcion realiza el movimiento de la maquina. Por el momento no es "inteligente", solo hace movimientos permitidos.
Parametros: 
tablero: La matriz del tablero.
coordFicha: La struct dada para las coordenadas de las fichas.
tipoFicha: El tipo de ficha que le toco(O o X).
*ficha, *fInic, *cInic, *fFinal, *cFinal: Punteros para modificar las coordenadas de las fichas.
*/
void jugadaMaquina (char tablero[N][N], struct coordFicha fichaMaquina[19], char tipoFicha, int *ficha, int *fInic, int *cInic, int *fFinal, int *cFinal){
	srand (time(NULL));
	int band = 0;
	do {
		*ficha = rand() % 19;
		*fInic = fichaMaquina[*ficha].fila;
		*cInic = fichaMaquina[*ficha].columna;
		*fFinal = -1;
		do {
			if (*fInic + 2 <= 15){
				if (*cInic + 2 <= 15 && tablero[*fInic + 2][*cInic + 2] == '_' && tablero[*fInic + 1][*cInic + 1] != '_'){
					*fFinal = *fInic + 2;
					*cFinal = *cInic + 2;
					band = 1;
				} else {
					 if (tablero[*fInic + 2][*cInic] == '_' && tablero[*fInic + 1][*cInic] != '_'){
						 *fFinal = *fInic + 2;
						 *cFinal = *cInic;
						 band = 1;
					 } else {
						 if (*cInic - 2 >= 0 && tablero[*fInic + 2][*cInic - 2] == '_' && tablero[*fInic + 1][*cInic - 1] != '_'){
							 *fFinal = *fInic + 2;
							 *cFinal = *cInic - 2;
							 band = 1;
						 }
					 }
				}
			}
			if (band == 0 && *fInic + 1 <= 15){
				if (*cInic + 1 <= 15 && tablero[*fInic + 1][*cInic + 1] == '_'){
					*fFinal = *fInic + 1;
					*cFinal = *cInic + 1;
					band = 1;
				} else {
					if (tablero[*fInic + 1][*cInic] == '_'){
						*fFinal = *fInic + 1;
						*cFinal = *cInic;
						band = 1;
					} else {
						if (*cInic - 1 >= 0 && tablero[*fInic + 1][*cInic - 1] == '_'){
							*fFinal = *fInic + 1;
							*cFinal = *cInic - 1;
							band = 1;
						}
					}
				}
			}
			if (band == 0){
				if (*cInic + 2 <= 15 && tablero[*fInic][*cInic + 2] == '_' && tablero[*fInic][*cInic + 1] != '_'){
					*fFinal = *fInic;
					*cFinal = *cInic + 2;
					band = 1;
				} else {
					if (tablero[*fInic][*cInic + 1] == '_'){
						*fFinal = *fInic;
						*cFinal = *cInic + 1;
						band = 1;
					} else {
						if (*cInic - 1 >= 0 && tablero[*fInic][*cInic - 1] == '_'){
							*fFinal = *fInic;
							*cFinal = *cInic - 1;
							band = 1;
						} else {
							if (*cInic - 2 >= 0 && tablero[*fInic][*cInic - 2] == '_' && tablero[*fInic][*cInic - 1] != '_'){
								*fFinal = *fInic;
								*cFinal = *cInic - 2;
								band = 1;
							}
						}
					}
				}
			}
			if (band == 0 && *fInic - 1 >= 0){
				if (*cInic + 1 <= 15 && tablero[*fInic - 1][*cInic + 1] == '_'){
					*fFinal = *fInic - 1;
					*cFinal = *cInic + 1;
					band = 1;
				} else {
					if (tablero[*fInic - 1][*cInic] == '_'){
						*fFinal = *fInic - 1;
						*cFinal = *cInic;
						band = 1;
					} else {
						if (*cInic - 1 >= 0 && tablero[*fInic - 1][*cInic - 1] == '_'){
							*fFinal = *fInic - 1;
							*cFinal = *cInic - 1;
							band = 1;
						}
					}
				}
			}
			if (band == 0 && *fInic - 2 >= 0){
				if (*cInic + 2 <= 15 && tablero[*fInic - 2][*cInic + 2] == '_' && tablero[*fInic - 1][*cInic + 1] != '_'){
					*fFinal = *fInic - 2;
					*cFinal = *cInic + 2;
					band = 1;
				} else {
					if (tablero[*fInic - 2][*cInic] == '_' && tablero[*fInic - 1][*cInic] != '_'){
						*fFinal = *fInic - 2;
						*cFinal = *cInic;
						band = 1;
					} else {
						if (*cInic - 2 >= 0 && tablero[*fInic - 2][*cInic - 2] == '_' && tablero[*fInic - 1][*cInic - 1] != '_'){
							*fFinal = *fInic - 2;
							*cFinal = *cInic - 2;
							band = 1;
						}
					}
				}
			}
			*fInic = *fFinal;
			*cInic = *cFinal;
		} while (band == 0 && *fFinal == fichaMaquina[*ficha].fila && *cFinal == fichaMaquina[*ficha].columna);
		if (*fFinal == fichaMaquina[*ficha].fila && *cFinal == fichaMaquina[*ficha].columna){
			*fFinal = *fInic;
			*cFinal = *cInic;
		}
	} while (*fFinal == -1);
	tablero[fichaMaquina[*ficha].fila][fichaMaquina[*ficha].columna] = '_';
	if (tipoFicha == 'O')
		tablero[*fFinal][*cFinal] = 'O';
	else
		tablero[*fFinal][*cFinal] = 'X';
	*fInic = fichaMaquina[*ficha].fila;
	*cInic = fichaMaquina[*ficha].columna;
	fichaMaquina[*ficha].fila = *fFinal;
	fichaMaquina[*ficha].columna = *cFinal;
}
/*Esta funcion termina el programa si encuentra un ganador. 
Parametros: 
tablero: Matriz del tablero
tipoficha: Recibe que el tipo de ficha de cada jugador (O o X)
Return: 
A si todavia no termina, el tipo de ficha ganador si termina.
*/
char verificarFindelJuego (char tablero[N][N], char tipoFicha){
	int i, j, k;
	// se verifica si todas las fichas O llegaron al campamento enemigo
	if (tipoFicha == 'O'){
		for (j = 0; j < 5; j++){
			if (tablero[0][j] != 'O')
				return 'A';
			}
		for (i = 1; i < 5; i++){
			for(j = 0; j < 6 - i; j++){
				if (tablero[i][j] != 'X')
					return 'A';
			}
		}
		return 'O';
	// se verifica si todas las fichas X llegaron al campamento enemigo
	} else {
		for(i = 11, k = 4; i < 15; i++, k--){
			for(j = 10 + k; j < 16; j++){
				if (tablero[i][j] != 'X')
					return 'A';
			}
		}
		for (j = 11; j < 16; j++){
			if (tablero[15][j] != 'X')
					return 'A';
		}
		return tipoFicha;
	}
}

int main(void) {
	srand (time(NULL));
	struct coordFicha fichasMaquina [19]; //almacena las posiciones de todas la fichas de la maquina
	int f1, c1, f2, c2, sorteoFicha, sorteoInicio;
	int ficha; // ficha: Número de ficha de la máquina
	char tablero[N][N], fichaUsuario, fichaMaquina, finJuego; 

    bienvenida();

    // Toma los valores de O o X dependeindo de la ficha
	sorteoFicha = rand() % 2;
	if (sorteoFicha == 0){
		fichaUsuario = 'O';
		fichaMaquina = 'X';
	} else {
		fichaUsuario = 'X';
		fichaMaquina = 'O';
	}
	inicializarTab (tablero, fichasMaquina, sorteoFicha);
	imprimirTab (tablero);
	printf("Eres la ficha %c y la maquina es la ficha %c\n", fichaUsuario, fichaMaquina);

    sorteoInicio = rand()%2;
    if(sorteoInicio==0){
        do {
		printf("Su turno\n");
		jugadaUsuario (tablero, fichaUsuario, &f1, &c1, &f2, &c2);
		finJuego = verificarFindelJuego (tablero, fichaUsuario);
		if (finJuego == 'A'){
			printf("Turno de la maquina\n");
			jugadaMaquina (tablero, fichasMaquina, fichaMaquina, &ficha, &f1, &c1, &f2, &c2);
			imprimirTab (tablero);
			printf("La maquina ha movido una ficha de la posicion (%d, %d) a la posicion (%d, %d)\n", f1 + 1, c1 + 1, f2 + 1, c2 + 1);
			finJuego = verificarFindelJuego (tablero, fichaMaquina);
		}
	}while (finJuego == 'A');
    }
    else{
        do{
            printf("Turno de la maquina\n");
            jugadaMaquina (tablero, fichasMaquina, fichaMaquina, &ficha, &f1, &c1, &f2, &c2);
            imprimirTab (tablero);
            printf("La maquina ha movido una ficha de la posicion (%d, %d) a la posicion (%d, %d)\n", f1 + 1, c1 + 1, f2 + 1, c2 + 1);
            finJuego = verificarFindelJuego (tablero, fichaMaquina);
            if (finJuego == 'A'){
                printf("Su turno\n");
                jugadaUsuario (tablero, fichaUsuario, &f1, &c1, &f2, &c2);
                finJuego = verificarFindelJuego (tablero, fichaUsuario);
            }

        }while(finJuego=='A');
            

    }
	
	if (finJuego == fichaUsuario)
		printf("Felicidades!!! \n Has Ganado :)");
	else
		printf("Perdiste :( \n Tal vez la proxima");
	return EXIT_SUCCESS;
}
