/* files.c
   Simulación básica de sistema de archivos
*/

#include <stdio.h>
#include <string.h>

#define MAX_FILES 20
#define MAX_NAME 50
#define MAX_CONTENT 256

typedef struct {
    char nombre[MAX_NAME];
    char contenido[MAX_CONTENT];
    int abierto;
    int usado;
} Archivo;

Archivo disco[MAX_FILES];

/* Inicializa estructura */
void init_filesystem() {
    int i;
    for(i = 0; i < MAX_FILES; i++) {
        disco[i].usado = 0;
        disco[i].abierto = 0;
        memset(disco[i].nombre, 0, MAX_NAME);
        memset(disco[i].contenido, 0, MAX_CONTENT);
    }
    printf("[FS] Sistema de archivos inicializado.\n");
}

/* Crear archivo */
void crear_archivo(char nombre[]) {
    int i;

    /* Verificar si ya existe */
    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado && strcmp(disco[i].nombre, nombre) == 0) {
            printf("[FS] Error: El archivo '%s' ya existe.\n", nombre);
            return;
        }
    }

    /* Buscar espacio libre */
    for(i = 0; i < MAX_FILES; i++) {
        if(!disco[i].usado) {
            strncpy(disco[i].nombre, nombre, MAX_NAME - 1);
            disco[i].nombre[MAX_NAME - 1] = '\0';
            memset(disco[i].contenido, 0, MAX_CONTENT);
            disco[i].abierto = 0;
            disco[i].usado = 1;
            printf("[FS] Archivo '%s' creado exitosamente.\n", nombre);
            return;
        }
    }

    printf("[FS] Error: No hay espacio disponible en el sistema de archivos.\n");
}

/* Abrir archivo */
void abrir_archivo(char nombre[]) {
    int i;

    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado && strcmp(disco[i].nombre, nombre) == 0) {
            if(disco[i].abierto) {
                /* Simulación de bloqueo por archivo en uso */
                printf("[FS] Error: El archivo '%s' ya está abierto (bloqueado).\n", nombre);
            } else {
                disco[i].abierto = 1;
                printf("[FS] Archivo '%s' abierto.\n", nombre);
            }
            return;
        }
    }

    printf("[FS] Error: Archivo '%s' no encontrado.\n", nombre);
}

/* Escribir archivo */
void escribir_archivo(char nombre[], char texto[]) {
    int i;

    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado && strcmp(disco[i].nombre, nombre) == 0) {
            if(!disco[i].abierto) {
                printf("[FS] Error: El archivo '%s' no está abierto. Ábralo primero.\n", nombre);
                return;
            }
            strncpy(disco[i].contenido, texto, MAX_CONTENT - 1);
            disco[i].contenido[MAX_CONTENT - 1] = '\0';
            printf("[FS] Contenido escrito en '%s'.\n", nombre);
            return;
        }
    }

    printf("[FS] Error: Archivo '%s' no encontrado.\n", nombre);
}

/* Leer archivo */
void leer_archivo(char nombre[]) {
    int i;

    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado && strcmp(disco[i].nombre, nombre) == 0) {
            if(!disco[i].abierto) {
                printf("[FS] Error: El archivo '%s' no está abierto. Ábralo primero.\n", nombre);
                return;
            }
            printf("[FS] Contenido de '%s':\n%s\n", nombre,
                   strlen(disco[i].contenido) > 0 ? disco[i].contenido : "(vacío)");
            return;
        }
    }

    printf("[FS] Error: Archivo '%s' no encontrado.\n", nombre);
}

/* Cerrar archivo */
void cerrar_archivo(char nombre[]) {
    int i;

    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado && strcmp(disco[i].nombre, nombre) == 0) {
            if(!disco[i].abierto) {
                printf("[FS] Aviso: El archivo '%s' ya estaba cerrado.\n", nombre);
            } else {
                disco[i].abierto = 0;
                printf("[FS] Archivo '%s' cerrado.\n", nombre);
            }
            return;
        }
    }

    printf("[FS] Error: Archivo '%s' no encontrado.\n", nombre);
}

/* Eliminar archivo */
void eliminar_archivo(char nombre[]) {
    int i;

    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado && strcmp(disco[i].nombre, nombre) == 0) {
            if(disco[i].abierto) {
                printf("[FS] Error: No se puede eliminar '%s', está abierto (bloqueado).\n", nombre);
                return;
            }
            disco[i].usado = 0;
            disco[i].abierto = 0;
            memset(disco[i].nombre, 0, MAX_NAME);
            memset(disco[i].contenido, 0, MAX_CONTENT);
            printf("[FS] Archivo '%s' eliminado.\n", nombre);
            return;
        }
    }

    printf("[FS] Error: Archivo '%s' no encontrado.\n", nombre);
}

/* Listar archivos */
void listar_archivos() {
    int i;
    int encontrados = 0;

    printf("\nArchivos en sistema:\n");
    printf("%-30s %-10s\n", "Nombre", "Estado");
    printf("----------------------------------------------\n");

    for(i = 0; i < MAX_FILES; i++) {
        if(disco[i].usado) {
            printf("%-30s %-10s\n",
                   disco[i].nombre,
                   disco[i].abierto ? "Abierto" : "Cerrado");
            encontrados++;
        }
    }

    if(encontrados == 0) {
        printf("(ningún archivo en el sistema)\n");
    }
}
