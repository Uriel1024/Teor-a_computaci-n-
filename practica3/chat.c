#include <stdio.h>
#include <string.h>

#define ESTADOS 5

// Estados finales: q2, q3, q4
int finales[ESTADOS] = {
    0, 0, 1, 1, 1
};

// Transiciones del AFN
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

// Variable global para saber si al menos un camino llegó a un estado final
int cadena_aceptada = 0;

// Función recursiva para trazar y mostrar cada camino
void evaluar_caminos(char cadena[], int indice, int estado_actual, int camino[]) {
    // Guardamos el estado actual en el historial del camino
    camino[indice] = estado_actual;

    // Caso base: llegamos al final de la cadena de texto
    if (cadena[indice] == '\0') {
        // Imprimimos la ruta completa
        for (int i = 0; i <= indice; i++) {
            printf("q%d", camino[i]);
            if (i < indice) printf(" -> ");
        }
        
        // Verificamos si este camino en particular es de aceptación
        if (finales[estado_actual] == 1) {
            printf(" [ACEPTADO]\n");
            cadena_aceptada = 1; // Marcamos que la cadena es válida
        } 
        return; // Terminamos esta rama de la recursividad
    }

    // Paso recursivo: buscar hacia dónde podemos ir con el símbolo actual
    int simbolo = get_simbolo(cadena[indice]);
    int camino_sin_salida = 1;

    for (int k = 0; k < ESTADOS; k++) {
        if (transiciones[estado_actual][simbolo][k] == 1) {
            camino_sin_salida = 0;
            // Llamada recursiva avanzando al siguiente caracter y estado
            evaluar_caminos(cadena, indice + 1, k, camino);
        }
    }

    // Opcional: Si el AFN "muere" antes de terminar de leer la cadena (conjunto vacío)
    if (camino_sin_salida == 1) {
        for (int i = 0; i <= indice; i++) {
            printf("q%d", camino[i]);
            if (i < indice) printf(" -> ");
        }
        printf(" -> VACIO [MUERTO ANTES DE TERMINAR]\n");
    }
}

int main(){
    char cadena[100];
    printf("Ingresa la cadena a evaluar: ");
    scanf("%99s", cadena);
    
    // Validación inicial
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] != 'a' && cadena[i] != 'b') {
            printf("La cadena no es valida.\n"); 
            return -1;
        }
    }

    // Arreglo para guardar el historial de la ruta (máximo 100 caracteres + 1 estado inicial)
    int camino[105]; 
    cadena_aceptada = 0; // Reiniciamos la variable global

    printf("\nCaminos evaluados:\n");
    // Iniciamos la recursividad desde el índice 0 de la cadena y el estado q0
    evaluar_caminos(cadena, 0, 0, camino);

    // Veredicto final general
    if (cadena_aceptada == 1) {
        printf("\nVEREDICTO: Cadena ACEPTADA por el AFN (al menos un camino llegó a un estado final).\n");
    } else {
        printf("\nVEREDICTO: Cadena RECHAZADA por el AFN (ningún camino llegó a un estado final).\n");
    }

    return 0;
}