/*
 * grafo.c
 *
 *  Created on: Nov 18, 2016
 *      Author: xtarke
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../fila/fila.h"
#include "../pilha/pilha.h"

#include "grafo.h"

struct vertices
{
    int id;
    int pai;
    int distancia;
    int visitado;

};

struct arestas
{
    int adj;
    int peso;
    int exported;

};

struct grafos
{
    int n_vertices;
    vertice_t *vertices;
    aresta_t **matriz_adj;	/* Matriz de adjacencia */
};


grafo_t *cria_grafo(int vertices)
{
    int i;
    aresta_t **matriz_adj;
    grafo_t *g = malloc(sizeof(grafo_t));

    if (g == NULL)
    {
        perror("cria_grafo (g)");
        exit(EXIT_FAILURE);
    }

    g->n_vertices = vertices;
    g->vertices = malloc(vertices * sizeof(vertice_t));

    if (g->vertices == NULL)
    {
        perror("cria_grafo (vertices)");
        exit(EXIT_FAILURE);
    }

    memset(g->vertices, 0, vertices * sizeof(vertice_t));

    matriz_adj = malloc(vertices * sizeof(aresta_t *));

    if (matriz_adj == NULL)
    {
        perror("cria_grafo (matriz_adj)");
        exit(EXIT_FAILURE);
    }

    for ( i = 0; i < vertices; i++ )
    {
        matriz_adj[i] = calloc(vertices, sizeof(vertice_t));

        if (matriz_adj[i] == NULL)
        {
            perror("cria_grafo (matriz_adj[i])");
            exit(EXIT_FAILURE);
        }
    }

    g->matriz_adj = matriz_adj;

    return g;
}

void liga_vertices(grafo_t*grafo,int fonte, int destino,int distancia)
{

    fonte--;
    destino--;
    aresta_t aresta;
    aresta.adj=TRUE;
    aresta.peso=distancia;
    grafo->matriz_adj[fonte][destino]=aresta ;
    grafo->matriz_adj[destino][fonte]=aresta ;


}

void libera_grafo (grafo_t *g)
{
    int i;

    if (g == NULL)
    {
        perror("libera_grafo");
        exit(EXIT_FAILURE);
    }

    for (i=0; i < g->n_vertices; i++)
        free(g->matriz_adj[i]);

    free(g->matriz_adj);
    free(g->vertices);
    free(g);
}


int cria_adjacencia(grafo_t *g, int u, int v)
{

    if (g == NULL)
    {
        return FALSE;
    }

    if (u > g->n_vertices || v > g->n_vertices )
        return FALSE;

    g->matriz_adj[u][v].adj = TRUE;

    return TRUE;
}

int rem_adjacencia(grafo_t *g, int u, int v)
{

    if (g == NULL)
    {
        return FALSE;
    }

    if (u > g->n_vertices || v > g->n_vertices)
        return FALSE;

    g->matriz_adj[u][v].adj = FALSE;

    return TRUE;
}

int adjacente(grafo_t *g, int u, int v)
{

    if (u > MAX_VERTICES || v > MAX_VERTICES)
        return FALSE;
              //  printf("\n[%d][%d]\n",u,v);
    return ((g->matriz_adj[u][v].adj));
}

int peso_distancia(grafo_t *g, int u, int v)
{

    if (u > MAX_VERTICES || v > MAX_VERTICES)
        return FALSE;

    return ((g->matriz_adj[u][v].peso));
}

void bfs(grafo_t* grafo,int inicial)
{
    inicial--;
    int i;
    fila_t*fila=cria_fila();

    for (i=0; i<grafo->n_vertices; i++)
    {
        grafo->vertices[i].distancia = -1;
        grafo->vertices[i].pai=0;

    }


    grafo->vertices[inicial].distancia=0;
    enqueue((void*)inicial,fila);

    // printf("adjacentes: %d\n",grafo->matriz_adj[0][0].adj);

    while(!fila_vazia(fila))
    {
        inicial=(int)dequeue(fila);

        //printf("Dequeue: %d dist %d\n",inicial+1,grafo->vertices[inicial].distancia);

        for (i=0; i<=grafo->n_vertices; i++)
        {

           // printf("adjacentes: %d\n",grafo->matriz_adj[inicial][i].adj);
            if (grafo->matriz_adj[inicial][i].adj)
            {
                    if ( grafo->vertices[i].distancia == -1){
                        if (grafo->vertices[i].pai==0){
                            grafo->vertices[i].pai = inicial;
                            enqueue((void*)i,fila);
                          //  printf("Enqueue: %d\n",i+1);
                        }
                    }
                    grafo->vertices[inicial].distancia = 1;
            }

        }


    }
	libera_fila(fila);

}

