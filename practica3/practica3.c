#include<stdio.h>

#define ESTADOS 5

// Estados finales: q2, q3, q4
int finales[ESTADOS] = {
    0, 0, 1, 1, 1
};

int camino[101];      
int aceptadas = 0;    
int total_ramas = 0;

// Transiciones del AFN
// transiciones[estado][simbolo][estado_destino]
int transiciones[ESTADOS][2][ESTADOS] = {
    // q0
    {
        {1, 0, 0, 1, 0},  // a -> q0, q3
        {1, 1,  0, 0, 0}  // b -> q0, q1
    },

    // q1
    {
        {0, 0, 0, 0, 0}, // a -> vacío
        {0, 0, 1,  0, 0}  // b -> q2
    },

    // q2
    {
        {0, 0, 1,  0, 0}, // a -> q2
        {0, 0, 1,  0, 0}  // b -> q2
    },

    // q3
    {
        {0, 0, 0, 0, 1},  // a -> q4
        {0, 0, 0, 0, 0}  // b -> vacío
    },

    // q4
    {
        {0, 0, 0, 0, 1},  // a -> q4
        {0, 0, 0, 0, 1}   // b -> q4
    }
};

int get_simbolo(char caracter){
    if(caracter == 'a') return 0;
    else return 1; 
}

void imprimir_rama(const char *cadena, int pos, const char *resultado){
    for(int i = 0; i <= pos; i++){
        printf("q%d", camino[i]);
        if(i < pos) printf(" -%c-> ", cadena[i]);
    }
    printf("  [%s]\n", resultado);
}

void explorar(const char *cadena, int pos, int estado){
    camino[pos] = estado;

    // Llegamos al final de la cadena
    if(cadena[pos] == '\0'){
        total_ramas++;
        if(finales[estado]){
            aceptadas++;
            imprimir_rama(cadena, pos, "ACEPTA");
        }
        return;
    }
    int simbolo = get_simbolo(cadena[pos]);

    for(int k = 0; k < ESTADOS; k++){
        if(transiciones[estado][simbolo][k]){
            explorar(cadena, pos + 1, k);   // una llamada por cada rama
        }
    }

}

int main(){
    char cadena[100];
    printf("Ingresa la cadena a evaluar: ");
    scanf("%99s",cadena);
    printf("\nRamas posibles:\n");
    explorar(cadena, 0, 0);   // empieza en q0
    printf("\nTotal de ramas: %d, aceptadas: %d\n", total_ramas, aceptadas);

    return 0;
}