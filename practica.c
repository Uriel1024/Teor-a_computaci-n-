#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    char *c1;
    char *c2;
}Cadenas; 


int menu(){
    int op;
    printf("\n\n\n1. Cambiar cadena. \n");
    printf("2. Obtener prefijo y sufijo. \n");
    printf("3. Obtener la subcadena. \n ");
    printf("4. Obtener la subsecuencia \n");
    printf("5. Potencia de una cadena \n");
    printf("-1. Para salir  ");
    printf("\n Ingresa una opcion para poder continuar: ");
    scanf("%d", &op);

    return op;  
}

Cadenas* cambiarCadena(){
    Cadenas *res = (Cadenas *)malloc(20* sizeof(Cadenas));

    res->c1 = (char *)malloc(sizeof(char));
    res->c2 = (char *)malloc(sizeof(char));

    printf("\nIngresa la cadena S: ");
    scanf("%s", res->c1);

    printf("\nIngresa la cadena P: "); 
    scanf("%s", res->c2);

    return res;
}

void prefijo_sufijo(char cadena[]){
    int tam = strlen(cadena);
    int pr = tam + 1;

    while(pr > tam){
    printf("\n\nIngresa el tamaño de elementos a recortar para la cadena (no mayor a %d):", tam );
    scanf("%d", &pr);
    }

    printf("El prefico de la cadena %s de %d elementos es:\n\n", cadena,tam);
    for(int i=0; i <= pr ; i++){
        printf("%c",cadena[i]);
    }

    printf("\n\nEl sufijo de la cadena %s de elementos %d es:\n\n",cadena,tam );
    for(int i = pr ; i <= tam ; i++){
        printf("%c",cadena[i]);
    }
}


void subcadena(Cadenas *cadena){
    return;
}


void potencia(char cadena[]){
    return;
}

void invertirCadena(char cadena[]) {
    return;
}



int main() {
 
    Cadenas *cadena = cambiarCadena();
    printf("\n La cadena S es %s", cadena->c1);
    printf("\n La cadena P es %s \n\n\n", cadena->c2);


    int op = menu();
    while (op != -1){

        switch (op){
            case 1:
                free(cadena->c1);
                free(cadena->c2);
                free(cadena);
                cadena = cambiarCadena();
                printf("\n La cadena S es %s", cadena->c1);
                printf("\n La cadena P es %s \n\n\n", cadena->c2);
            break;

            case 2:
                prefijo_sufijo(cadena->c1);
                prefijo_sufijo(cadena->c2);                
            break;
            case 3:
            break;

            case 4:
            break;

            case 5:
            break;
            
            default:
                printf("Ingesa una opcion valida. ");
            break;
        }
        op = menu();    
    }
    free(cadena->c1);
    free(cadena->c2);
    free(cadena);

    return 0;
}
