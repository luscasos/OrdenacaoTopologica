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

grafo_t *cria_grafo(int vertices);
void libera_grafo (grafo_t *g);
int cria_adjacencia(grafo_t *g, int u, int v);
void liga_vertices(grafo_t*grafo,int fonte, int destino,int distancia);
void cria_titulo(grafo_t* g,int id,int t);
void exportar_grafo_dot(const char *filename, grafo_t *grafo);
void imprime_matriz(grafo_t *grafo);
void cria_titulo(grafo_t* g,int id,int t);
grafo_t* Ler_arq(void);
void ordenacao_topologica(grafo_t* g);
int testa_direcional(grafo_t* g);
void imprime_vertices(grafo_t *g);
int adjacente(grafo_t *g, int u, int v);
int dfs(grafo_t* grafo,int inicial);
/*
int rem_adjacencia(grafo_t *g, int u, int v);

int peso_distancia(grafo_t *g, int u, int v);

void bfs(grafo_t* grafo,int inicial);

void vertice_set_id(grafo_t *g);
void exportar_bfs(const char *filename, grafo_t *grafo);
*/

#endif /* GRAFO_H_ */
