/*Nombre del programa: GamerZone
Autores: Cristhian Ramírez
Equipo Diclonyx
Versión: 4
Compilador: Dev-C++ 5.11*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h> 
#include <windows.h>		

//Definición del tamaño del tablero conecta 4
#define FILAS_C4 6
#define COLUMNAS_C4 7

//LISTADO DE COLORES
enum colors { 
 NEGRO = 0,
 AZUL = 1,
 VERDE = 2,
 CYAN = 3,
 ROJO = 4,
 MAGENTA = 5,
 CAFE = 6,
 L_GRIS = 7,
 D_GRIS = 8,
 L_AZUL = 9,
 L_VERDE = 10,
 L_CYAN = 11,
 L_ROJO = 12,
 L_MAGENTA = 13,
 AMARILLO = 14,
 BLANCO = 15
};

//Declaración de funciones
void generarTablero(char [FILAS_C4][COLUMNAS_C4]);
void imprimirTablero(char [FILAS_C4][COLUMNAS_C4]);
void jugarContraJugador ();
void jugarContraMaquina();
int selectorDificultadC4();
int generarMovimientoMaquina (char [FILAS_C4][COLUMNAS_C4], int);
void insertarFicha (char [FILAS_C4][COLUMNAS_C4], int , int * );
int verificarGanador(char [FILAS_C4][COLUMNAS_C4], int , char [], char*);
void agregarNombre(char*, char*);
void imprimirLeaderboard ();
void imprimir_instrucciones();
void color(int Background, int Text);

/*-------------------------------------------------------------
A PARTIR DE AQUI EMPIEZAN LAS FUNCIONES PARA EL JUEGO CONECTA 4
--------------------------------------------------------------*/
int main(){
	setlocale(LC_ALL,"spanish");
	char opc, extra[100];
	do {
		// Imprimir el menú de opciones
		color(NEGRO,CYAN);printf("------------------------------------------------------------\n");
		color(NEGRO,L_ROJO);
		printf("  /  __ \\                          | |           /   |\n");
    	printf("  | /  \\/  ___   _ __    ___   ___ | |_   __ _  / /| |\n");
    	printf("  | |     / _ \\ | '_ \\  / _ \\ / __|| __| / _` |/ /_| |\n");
    	printf("  | \\__/\\| (_) || | | ||  __/| (__ | |_ | (_| |\\___  |\n");
    	printf("   \\____/ \\___/ |_| |_| \\___| \\___| \\__| \\__,_|    |_/\n");
		color(NEGRO,CYAN);
		printf("------------------------------------------------------------\n");
		printf("---------------------Equipo Diclonyx------------------------\n");
		printf("------------------------------------------------------------\n");;color(NEGRO,BLANCO);
		color(NEGRO,VERDE); printf("      _____________   "); color(NEGRO,CYAN); printf("      _____________\n");
		color(NEGRO,VERDE); printf("     /             \\  "); color(NEGRO,CYAN); printf("     /             \\\n");
		color(NEGRO,VERDE); printf("    |  1:JUGAR VS   |   "); color(NEGRO,CYAN); printf("  |  2:JUGAR VS   |\n");
		color(NEGRO,VERDE); printf("    |  OTRO JUGADOR |   "); color(NEGRO,CYAN); printf("  |     MAQUINA   |\n");
		color(NEGRO,VERDE); printf("     \\_____________/    "); color(NEGRO,CYAN); printf("   \\_____________/\n");
		printf("\n");
		color(NEGRO,AZUL); printf("     ______________     "); color(NEGRO,MAGENTA); printf("    ______________\n");
		color(NEGRO,AZUL); printf("    /              \\  "); color(NEGRO,MAGENTA); printf("     /              \\\n");
		color(NEGRO,AZUL); printf("   |3:INSTRUCCIONES |   "); color(NEGRO,MAGENTA); printf("  | 4:LEADERBOARD |\n");
		color(NEGRO,AZUL); printf("    \\______________/   "); color(NEGRO,MAGENTA); printf("    \\______________/\n");
		printf("\n");
		color(NEGRO,ROJO);printf("                  ______________   \n");
		printf("                 /              \\  \n");
		printf("                |    5:SALIR     |   \n");
		printf("                 \\______________/  \n\n");
		color(NEGRO,BLANCO); printf("           INGRESE UNA OPCIÓN DEL MENÚ: ");
		do{
			scanf(" %c", &opc);
			if (opc != '1' && opc != '2' && opc != '3' && opc != '4' && opc != '5'){
				printf("Elección invalida. Intente de nuevo: ");
			}
			gets(extra); 
		}while (opc != '1' && opc != '2' && opc != '3'&& opc != '4' && opc != '5'); //Ciclo para validar la entrada
		
		// Ejecutar la opción elegida
		switch (opc) {
		case '1':
			jugarContraJugador();//Llamada a la función para jugar contra otro jugador
			break;
		case '2':
			jugarContraMaquina();//Llamada a la función para jugar contra la máquina
			break;
		case '3':
			imprimir_instrucciones();//Llamada a la función que imprime las instrucciones
			break;
		case '4':
			imprimirLeaderboard();
			break;
		case '5':
			printf("\nSaliendo del juego...\n");
			color(NEGRO, VERDE); printf("Hasta la próxima:)\n"); 
			sleep(2);
			color(NEGRO,BLANCO);
			break;
		}
		system("cls");
	} while (opc != '5');
	return;
}

