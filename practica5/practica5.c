#include <stdio.h>
#include <string.h>

#define MAX 256

// Variables globales para poder guardar el autómata y los caminos
int numEstados = 0, numSimbolos = 0, numFinales = 0, numTransiciones = 0, aceptadas = 0, total_ramas = 0;

char estados[MAX][MAX], alfabeto[MAX][MAX], finales[MAX][MAX];
char inicial[MAX], linea[MAX];

// Transiciones del AFN
// transiciones[estado][simbolo][estado_destino]
char transiciones_aux[MAX][3][MAX];
int camino[MAX];
int matriz_trans[MAX][MAX][MAX];

/* 
El autómata que recibe viene en el txt de esta forma:
Q = estados del autómata (0, 1, 2, 3, 4)
Σ = alfabeto (a, b, c...)
E = entradas posibles
S = salidas posibles
δ = transiciones (estado actual, entrada, próximo estado)
*/

// Lee el txt donde viene el autómata con sus respectivas reglas.
void leer_txt() {
    FILE *archivo = fopen("automata.txt", "r");

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
                snprintf(transiciones_aux[numTransiciones][columna], MAX, "%s", token);
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

int estado(const char *caracter) {
    for (int i = 0; i < numEstados; i++) {
        if (strcmp(estados[i], caracter) == 0) {
            return i;
        }
    }
    // Para el estado que no existe 
    return -1;
}

int obtener_simbolo(const char *simbolo) {
    for (int i = 0; i < numSimbolos; i++) {
        if (strcmp(alfabeto[i], simbolo) == 0) {
            return i;
        }
    }
    return -1;
}

int es_final(int estado_idx) {
    for (int i = 0; i < numFinales; i++) {
        if (estado(estados[estado_idx]) == estado(finales[i])) {
            return 1;
        }
    }
    return 0;
}

// Función para crear la matriz de transiciones
void crear_matriz() {
    for (int i = 0; i < numTransiciones; i++) {
        int origen = estado(transiciones_aux[i][0]);
        int simbolo = obtener_simbolo(transiciones_aux[i][1]);
        int destino = estado(transiciones_aux[i][2]);
        if (origen != -1 && simbolo != -1 && destino != -1) {
            matriz_trans[origen][simbolo][destino] = 1;
        }
    }
}

void imprimir_rama(const char *cadena, int pos, const char *resultado) {
    for (int i = 0; i <= pos; i++) {
        printf("%s", estados[camino[i]]);

        if (i < pos) {
            printf(" -%c-> ", cadena[i]);
        }
    }

    printf(" [%s]\n", resultado);
}

void explorar(const char *cadena, int pos, int estado_idx) {
    camino[pos] = estado_idx;

    // Llegamos al final de la cadena
    if (cadena[pos] == '\0') {
        total_ramas++;
        if (es_final(estado_idx)) { // Corregido: se pasa el índice entero
            aceptadas++;
            imprimir_rama(cadena, pos, "Cadena valida");
        }else return;
    }

    // Convertir el carácter actual de la cadena a string para buscarlo en el alfabeto
    char simbolo_str[2] = {cadena[pos], '\0'};
    int simbolo_idx = obtener_simbolo(simbolo_str);
    
    if (simbolo_idx == -1) {
        printf("Cadena con caracteres que no pertenecen al alfabeto.\n");
        return;
    }

    // Explorar todas las transiciones posibles desde este estado y símbolo (para AFN)
    for (int k = 0; k < numEstados; k++) {
        if (matriz_trans[estado_idx][simbolo_idx][k]) {
            explorar(cadena, pos + 1, k);   // Una llamada por cada rama
        }
    }
}

int main() {
    leer_txt();
    crear_matriz(); // ¡Importante! Se añadió la llamada para llenar la matriz

    char cadena[100];
    printf("Ingresa la cadena a evaluar: ");
    scanf("%99s", cadena);
    
    int inicial_idx = estado(inicial);
    if (inicial_idx == -1) {
        printf("Error: Estado inicial no encontrado.\n");
        return 1;
    }

    printf("\nRamas posibles:\n");
    explorar(cadena, 0, inicial_idx);   // Empieza en el estado inicial
    
    // Corregido: se añadió el especificador de formato %d
    printf("\nTotal de ramas: %d (Aceptadas: %d)\n", total_ramas, aceptadas);

    return 0;
}