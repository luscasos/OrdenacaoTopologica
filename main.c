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


int main(void) {

	grafo_t *g;

	g = Ler_arq();

    imprime_matriz(g);

    imprime_vertices(g);

    exportar_grafo_dot("grafo.dot",g);

	libera_grafo(g);

	return EXIT_SUCCESS;
}