//--------FUNCION PARA JUGAR CONTRA OTRO JUGADOR----------
void jugarContraJugador (){
	system("cls");
	char tablero[FILAS_C4][COLUMNAS_C4], movimiento_aux, nombre1[20], nombre2[20], extra[100];
	int ganador=0, jugador, movimiento,n_movimientos=0;
	char* archivo = "leaderboard_1vs1.txt"; //archivo de texto para el leaderboard de este modo
	
	color(NEGRO,CYAN); printf("--------------------------------\n");
	printf("            Jugar vs            \n");
	printf("          Otro Jugador          \n");
	printf("--------------------------------\n"); color(NEGRO,BLANCO);
	do{
	 	printf("Ingrese el nombre del jugador 1: ");
	 	scanf("%s",nombre1);
	 	printf("\n");
	 	if (strcmp(nombre1,"maquina") == 0 ){
	 	 	printf("Nombre inválido, intente de nuevo.\n");
		  }
	}while(strcmp(nombre1,"maquina") == 0 );//Validacion para no ingresar el nombre asignado para la maquina en el modo vs maquina
	
	 do{
	 	printf("Ingrese el nombre del jugador 2: ");
	 	scanf("%s",nombre2);
	 	 printf("\n");	
	 	 if (strcmp(nombre2,"maquina") == 0 ){
	 	 	printf("Nombre inválido, intente de nuevo.\n");
		  }
	}while(strcmp(nombre2,"maquina") == 0 );
	generarTablero(tablero);//Llamada a función que genera la matriz del tablero
	imprimirTablero(tablero);//Llamada a la función que imprime el tablero actuzalizado
	
	do{
	 //ENTRADA PARA JUGADOR 1:
	 jugador=1;
	 printf("\nTurno de: ");color(NEGRO,AZUL);printf("%s.", nombre1);color(NEGRO,BLANCO);
	 printf("\nIngrese su movimiento (columna 1-7): ");
	 do{
		 scanf(" %c",&movimiento_aux); 
		 gets(extra);
		 if(movimiento_aux != '1' && movimiento_aux != '2' && movimiento_aux != '3' && movimiento_aux != '4' && movimiento_aux != '5' && movimiento_aux != '6' && movimiento_aux != '7' ){
			 printf("Movimiento invalido. Ingrese de nuevo: ");
		 }
	 } while(movimiento_aux != '1' && movimiento_aux != '2' && movimiento_aux != '3' && movimiento_aux != '4' && movimiento_aux != '5' && movimiento_aux != '6' && movimiento_aux != '7');//Validación del movimiento
	 n_movimientos++;//Contador de movimientos
	 
	 movimiento = movimiento_aux-48;
	 movimiento=movimiento-1;//Se le resta 1 ya que la matriz inicia en 0
	 insertarFicha (tablero,jugador,&movimiento); //Llamada a la función que inserta la ficha en la matriz (tablero)
	 system("cls");//Limpiamos la pantalla
	 imprimirTablero(tablero);//LLamada a la función que imprime el tablero
	 ganador=verificarGanador(tablero, jugador, nombre1, archivo); //Llamada a la función que verifica si se genera una victoria
	 if (ganador==1) break;
	 
	 //ENTRADA PARA JUGADOR 2:
	 jugador=2;
	 printf("\nTurno de: ");color(NEGRO,ROJO);printf("%s.",nombre2);color(NEGRO,BLANCO);
	 printf("\nIngrese su movimiento (columna 1-7): ");
	 do{
		 scanf(" %c",&movimiento_aux); 
		 gets(extra);
		 if(movimiento_aux != '1' && movimiento_aux != '2' && movimiento_aux != '3' && movimiento_aux != '4' && movimiento_aux != '5' && movimiento_aux != '6' && movimiento_aux != '7' ){
			 printf("Movimiento invalido. Ingrese de nuevo: ");
		 }
	 } while(movimiento_aux != '1' && movimiento_aux != '2' && movimiento_aux != '3' && movimiento_aux != '4' && movimiento_aux != '5' && movimiento_aux != '6' && movimiento_aux != '7');//Validación del movimiento
	 movimiento = movimiento_aux-48;
	 
	 movimiento=movimiento-1;
	 insertarFicha (tablero,jugador,&movimiento);
	 n_movimientos++;
	 system("cls");
	 imprimirTablero(tablero);
	 ganador=verificarGanador(tablero, jugador, nombre2, archivo);//Llamada a la función que verifica si el movimiento termina en victoria
	 printf("\n");
	 if (ganador==1) break;
	 
	} while(n_movimientos<42);
	
	if(ganador!=1) {
		color(NEGRO,VERDE); printf("¡El resultado es un empate!\n"); color(NEGRO,BLANCO);	
	}
	
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
	char tablero[FILAS_C4][COLUMNAS_C4], movimiento_aux, nombre[20], extra[100];
	int ganador=0, movimiento, jugador, n_movimientos=0, dificultad;
	char* archivo = "leaderboard_vs_maquina.txt"; //archivo de texto para el leaderboard de este modo
	
	dificultad=selectorDificultadC4();//LLamada a la función que imprime el menú de selección de dificultad
	if (dificultad==4) return;
	
	color(NEGRO,CYAN); printf("--------------------------------\n");
	printf("            Jugar vs            \n");
	printf("            Maquina             \n");
	printf("--------------------------------\n");
	if (dificultad==1){
		printf("--------Dificultad: "); color(NEGRO,VERDE); printf("Fácil"); color(NEGRO,CYAN); printf("-------\n");
	}
	else if (dificultad==2){
		printf("-------Dificultad: "); color(NEGRO,AMARILLO); printf("Mediana"); color(NEGRO,CYAN); printf("------\n");	
	}
	else if (dificultad==3){
		printf("-------Dificultad: "); color(NEGRO,ROJO); printf("Difícil"); color(NEGRO,CYAN); printf("------\n");
	}
	printf("--------------------------------\n"); color(NEGRO,BLANCO);
	
	do{
		printf("Ingrese el nombre del jugador: ");
		scanf("%s",nombre);
		if (strcmp(nombre,"maquina") == 0 ){
		 	printf("Nombre inválido, intente de nuevo.\n");
		}
	}while (strcmp(nombre,"maquina") == 0 );
	
	generarTablero(tablero); //Llamada a función que genera la matriz del tablero
	imprimirTablero(tablero); //Llamada a función que imprime el tablero
	
	do{
		
		//ENTRADA PARA JUGADOR 1:
		jugador=1;
		printf("\nTurno de: ");color(NEGRO,AZUL);printf("%s.",nombre);color(NEGRO,BLANCO);
		printf("\nIngrese su movimiento (columna 1-7): ");
		do{
		 scanf(" %c",&movimiento_aux); 
		 gets(extra);
		 if(movimiento_aux != '1' && movimiento_aux != '2' && movimiento_aux != '3' && movimiento_aux != '4' && movimiento_aux != '5' && movimiento_aux != '6' && movimiento_aux != '7' ){
			 printf("Movimiento invalido. Ingrese de nuevo: ");
		 }
	 	} while(movimiento_aux != '1' && movimiento_aux != '2' && movimiento_aux != '3' && movimiento_aux != '4' && movimiento_aux != '5' && movimiento_aux != '6' && movimiento_aux != '7');
		n_movimientos++;
		movimiento = movimiento_aux-48;
		movimiento=movimiento-1;
		insertarFicha (tablero,jugador,&movimiento);//Llamada a función que pone la nueva ficha en la matriz (tablero)
		system("cls");
		imprimirTablero(tablero);
		ganador=verificarGanador(tablero, jugador, nombre, archivo);//Llamada a la función que verifica si el movimiento termina en victoria
		if (ganador==1) break;
		
		//TURNO PARA JUGADOR 2 (MAQUINA): 
		jugador=2;
		movimiento=generarMovimientoMaquina(tablero, dificultad);//Llamada a la función que genera el movimiento de la PC
		insertarFicha (tablero,jugador,&movimiento);
		system("cls");
		printf("\nJugador %i ha hecho su movimiento en la columna %i.",jugador, movimiento+1);
		printf("\n");
		n_movimientos++;//Cuenta del numero de movimientos
		imprimirTablero(tablero);
		ganador=verificarGanador(tablero, jugador, "maquina", archivo);//Llamada a la función que verifica si el movimiento termina en victoria
		printf("\n");
		if (ganador==1) break;
		
	} while(n_movimientos<42);
	
	if(ganador!=1){
		color(NEGRO,VERDE);printf("¡El resultado es un empate!\n"); color(NEGRO,BLANCO);
	}
	
	printf("Presione la tecla \"q\" para regresar al menú del juego...\n");
	while (getchar() != 'q') {
		// Espera hasta que se presione la tecla 'q'
	}
	getchar();
	memset(tablero,0,FILAS_C4*COLUMNAS_C4);
	system("cls");
	return;
}