void dfs(grafo_t* grafo,int inicial)
{
    inicial--;
    int i;
    pilha_t*pilha=cria_pilha();

    for (i=0; i<grafo->n_vertices; i++)
    {
        grafo->vertices[i].visitado = 0;
    }
    push((void*)inicial,pilha);
   // printf("push %d\n",inicial);
    while(!pilha_vazia(pilha))
    {
        inicial=(int)pop(pilha);
        //printf("pop %d\n",inicial);

            if (grafo->vertices[inicial].visitado == 0)
            {
                   grafo->vertices[inicial].visitado = 1;
                   printf("Visitado: %d\n",inicial+1);
                   for (i=0;i<=grafo->n_vertices;i++){
                        if (grafo->matriz_adj[inicial][i].adj)
                            push((void*)i,pilha);
                          //  printf("push %d\n",i);
                   }
            }
        }

    libera_pilha(pilha);
}

void exportar_grafo_dot(const char *filename, grafo_t *grafo) {
    #ifdef DEBUG
        printf("\nexporta grafo:");
    #endif
    FILE *file;
    if (filename == NULL || grafo == NULL){
        fprintf(stderr, "exportar_grafp_dot: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(filename, "w");

    if (file == NULL){
        perror("exportar_grafp_dot:");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < grafo->n_vertices; i++)
        for (int j = 0; j <grafo->n_vertices; j++)
            grafo->matriz_adj[i][j].exported=0;


    fprintf(file, "graph {\n");
    for (int i = 0; i < grafo->n_vertices; i++) {
        for (int j = 0; j <grafo->n_vertices; j++) {
            if ((!grafo->matriz_adj[i][j].exported &&!grafo->matriz_adj[j][i].exported )&& grafo->matriz_adj[i][j].adj) {

                fprintf(file, "\t%d -- %d [label = %d];\n",
                    grafo->vertices[i].id,
                    grafo->vertices[j].id,
                    grafo->matriz_adj[i][j].peso);
                grafo->matriz_adj[i][j].exported = TRUE;
            }
        }
    }
    fprintf(file, "}\n");
    fclose(file);
}

void vertice_set_id(grafo_t *g)
{
    int i;
    for (i=0; i < g->n_vertices; i++)
        g->vertices[i].id = i+1;
}

void exportar_bfs(const char *filename, grafo_t *grafo){

int i;
    FILE *file;
    if (filename == NULL || grafo == NULL){
        fprintf(stderr, "exportar_grafp_dot: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(filename, "w");
    fprintf(file, "graph {\n");
    for (i=0; i < grafo->n_vertices; i++)
    {
        if (grafo->matriz_adj[i][(int)grafo->vertices[i].pai-1].peso>=0)
        {
            //printf("%d\n", grafo->vertices[i].id);
           // printf("%d\n",grafo->vertices[i].pai);
            fprintf(file, "\t%d -- %d [label = %d];\n",
                    grafo->vertices[i].id,
                    grafo->vertices[grafo->vertices[i].pai].id,
                    grafo->matriz_adj[i][grafo->vertices[i].pai-1].peso);
        }

    }
    fprintf(file, "}\n");
    fclose(file);
}

void imprime_matriz(grafo_t *grafo)
{
    int i,j;
    	printf("     ");
	for(i=0; i < grafo->n_vertices; i++)
        printf("%2.d ",i+1);
        printf("\n");
    for(i=0; i < grafo->n_vertices; i++)
        printf("----");
        printf("\n");
	for (i=0; i < grafo->n_vertices; i++){
            printf("%2d | ",i+1);
		for (j=0; j < grafo->n_vertices; j++)
			printf("%2d ", adjacente(grafo,i,j));
			printf("\n");
	}
}
