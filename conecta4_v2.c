/*Autor: Diclonyx*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h> 			
//Para números aleatorios

//Definición del tamaño del tablero
#define FILAS_C4 6
#define COLUMNAS_C4 7

//Definición de colores de texto
#define ROJO "\x1b[31m"
#define AZUL "\x1b[34m"
#define VERDE "\x1b[32m"
#define CYAN  "\x1b[36m"
#define RESET_COLOR "\x1b[0m"

//Cohesión de funciones
void generarTablero(char [FILAS_C4][COLUMNAS_C4]);
void imprimirTablero(char [FILAS_C4][COLUMNAS_C4]);
void jugarContraJugador ();
void jugarContraMaquina();
int generarMovimientoMaquina (char [FILAS_C4][COLUMNAS_C4]);
void insertarFicha (char [FILAS_C4][COLUMNAS_C4], int , int * );
int verificarGanador(char [FILAS_C4][COLUMNAS_C4], int );
void imprimir_instrucciones();


int main(int argc, char *argv[]) {
	setlocale(LC_ALL,"spanish");
	char opc;
	do {
		// Imprimir el menú de opciones
		printf(CYAN "--------------------------------\n");
		printf("          Bienvenido a          \n");
		printf("           Conecta 4            \n");
		printf("--------------------------------\n");
		printf("---------Equipo Diclonyx--------\n");
		printf("--------------------------------\n" RESET_COLOR);
		printf("1. Jugar contra otro jugador\n");
		printf("2. Jugar contra la máquina\n");
		printf("3. Instrucciones\n");
		printf("4. Salir\n");
		printf("\nIngrese su elección (1-4): ");
		do{
			scanf("%c", &opc);
			if (opc != '1' && opc != '2' && opc != '3' && opc != '4'){
				printf("Elección invalida. Intente de nuevo: ");
				getchar();
			}
		}while (opc != '1' && opc != '2' && opc != '3'&& opc != '4'); //Ciclo para validar la entrada
		
		// Ejecutar la opción elegida
		switch (opc) {
		case '1':
			jugarContraJugador();
			break;
		case '2':
			jugarContraMaquina();
			break;
		case '3':
			imprimir_instrucciones();
			break;
		case '4':
			printf("\nSaliendo del juego...\n");
			printf(VERDE "Hasta la próxima:)\n" RESET_COLOR);
			break;
		}
	} while (opc != '4');

	return 0;
}

//--------FUNCION PARA JUGAR CONTRA OTRO JUGADOR----------
void jugarContraJugador (){
	system("cls");
	char tablero[FILAS_C4][COLUMNAS_C4];
	int ganador=0, movimiento, jugador, n_movimientos=0;
	
	generarTablero(tablero);//Se genera la matriz del tablero
	imprimirTablero(tablero);//Se imprime el tablero mediante una llamada a función
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
	 } while(movimiento<1 || movimiento>7);//Validación del movimiento
	 n_movimientos++;//Contador de movimientos
	 
	 movimiento=movimiento-1;//Se le resta 1 ya que la matriz inicia en 0
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
	 insertarFicha (tablero,jugador,&movimiento);//Llamada a la función insertarFicha
	 n_movimientos++;
	 printf("\n");
	 imprimirTablero(tablero);
	 ganador=verificarGanador(tablero, jugador);//Verificamos si el último movimiento da como resultado una victoria
	 printf("\n");
	 if (ganador==1) break;
	 
	} while(n_movimientos<42);
	
	if(n_movimientos==42) printf("¡El resultado es un empate!\n");
	
	printf("Presione la tecla \"q\" para regresar al menú del juego...\n");
	while (getchar() != 'q') {
		// Espera hasta que se presione la tecla 'q' para volver al menú del juego
	}
	memset(tablero,0,FILAS_C4*COLUMNAS_C4);//Limpieza de la matriz
	system("cls");//Limpieza de la pantalla
	getchar();
	return;
}
	

//FUNCION PARA JUGAR CONTRA MAQUINA
void jugarContraMaquina(){
	system("cls");
	char tablero[FILAS_C4][COLUMNAS_C4];
	int ganador=0, movimiento, jugador, n_movimientos=0;
	
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
		n_movimientos++;
		
		movimiento=movimiento-1;
		insertarFicha (tablero,jugador,&movimiento);
		printf("\n");
		imprimirTablero(tablero);
		ganador=verificarGanador(tablero, jugador);
		if (ganador==1) break;
		
		//TURNO PARA JUGADOR 2 (MAQUINA): 
		jugador=2;
		printf("\nTurno de: Jugador %i.",jugador);
		movimiento=generarMovimientoMaquina(tablero);//Llamada a la función que genera el movimiento de la PC
		insertarFicha (tablero,jugador,&movimiento);
		printf("\nJugador %i ha hecho su movimiento en la columna %i.",jugador, movimiento+1);
		n_movimientos++;//Cuenta del numero de movimientos
		printf("\n");
		imprimirTablero(tablero);
		ganador=verificarGanador(tablero, jugador);
		printf("\n");
		if (ganador==1) break;
		
	} while(n_movimientos<42);
	
	if(n_movimientos==42) printf(VERDE "¡El resultado es un empate!\n" RESET_COLOR);
	
	printf("Presione la tecla \"q\" para regresar al menú del juego...\n");
	while (getchar() != 'q') {
		// Espera hasta que se presione la tecla 'q'
	}
	getchar();
	memset(tablero,0,FILAS_C4*COLUMNAS_C4);
	system("cls");
	return;
}

//Funcion para generar el movimiento de la computadora de acuerdo a casos posibles
int generarMovimientoMaquina (char tablero[FILAS_C4][COLUMNAS_C4]){
	
	int i, j, movimiento;
	char simbolo_jugador, simbolo_maquina, simbolo_vacio;
	
	simbolo_maquina='X';
	simbolo_jugador='O';
	simbolo_vacio=' ';
	
	//Generar un primer movimiento aleatorio
	srand(time(NULL));
	movimiento = rand() % 7; 
	
	//Condicional para el caso en el que se trate de ingresar una ficha en una columna ya llena.
	do{
		if (tablero[0][movimiento] != simbolo_vacio){
			movimiento = rand() % 7; // Generar un número entero aleatorio entre 0 y 6.
			i=FILAS_C4;
		}
	}while (tablero[0][movimiento] != simbolo_vacio);
	/*Nota: Se añade en esta misma funcion y no en la de "insertarFicha" con el propósito
	de no afectar el funcionamiento de esta última en el proceso de "jugarContraJugador"*/
	
	
	/*------Analizar posibilidad de victoria del rival
	Explicación: Se revisa el tablero actual en busca de posibles movimientos del rival que terminen
	en su victoria, de encontrarse alguno, el movimiento generado contrarresta esa posibilidad*/
	
	// Revisar horizontalmente (Desde la Izquierda)
	for (i=0; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			if (tablero[i][j] == simbolo_jugador && tablero[i][j+1] ==
				simbolo_jugador && tablero[i][j+2] == simbolo_jugador){
				if (i==FILAS_C4-1 && tablero[i][j+3] == simbolo_vacio){
					movimiento=j+3;
				}
				else if (i != FILAS_C4-1 && tablero[i][j+3] == simbolo_vacio && tablero[i-1][j+3] != simbolo_vacio){
					movimiento=j+3;
				}
			}
		}
	}

	//Revisar horizontalmente (Desde la Derecha)
	for (i=0; i<FILAS_C4; i++) {
		for (j = COLUMNAS_C4-1; j >= 3; j--) {
			if (tablero[i][j] == simbolo_jugador && tablero[i][j-1] ==
				simbolo_jugador && tablero[i][j-2] == simbolo_jugador){
				
				if (i == FILAS_C4-1 && tablero[i][j-3] == simbolo_vacio){
					movimiento=j-3;
				}
				else if (i != FILAS_C4-1 && tablero[i][j-3] == simbolo_vacio && tablero[i-1][j-3] != simbolo_vacio){
					movimiento=j-3;
				}
			}
		}
	}

	//Revisar horizontalmente (Espacios entre fichas)
	for (i=0; i<FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			
			if (tablero[i][j] == simbolo_jugador &&
				tablero[i][j+1] == simbolo_vacio &&
				tablero[i][j+2]== simbolo_jugador &&
				tablero[i][j+3]== simbolo_jugador){
				
				if(i == FILAS_C4-1){
					movimiento=j+1;
				}
				
				else if (i != FILAS_C4-1 && tablero[i-1][j+2] != simbolo_vacio){
					movimiento=j+1;
				}
			}
			else if (tablero[i][j] == simbolo_jugador &&
					tablero[i][j+1] == simbolo_jugador &&
					tablero[i][j+2]== simbolo_vacio &&
					tablero[i][j+3]== simbolo_jugador){
				
				if (i == FILAS_C4-1){
					movimiento=j+2;
				}
				else if (i != FILAS_C4-1 && tablero[i-1][j+2] != simbolo_vacio){
					movimiento=j+2;
				}
				
			}
		}
	}

	// Revisar verticalmente
	for (j = 0; j < COLUMNAS_C4; j++) {
		for (i = FILAS_C4-1; i >= 3; i--) {
			if (tablero[i][j] == simbolo_jugador &&
				tablero[i-1][j] == simbolo_jugador &&
				tablero[i-2][j] == simbolo_jugador &&
				tablero[i-3][j] == simbolo_vacio) {
				movimiento=j;
			}
		}
	}

	/*-----------------------------------------
	Analizar posibilidad de victoria de la PC
	-------------------------------------------
	Explicación: Se revisa el tablero actual en busca de posibles movimientos de la máquina que terminen
	en su victoria, de encontrarse alguno, el movimiento generado se da en esa posición*/
	
	// Revisar horizontalmente (Desde la Izquierda)
	for (i = 0; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			if (tablero[i][j] == simbolo_maquina &&
				tablero[i][j+1] == simbolo_maquina &&
				tablero[i][j+2] == simbolo_maquina){
				if (i == FILAS_C4-1 && tablero[i][j+3] == simbolo_vacio  ){
					movimiento=j+3;
				}
				else if (i != FILAS_C4-1 && tablero[i][j+3] == simbolo_vacio && tablero[i-1][j+3] != simbolo_vacio){
					movimiento=j+3;
				}
			}
		}
	}
	

	//Revisar horizontalmente (Desde la Derecha)
	for (i = 0; i < FILAS_C4; i++) {
		for (j = COLUMNAS_C4-1; j >= 3; j--) {
			if (tablero[i][j] == simbolo_maquina &&
				tablero[i][j-1] == simbolo_maquina &&
				tablero[i][j-2] == simbolo_maquina){
				
				if (tablero[i][j-3] == simbolo_vacio && i==FILAS_C4-1){
					movimiento=j-3;
				}
				else if (tablero[i][j-3] == simbolo_vacio && tablero[i-1][j-3] != simbolo_vacio){
					movimiento=j-3;
				}
			}
		}
	}

	//Revisar horizontalmente (Espacios entre fichas)
	for (i = 0; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			
			if (tablero[i][j] == simbolo_maquina &&
				tablero[i][j+1] == simbolo_vacio &&
				tablero[i][j+2] == simbolo_maquina &&
					tablero[i][j+3]== simbolo_maquina){
				
				if(i == FILAS_C4-1){
					movimiento=j+1;
				}
				else if (i != FILAS_C4-1 && tablero[i-1][j+2] != simbolo_vacio){
					movimiento=j+1;
				}
			}
			else if (tablero[i][j] == simbolo_maquina &&
				tablero[i][j+1] == simbolo_maquina &&
				tablero[i][j+2]== simbolo_vacio &&
				tablero[i][j+3]== simbolo_maquina){
				
				if (i == FILAS_C4-1){
					movimiento=j+2;
				}
				else if (i != FILAS_C4-1 && tablero[i-1][j+2] != simbolo_vacio){
					movimiento=j+2;
				}
				
			}
		}
	}

	// Revisar verticalmente
	for (j = 0; j < COLUMNAS_C4; j++) {
		for (i = FILAS_C4-1; i >= 3; i--) {
			if (tablero[i][j] == simbolo_maquina &&
				tablero[i-1][j] == simbolo_maquina &&
				tablero[i-2][j] == simbolo_maquina &&
				tablero[i-3][j] == simbolo_vacio) {
				movimiento=j;
			}
		}
	}
	
	return (movimiento);
	
}
	
