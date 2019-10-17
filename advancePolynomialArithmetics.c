#include "advancePolynomialArithmetics2.h"
#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdlib.h>

int main() {
  /* test(); */
  struct Polynomial *poly1, *poly2, *poly5, *poly6;
  /* int n = 511; */
  /* int n = 1023; */
  int n = 16383;
  /* int n = 524287; */

  poly1 = generatePolynomial(n);
  poly2 = generatePolynomial(n);
  poly5 = generatePolynomial(n);
  poly6 = generatePolynomial(n);

  /* printPolynomial(poly1); */
  /* printPolynomial(poly2); */
  /* printf("hola\n"); */
  /* struct Node *head_poly3 = NULL; */
  /* struct Node *tail_poly3 = NULL; */

  double time_spent = 0.0;

  clock_t begin = clock();
  struct Polynomial *poly3 = decreaseAndConquer(poly5, poly6);
  /* struct Polynomial *poly4 = karatsuba(poly1, poly2); */
  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time elapsed is %f seconds\n", time_spent);

  time_spent = 0.0;

  begin = clock();
  /* struct Polynomial *poly3 = decreaseAndConquer(poly5, poly6); */
  struct Polynomial *poly4 = karatsuba(poly1, poly2);
  end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time elapsed is %f seconds\n", time_spent);

  /* printPolynomial_nodes(poly3->head); */
  /* printPolynomial_nodes(poly4->head); */

  freePolynomial(poly1);
  freePolynomial(poly2);
  freePolynomial(poly3);
  freePolynomial(poly4);
  freePolynomial(poly5);
  freePolynomial(poly6);
  printf("\n");
  return 0;
}
