#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define VERDE "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define RESET_COLOR "\x1b[0m"

void escogerDificultad(int *, int *);
void escogerPalabra(char[50][10], int, char[10]);
void imprimirEncabezado();
void imprimirReglas();
void imprimirIntentos(int*, char[12][10], char[10], int, int);
void limpiarMatriz(char[12][10]);

int main(){
	setlocale(LC_ALL, "spanish");
	int opcion_menu, largo_palabra, intentos, victoria, i;
	char posibles_palabras[50][10];
	char palabra_escogida[10];
	char intento_palabra[12][10];
	victoria=0;
	i=0;
	opcion_menu=0;
	
	while(opcion_menu!=2){
		printf("------------------------------------------------------------\n");
		printf("                  Bienvenido a wordle\n");
		printf("------------------------------------------------------------\n\n\n");
		printf("1. JUGAR\n");
		printf("2. SALIR\n");
		printf("\nSeleccione una opción ");
		scanf("%d",&opcion_menu);
		if(opcion_menu==1){
			int intentos_aux = 0;
			system("cls");
			imprimirEncabezado();
			imprimirReglas();
			printf("\nPresione enter para continuar\n");
			getchar();
			getchar();
			system("cls");
			escogerDificultad(&largo_palabra,&intentos);
			system("cls");
			escogerPalabra(posibles_palabras, largo_palabra, palabra_escogida);
			limpiarMatriz(intento_palabra);
			victoria=0;
			i=0;
			while(intentos_aux<intentos){
				imprimirEncabezado();
				if(intentos_aux > 0){
					imprimirIntentos(&victoria, intento_palabra, palabra_escogida, i, largo_palabra);
				}
				if(victoria==1){
					break;
				}
				printf("\nTe quedan %d intentos\n\n", intentos-intentos_aux);
				printf("Ingrese una palabra\n");
				scanf("%s", intento_palabra[i]);
				getchar();
				intentos_aux++;
				i++;
				system("cls");
			}
			system("cls");
			imprimirEncabezado();
			imprimirIntentos(&victoria, intento_palabra, palabra_escogida, i, largo_palabra);
			if(victoria==0){
				printf("\nPerdiste, la palabra era %s",palabra_escogida);
			}else{
				printf("\nGanaste, la palabra era %s",palabra_escogida);
			}
			getchar();
		}
		system("cls");
	}

	return 0;
}

void escogerDificultad(int *largo_palabra, int *intentos){
	do{
		system("cls");
		imprimirEncabezado();
		printf("Seleccione el largo de su palabra\n\n");
		printf("1. 5 letras\n");
		printf("2. 6 letras\n");
		printf("3. 7 letras\n\n");
		printf(":");
		scanf("%d",largo_palabra);
		system("cls");
		imprimirEncabezado();
		printf("\nSeleccione el número de intentos\n\n");
		printf("1. 6 intentos\n");
		printf("2. 9 intentos\n");
		printf("3. 12 intentos\n\n");
		printf(":");
		scanf("%d",intentos);
	}while((*largo_palabra>3||*largo_palabra<1)||(*intentos>3||*intentos<1));
	switch(*intentos){
		case 1:
			*intentos=6;
			break;
		case 2:
			*intentos=9;
			break;
		case 3:
			*intentos=12;
			break;
	}
}

void escogerPalabra(char posibles_palabras[50][10], int largo_palabra, char palabra_escogida[10]){
	int i, j;
	i=0;
	j=0;
	srand(time(NULL));
	FILE *lista_palabras;
	
	switch(largo_palabra){
		case 1:
			lista_palabras= fopen("palabras_cinco_letras.txt", "r");
			if(lista_palabras==NULL){
				printf("No se pudo abrir el archivo");
			}
			while(fgets(posibles_palabras[i], 10, lista_palabras)){
				i++;
			}
			j=rand()%50;
			strcpy(palabra_escogida, posibles_palabras[j]);
			break;
		case 2:
			lista_palabras= fopen("palabras_seis_letras.txt", "r");
			if(lista_palabras==NULL){
				printf("No se pudo abrir el archivo");
			}
			while(fgets(posibles_palabras[i], 10, lista_palabras)){
				i++;
			}
			j=rand()%50;
			strcpy(palabra_escogida, posibles_palabras[j]);
			break;
		case 3:
			lista_palabras= fopen("palabras_siete_letras.txt", "r");
			if(lista_palabras==NULL){
				printf("No se pudo abrir el archivo");
			}
			while(fgets(posibles_palabras[i], 10, lista_palabras)){
				i++;
			}
			j=rand()%50;
			strcpy(palabra_escogida, posibles_palabras[j]);
			break;
	}
	fclose(lista_palabras);
}

void imprimirEncabezado(){
	printf("------------------------------------------------------------\n");
	printf("                          WORDLE\n");
	printf("------------------------------------------------------------\n\n\n");
}
void imprimirReglas(){
	printf("El objetivo de este juego es adivinar la palabra secreta,\n");
	printf("para ello debera escoger primero el largo de la palabra\n");
	printf("secreta y la cantidad de intentos que desea para adivinar.\n\n");
	printf("El juego es muy sencillo, en cada intento ingresara una\n");
	printf("palabra y dependiendo de las letras pasará lo siguiente:\n\n");
	printf("1. Si una letra esta de color blanco significa que no aparece\n");
	printf("en la palabra secreta\n");
	printf("2. Si una letra esta de color amarillo significa que aparece\n");
	printf("en la palabra secreta pero no en esa posición\n");
	printf("3. Si una letra esta de color verde significa que aparece\n");
	printf("en la palabra secreta y en esa posición\n\n");
	printf("Si adivinas la palabra secreta ¡Ganas!\n");
}

void imprimirIntentos(int *victoria, char intento_palabra[12][10], char palabra_escogida[10], int i, int largo){
	int j, k, m, n, letras_iguales;
	if(largo==1)n=5;
	if(largo==2)n=6;
	if(largo==3)n=7;
	int encontrado;
	letras_iguales=0;
	
	for(j=0;j<i;j++){
		letras_iguales=0;
		for(k=0;k<n;k++){
			encontrado=0;
			if(intento_palabra[j][k]==palabra_escogida[k]){
				printf(VERDE "%c",intento_palabra[j][k]);
				printf(RESET_COLOR);
				letras_iguales++;
				continue;
			}
			for(m=0;m<n;m++){
				if(intento_palabra[j][k]==palabra_escogida[m]){
					printf(AMARILLO "%c",intento_palabra[j][k]);
					printf(RESET_COLOR);
					encontrado=1;
					break;
				}		
			}
			if(encontrado==0){
				printf("%c",intento_palabra[j][k]);
				printf(RESET_COLOR);
			}
		}
		printf("\n");
	}
	if(letras_iguales==n){
		*victoria=1;
	}
}

void limpiarMatriz(char intento_palabra[12][10]){
	int i, j;
	
	for(i=0;i<12;i++){
		for(j=0;j<10;j++){
			intento_palabra[i][j]=0;
		}
	}
}
