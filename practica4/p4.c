#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 256

/* 
El automata que recibe viene en el txt de esta forma:
Q = estados del automata (0, 1, 2, 3, 4)
Σ = alfabeto (a, b, c...)
E = entradas posibles
S = salidas posibles
δ = transiciones (estado actual, entrada, próximo estado)
*/

char estados[MAX][MAX];
char alfabeto[MAX][MAX];
char finales[MAX][MAX];
char transiciones[MAX][3][MAX];

char inicial[MAX];
char linea[MAX];

// Contadores globales
int numEstados = 0, numSimbolos = 0, numFinales = 0, numTransiciones = 0;

void leer_txt(){
    FILE *archivo = fopen("prueba.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir automata.txt\n");
        return;
    }

    int lineaActual = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';
        lineaActual++;

        if (lineaActual == 1) {
            char *token = strtok(linea, ",");
            while (token != NULL) {
                snprintf(estados[numEstados], MAX, "%s", token);
                numEstados++;
                token = strtok(NULL, ",");
            }
        }
        else if (lineaActual == 2) {
            char *token = strtok(linea, ",");
            while (token != NULL) {
                snprintf(alfabeto[numSimbolos], MAX, "%s", token);
                numSimbolos++;
                token = strtok(NULL, ",");
            }
        }
        else if (lineaActual == 3) {
            snprintf(inicial, MAX, "%s", linea);
        }
        else if (lineaActual == 4) {
            char *token = strtok(linea, ",");
            while (token != NULL) {
                snprintf(finales[numFinales], MAX, "%s", token);
                numFinales++;
                token = strtok(NULL, ",");
            }
        }
        else {
            char *token = strtok(linea, ",");
            int columna = 0;
            while (token != NULL && columna < 3) {
                snprintf(transiciones[numTransiciones][columna], MAX, "%s", token);
                columna++;
                token = strtok(NULL, ",");
            }
            if (columna == 3) {
                numTransiciones++;
            }
        }
    }
    fclose(archivo);
}

// Función auxiliar para obtener el índice de un estado a partir de su nombre
int obtener_indice_estado(char *nombre) {
    for (int i = 0; i < numEstados; i++) {
        if (strcmp(estados[i], nombre) == 0) {
            return i;
        }
    }
    return -1;
}

// Función para imprimir un subconjunto representado como un arreglo de 0s y 1s
void imprimir_subconjunto(int *subconjunto, int n) {
    // Verificar si el subconjunto está vacío
    int vacio = 1;
    for (int i = 0; i < n; i++) {
        if (subconjunto[i] == 1) {
            vacio = 0;
            break;
        }
    }

    if (vacio) {
        printf("%-15s", "0");
        return;
    }
    
    char buffer[256] = "{";
    int primero = 1;
    for (int i = 0; i < n; i++) {
        if (subconjunto[i] == 1) {
            if (!primero) strcat(buffer, ",");
            strcat(buffer, estados[i]);
            primero = 0;
        }
    }
    strcat(buffer, "}");
    printf("%-15s", buffer);
}


int main(void) {
    leer_txt();
    int total_subconjuntos = 1;
    for (int i = 0; i < numEstados; i++) {
        total_subconjuntos *= 2;
    }

    int **subconjuntos = malloc(total_subconjuntos * sizeof(int *));
    for (int k = 0; k < total_subconjuntos; k++) {
        subconjuntos[k] = calloc(numEstados, sizeof(int));
    }

    // Llenar la matriz de subconjuntos usando un contador binario aritmético puro
    for (int k = 1; k < total_subconjuntos; k++) {
        // Copiar el estado anterior
        for (int i = 0; i < numEstados; i++) {
            subconjuntos[k][i] = subconjuntos[k - 1][i];
        }
        // Sumar 1 en binario (con acarreo)
        int carry = 1;
        for (int i = 0; i < numEstados && carry; i++) {
            int suma = subconjuntos[k][i] + carry;
            subconjuntos[k][i] = suma % 2;
            carry = suma / 2;
        }
    }

    int ***tabla_destinos = malloc(total_subconjuntos * sizeof(int **));
    for (int k = 0; k < total_subconjuntos; k++) {
        tabla_destinos[k] = malloc(numSimbolos * sizeof(int *));
        for (int s = 0; s < numSimbolos; s++) {
            tabla_destinos[k][s] = calloc(numEstados, sizeof(int));
        }
    }

    for (int k = 0; k < total_subconjuntos; k++) {
        for (int s = 0; s < numSimbolos; s++) {
            // para revisar cada estado individual dentro del subconjunto actual
            for (int i = 0; i < numEstados; i++) {
                if (subconjuntos[k][i] == 1) {
                    // busca transiciones para el estado 'i' con el símbolo 's'
                    for (int t = 0; t < numTransiciones; t++) {
                        if (strcmp(transiciones[t][0], estados[i]) == 0 &&
                            strcmp(transiciones[t][1], alfabeto[s]) == 0) {
                            
                            int indice_destino = obtener_indice_estado(transiciones[t][2]);
                            if (indice_destino != -1) {
                                // Agregar al subconjunto destino (unión mediante arreglo)
                                tabla_destinos[k][s][indice_destino] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Imprimir encabezado de la tabla
    printf("estado\t\t\t");
    for (int s = 0; s < numSimbolos; s++) {
        printf("%-15s \t ", alfabeto[s]);
    }
    printf("\n\n");
    
    for (int i = 0; i < 90; i++) printf("-");
    printf("\n");

    for (int k = 0; k < total_subconjuntos; k++) {
        imprimir_subconjunto(subconjuntos[k], numEstados);
        printf(" | ");

        // 2. Imprimir los destinos calculados previamente
        for (int s = 0; s < numSimbolos; s++) {
            imprimir_subconjunto(tabla_destinos[k][s], numEstados);
        }
        printf(" | \n");
    }

    // Liberar memoria dinámica
    for (int k = 0; k < total_subconjuntos; k++) {
        for (int s = 0; s < numSimbolos; s++) {
            free(tabla_destinos[k][s]);
        }
        free(tabla_destinos[k]);
        free(subconjuntos[k]);
    }
    free(tabla_destinos);
    free(subconjuntos);

    return 0;
}