//Funcion para seleccionar la dificultad en el modo vs máquina
int selectorDificultadC4(){
	int opcion;

	// Imprimir el menú de dificultad
	color(NEGRO,CYAN); printf("--------------------------------\n");
	printf("            Jugar vs            \n");
	printf("            Maquina             \n");
	printf("--------------------------------\n");
	printf("------Seleccionar dificultad----\n");
	printf("--------------------------------\n"); color(NEGRO,BLANCO);
	color(NEGRO,VERDE); printf("1. Fácil\n");
	color(NEGRO,AMARILLO); printf("2. Intermedia\n");
	color(NEGRO,ROJO); printf("3. Difícil\n"); 
	color(NEGRO,CYAN); printf("4. Salir\n");color(NEGRO,BLANCO);
	printf("\nIngrese su elección (1-4): ");
	do{
		scanf("%i", &opcion);
		if (opcion<1 || opcion>4){
			printf("Elección invalida. Intente de nuevo: ");
			getchar();
		}
	}while (opcion<1 || opcion>4); //Ciclo para validar la entrada
	
	getchar();
	system("cls");
	return (opcion);
}

//Funcion para generar el movimiento de la computadora de acuerdo a casos posibles
int generarMovimientoMaquina (char tablero[FILAS_C4][COLUMNAS_C4], int dificultad){
	
	int i, j, movimiento;
	char simbolo_jugador, simbolo_maquina, simbolo_vacio;
	
	simbolo_maquina='X';
	simbolo_jugador='O';
	simbolo_vacio=' ';
	
	//Generar un movimiento aleatorio
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
	
	//Movimientos para dificiltad fácil o superior: inserta ficha en sitios continuos a una ya puesta
	for (i=FILAS_C4-1; i >= 0; i--) {	
		for (j = 0; j < COLUMNAS_C4; j++) {
			if (tablero[i][j] == simbolo_maquina){
				if (j < COLUMNAS_C4 - 1 && tablero[i][j+1] == simbolo_vacio){
					movimiento=j+1;
					break;
				}
				else if (j!=0 && tablero[i][j-1] == simbolo_vacio){
					movimiento=j-1;
					break;
				}
			}
		}
	}
	
	for (i=FILAS_C4-1; i > 0; i--) {
		for (j = 0; j < COLUMNAS_C4; j++) {
			if (tablero[i][j] == simbolo_maquina){
				if (tablero[i-1][j] == simbolo_vacio){
					movimiento=j;
					break;
				}
			}
		}
	}
	/*------Analizar posibilidad de victoria del rival
	Explicación: Se revisa el tablero actual en busca de posibles movimientos del rival que terminen
	en su victoria, de encontrarse alguno, el movimiento generado contrarresta esa posibilidad.
	(Ciertas decisiones se habilitan dependiendo del nivel de dificultad)*/
	
	if (dificultad==2 || dificultad==3){	//Movimientos para dificultad media y difícil
		
		// Revisar horizontalmente (Desde la Izquierda)
		for (i=0; i < FILAS_C4; i++) {
			for (j = 0; j < COLUMNAS_C4 - 3; j++) {
				if (tablero[i][j] == simbolo_jugador && tablero[i][j+1] == simbolo_jugador &&
				tablero[i][j+2] == simbolo_jugador && tablero[i][j+3] == simbolo_vacio){
					if (i==FILAS_C4-1 || (i != FILAS_C4-1  && tablero[i+1][j+3] != simbolo_vacio)){
						movimiento=j+3;
						break;
					}
				}
			}
		}
	
	
		//Revisar horizontalmente (Desde la Derecha)
		for (i=0; i<FILAS_C4; i++) {
			for (j = COLUMNAS_C4-1; j >= 3; j--) {
				if (tablero[i][j] == simbolo_jugador && tablero[i][j-1] == simbolo_jugador &&
				tablero[i][j-2] == simbolo_jugador && tablero[i][j-3]== simbolo_vacio){
					if (i == FILAS_C4-1 || (i != FILAS_C4-1 && tablero[i+1][j-3] != simbolo_vacio)){
						movimiento=j-3;
						break;
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
						break;
					}
					
					else if (i != FILAS_C4-1 && tablero[i-1][j+2] != simbolo_vacio){
						movimiento=j+1;
						break;
					}
					
				}
				else if (tablero[i][j] == simbolo_jugador &&
						tablero[i][j+1] == simbolo_jugador &&
						tablero[i][j+2]== simbolo_vacio &&
						tablero[i][j+3]== simbolo_jugador){
					
					if (i == FILAS_C4-1){
						movimiento=j+2;
						break;
					}
					else if (i != FILAS_C4-1 && tablero[i+1][j+2] != simbolo_vacio){
						movimiento=j+2;
						break;
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
					break;
				}
			}
		}
	}
		
	
	if (dificultad==3){ 	//Movimientos para dificultad difícil
		// Revisar diagonalmente (de abajo hacia arriba) desde la izquierda
		for (i = FILAS_C4 - 1; i >= 3; i--) {
	   		for (j = 0; j <= COLUMNAS_C4 - 4; j++) {
	       		if (tablero[i][j] == simbolo_jugador && tablero[i-1][j+1] == simbolo_jugador && tablero[i-2][j+2] == simbolo_jugador && tablero[i-3][j+3] == simbolo_vacio && tablero[i-2][j+3] != simbolo_vacio) {
	                movimiento = j+3;
	                break;
	        	}
	    	}
		}

		// Revisar diagonalmente (de abajo hacia arriba) desde la derecha
		for (i = FILAS_C4 - 1; i >= 3; i--) {
	   		for (j = COLUMNAS_C4 - 1; j >= 3; j--) {
	        	if (tablero[i][j] == simbolo_jugador && tablero[i-1][j-1] == simbolo_jugador && tablero[i-2][j-2] == simbolo_jugador && tablero[i-3][j-3] == simbolo_vacio && tablero[i-2][j-3] != simbolo_vacio) {
	                movimiento = j-3;
	                break;
	        	}
	    	}
		}
	}


	/*-----------------------------------------
	Analizar posibilidad de victoria de la PC
	-------------------------------------------
	Explicación: Se revisa el tablero actual en busca de posibles movimientos de la máquina que terminen
	en su victoria, de encontrarse alguno, el movimiento generado se da en esa posición*/
	
	if (dificultad == 2 || dificultad==3){	//Movimientos para dificultad mediana y difícil
	
		// Revisar horizontalmente (Desde la Izquierda)
		for (i = 0; i < FILAS_C4; i++) {
			for (j = 0; j < COLUMNAS_C4 - 3; j++) {
				if (tablero[i][j] == simbolo_maquina &&
					tablero[i][j+1] == simbolo_maquina &&
					tablero[i][j+2] == simbolo_maquina &&
					tablero[i][j+3] == simbolo_vacio){
					if (i == FILAS_C4-1 || (i != FILAS_C4-1 && tablero[i+1][j+3] != simbolo_vacio)){
						movimiento=j+3;
						break;
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
						break;
					}
					else if (tablero[i][j-3] == simbolo_vacio && tablero[i+1][j-3] != simbolo_vacio){
						movimiento=j-3;
						break;
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
						break;
					}
					else if (i != FILAS_C4-1 && tablero[i+1][j+2] != simbolo_vacio){
						movimiento=j+1;
						break;
					}
				}
				else if (tablero[i][j] == simbolo_maquina &&
					tablero[i][j+1] == simbolo_maquina &&
					tablero[i][j+2]== simbolo_vacio &&
					tablero[i][j+3]== simbolo_maquina){
					
					if (i == FILAS_C4-1){
						movimiento=j+2;
						break;
					}
					else if (i != FILAS_C4-1 && tablero[i+1][j+2] != simbolo_vacio){
						movimiento=j+2;
						break;
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
					break;
				}
			}
		}
		
	}
	
	if (dificultad == 3){ 	//Movimientos para dificultad difícil

		// Revisar diagonalmente (de abajo hacia arriba) desde la izquierda
		for (i = FILAS_C4 - 1; i >= 3; i--) {
		    for (j = 0; j <= COLUMNAS_C4 - 4; j++) {
		        if (tablero[i][j] == simbolo_maquina && tablero[i-1][j+1] == simbolo_maquina && tablero[i-2][j+2] == simbolo_maquina && tablero[i-3][j+3] == simbolo_maquina && tablero[i-2][j+3] != simbolo_vacio) {
	                movimiento = j+3;
	                break;
		        }
		    }
		}
	
		// Revisar diagonalmente (de abajo hacia arriba) desde la derecha
		for (i = FILAS_C4 - 1; i >= 3; i--) {
		    for (j = COLUMNAS_C4 - 1; j >= 3; j--) {
		        if (tablero[i][j] == simbolo_maquina && tablero[i-1][j-1] == simbolo_maquina && tablero[i-2][j-2] == simbolo_maquina && tablero[i-3][j-3] == simbolo_maquina && tablero[i-2][j-3] != simbolo_vacio) {
	                movimiento = j-3;
	                break;
		        }
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
				color(NEGRO,AZUL); printf("O");	color(NEGRO,BLANCO);
			}
			else if (tablero[i][j]=='X'){
				color(NEGRO,ROJO); printf("X"); color(NEGRO,BLANCO);
			}
			else{
				printf(" ");
			}
		}
		printf("|\n");
	}
	return;
}

//Función que verifica si después de un movimiento el jugador ha ganado y añade el nombre del jugador al listado del leaderboard
int verificarGanador(char tablero[FILAS_C4][COLUMNAS_C4], int jugador, char nombre[], char* archivo) {
	int i, j, verificacion_ganador=0;
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
						verificacion_ganador=1;
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
				verificacion_ganador=1;
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
				verificacion_ganador=1;
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
				verificacion_ganador=1;
			}
		}
	}
	
	if(verificacion_ganador==1){
		color(NEGRO,VERDE); printf("\n¡El jugador %i (%s) ha ganado!\n", jugador, nombre); color(NEGRO,BLANCO);
		agregarNombre(archivo, nombre);//Llamada a la función que añade el nombre del ganador al leaderboard
		return 1;
	}
	
	return 0;
}

