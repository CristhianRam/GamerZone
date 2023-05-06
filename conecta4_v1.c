/*Autor: fukin cram*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define FILAS_C4 6
#define COL_C4 7

void generarTablero(char [FILAS_C4][COL_C4]);
void imprimirTablero(char [FILAS_C4][COL_C4]);
void jugarContraJugador (char [FILAS_C4][COL_C4]);
void insertarFicha (char tablero[FILAS_C4][COL_C4], int jugador, int * );
int verificarGanador(char tablero[FILAS_C4][COL_C4], int jugador);


int main(int argc, char *argv[]) {
	char tablero[FILAS_C4][COL_C4];
	int opc;
	
	do {
		// Imprimir el menú de opciones
		printf("\n--------------------------------\n");
		printf("          Bienvenido a          \n");
		printf("           Conecta 4            \n");
		printf("--------------------------------\n");
		printf("1. Jugar contra otro jugador\n");
		printf("2. Jugar contra la máquina\n");
		printf("3. Salir\n");
		printf("Ingrese su elección (1-3): ");
		scanf("%d", &opc);
		
		// Ejecutar la opción elegida
		switch (opc) {
		case 1:
			jugarContraJugador(tablero);
			break;
		case 2:
			//jugarContraMaquina();
			break;
		case 3:
			printf("Saliendo del juego...\n");
			break;
		default:
			printf("Elección inválida. Intente de nuevo.\n");
			break;
		}
	} while (opc != 3);

	return 0;
}

//Función que genera el tablero con espacios en blanco
void generarTablero(char tablero[FILAS_C4][COL_C4]) {
	for (int i = 0; i < FILAS_C4; i++) {
		for (int j = 0; j < COL_C4; j++) {
			tablero[i][j] = ' ';
		}
	}
}

//Función que imprime el tablero con el formato del juego
void imprimirTablero(char tablero[FILAS_C4][COL_C4]) {
	printf(" 1 2 3 4 5 6 7\n");
	for (int i = 0; i < FILAS_C4; i++) {
		for (int j = 0; j < COL_C4; j++) {
			printf("|%c", tablero[i][j]);
		}
		printf("|\n");
	}
}

/*--------------------------------------------------------
---------FUNCION PARA JUGAR CONTRA OTRO JUGADOR-----------
--------------------------------------------------------*/
void jugarContraJugador (char tablero[FILAS_C4][COL_C4]){
	system("cls");
	int ganador=0, movimiento, jugador, nMovimientos=0;
	
	generarTablero(tablero);
	imprimirTablero(tablero);
	do{
		
	 //ENTRADA PARA JUGADOR 1:
	 jugador=1;
	 printf("\nTurno de: Jugador %i.",jugador);
	 printf("\nIngrese su movimiento (columna 1-7): ");
	 do{
		 scanf("%i",&movimiento); 
		 if(movimiento<1 || movimiento>7){
			 printf("Movimiento invalido. Ingrese de nuevo: ");
		 }
	 } while(movimiento<1 || movimiento>7);
	 nMovimientos++;
	 
	 movimiento=movimiento-1;
	 insertarFicha (tablero,jugador,&movimiento);
	 printf("\n");
	 imprimirTablero(tablero);
	 ganador=verificarGanador(tablero, jugador);
	 if (ganador==1) break;
	 
	
	 
	 //ENTRADA PARA JUGADOR 2:
	 jugador=2;
	 printf("\nTurno de: Jugador %i.",jugador);
	 printf("\nIngrese su movimiento (columna 1-7): ");
	 do{
		 scanf("%i",&movimiento); 
		 if(movimiento<1 || movimiento>7){
			 printf("Movimiento invalido. Ingrese de nuevo: ");
		 }
	 } while(movimiento<1 || movimiento>7);
	 
	 movimiento=movimiento-1;
	 insertarFicha (tablero,jugador,&movimiento);
	 nMovimientos++;
	 printf("\n");
	 imprimirTablero(tablero);
	 ganador=verificarGanador(tablero, jugador);
	 printf("\n");
	 if (ganador==1) break;
	 
	} while(nMovimientos<42);
	
	if(nMovimientos==42) printf("¡El resultado es un empate!\n");
	
	printf("Presione la tecla \"q\" para regresar al menú del juego...\n");
	while (getchar() != 'q') {
		// Esperamos hasta que se presione la tecla 'q'
	}
	system("cls");
	return;
}
	
	
void insertarFicha (char tablero[FILAS_C4][COL_C4], int jugador, int *movimiento){
	int i;
	char simboloJugador;
	if (jugador==1){
		simboloJugador='O';
	}
	else simboloJugador='X';
	
	for (i=FILAS_C4-1;i>=0;i--){
		
		if (tablero[i][*movimiento] == ' '){
			tablero[i][*movimiento] = simboloJugador;
			break;
		}
		//Condicional para el caso en el que se trate de ingresar una ficha en una columna ya llena.
		if (i == 0 && tablero[i][*movimiento] != ' '){
			printf("Movimiento invalido. Ingrese de nuevo: ");
			scanf("%i",movimiento);
			*movimiento=*movimiento-1;
			i=FILAS_C4;
		}
	}
	
}
	
//Función que verifica si después de un movimiento el jugador ha ganado
int verificarGanador(char tablero[FILAS_C4][COL_C4], int jugador) {
	int i, j;
	char simboloJugador;
	if (jugador==1){
		simboloJugador='O';
	}
	else simboloJugador='X';
	
	// Revisar horizontalmente
	for (i = 0; i < FILAS_C4; i++) {
		for (j = 0; j < COL_C4 - 3; j++) {
			if (tablero[i][j] == simboloJugador &&
				tablero[i][j+1] == simboloJugador &&
					tablero[i][j+2] == simboloJugador &&
						tablero[i][j+3] == simboloJugador) {
				printf("\n¡El jugador %i ha ganado!\n",jugador);
				return 1;
			}
		}
	}
	
	// Revisar verticalmente
	for (i = 0; i < FILAS_C4 - 3; i++) {
		for (j = 0; j < COL_C4; j++) {
			if (tablero[i][j] == simboloJugador &&
				tablero[i+1][j] == simboloJugador &&
					tablero[i+2][j] == simboloJugador &&
						tablero[i+3][j] == simboloJugador) {
				printf("\n¡El jugador %i ha ganado!\n",jugador);
				return 1;
			}
		}
	}
	
	// Revisar en diagonal hacia arriba
	for (i = 3; i < FILAS_C4; i++) {
		for (j = 0; j < COL_C4 - 3; j++) {
			if (tablero[i][j] == simboloJugador &&
				tablero[i-1][j+1] == simboloJugador &&
					tablero[i-2][j+2] == simboloJugador &&
						tablero[i-3][j+3] == simboloJugador) {
				printf("\n¡El jugador %i ha ganado!\n",jugador);
				return 1;
			}
		}
	}
	
	// Revisar en diagonal hacia abajo
	for (i = 0; i < FILAS_C4 - 3; i++) {
		for (j = 0; j < COL_C4 - 3; j++) {
			if (tablero[i][j] == simboloJugador &&
				tablero[i+1][j+1] == simboloJugador &&
					tablero[i+2][j+2] == simboloJugador &&
						tablero[i+3][j+3] == simboloJugador) {
				printf("\n¡El jugador %i ha ganado!\n",jugador);
				return 1;
			}
		}
	}
	
	return 0;
}
