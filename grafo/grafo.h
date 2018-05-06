/*
 * grafo.h
 *
 *  Created on: Nov 18, 2016
 *      Author: xtarke
 */

#ifndef GRAFO_H_
#define GRAFO_H_


#define MAX_VERTICES 50

#define TRUE 1
#define FALSE 0

typedef struct vertices vertice_t;
typedef struct arestas aresta_t;
typedef struct grafos grafo_t;
typedef struct dado dado_t;
//funções do dado
grafo_t* ler_arquivo(char* arquivo);
vertice_t *cria_vertice(void);
void alocaprocesso(vertice_t* V,int tamanho);
void copia_dep(vertice_t **V, int tamanho, int *dep);


grafo_t *cria_grafo(int vertices);
void libera_grafo (grafo_t *g);
int cria_adjacencia(grafo_t *g, int u, int v);
void liga_vertices(grafo_t*grafo,int fonte, int destino,int distancia);
int rem_adjacencia(grafo_t *g, int u, int v);
int adjacente(grafo_t *g, int u, int v);
int peso_distancia(grafo_t *g, int u, int v);
void dfs(grafo_t* grafo,int inicial);
void bfs(grafo_t* grafo,int inicial);
void exportar_grafo_dot(const char *filename, grafo_t *grafo);
void vertice_set_id(grafo_t *g);
void exportar_bfs(const char *filename, grafo_t *grafo);
void imprime_matriz(grafo_t *grafo);

#endif /* GRAFO_H_ */
