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

	grafo_t *g;

	g = ler_arquivo("montagemcarro.txt");



	libera_grafo(g);

	return EXIT_SUCCESS;
}
