/* kernel.c
   Núcleo principal del sistema
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototipos - Sistema de archivos */
void init_filesystem();
void listar_archivos();
void crear_archivo(char nombre[]);
void abrir_archivo(char nombre[]);
void escribir_archivo(char nombre[], char texto[]);
void leer_archivo(char nombre[]);
void cerrar_archivo(char nombre[]);
void eliminar_archivo(char nombre[]);

/* Prototipos - módulos previos */
void init_memoria();
void mostrar_memoria();
void asignar_memoria(int pid, int size);
void liberar_memoria(int pid);

void init_procesos();
void crear_proceso(char nombre[]);
void listar_procesos();
void terminar_proceso(int pid);

/* Utilidad: eliminar salto de línea de fgets */
void limpiar_newline(char *str) {
    int len = strlen(str);
    if(len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void mostrar_menu() {
    printf("\n============= Mini Kernel =============\n");
    printf("--- Archivos ---\n");
    printf("1. Crear archivo\n");
    printf("2. Abrir archivo\n");
    printf("3. Leer archivo\n");
    printf("4. Escribir archivo\n");
    printf("5. Cerrar archivo\n");
    printf("6. Eliminar archivo\n");
    printf("7. Listar archivos\n");
    printf("--- Procesos ---\n");
    printf("8. Crear proceso\n");
    printf("9. Listar procesos\n");
    printf("10. Terminar proceso\n");
    printf("--- Memoria ---\n");
    printf("11. Asignar memoria a proceso\n");
    printf("12. Liberar memoria de proceso\n");
    printf("13. Mostrar estado de memoria\n");
    printf("--- Sistema ---\n");
    printf("14. Estado global del sistema\n");
    printf("0. Salir\n");
    printf("Seleccione: ");
}

void estado_global() {
    printf("\n======== Estado Global del Sistema ========\n");
    listar_procesos();
    mostrar_memoria();
    listar_archivos();
    printf("===========================================\n");
}

int main() {

    int opcion;
    char nombre[50];
    char texto[256];
    int pid, size;

    /* Inicialización de todos los módulos */
    printf("[Kernel] Iniciando sistema...\n");
    init_memoria();
    init_procesos();
    init_filesystem();
    printf("[Kernel] Sistema listo.\n");

    do {
        mostrar_menu();
        scanf("%d", &opcion);
        getchar(); /* consumir newline */

        switch(opcion) {

            /* --- Archivos --- */
            case 1:
                printf("Nombre del archivo: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                crear_archivo(nombre);
                break;

            case 2:
                printf("Nombre del archivo: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                abrir_archivo(nombre);
                break;

            case 3:
                printf("Nombre del archivo: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                leer_archivo(nombre);
                break;

            case 4:
                printf("Nombre del archivo: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                printf("Texto a escribir: ");
                fgets(texto, sizeof(texto), stdin);
                limpiar_newline(texto);
                escribir_archivo(nombre, texto);
                break;

            case 5:
                printf("Nombre del archivo: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                cerrar_archivo(nombre);
                break;

            case 6:
                printf("Nombre del archivo a eliminar: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                eliminar_archivo(nombre);
                break;

            case 7:
                listar_archivos();
                break;

            /* --- Procesos --- */
            case 8:
                printf("Nombre del proceso: ");
                fgets(nombre, sizeof(nombre), stdin);
                limpiar_newline(nombre);
                crear_proceso(nombre);
                break;

            case 9:
                listar_procesos();
                break;

            case 10:
                printf("PID del proceso a terminar: ");
                scanf("%d", &pid);
                getchar();
                liberar_memoria(pid);   /* liberar recursos antes de terminar */
                terminar_proceso(pid);
                break;

            /* --- Memoria --- */
            case 11:
                printf("PID del proceso: ");
                scanf("%d", &pid);
                getchar();
                printf("Tamaño a asignar (KB): ");
                scanf("%d", &size);
                getchar();
                asignar_memoria(pid, size);
                break;

            case 12:
                printf("PID del proceso: ");
                scanf("%d", &pid);
                getchar();
                liberar_memoria(pid);
                break;

            case 13:
                mostrar_memoria();
                break;

            /* --- Sistema --- */
            case 14:
                estado_global();
                break;

            case 0:
                printf("[Kernel] Liberando recursos y apagando sistema...\n");
                break;

            default:
                printf("[Kernel] Opción inválida. Intente de nuevo.\n");
        }

    } while(opcion != 0);

    printf("[Kernel] Sistema apagado correctamente.\n");
    return 0;
}
