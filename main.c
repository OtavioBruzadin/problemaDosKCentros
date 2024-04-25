#include <stdio.h>
#include <limits.h>

#define MAX_PR 20

typedef struct {
    char nome[100];
    int dist[MAX_PR];
} Predio;

void inicializa_distancias(Predio predios[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                predios[i].dist[j] = 0;
            else
                predios[i].dist[j] = INT_MAX;
        }
    }
}

void seleciona_centros(Predio predios[], int n, int k, int centros[]) {
    int distancias[MAX_PR], min_dist;
    for (int i = 0; i < n; i++) {
        distancias[i] = INT_MAX;
    }

    // Seleciona o primeiro prédio como centro
    centros[0] = 0;
    int num_centros = 1;

    while (num_centros < k) {
        for (int i = 0; i < n; i++) {
            min_dist = INT_MAX;
            // Encontrar a menor distância deste prédio para qualquer centro já selecionado
            for (int j = 0; j < num_centros; j++) {
                if (predios[i].dist[centros[j]] < min_dist) {
                    min_dist = predios[i].dist[centros[j]];
                }
            }
            distancias[i] = min_dist;
        }

        // Escolher o prédio com a maior dessas distâncias mínimas
        int max_dist = -1;
        int novo_centro = -1;
        for (int i = 0; i < n; i++) {
            if (distancias[i] > max_dist) {
                max_dist = distancias[i];
                novo_centro = i;
            }
        }

        centros[num_centros++] = novo_centro;
    }
}

int main() {
    FILE *entrada = fopen("entrada.txt", "r");
    FILE *saida = fopen("saida.txt", "w");

    if (!entrada || !saida) {
        printf("Erro ao abrir arquivos!\n");
        return 1;
    }

    int n, k, m;
    fscanf(entrada, "%d %d", &n, &k);
    Predio predios[MAX_PR];

    for (int i = 0; i < n; i++) {
        fscanf(entrada, " %99[^\n]", predios[i].nome);
    }

    inicializa_distancias(predios, n);

    fscanf(entrada, "%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        fscanf(entrada, "%d %d %d", &u, &v, &d);
        predios[u-1].dist[v-1] = d;
        predios[v-1].dist[u-1] = d;
    }

    int centros[MAX_PR];
    seleciona_centros(predios, n, k, centros);

    for (int i = 0; i < k; i++) {
        fprintf(saida, "%s\n", predios[centros[i]].nome);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
