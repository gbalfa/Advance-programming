#include "advancePolynomialArithmetics2.h"
#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdlib.h>

int main() {
  /* test(); */
  struct Polynomial *poly1, *poly2;
  int n = 3;
  /* int n = 524287; */

  poly1 = generatePolynomial(n);
  poly2 = generatePolynomial(n);

  printPolynomial(poly1);
  printPolynomial(poly2);
  /* printf("hola\n"); */
  /* struct Node *head_poly3 = NULL; */
  /* struct Node *tail_poly3 = NULL; */

  double time_spent = 0.0;

  clock_t begin = clock();

  /* struct Polynomial *poly3; */

  struct Polynomial *poly3 = decreaseAndConquer(poly1, poly2);
  struct Polynomial *poly4 = karatsuba(poly1, poly2);

  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time elapsed is %f seconds\n", time_spent);
  printPolynomial(poly3);
  printPolynomial(poly4);

  freePolynomial(poly1);
  freePolynomial(poly2);
  freePolynomial(poly3);
  freePolynomial(poly4);
  printf("\n");
  return 0;
}
