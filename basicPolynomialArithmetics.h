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
struct Polynomial *copyPolynomial(struct Polynomial *polynomial) {

  struct Node *tail = polynomial->tail;

  struct Polynomial *new_polynomial =
      (struct Polynomial *)malloc(sizeof(struct Polynomial));
  new_polynomial->head = NULL;
  new_polynomial->tail = NULL;
  new_polynomial->degree = polynomial->degree;

  while (tail != NULL) {
    push(new_polynomial, tail->coeff, tail->exp);
    tail = tail->prev;
  }
  return new_polynomial;
}

/**
 *  \brief Sums two polynomials.
 *
 *  Compares the degrees of the polinomials and overwrite the coefficients of
 *  the  greatest one with the sum result.
 *
 *  \param Polynomials.
 *  \return A polynomial with the Sum of the polynomials.
 */
struct Polynomial *addPolynomials(struct Polynomial* poly1, struct Polynomial* poly2) {
  struct Polynomial* lesser_poly;
  struct Polynomial* greatest_poly;
  if(poly1->degree > poly2->degree){
    greatest_poly = poly1;
    lesser_poly = poly2;
  } else {
    greatest_poly = poly2;
    lesser_poly = poly1;
  }
  struct Node* node_greatest_poly = greatest_poly->head;
  struct Node* node_lesser_poly = lesser_poly->head;
  while(node_lesser_poly != NULL){
    node_greatest_poly->coeff += node_lesser_poly->coeff;
    node_greatest_poly = node_greatest_poly->next;
    node_lesser_poly = node_lesser_poly->next;
  }
  return greatest_poly;
}

/**
 *  \brief Substract two polynomials.
 *
 *  Compares the degrees of the polinomials and overwrite the coefficients of
 *  the greatest one with the substract result.
 *
 *  \param Polynomials.
 *  \return A polynomial with the Sum of the polynomials.
 */
struct Polynomial *substractPolynomials(struct Polynomial* poly1, struct Polynomial* poly2) {
  struct Polynomial* lesser_poly;
  struct Polynomial* greatest_poly;
  if(poly1->degree > poly2->degree){
    greatest_poly = poly1;
    lesser_poly = poly2;
  } else {
    greatest_poly = poly2;
    lesser_poly = poly1;
  }
  struct Node* node_greatest_poly = greatest_poly->head;
  struct Node* node_lesser_poly = lesser_poly->head;
  while(node_lesser_poly != NULL){
    node_greatest_poly->coeff -= node_lesser_poly->coeff;
    node_greatest_poly = node_greatest_poly->next;
    node_lesser_poly = node_lesser_poly->next;
  }
  return greatest_poly;
}

#endif /* BASICPOLYNOMIALARITHMETICS_H */
