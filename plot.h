#ifndef PLOT_H
#define PLOT_H

#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdio.h>

void dACTestPlotFile(int start, int stop, int step) {
  FILE *ofp;
  ofp = fopen("dACTestPlotFile.csv", "w");
  fprintf(ofp, "n,t");
  while (start <= stop) {
    struct Polynomial *polynomial = generatePolynomial(start);
    struct Polynomial *copyPoly = copyPolynomial(polynomial);

    double time_spent = 0.0;

    clock_t begin = clock();

    struct Polynomial *productDecrease =
        decreaseAndConquer(polynomial, copyPoly);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    fprintf(ofp, "\n%d,%f", start, time_spent);

    freePolynomial(productDecrease);
    freePolynomial(polynomial);
    freePolynomial(copyPoly);

    start += step;
  }
  int fclose(FILE * ofp);
  return;
}

#endif /* PLOT_H */