//Función que añade el nombre del ganador al archivo .txt del leaderboard
void agregarNombre(char* archivo, char* nombre) {
    FILE *fp;
    char linea[100];
    int encontrado = 0;
    if (strcmp(nombre,"maquina") != 0 ){ //Si el ganador fue la máquina del modo vs máquina no se toma en cuenta para el leaderboard
	    fp = fopen(archivo, "r+");//abrimos el archivo en modo lectura y eacritura
	    if (fp != NULL) {
	        while (fgets(linea, sizeof(linea), fp)) {
	            char linea_nombre[100];
	            int frecuencia;
	            sscanf(linea, "%s %d", linea_nombre, &frecuencia);// Leer el nombre y la frecuencia de la línea
	            if (strcmp(nombre, linea_nombre) == 0) {  // Si el nombre ya existe en el archivo, aumentar su frecuencia
	                fseek(fp, -(strlen(linea)+1), SEEK_CUR);// Retroceder al inicio de la línea
	                fprintf(fp, "%s %d\n", nombre, frecuencia+1);// Escribir el nombre y la nueva frecuencia
	                encontrado = 1;// Indicar que el nombre fue encontrado
	                break;
	            }
	        }
	        if (!encontrado) {  // Si el nombre no existe en el archivo, agregarlo con frecuencia 1
	            fprintf(fp, "%s %d\n", nombre, 1);
	        }
	        fclose(fp);//cerramos el archivo
	    } else {
	        printf("Error: no se pudo abrir el archivo.\n");//Imprimir si el archivo no se puede abrir
	    }
	}
}

