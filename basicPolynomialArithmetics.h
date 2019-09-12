#ifndef BASICPOLYNOMIALARITHMETICS_H
#define BASICPOLYNOMIALARITHMETICS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "doublyLinkedListPolynomial.h"
#include "polynomialsLinkedList.h"

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
struct Polynomial *addPolynomials(struct Polynomial *poly1,
                                  struct Polynomial *poly2) {
  struct Polynomial *lesser_poly;
  struct Polynomial *greatest_poly;
  if (poly1->degree > poly2->degree) {
    greatest_poly = poly1;
    lesser_poly = poly2;
  } else {
    greatest_poly = poly2;
    lesser_poly = poly1;
  }
  struct Node *node_greatest_poly = greatest_poly->head;
  struct Node *node_lesser_poly = lesser_poly->head;
  while (node_lesser_poly != NULL) {
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
 *  the greatest one with the difference poly1 - poly2.
 *
 *  \param Polynomials.
 *  \return A polynomial with the Sum of the polynomials.
 */
struct Polynomial *subtractPolynomials(struct Polynomial *poly1,
                                       struct Polynomial *poly2) {
  struct Polynomial *greatest_poly;
  struct Node *node_greatest_poly;
  struct Node *node_lesser_poly;
  if (poly1->degree >= poly2->degree) {
    greatest_poly = poly1;
    node_lesser_poly = poly2->head;
    node_greatest_poly = greatest_poly->head;
    while (node_lesser_poly != NULL) {
      node_greatest_poly->coeff -= node_lesser_poly->coeff;
      node_greatest_poly = node_greatest_poly->next;
      node_lesser_poly = node_lesser_poly->next;
    }
  } else {
    greatest_poly = poly2;
    node_lesser_poly = poly1->head;
    node_greatest_poly = greatest_poly->head;
    while (node_lesser_poly != NULL) {
      node_greatest_poly->coeff =
          node_lesser_poly->coeff - node_greatest_poly->coeff;
      node_greatest_poly = node_greatest_poly->next;
      node_lesser_poly = node_lesser_poly->next;
    }
    while (node_greatest_poly != NULL) {
      node_greatest_poly->coeff *= -1;
      node_greatest_poly = node_greatest_poly->next;
    }
  }
  return greatest_poly;
}

/**
 *  \brief Brute Force Polynomials product.
 *
 *  Multiplies two polynomials.
 *
 *  \param poly1 Polynomial
 *  \param poly2 Polynomial
 *  \return product Polynomial
 */
struct Polynomial *multiplyPolynomials(struct Polynomial *poly1,
                                       struct Polynomial *poly2) {
  struct Node *node_poly1 = poly1->tail;
  struct Node *node_poly2 = poly2->tail;

  struct PolynomialsLinkedListNode *list = NULL;

  /* each monomial of poly1 multiplicated by every poly2 monomial */
  int i = poly1->degree;
  while (node_poly1 != NULL) {
    struct Polynomial *new_poly =
        (struct Polynomial *)malloc(sizeof(struct Polynomial));
    new_poly->head = NULL;
    new_poly->tail = NULL;
    new_poly->degree = poly2->degree + i;
    node_poly2 = poly2->tail;
    int j = new_poly->degree; /* exponents */
    while (node_poly2 != NULL) {
      push(new_poly, node_poly1->coeff * node_poly2->coeff, j);
      node_poly2 = node_poly2->prev;
      --j;
    }
    push2(&list, new_poly);
    node_poly1 = node_poly1->prev;
    --i;
  }
  /* Create result polynomial */
  struct Polynomial *result =
      (struct Polynomial *)malloc(sizeof(struct Polynomial));
  result->head = NULL;
  result->tail = NULL;
  result->degree = poly1->degree + poly2->degree;
  int exponent = result->degree;
  for (int i = result->degree; i >= 0; --i) {
    push(result, 0, exponent);
    --exponent;
  }
  /* Add Polynomials */
  struct Node *node_result = result->head;
  struct Node *node_poly;
  struct PolynomialsLinkedListNode *tmp_list = list;
  while (tmp_list != NULL) {
    node_result = result->head;
    node_poly = tmp_list->poly->head;
    for (int i = tmp_list->poly->head->exp; i > 0; --i) {
      node_result = node_result->next;
    }
    struct Node *tmp_node_result = node_result;
    while (node_poly != NULL) {
      tmp_node_result->coeff += node_poly->coeff;
      tmp_node_result = tmp_node_result->next;
      node_poly = node_poly->next;
    }
    tmp_list = tmp_list->next;
  }
  freePolynomialsList(list);
  return result;
}
struct Polynomial *decreaseAndConquer(struct Polynomial *Poly1, struct Polynomial *Poly2){
  struct Polynomial *Result;
  Result = (struct Polynomial*)malloc(sizeof(struct Polynomial));
  Result->head = NULL;
  Result->tail = NULL;
  Result->degree = Poly1->degree + Poly2->degree;
  for (int i=Result->degree ;i>=0 ;--i){
    push(Result, 0, i);
  }
  struct Node *Factor1 = Poly1->tail;
  struct Node *Factor2 = Poly2->tail;
  struct Node *Position = Result->tail;
  struct Node *Temp = Result->tail;
  while(Factor1 != NULL){
      Position = Temp;
      Factor2 = Poly2->tail;
    while(Factor2 != NULL){
      Position->coeff +=  Factor1->coeff * Factor2->coeff;
      Position = Position->prev;
      Factor2 = Factor2->prev;
    }
    Factor1 = Factor1->prev;
    Temp = Temp->prev;
  }
  return Result;
}


#endif /* BASICPOLYNOMIALARITHMETICS_H */
