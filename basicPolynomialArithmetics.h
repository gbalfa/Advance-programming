#ifndef BASICPOLYNOMIALARITHMETICS_H
#define BASICPOLYNOMIALARITHMETICS_H

#include <stdio.h>
#include <stdlib.h>

#include "doublyLinkedListPolynomial.h"

/**
 *  \brief Clones a Polynomial.
 *
 *  \param Polynomial.
 *  \return Polynomial.
 */
struct Polynomial *copyPolynomial(struct Polynomial list) {

  struct Node *tail = list.tail;

  struct Polynomial *new_list =
      (struct Polynomial *)malloc(sizeof(struct Polynomial));
  new_list->head = NULL;
  new_list->tail = NULL;

  while (tail != NULL) {
    push(new_list, tail->coeff, tail->exp);
    tail = tail->prev;
  }
  return new_list;
}

/**
 *  \brief Sums two polynomials.
 *
 *  Compares the degrees of the polinomials and overwrite the greatest one
 *  with the result.
 *
 *  \param Polynomials.
 *  \return A polynomial with the Sum of the polynomials.
 */
/* struct Polynomial *sumPolynomials(struct Polynomial* poly1, struct Polynomial* poly2) { */

/* } */

#endif /* BASICPOLYNOMIALARITHMETICS_H */