//Funcion para imprimir el leaderboard
void imprimirLeaderboard (){
	int opcion;
	FILE *fp;
    char linea[100];
    char nombres[5][100];
    char* archivo;
    int frecuencias[5] = {0},i, j;
    
    system("cls");
	color(NEGRO,CYAN); printf("--------------------------------\n");
	printf("          LEADERBOARDS          \n");
	printf("--------------------------------\n"); 
	printf("---------Seleccionar Modo-------\n");
	printf("--------------------------------\n"); color(NEGRO,BLANCO);
	printf("1. Modo vs otro jugador\n");
	printf("2. Modo vs máquina\n");
	printf("3. Volver\n");
	printf("\nIngrese su elección (1-3): ");
	do{
		scanf("%i", &opcion);
		if (opcion<1 || opcion>3){
			printf("Elección invalida. Intente de nuevo: ");
		}
	}while (opcion<1 || opcion>3); //Ciclo para validar la entrada
	system("cls");
	switch(opcion){
		case 1:
			archivo = "leaderboard_1vs1.txt";
			color(NEGRO, MAGENTA);printf("\n      Leaderboard modo vs otro jugador          \n");color(NEGRO, BLANCO);
			break;
		case 2:
			archivo = "leaderboard_vs_maquina.txt";
			color(NEGRO, MAGENTA);printf("\n       Leaderboard modo vs maquina           \n\n");color(NEGRO, BLANCO);
			break;
		case 3:
			return;
	}
    
    fp = fopen(archivo, "r");
    if (fp != NULL) {
    	//ciclo while para leer cada línea del archivo utilizando la función fgets
        while (fgets(linea, sizeof(linea), fp)) {
            char linea_nombre[100];
            int frecuencia;
            sscanf(linea, "%s %d", linea_nombre, &frecuencia);//Almacenar el nombre y la frecuencia en variables temporales
            for (i = 0; i < 5; i++) {  // Buscar los 5 nombres más frecuentes
                if (frecuencia > frecuencias[i]) { //Comparar la frecuencia de la línea actual con las frecuencias almacenadas en el array frecuencias
                   //Si la frecuencia actual es mayor que alguna de las frecuencias almacenadas en frecuencias, mueve los nombres y frecuencias hacia abajo en el array
				    for (j = 4; j > i; j--) { 
                        strcpy(nombres[j], nombres[j-1]);
                        frecuencias[j] = frecuencias[j-1];
                    }
                    strcpy(nombres[i], linea_nombre);  
                    frecuencias[i] = frecuencia; //Insertar el nuevo nombre y su frecuencia en la posición correcta.
                    break;
                }
            }
        }
        fclose(fp);//cerrar el archivo
	}
    printf( "Nickname (Número de Victorias) \n");
    for (i = 0; i < 5; i++) {
        if (frecuencias[i] > 0) {
            printf("%i.- %s (%d)\n",i+1, nombres[i], frecuencias[i]);
        }
    }
    
	printf("\nPresione la tecla \"q\" para regresar al menú del juego...\n");
	while (getchar() != 'q') {
		// Espera hasta que se presione la tecla 'q' para volver al menú del juego
	}
	getchar();
	system("cls");		
}

//Funcion para imprimir instrucciones
void imprimir_instrucciones() {
	system("cls");
   color(NEGRO,ROJO); printf("Bienvenido al juego Conecta 4!\n\n"); color(NEGRO,BLANCO);
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

/*----------------------------------------------------------	
-----------Funciones generales del programa completo--------
------------------------------------------------------------*/
//Función para el color del texto:
void color(int Background, int Text){ 
 HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
 int    New_Color= Text + (Background * 16);
 SetConsoleTextAttribute(Console, New_Color); 
}

