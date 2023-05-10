
/*  
Nombre del programa: Escapa del laberinto
Autora: Maricarmen Buenfil Perez
Equipo Diclonyx
Version 1.1
Fecha 05/05/23
Compilador: Dev-C++ 5.11
*/

//Declaración de librerias
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>  
#include <stdlib.h>


bool evaluador_de_partida = 1; //Evaluador del ciclo de partida del laberinto
int num_jugadores; //Total de jugadores
clock_t inicio_tiempo, fin_tiempo; //Variables de temporizador
FILE *archivo;

//Daatos de los jugadores
struct DatosJugadores{
	
	char nombre[10];
	int error;
	double tiempo_total;
	char modo[7];
	
}jugador[50];

//Declaración de funciones
void evaluarPartida( int fila, int columna, char laberinto[fila][columna]);

void Color(int Background, int Text);
       
enum Colors { 
	 BLACK = 0,
	 BLUE = 1,
	 GREEN = 2,
	 CYAN = 3,
	 RED = 4,
	 MAGENTA = 5,
	 BROWN = 6,
	 LGREY = 7,
	 DGREY = 8,
	 LBLUE = 9,
	 LGREEN = 10,
	 LCYAN = 11,
	 LRED = 12,
	 LMAGENTA = 13,
	 YELLOW = 14,
	 WHITE = 15
};

