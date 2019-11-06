#include "advancePolynomialArithmetics2.h"
#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include "plot.h"
#include <stdlib.h>

/* Program used to save timings of methods */

int main() {
  /* test(); */
  FILE *ofp, *ofpK;
  ofp = fopen("decreaseTestPlotFile.csv", "w");
  ofpK = fopen("karatsubaTestPlotFile.csv", "w");
  fprintf(ofp, "n,t");
  fprintf(ofpK, "n,t");
  int pruebas = 1;

  struct Polynomial *poly1, *poly2, *poly3, *poly4;
  double prom_karatsuba, prom_decrease;

  /* for (int i = 4; i <= 1024; i = 2 * i) { */
  for (int i = 3; i <= 3; i = 2 * i) {

    int n = i-1;
    poly1 = generatePolynomial(n);
    poly2 = generatePolynomial(n);

    double time_spent;
    clock_t begin, end;

    time_spent = 0.0;
    for (int j = 0; j < pruebas; ++j) {
      begin = clock();
      poly3 = decreaseAndConquer(poly1, poly2);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
      /* printf("time elapsed is %f seconds\n", time_spent); */
    }
    prom_decrease = time_spent / pruebas;
    fprintf(ofp, "\n%d,%f", i, prom_decrease);

    time_spent = 0.0;
    for (int j = 0; j < pruebas; ++j) {
      poly1 = generatePolynomial(n);
      poly2 = generatePolynomial(n);
      begin = clock();
      poly4 = karatsuba(poly1, poly2);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
      /* printf("time elapsed is %f seconds\n", time_spent); */
    }
    prom_karatsuba = time_spent / pruebas;
    fprintf(ofpK, "\n%d,%f", i, prom_karatsuba);

    printPolynomial_nodes(poly3->head);
    printPolynomial_nodes(poly4->head);

    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(poly3);
    freePolynomial(poly4);
    /* printf("\n"); */
  }

  int fclose(FILE * ofp);
  int fclose(FILE * ofpK);
  return 0;
}
