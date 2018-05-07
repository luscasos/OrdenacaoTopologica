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
    int n_dependencias;
    char *titulo;
};

struct arestas
{
    int dependencia;
    int exported;

};

struct grafos
{
    int n_vertices;
    vertice_t *vertices;
    aresta_t **matriz_adj;
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

grafo_t* Ler_arq(void)
{
    int i=0,id,dep,n,t;
    grafo_t*g;
    aresta_t aresta;
    aresta.dependencia=1;
    char buffer[128];
    FILE *fp;
    fp = fopen ("montagemcarro.txt", "r");
    if (fp == NULL)
    {
        printf ("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while ((fgets(buffer,128,fp))!=NULL)   //conta linha
        i++;
    rewind(fp);
   // printf("%d\n\n",i);
    g=cria_grafo(i-1);
    fgets(buffer,128,fp);
    while(!feof(fp))
    {
        n=0;
        fscanf(fp,"%d, %[^,]",&id,buffer);
        t=strlen(buffer);
        cria_titulo(g,id,t);
        strcpy(g->vertices[id].titulo,buffer);
        //printf("%d, %s\t",id,buffer);
            while(fscanf(fp,",%d",&dep)==1)
            {
                //printf("%d\t",dep);
                g->matriz_adj[id][dep]=aresta;      // cria dependencia entre id e dep
                n++;
            }
            fscanf(fp,"%*[^\n]");
            //printf("\n");
        g->vertices[id].n_dependencias=n;
        g->vertices[id].id=id;
    }
    fclose(fp);
    return g;
}

void ordenacao_topologica(grafo_t* g)
{
    int i, j, id;
    fila_t* Q = cria_fila();
    for(i=0;i<g->n_vertices;i++){
        if(g->vertices[i].n_dependencias==0){
            enqueue((void*)i, Q);
            printf("N[%d]=0.\n", i);
        }
    }
    while(!fila_vazia(Q))
    {
        i=(int)dequeue(Q);
        printf("%d\t%30s numero de dependencias diretas: %d\n",i,g->vertices[i].titulo,g->vertices[i].n_dependencias);
        if(g->vertices[i].n_dependencias==0)//caso a etapa não depender de ninguem, entrará na condição
        {
            for(j=0; j<g->n_vertices; j++)
            {

                if(adjacente(g, j, i)==1)//caso o elemento j dependa do elemento i, entrará na condição
                {
                    //printf("%d\n", j);
                    g->vertices[j].n_dependencias--;//subtraisse um do n de vertices que são antecessores do elemento j
                    if(g->vertices[j].n_dependencias == 0){
                        enqueue((void*)j, Q);
                        //printf("%d\n",j);
                    }
                }
            }
        }
    }
    libera_fila(Q);
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
    {
         free(g->matriz_adj[i]);
         free(g->vertices[i].titulo);
    }


    free(g->matriz_adj);
    free(g->vertices);
    free(g);
}

/*

int cria_adjacencia(grafo_t *g, int u, int v)
{

    if (g == NULL)
    {
        return FALSE;
    }

    if (u > g->n_vertices || v > g->n_vertices )
        return FALSE;

    g->matriz_adj[u][v].dependencia = TRUE;

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

    g->matriz_adj[u][v].dependencia = FALSE;

    return TRUE;
}
*/
int adjacente(grafo_t *g, int u, int v)
{

    if (u > MAX_VERTICES || v > MAX_VERTICES)
        return FALSE;
              //  printf("\n[%d][%d]\n",u,v);
    return ((g->matriz_adj[u][v].dependencia));
}
/*


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
                            grafo->vertices[i].distancia = grafo->matriz_adj[inicial][i].peso;
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
        if (grafo->vertices[i].pai!=0)
        {
            //printf("%d\n", grafo->vertices[i].id);
           // printf("%d\n",grafo->vertices[i].pai);
            fprintf(file, "\t%d -- %d [label = %d];\n",
                    grafo->vertices[i].id,
                    grafo->vertices[i].pai+1,
                    grafo->matriz_adj[i][grafo->vertices[i].pai].peso);
        }

    }
    fprintf(file, "}\n");
    fclose(file);
}

*/

void vertice_set_id(grafo_t *g)
{
    int i;
    for (i=0; i < g->n_vertices; i++)
        g->vertices[i].id = i+1;
}

void imprime_matriz(grafo_t* grafo)
{
    int i,j;
          	printf("     ");
	for(i=0; i < grafo->n_vertices; i++)
        printf("%2d ",i);
        printf("\n");
    for(i=0; i < grafo->n_vertices; i++)
        printf("---");
        printf("\n");
	for (i=0; i < grafo->n_vertices; i++){
            printf("%2d | ",i);
		for (j=0; j < grafo->n_vertices; j++)
			printf("%2d ", grafo->matriz_adj[i][j].dependencia);
			printf("\n");
	}
}

void imprime_vertices(grafo_t *g)
{
    int i;
    for(i=0; i<g->n_vertices;i++)
        printf("%d\t%30s numero de dependencias diretas: %d\n",i,g->vertices[i].titulo,g->vertices[i].n_dependencias);
}

void cria_titulo(grafo_t* g,int id,int t){
    g->vertices[id].titulo=(char *)malloc(sizeof(char) * (t+1));

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
            if ((!grafo->matriz_adj[i][j].exported &&!grafo->matriz_adj[j][i].exported )&& grafo->matriz_adj[i][j].dependencia) {

                fprintf(file, "\t%d -> %d ;\n",grafo->vertices[i].id,grafo->vertices[j].id);
                grafo->matriz_adj[i][j].exported = TRUE;
            }
        }
    }
    fprintf(file, "}\n");
    fclose(file);
}
