#include <stdio.h>

int transiciones[5][2] = {
    {0b01001, 0b00011},
    {0b00000, 0b00100},
    {0b00100, 0b00100},
    {0b10000, 0b00000},
    {0b10000, 0b10000}
};

int estadosFinales = 0b11100, valida = 0;

void imprimirCamino(int camino[], int longitud, char cadena[]) {
    for (int i = 0; i < longitud; i++) {
        if (i > 0)
            printf(" -> %c -> ", cadena[i - 1]);

        printf("q%d", camino[i]);
    }
    printf("\n");
}

void explorar(char cadena[], int pos, int estado, int camino[]) {
    camino[pos] = estado;

    if (cadena[pos] == '\0') {    
        if (estadosFinales & (1 << estado)) {
            imprimirCamino(camino, pos + 1, cadena);
            valida = 1;
        }
        return;
    }

    int simbolo = cadena[pos] - 'a';
    int destinos = transiciones[estado][simbolo];

    if (destinos == 0)  return;

    for (int j = 0; j < 5; j++) {
        if (destinos & (1 << j)) {
            explorar(cadena, pos + 1, j, camino);
        }
    }
}

int main() {
    char cadena[100];
    int camino[101];

    printf("Ingresa la cadena a verificar: ");
    scanf("%99[^\n]", cadena);

    explorar(cadena, 0, 0, camino);
    printf("\n");
    printf(valida ? "TRUE\n" : "DOU\n");

    return 0;
}