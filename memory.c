/* memory.c */
#include <stdio.h>
#include <string.h>

#define MAX_BLOQUES 16
#define TAM_TOTAL   1024

typedef struct { int pid; int size; } BloqueMemoria;
static BloqueMemoria memoria[MAX_BLOQUES];
static int libre = TAM_TOTAL;

void init_memoria() {
    int i;
    for (i = 0; i < MAX_BLOQUES; i++) { memoria[i].pid = -1; memoria[i].size = 0; }
    libre = TAM_TOTAL;
    printf("[MEM] Memoria inicializada (%d KB disponibles).\n", TAM_TOTAL);
}
void asignar_memoria(int pid, int size) {
    int i;
    if (size > libre) { printf("[MEM] Error: memoria insuficiente.\n"); return; }
    for (i = 0; i < MAX_BLOQUES; i++) {
        if (memoria[i].pid == -1) {
            memoria[i].pid = pid; memoria[i].size = size; libre -= size;
            printf("[MEM] Asignados %d KB al proceso %d.\n", size, pid); return;
        }
    }
    printf("[MEM] Error: tabla llena.\n");
}
void liberar_memoria(int pid) {
    int i, lib = 0;
    for (i = 0; i < MAX_BLOQUES; i++) {
        if (memoria[i].pid == pid) { libre += memoria[i].size; lib += memoria[i].size; memoria[i].pid = -1; memoria[i].size = 0; }
    }
    if (lib > 0) printf("[MEM] Liberados %d KB del proceso %d.\n", lib, pid);
    else printf("[MEM] Proceso %d sin memoria asignada.\n", pid);
}
void mostrar_memoria() {
    int i;
    printf("\n[MEM] Memoria: %d KB libres / %d KB total\n", libre, TAM_TOTAL);
    for (i = 0; i < MAX_BLOQUES; i++)
        if (memoria[i].pid != -1) printf("  PID %-4d -> %d KB\n", memoria[i].pid, memoria[i].size);
}
