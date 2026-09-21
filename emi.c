#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTER 1000

char cadena1[MAX_CHARACTER];
char cadena2[MAX_CHARACTER];
char cadenaInvertido[MAX_CHARACTER];
char cadenaCopiada[MAX_CHARACTER];

void seleccionOpcion();
void prefijo(char cadena[], int tamanioCadena, int eliminacion);
void sufijo(char cadena[], int tamanioCadena, int eliminacion);
void subcadena();
void subsecuencia();
void cadencia_potencia();
void invertirCadena(char cadena[], char cadenaInvertido[]);

int main() {
    int opcion;

    do {
        printf("\n--- OPERACIONES CON CADENAS ---\n");
        printf("1. Sufijo\n");
        printf("2. Prefijo\n");
        printf("3. Subcadena\n");
        printf("4. Subsecuencia\n");
        printf("5. Potencia de cadena\n");
        printf("6. Salir\n");

        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        getchar();

        switch (opcion) {

            case 1: {
                int eliminacion;

                seleccionOpcion();

                printf("Introduce cuantos caracteres deseas eliminar: ");
                scanf("%d", &eliminacion);

                if (eliminacion < 0 ||
                    eliminacion > strlen(cadena1) ||
                    eliminacion > strlen(cadena2)) {

                    printf("Cantidad invalida. No puedes eliminar mas caracteres de los que contiene la cadena.\n");
                    break;
                    }

                printf("\nCadena 1:\n");
                prefijo(cadena1, strlen(cadena1), eliminacion);

                printf("Cadena 2:\n");
                prefijo(cadena2, strlen(cadena2), eliminacion);

                break;
            }

            case 2: {
                int eliminacion;

                seleccionOpcion();

                printf("Introduce cuantos caracteres deseas eliminar: ");
                scanf("%d", &eliminacion);

                if (eliminacion < 0 ||
                    eliminacion > strlen(cadena1) ||
                    eliminacion > strlen(cadena2)) {

                    printf("Cantidad invalida. No puedes eliminar mas caracteres de los que contiene la cadena.\n");
                    break;
                    }

                printf("\nCadena 1:\n");
                sufijo(cadena1, strlen(cadena1), eliminacion);

                printf("Cadena 2:\n");
                sufijo(cadena2, strlen(cadena2), eliminacion);

                break;
            }

            case 3:
                subcadena();
                break;

            case 4:
                subsecuencia();
                break;

            case 5:
                cadencia_potencia();
                break;

            case 6:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 6);

    return 0;
}

void seleccionOpcion() {
    printf("Introduce la primera cadena: ");
    fgets(cadena1, sizeof(cadena1), stdin);
    cadena1[strcspn(cadena1, "\n")] = '\0';

    printf("Introduce la segunda cadena: ");
    fgets(cadena2, sizeof(cadena2), stdin);
    cadena2[strcspn(cadena2, "\n")] = '\0';
}

void prefijo(char cadena[], int tamanioCadena, int eliminacion) {
    if (tamanioCadena <= eliminacion) {
        cadena[0] = '\0';
        printf("Resultado de la cadena: cadena vacia\n");
    }
    else {
        cadena[tamanioCadena - eliminacion] = '\0';
        printf("Resultado de la cadena: %s\n", cadena);
    }
}

void sufijo(char cadena[], int tamanioCadena, int eliminacion) {
    if (tamanioCadena <= eliminacion) {
        cadena[0] = '\0';
        printf("Resultado de la cadena: cadena vacia\n");
    }
    else {
        char *origen = cadena + eliminacion;
        char *destino = cadena;

        while (*origen != '\0') {
            *destino = *origen;
            origen++;
            destino++;
        }

        *destino = '\0';

        printf("Resultado de la cadena: %s\n", cadena);
    }
}

void subcadena() {
    int eliminacion;
    char seleccion;
    int continuar = 1;

    char temp1[MAX_CHARACTER];
    char temp2[MAX_CHARACTER];

    seleccionOpcion();

    strcpy(temp1, cadena1);
    strcpy(temp2, cadena2);

    while (continuar == 1) {
        int len1 = strlen(temp1);
        int len2 = strlen(temp2);

        if (len1 == 0 && len2 == 0) {
            printf("\nAmbas cadenas estan vacias.\n");
            break;
        }

        printf("\nCadena 1 actual: %s\n",
               len1 == 0 ? "cadena vacia" : temp1);

        printf("Cadena 2 actual: %s\n",
               len2 == 0 ? "cadena vacia" : temp2);

        printf("Que lado desea eliminar? Derecha (d) o Izquierda (i): ");
        scanf(" %c", &seleccion);

        printf("Introduce cuantos caracteres deseas eliminar: ");
        scanf("%d", &eliminacion);

        if (eliminacion <= 0) {
            printf("Cantidad invalida para eliminar.\n");
        }
        else if (seleccion == 'i' || seleccion == 'I') {

            printf("\n--- Aplicando eliminacion por la izquierda ---\n");

            printf("Cadena 1:\n");
            sufijo(temp1, len1, eliminacion);

            printf("Cadena 2:\n");
            sufijo(temp2, len2, eliminacion);
        }
        else if (seleccion == 'd' || seleccion == 'D') {

            printf("\n--- Aplicando eliminacion por la derecha ---\n");

            printf("Cadena 1:\n");
            prefijo(temp1, len1, eliminacion);

            printf("Cadena 2:\n");
            prefijo(temp2, len2, eliminacion);
        }
        else {
            printf("Opcion de lado invalida.\n");
        }

        if (strlen(temp1) == 0 && strlen(temp2) == 0) {
            printf("\nAmbas cadenas han quedado vacias.\n");
            break;
        }

        printf("\nDesea continuar eliminando sobre estas subcadenas? Si(1) / No(2): ");
        scanf("%d", &continuar);

        if (continuar == 2) {
            break;
        }
    }

    printf("\n========================================\n");

    if (strlen(temp1) == 0) {
        printf("Resultado final Subcadena 1: cadena vacia\n");
    }
    else {
        printf("Resultado final Subcadena 1: %s\n", temp1);
    }

    if (strlen(temp2) == 0) {
        printf("Resultado final Subcadena 2: cadena vacia\n");
    }
    else {
        printf("Resultado final Subcadena 2: %s\n", temp2);
    }

    printf("========================================\n");
}

void subsecuencia() {
    char caracteresEliminar[MAX_CHARACTER];
    int seleccion = 0;

    seleccionOpcion();

    while (seleccion != 2) {

        printf("Desea eliminar caracteres en las cadenas si(1)/no(2): ");
        scanf("%d", &seleccion);
        getchar();

        if (seleccion == 1) {

            printf("Introduce los caracteres que desea eliminar: ");
            fgets(caracteresEliminar, sizeof(caracteresEliminar), stdin);
            caracteresEliminar[strcspn(caracteresEliminar, "\n")] = '\0';

            /*
             * CADENA 1
             */
            char *origen1 = cadena1;
            char *destino1 = cadena1;

            while (*origen1 != '\0') {

                if (strchr(caracteresEliminar, *origen1) == NULL) {
                    *destino1 = *origen1;
                    destino1++;
                }

                origen1++;
            }

            *destino1 = '\0';


            /*
             * CADENA 2
             */
            char *origen2 = cadena2;
            char *destino2 = cadena2;

            while (*origen2 != '\0') {

                if (strchr(caracteresEliminar, *origen2) == NULL) {
                    *destino2 = *origen2;
                    destino2++;
                }

                origen2++;
            }

            *destino2 = '\0';


            printf("\nResultado cadena 1: %s\n",
                   strlen(cadena1) == 0 ? "cadena vacia" : cadena1);

            printf("Resultado cadena 2: %s\n",
                   strlen(cadena2) == 0 ? "cadena vacia" : cadena2);
        }
    }

    printf("\nResultado final cadena 1: %s\n",
           strlen(cadena1) == 0 ? "cadena vacia" : cadena1);

    printf("Resultado final cadena 2: %s\n",
           strlen(cadena2) == 0 ? "cadena vacia" : cadena2);
}

void cadencia_potencia() {
    int potencia;

    seleccionOpcion();

    printf("Introduce una potencia: ");
    scanf("%d", &potencia);

    printf("\n--- Cadena 1 ---\n");
    printf("Cadena obtenida: %s.\n", cadena1);
    printf("Potencia obtenida: %d.\n", potencia);

    if (potencia > 0) {

        strcpy(cadenaCopiada, cadena1);

        for (int i = 1; i < potencia; i++) {
            strcat(cadena1, cadenaCopiada);
        }

        printf("Resultado de la cadena: %s\n", cadena1);
    }
    else if (potencia == 0) {
        printf("Resultado de la cadena: cadena vacia\n");
    }
    else {
        invertirCadena(cadena1, cadenaInvertido);

        strcpy(cadenaCopiada, cadenaInvertido);

        for (int i = -1; i > potencia; i--) {
            strcat(cadenaInvertido, cadenaCopiada);
        }

        printf("Resultado de la cadena: %s\n", cadenaInvertido);
    }

    printf("\n--- Cadena 2 ---\n");
    printf("Cadena obtenida: %s.\n", cadena2);
    printf("Potencia obtenida: %d.\n", potencia);

    if (potencia > 0) {

        strcpy(cadenaCopiada, cadena2);

        for (int i = 1; i < potencia; i++) {
            strcat(cadena2, cadenaCopiada);
        }

        printf("Resultado de la cadena: %s\n", cadena2);
    }
    else if (potencia == 0) {
        printf("Resultado de la cadena: cadena vacia\n");
    }
    else {
        invertirCadena(cadena2, cadenaInvertido);

        strcpy(cadenaCopiada, cadenaInvertido);

        for (int i = -1; i > potencia; i--) {
            strcat(cadenaInvertido, cadenaCopiada);
        }

        printf("Resultado de la cadena: %s\n", cadenaInvertido);
    }
}

void invertirCadena(char cadena[], char cadenaInvertido[]) {
    char *origen = cadenaInvertido;
    char *final = cadena + strlen(cadena) - 1;

    while (final >= cadena) {
        *origen = *final;

        final--;
        origen++;
    }

    *origen = '\0';
}