/*  

Autora: Maricarmen Buenfil Perez
Version 1
Fecha 02/05/23
Compilador Dev-C++ 5.11
*/

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>  

bool E = 1; 
int num_jugadores;
clock_t inicio, fin;

struct datos{
	
	char nombre[10];
	int error;
	double tiempo_total;
	char modo[7];
	
}jugador[50];

//Funcion de evaluador de entrada de direccion del laberinto
void evaluador( int f, int c, char laberinto[f][c]);

//Funcion con fines de diseño en pantalla
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

//Funcion del menu del juego 
int menu_laberinto(  ){
	Color(BLACK, LMAGENTA);
	printf("\n--------------------------------\n");
	printf("          Bienvenido a          \n");
	printf("      Escapa del laberinto           \n");
	printf("--------------------------------\n");
	printf("---------Equipo Diclonyx--------\n");
	printf("--------------------------------\n");
	Color(BLACK, WHITE);
	printf("1. Instrucciones \n");
	printf("2. Jugar \n");
	printf("3. Tablero \n");
	printf("4. Volver al menú principal \n");
	
	int num_menu;
	printf("Seleccione una opción: \n");
	scanf("%d", &num_menu);
	
	return num_menu;
	
	
}

//Funcion de impresion del laberinto en cada vez que avanza en jugador
void impresion_laberinto(int f, int c, char laberinto[f][c]){
    int i, k;
    for (i = 0; i < f; i++) {
        for (k = 0; k < c; k++) {
        	if(laberinto[i][k] == 'o'){
        	Color(BLACK, RED);printf("%c", laberinto[i][k]);Color(BLACK, WHITE);
        		
			}else{
				printf("%c", laberinto[i][k]);
			}
            
        }
        printf("\n");
    }
}

//Funcion para determinar la posiciond del jugador dentro de la matriz

void posicion_laberinto(int *x, int *y , int f, int c, char laberinto[f][c], char limpiador[f][c]){
	
	int k, j;
	
			
	if (*x == f - 2 && *y == c - 2) {
		
	system("cls");
	
    fin = clock(); // registrar el tiempo de finalización
    jugador[num_jugadores].tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC; // calcular el tiempo que tardó el jugador en ganar
    Color(BLACK, LGREEN);printf(" \n  ¡F E L I C I D A D E S !  \n  ¡H A Z   G A N A D O! :) \n");Color(BLACK, WHITE);
    E = 0;
	  
   	}else if(laberinto[*x][*y] == '.' || laberinto[*x][*y] == 'o'  ){
		
		laberinto[*x][*y] = 'o';
		
		impresion_laberinto(f, c, laberinto);	
		printf("Introduzca la direccion ( w / s / a / d ) \n");
		
	}else if(laberinto[*x][*y]== '#'){
		
		(jugador[num_jugadores].error)++;
		Color(BLACK, RED);printf("\n ------- UPPS. Hubo un choque... Inicia de nuevo --------- \n\n");
		Color(BLACK, LMAGENTA);printf("Tu posición es [1][1] \n");Color(BLACK, WHITE);
		
		
		for(k=0; k < f; k++){
			for(j=0; j < c; j++){
			
				if(limpiador[k][j] == 'o'){
					laberinto[k][j] = '.';	
				}
				
				limpiador[k][j] = ' ' ;
			
		}
			
		}
		
		laberinto[*x][*y] = '#';
		
		*x=1;
		*y=1;
		
		impresion_laberinto(f, c, laberinto);	
		printf("Introduzca la direccion ( w / s / a / d ) \n");
		
	}
	
}

