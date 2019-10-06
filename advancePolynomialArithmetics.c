#include "advancePolynomialArithmetics3.h"
#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdlib.h>

int main() {
  struct Polynomial *poly1, *poly2;
  /* int n = 16383; */
  int n = 16383;

  poly1 = generatePolynomial(n);
  poly2 = generatePolynomial(n);

  /* printPolynomial(poly2); */
  /* printPolynomial(poly2); */
  /* struct Node *head_poly3 = NULL; */
  /* struct Node *tail_poly3 = NULL; */

  double time_spent = 0.0;

  clock_t begin = clock();

  /* struct Polynomial *poly3; */
  /* struct Polynomial *poly3 = decreaseAndConquer(poly1, poly2); */

  struct Polynomial *poly4 = divAndConquer(poly1, poly2, n + 1);

  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time elapsed is %f seconds\n", time_spent);
  /* struct Polynomial *poly3; */
  /* poly3 = decreaseAndConquer(poly1, poly2); */
  /* printPolynomial_nodes(head_poly3); */
  /* printPolynomial_nodes(poly3->head); */
  /* printPolynomial_nodes(poly4->head); */

  freePolynomial(poly1);
  freePolynomial(poly2);
  /* freePolynomial(poly3); */
  freePolynomial(poly4);
  printf("\n");
  return 0;
}