/*--------------------------------------------------------
------------------FUNCIONES GENERALES---------------------
--------------------------------------------------------*/
//Función que genera el tablero con espacios en blanco
void generarTablero(char tablero[FILAS_C4][COLUMNAS_C4]) {
	int i, j;
	for (i = 0; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4; j++) {
			tablero[i][j] = ' ';
		}
	}
}

//Función para insertar la ficha en la elección del jugador
void insertarFicha (char tablero[FILAS_C4][COLUMNAS_C4], int jugador, int *movimiento){
	int i;
	char simbolo_jugador;
	if (jugador==1){
		simbolo_jugador='O';
	}
	else simbolo_jugador='X';
	
	for (i=FILAS_C4-1;i>=0;i--){
		
		if (tablero[i][*movimiento] == ' '){
			tablero[i][*movimiento] = simbolo_jugador;
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

//Función que imprime el tablero con el formato del juego
void imprimirTablero(char tablero[FILAS_C4][COLUMNAS_C4]) {
	int i, j;
	printf(" 1 2 3 4 5 6 7\n");
	for (i = 0; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4; j++) {
			printf("|" );
			if (tablero[i][j]=='O'){
				printf(AZUL "O" RESET_COLOR);	
			}
			else if (tablero[i][j]=='X'){
				printf(ROJO "X" RESET_COLOR);
			}
			else{
				printf(" ");
			}
		}
		printf("|\n");
	}
}

//Función que verifica si después de un movimiento el jugador ha ganado
int verificarGanador(char tablero[FILAS_C4][COLUMNAS_C4], int jugador) {
	int i, j;
	char simbolo_jugador;
	if (jugador==1){
		simbolo_jugador='O';
	}
	else simbolo_jugador='X';
	
	// Revisar horizontalmente
	for (i = 0; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			if (tablero[i][j] == simbolo_jugador &&
				tablero[i][j+1] == simbolo_jugador &&
					tablero[i][j+2] == simbolo_jugador &&
						tablero[i][j+3] == simbolo_jugador) {
				printf(VERDE "\n¡El jugador %i ha ganado!\n" RESET_COLOR, jugador);
				return 1;
			}
		}
	}
	
	// Revisar verticalmente
	for (i = 0; i < FILAS_C4 - 3; i++) {
		for (j = 0; j < COLUMNAS_C4; j++) {
			if (tablero[i][j] == simbolo_jugador &&
				tablero[i+1][j] == simbolo_jugador &&
					tablero[i+2][j] == simbolo_jugador &&
						tablero[i+3][j] == simbolo_jugador) {
				printf(VERDE "\n¡El jugador %i ha ganado!\n" RESET_COLOR, jugador);
				return 1;
			}
		}
	}
	
	// Revisar en diagonal hacia arriba
	for (i = 3; i < FILAS_C4; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			if (tablero[i][j] == simbolo_jugador &&
				tablero[i-1][j+1] == simbolo_jugador &&
					tablero[i-2][j+2] == simbolo_jugador &&
						tablero[i-3][j+3] == simbolo_jugador) {
				printf(VERDE "\n¡El jugador %i ha ganado!\n" RESET_COLOR, jugador);
				return 1; 
			}
		}
	}
	
	// Revisar en diagonal hacia abajo
	for (i = 0; i < FILAS_C4 - 3; i++) {
		for (j = 0; j < COLUMNAS_C4 - 3; j++) {
			if (tablero[i][j] == simbolo_jugador &&
				tablero[i+1][j+1] == simbolo_jugador &&
					tablero[i+2][j+2] == simbolo_jugador &&
						tablero[i+3][j+3] == simbolo_jugador) {
				printf(VERDE "\n¡El jugador %i ha ganado!\n" RESET_COLOR, jugador);
				return 1;
			}
		}
	}
	
	return 0;
}

void imprimir_instrucciones() {
	system("cls");
    printf(ROJO "Bienvenido al juego Conecta 4!\n\n" RESET_COLOR);
    printf("El objetivo del juego es conectar cuatro fichas del mismo color\n");
    printf("en una línea vertical, horizontal o diagonal.\n");
    printf("Para jugar, simplemente elige una columna donde dejar caer tu ficha.\n");
    printf("La ficha caerá hasta el fondo de la columna o sobre otra ficha que esté en su camino.\n");
    printf("El primer jugador en conectar cuatro fichas gana la partida.\n");
    printf("Si todas las casillas del tablero están ocupadas y nadie ha conectado cuatro fichas, la partida termina en empate.\n");
    
    	printf("\nPresione la tecla \"q\" para regresar al menú del juego...\n");
	while (getchar() != 'q') {
		// Espera hasta que se presione la tecla 'q' para volver al menú del juego
	}
	getchar();
	system("cls");
	return;
}
