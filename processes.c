/* processes.c */
#include <stdio.h>
#include <string.h>

#define MAX_PROCESOS 10
typedef enum { LISTO, EJECUTANDO, TERMINADO } EstadoProceso;
typedef struct { int pid; char nombre[50]; EstadoProceso estado; int usado; } Proceso;
static Proceso tabla[MAX_PROCESOS];
static int siguiente_pid = 1;

void init_procesos() {
    int i;
    for (i = 0; i < MAX_PROCESOS; i++) tabla[i].usado = 0;
    siguiente_pid = 1;
    printf("[PROC] Planificador inicializado.\n");
}
void crear_proceso(char nombre[]) {
    int i;
    for (i = 0; i < MAX_PROCESOS; i++) {
        if (!tabla[i].usado) {
            tabla[i].pid = siguiente_pid++; tabla[i].estado = LISTO; tabla[i].usado = 1;
            strncpy(tabla[i].nombre, nombre, 49); tabla[i].nombre[49] = '\0';
            printf("[PROC] Proceso '%s' creado con PID %d.\n", tabla[i].nombre, tabla[i].pid); return;
        }
    }
    printf("[PROC] Error: tabla llena.\n");
}
void listar_procesos() {
    int i, found = 0;
    printf("\n[PROC] Procesos activos:\n");
    printf("%-6s %-20s %-12s\n", "PID", "Nombre", "Estado");
    printf("--------------------------------------\n");
    for (i = 0; i < MAX_PROCESOS; i++) {
        if (tabla[i].usado && tabla[i].estado != TERMINADO) {
            printf("%-6d %-20s %-12s\n", tabla[i].pid, tabla[i].nombre,
                   tabla[i].estado == LISTO ? "LISTO" : "EJECUTANDO");
            found++;
        }
    }
    if (!found) printf("(ninguno)\n");
}
void terminar_proceso(int pid) {
    int i;
    for (i = 0; i < MAX_PROCESOS; i++) {
        if (tabla[i].usado && tabla[i].pid == pid) {
            tabla[i].estado = TERMINADO; tabla[i].usado = 0;
            printf("[PROC] Proceso %d terminado.\n", pid); return;
        }
    }
    printf("[PROC] Proceso %d no encontrado.\n", pid);
}
