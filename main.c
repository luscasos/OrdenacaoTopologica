/*
 ============================================================================
 Name        : grafos-adj-matrix.c
 Author      : Renan Augusto Starke
 Version     :
 Copyright   : Renan, todo os direitos reservados
 Description : grafos com matriz de adjacencia, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "./grafo/grafo.h"
#define VERTICES 12

int main(void) {


	int i,j;
	grafo_t *g;

	g = cria_grafo(VERTICES);


    liga_vertices(g,1,2,7);
    liga_vertices(g,1,3,9);
    liga_vertices(g,1,6,14);
    liga_vertices(g,2,3,10);
    liga_vertices(g,2,4,15);
    liga_vertices(g,3,4,11);
    liga_vertices(g,4,5,6);
    liga_vertices(g,5,6,9);
    liga_vertices(g,3,6,2);
    liga_vertices(g,7,8,9);
    liga_vertices(g,8,9,4);
    liga_vertices(g,10,11,1);
    liga_vertices(g,12,11,4);
    liga_vertices(g,10,12,8);

    vertice_set_id(g);
    printf("BATATAO\n");


	/* Imprimi matriz */
	printf("     ");
	for(i=0; i < VERTICES; i++)
        printf("%2.d ",i+1);
        printf("\n");
    for(i=0; i < VERTICES; i++)
        printf("----");
        printf("\n");
	for (i=0; i < VERTICES; i++){
            printf("%2d | ",i+1);
		for (j=0; j < VERTICES; j++)
			printf("%2d ", adjacente(g,i,j));
			printf("\n");
	}
    exportar_grafo_dot("grafo.dot",g);
	bfs(g,3);

	exportar_bfs("grafobfs.dot",g);

	dfs(g,3);



	libera_grafo(g);

	return EXIT_SUCCESS;
}