int main() {
    setlocale(LC_ALL, "");
    
    int menu, k;
    num_jugadores=0;
	
	for(k=0;k<50;k++){
        jugador[k].tiempo_total = 0;
    }
    
    
    do{
	E=1;
    menu = menu_laberinto( );
    
    //Seleccion de opciones del menu del juego
    switch(menu){
    	
    	case 1: 
    	system("cls");
    	//Introduccion
    	Color(BLACK, LMAGENTA);printf("\n Escapa del laberinto \n");Color(BLACK, WHITE);
    	
    	printf("\nEl juego de escapar del laberinto es un juego en el que el jugador debe encontrar la salida de un\nlaberinto lo más rápido posible. El laberinto consta de pasillos que llevan a diferentes áreas del\nlaberinto, pero solo uno de ellos conduce a la salida.\n" );
    	printf("\nEl jugador comienza en una posición determinada en el laberinto y debe avanzar por los pasillos,\nhasta encontrar la salida. \n  ");
    	printf("\nEl juego tiene tres modalidades fácil, medio y difícil lo cual depende del tamaño del laberinto. Al \nconcluir el juego se presentará los errores que tuviste, es decir las veces que chocaste con una\npared, y el tiempo en que resolviste el laberinto, lo que agrega un factor de emoción al juego.");
	
		break;
    	
    	case 2: 
    	system("cls");
    	num_jugadores++;
		//Menu cuando el jugador le da a jugar
    	printf("\n Ingrese el nombre del jugador: \n");
    	scanf("%s", jugador[num_jugadores].nombre);
	    printf("\nSelecciona la modalidad del juego:\n");
	    printf("1. Fácil\n");
	    printf("2. Medio\n");
	    printf("3. Difícil\n");
	    
	    int opcion;
	    int f=0, c=0;
	    
	    scanf("%d", &opcion);
		system("cls");
		
		
		//impresion de laberintos por dificultad
		Color(BLACK, LMAGENTA); printf("\n L A B E R I N T O \n"); Color(BLACK, WHITE);
	    switch (opcion) {
	        case 1: 
	        
	            f=10;
	            c=10;
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
	        	strcpy(jugador[num_jugadores].modo, "Fácil");
	            impresion_laberinto(f, c, laberinto_facil);	
	            evaluador(f, c, laberinto_facil);
	            break;
	        
	        case 2:
	        	
	        	f=20;
	            c=20;
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
	            impresion_laberinto(f, c, laberinto_medio);	
	            evaluador(f, c, laberinto_medio);
	            break;
	            
	        case 3:
	        	
	        	f=30;
	            c=30;
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
	            impresion_laberinto(f, c, laberinto_dificil);	
	            evaluador(f, c, laberinto_dificil);
	            
	            break;
	             
	        default:
	            printf("Opción inválida\n");
	            break;
	    }
    	
    	break;
    	
    	//Tablero de puntuacion
    	case 3:
    	system("cls");
    	k=0;
    	
    	Color(BLACK, LMAGENTA);printf("\n             Leaderboard                  \n ");Color(BLACK, WHITE);
    	printf( "Nickname       Errores       Tiempo final     Modalidad \n");
    	
    	while(k < num_jugadores ){
    		
    		printf( "%s                   %d         %.3f         %s \n", jugador[k+1].nombre,jugador[k+1].error, jugador[num_jugadores].tiempo_total, jugador[k+1].modo );
    		k++;
		}
    	
    	break;
    	
    	//Regresa al menu principal de los 4 juegos
    	case 4:
        printf("\n Menú principal \n");
        break;
    	
    	default:
        printf("\nOpcion invalida\n");
        break;
	}
	//Retorno al menu del juego
		Color(BLACK,BROWN);printf("\n\n Presione cualquier letra para volver al menú del juego... \n ");Color(BLACK, WHITE);
        getchar();
        getchar(); 
        printf("\n");
        system("cls");
        
    } while (menu != 4);
    	
    return 0;
}

//Evaluador de posiciones por la dirreccion del jugador
void evaluador( int f, int c, char laberinto[f][c]){
	
	int filaActual=1;
	int columnaActual=1;
	char limpiador[f][c];
	
	printf("Introduzca la dirección ( w / s / a / d ) \n");
	Color(BLACK, LMAGENTA);printf("Tu posición es [1][1] \n");	Color(BLACK, WHITE);
	
	inicio = clock(); // registrar el tiempo de inicio
	
	while(E){
		
		char movimiento;
		
		movimiento=getch();
		
		switch(movimiento){
			
			case 'w':
				
				if( filaActual > 0 ){
					
					filaActual--;
					limpiador[filaActual][columnaActual] = 'o';
					
					posicion_laberinto(&filaActual, &columnaActual , f, c, laberinto, limpiador);
				}
					
			break;
			
			case 's':
				
				if( filaActual > 0 ){
					
					filaActual++;
					limpiador[filaActual][columnaActual] = 'o';
					posicion_laberinto(&filaActual, &columnaActual , f, c, laberinto, limpiador);
				}
					
			break;
			
			case 'a':
				
				if( filaActual > 0 ){
					
					columnaActual--;
					limpiador[filaActual][columnaActual] = 'o';
					posicion_laberinto(&filaActual, &columnaActual , f, c, laberinto, limpiador);
				}
					
			break;
			
			case 'd':
				
				if( filaActual > 0 ){
					
					columnaActual++;
					limpiador[filaActual][columnaActual] = 'o';
					posicion_laberinto(&filaActual, &columnaActual , f, c, laberinto, limpiador);
				}
					
			break;
			
		}	
		
	}
					
}

void Color(int Background, int Text){ 
 HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
 int    New_Color= Text + (Background * 16);
 SetConsoleTextAttribute(Console, New_Color); 
}