int imprimirMenuLaberinto(  ){
	Color(BLACK, LCYAN);
	//Impresión del menú del juego
	printf("\n------------------------------------------------------------------------------------------------------------------\n");
	printf("  _____                                       _        _   _         _                  _         _          \n");
  	printf(" |  ___|                                     | |      | | | |       | |                (_)       | |         \n");
  	printf(" | |__   ___   ___   __ _  _ __    __ _    __| |  ___ | | | |  __ _ | |__    ___  _ __  _  _ __  | |_   ___  \n");
  	printf(" |  __| / __| / __| / _` || '_ \\  / _` |  / _` | / _ \\| | | | / _` || '_ \\  / _ \\| '__|| || '_ \\ | __| / _ \\ \n");
  	printf(" | |___ \\__ \\| (__ | (_| || |_) || (_| | | (_| ||  __/| | | || (_| || |_) ||  __/| |   | || | | || |_ | (_) |\n");
  	printf(" \\____/ |___/ \\___| \\__,_|| .__/  \\__,_|  \\__,_| \\___||_| |_| \\__,_||_.__/  \\___||_|   |_||_| |_| \\__| \\___/ \n");
  	printf("                         | |                                                                                \n");
	printf("                         |_|                                                                                \n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("--------------------------------------------------Equipo Diclonyx-------------------------------------------------\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	Color(BLACK, WHITE);
	printf("\n");
		Color(BLACK,WHITE); printf("\n             _________________                      ");printf("            ");	Color(BLACK,WHITE); printf("         _________________                      \n");
		Color(BLACK,WHITE); printf("            /                 \\                      ");printf("            "); Color(BLACK,WHITE); printf("       /                 \\                      \n"); 
		Color(BLACK,WHITE); printf("           |  1:Instrucciones  |                        ");printf("            "); Color(BLACK,WHITE); printf("   |     2. Jugar      |                        \n"); 
		Color(BLACK,WHITE); printf("            \\_________________/                         ");printf("            "); Color(BLACK,WHITE); printf("    \\_________________/                        \n "); 
	printf("\n");
		Color(BLACK,WHITE); printf("\n             _________________                      ");printf("            ");	Color(BLACK,WHITE); printf("         _________________                      \n");
		Color(BLACK,WHITE); printf("            /                 \\                      ");printf("            "); Color(BLACK,WHITE); printf("       /                 \\                      \n"); 
		Color(BLACK,WHITE); printf("           |     3: Tablero    |                        ");printf("            "); Color(BLACK,WHITE); printf("   | 4: Menú principal |                        \n"); 
		Color(BLACK,WHITE); printf("            \\_________________/                         ");printf("            "); Color(BLACK,WHITE); printf("    \\_________________/                        \n "); 
		
	//Selección de opción
	int num_menu;
	Color(BLACK, BLUE);printf("\n\n                                         Seleccione una opción:");Color(BLACK, WHITE);scanf("%d", &num_menu);
	
	
	return num_menu; //Retorna la opción
	
}

void imprimirLaberinto(int fila, int columna, char laberinto[fila][columna]){
	//Impresión del laberinto actualizado
	
	system("cls");
	printf("\n");
	
    int i, k;
    for (i = 0; i < fila; i++) {
        for (k = 0; k < columna; k++) {
        	if(laberinto[i][k] == 'o'){
        	Color(BLACK, RED);printf("%c", laberinto[i][k]);Color(BLACK, WHITE);
        		
			}else{
				printf("%c", laberinto[i][k]);
			}
            
        }
        printf("\n");
    }
    
}

void verificarPosicionLaberinto(int *x, int *y , int fila, int columna, char laberinto[fila][columna], char limpiador[fila][columna]){
	
	int k, j;
	
	if (*x == fila - 2 && *y == columna - 2) { //El jugador ha llegado a la meta
		
		system("cls");
	
	    fin_tiempo = clock(); // registrar el tiempo de finalización
	    jugador[num_jugadores].tiempo_total = (double)(fin_tiempo - inicio_tiempo) / CLOCKS_PER_SEC; // calcular el tiempo que tardó el jugador en ganar
	    Color(BLACK, LGREEN);printf(" \n  ¡F E L I C I D A D E S !  \n  ¡H A Z   G A N A D O! :) \n");Color(BLACK, WHITE);
	    evaluador_de_partida = 0;
	  
   	}else if(laberinto[*x][*y] == '.' || laberinto[*x][*y] == 'o'  ){ //Recorrido del jugador en el laberinto
		
		laberinto[*x][*y] = 'o';
		
		imprimirLaberinto(fila, columna, laberinto);	//Invocar impresión de laberinto
		printf("\n");
		printf("Introduzca la direccion ( w / s / a / d ) \n");
		
	}else if(laberinto[*x][*y]== '#'){ //El jugador ha chocado contra una pared
		
		(jugador[num_jugadores].error)++; //Contador de errores
		
		
		//Restauracion del laberinto al original
		for(k=0; k < fila; k++){
			for(j=0; j < columna; j++){
			
				if(limpiador[k][j] == 'o'){
					laberinto[k][j] = '.';	
				}
				
				limpiador[k][j] = ' ' ;
			
			}
			
		}
		
		laberinto[*x][*y] = '#';
		
		//Retoma posición inicial
		*x=1;
		*y=1;
		
		imprimirLaberinto(fila, columna, laberinto);	//Invocar impresión de laberinto
		Color(BLACK, RED);printf("\n ------- UPPS. Hubo un choque... Inicia de nuevo --------- \n\n");
		Color(BLACK, LMAGENTA);printf("Tu posición es [1][1] \n");Color(BLACK, WHITE);
		printf("\n");
		printf("Introduzca la direccion ( w / s / a / d ) \n");
		
	}
	
}

int main() {
    setlocale(LC_ALL, "");
    
    int menu, k;
    num_jugadores=0;
	
	//Limpiador de tiempos
	for(k=0;k<50;k++){
        jugador[k].tiempo_total = 0;
    }
    
    
    do{
	evaluador_de_partida=1;
    menu = imprimirMenuLaberinto(); //Invocar menu del juego
    
    switch(menu){
    	
    	case 1:  //Introducción
    	system("cls");
    	
    	Color(BLACK, LMAGENTA);printf("\n Escapa del laberinto \n");Color(BLACK, WHITE);
    	
    	printf("\nEl juego de escapar del laberinto es un juego en el que el jugador debe encontrar la salida de un\nlaberinto lo más rápido posible. El laberinto consta de pasillos que llevan a diferentes áreas del\nlaberinto, pero solo uno de ellos conduce a la salida.\n" );
    	printf("\nEl jugador comienza en una posición determinada en el laberinto y debe avanzar por los pasillos,\nhasta encontrar la salida. \n  ");
    	printf("\nEl juego tiene tres modalidades fácil, medio y difícil lo cual depende del tamaño del laberinto. Al \nconcluir el juego se presentará los errores que tuviste, es decir las veces que chocaste con una\npared, y el tiempo en que resolviste el laberinto, lo que agrega un factor de emoción al juego.");
	
		break;
    	
    	case 2: //Inicio del juego del laberinto
    	system("cls");
    	num_jugadores++; //Contador de jugadores aumenta

		//Impresión de menú de modalidades
    	printf("\n Ingrese el nombre del jugador: \n");
    	scanf("%s", jugador[num_jugadores].nombre);
	    printf("\nSelecciona la modalidad del juego:\n");
	    printf("1. Fácil\n");
	    printf("2. Medio\n");
	    printf("3. Difícil\n");
	    
	    int opcion;
	    int fila=0, columna=0;
	    
	    scanf("%d", &opcion);
		system("cls");
		
		//Evalua opcion de la modalidad del laberinto
		Color(BLACK, LMAGENTA); printf("\n L A B E R I N T O \n"); Color(BLACK, WHITE);
	    switch (opcion) {
	        case 1: 
	        
	            fila=10;
	            columna=10;
	            char laberinto_facil[10][10] = {
	                "##########",
	                "#..#.....#",
	                "##.#.#.###",
	                "##.#.#...#",
	                "##.#.#.###",
	                "##...#.###",
	                "######.###",
	                "###....###",
	                "###.##...#",
	                "##########",
	            };
	        	strcpy(jugador[num_jugadores].modo, "Fácil"); //Indica modalidad del laberinto
	            imprimirLaberinto(fila, columna, laberinto_facil);	//Imprime el laberinto de la modalidad seleccionada
	            evaluarPartida(fila, columna, laberinto_facil); //Evalua el juego del laberinto
	            break;
	        
	        case 2:
	        	
	        	fila=20;
	            columna=20;
	            char laberinto_medio[20][20] = {
	                "####################",
					"#..................#",
					"#.#####.#####.#.####",
					"#.#...#...#...#.#..#",
					"#.#.#.#.###.#.#.#.##",
				    "#...#.#...#.#.....##",
				    "###.#.###.#.#.#.#.##",
				    "#.....#...#.#.#.#..#",
				    "#.#####.#.#.#.#.#.##",
					"#.......#.#...#.#..#",
				    "#####.#.#.#.#.#.#.##",
				    "#...#.#...#...##..##",
				    "#.#.#.#.#.#####.#.##",
					"#.#.#...#.......####",
				    "#.#.#.#.#.###.#.#.##",
				    "#.....#..##...#....#",
				    "#.#######.#.#.######",
				    "#..........##......#",
				    "#####.############.#",
				    "####################",
	            };
	            strcpy(jugador[num_jugadores].modo, "Medio");
	            imprimirLaberinto(fila, columna, laberinto_medio);	
	            evaluarPartida(fila, columna, laberinto_medio);
	            break;
	            
	        case 3:
	        	
	        	fila=30;
	            columna=30;
	            char laberinto_dificil[30][30] = {
	                    "##############################",
					    "#...........................##",
					    "#.#####.#.#####.#.#.#.#.#.####",
					    "#...#...#...#...#.#.#.#.#...##",
					    "#.#.#.###.#.#.###.#.#.#.###.##",
					    "#.#.#.#...#.#.#...#.#.#.....##",
					    "#.#.###.#.#.#.#.#.#.#.#.###.##",
					    "#.#...#.#.#.#.#.#.#.#.#.#...##",
					    "#.###.#.###.#.#.#.#.#.#.#.#.##",
					    "#.....#.#...#.#.#.#.#.#.#.#.##",
					    "#######.#.#.#.#.#.#.#.#.#.#.##",
					    "#.......#.#.#.#.#.#.#.#.#.#.##",
					    "#.#######.#.#.#.#.#.#.#.#.#.##",
					    "#.#.......#.#.#.#.#.#.#.#.#.##",
					    "#.#.#######.#.#.#.#.#.#.#.#.##",
					    "#.#.#.......#.#.#.#.#.#.#.#.##",
					    "#.#.#.#######.#.#.#.#.#.#.#.##",
					    "#.#.#.#.......#.#.#.#.#.#.#.##",
					    "#.#.#.#.#######.#.#.#.#.#.#.##",
					    "#.#.#.#.#.......#.#.#.#.#.#.##",
					    "#.#.#.#.#.#######.#.#.#.#.#.##",
					    "#.#.#.#.#.#.......#.#.#.#.#.##",
					    "#.#.#.#.#.#.#######.#.#.#.#.##",
					    "#.#.#.#.#.#.#.......#.#.#.#.##",
					    "#.#.#.#.#.#.#.#######.#.#.#.##",
					    "#.#.#.#.#.#.#.#.......#.#.#.##",
					    "#.#.#.#.#.#.#.#.###.###.#.#.##",
					    "#.#.#.#.#.#.#.#.#.......#.#.##",
					    "#.#.#.#.#.#.#.#.#.##.##.#.#..#",
					    "##############################",
	            };
	            strcpy(jugador[num_jugadores].modo, "Dificil");
	            imprimirLaberinto(fila, columna, laberinto_dificil);	
	            evaluarPartida(fila, columna, laberinto_dificil);
	            
	            break;
	             
	        default:
	            printf("Opción inválida\n");
	            break;
	    }
    	
    	break;
    		
    	case 3: //Tablero de puntuaciones
    	system("cls");
    	k=0;
    	
    	archivo = fopen("Tablero.txt", "a");
    
	    if (archivo == NULL) {
	        printf("No se pudo crear el archivo.\n");
	        return 1;
	    }
    	
    
    	Color(BLACK, LMAGENTA);printf("\n                           Leaderboard                  \n ");Color(BLACK, WHITE);
    	printf( "Nickname       Errores       Tiempo final     Modalidad \n");
    	
    	while(k < num_jugadores ){
    		
    		fprintf( archivo, "%s                   %d         %.3f         %s \n", jugador[k+1].nombre,jugador[k+1].error, jugador[k+1].tiempo_total, jugador[k+1].modo );
    		
			k++;//Impresión de todos los datos del jugador
		}
		
		fclose(archivo);
		
		archivo = fopen("Tablero.txt", "r");
		
		
		if (archivo == NULL) {
	      printf("No se puede abrir el archivo.\n");
	      return 1;
	  	}
	   
		while (fscanf(archivo, "%s %d %lf %s", jugador[k+1].nombre, &jugador[k+1].error, &jugador[k+1].tiempo_total, jugador[k+1].modo) == 4) {
		   printf("%s                   %d         %.3f         %s \n", jugador[k+1].nombre, jugador[k+1].error, jugador[k+1].tiempo_total, jugador[k+1].modo);
		   k++;
		}
      
		 fclose(archivo);	
			
			
    	break;
    	
    	case 4: //Retorno al menu principal
    		
        break;
    	
    	default: 
        printf("\nOpcion invalida\n");
        break;
	}
		//Retorno al menu de juego
		Color(BLACK,BROWN);printf("\n\n Presione cualquier letra para volver ... \n ");Color(BLACK, WHITE);
        getchar();
        getchar(); 
        printf("\n");
        system("cls");
        
    } while (menu != 4);
    	
    return 0;
}

void evaluarPartida( int fila, int columna, char laberinto[fila][columna]){ //Evalua el recorrido del jugador en el laberinto
	
	//Posicion inicial
	int fila_actual=1;
	int columna_actual=1;
	char limpiador[fila][columna]; //Limpiador en caso de que choque contra una pared
	
	printf("\n");
	printf("Introduzca la dirección ( w / s / a / d ) \n");
	Color(BLACK, LMAGENTA);printf("Tu posición es [1][1] \n");	Color(BLACK, WHITE);

	inicio_tiempo = clock(); // registrar el tiempo de inicio
	
	while(evaluador_de_partida){
		
		char movimiento;
		
		movimiento=getch(); //Leer dirrección 
		
		switch(movimiento){  //Evaluacion de dirrección 
			
			case 'w':
				
				if( fila_actual > 0 ){
					
					fila_actual--;
					limpiador[fila_actual][columna_actual] = 'o'; //Guardar posiciones en el limpiador
					
					verificarPosicionLaberinto(&fila_actual, &columna_actual , fila, columna, laberinto, limpiador); //Invocar función de posiciones 
				}
					
			break;
			
			case 's':
				
				if( fila_actual > 0 ){
					
					fila_actual++;
					limpiador[fila_actual][columna_actual] = 'o';
					verificarPosicionLaberinto(&fila_actual, &columna_actual , fila, columna, laberinto, limpiador);
				}
					
			break;
			
			case 'a':
				
				if( fila_actual > 0 ){
					
					columna_actual--;
					limpiador[fila_actual][columna_actual] = 'o';
					verificarPosicionLaberinto(&fila_actual, &columna_actual , fila, columna, laberinto, limpiador);
				}
					
			break;
			
			case 'd':
				
				if( fila_actual > 0 ){
					
					columna_actual++;
					limpiador[fila_actual][columna_actual] = 'o';
					verificarPosicionLaberinto(&fila_actual, &columna_actual , fila, columna, laberinto, limpiador);
				}
					
			break;
			
		}	
		
	}
					
}

//Función de colores 

void Color(int Background, int Text){ 
 HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
 int    New_Color= Text + (Background * 16);
 SetConsoleTextAttribute(Console, New_Color); 
}

