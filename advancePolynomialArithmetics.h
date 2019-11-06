#ifndef ADVANCEPOLYNOMIALARITHMETICS_H
#define ADVANCEPOLYNOMIALARITHMETICS_H

#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdlib.h>

/**
 *  \brief Create Node.
 */
struct Node *createNode(double new_coeff, int new_exp) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  /* put in the data  */
  new_node->coeff = new_coeff;
  new_node->exp = new_exp;
  return new_node;
}

/**
 *  \brief Push_nodes
 */
void pushNode(struct Node **head_ref, double new_coeff, int new_exp) {
  struct Node *new_node = createNode(new_coeff, new_exp);
  /* since we are adding at the beginning,
     prev is always NULL */
  new_node->prev = NULL;
  /* link the old node off the new node */
  new_node->next = (*head_ref);
  /* change prev of head node to new node */
  if ((*head_ref) != NULL)
    (*head_ref)->prev = new_node;
  /* move the head to point to the new node */
  (*head_ref) = new_node;
}

/**
 *  \brief Add polynomials poly1 and poly2 in a new polynomial.
 *
 *  poly1 degree <= poly2 degree
 *
 *  \param param
 *  \return return type
 */
struct Node *addPolynomial_nodes(struct Node *poly1, struct Node *poly2,
                                 int poly2_tail_exp) {
  struct Node *result = NULL;
  for (int i = poly2_tail_exp; i >= poly1->exp; --i) {
    pushNode(&result, 0, i);
  }
  struct Node *tmp0 = result, *tmp1 = poly1, *tmp2 = poly2;
  while (tmp1 != NULL && tmp1->exp < poly2->exp) {
    tmp0->coeff = tmp1->coeff;
    tmp0 = tmp0->next;
    tmp1 = tmp1->next;
  }
  while (tmp1 != NULL) {
    tmp0->coeff = tmp1->coeff + tmp2->coeff;
    tmp0 = tmp0->next;
    tmp1 = tmp1->next;
    tmp2 = tmp2->next;
  }
  while (tmp2 != NULL) {
    tmp0->coeff = tmp2->coeff;
    tmp0 = tmp0->next;
    tmp2 = tmp2->next;
  }
  return result;
}

/**
 *  \brief function description
 *
 *  Detailed description
 *
 *  \param param
 *  \return return type
 */
struct Node *decreaseAndConquer_forDAC(struct Node *poly1, struct Node *poly2,
                               int poly_tail_exp){
  struct Node *sum_pos, *head_sum_result, *factor1, *factor2, *start_sum_pos,
      *tail_sum;

  int result_degree = poly_tail_exp * 2;
  head_sum_result = NULL;
  for (int i = result_degree; i >= 0; --i) {
    pushNode(&head_sum_result, 0, i);
  }

  factor1 = poly1;
  factor2 = NULL;
  start_sum_pos = head_sum_result;
  sum_pos = NULL;
  while (factor1 != NULL) {
    sum_pos = start_sum_pos;
    factor2 = poly2;
    while (factor2 != NULL) {
      sum_pos->coeff += factor1->coeff * factor2->coeff;
      sum_pos = sum_pos->next;
      factor2 = factor2->next;
    }
    factor1 = factor1->next;
    tail_sum = start_sum_pos;
    start_sum_pos = start_sum_pos->next;
  }
  return head_sum_result;
}

/**
 *  \brief Multiply two Monomials and save the result on a external poly.
 *
 *  \params Node
 *  \return void
 */
void multiplyMonomials(struct Node *mono1, struct Node *mono2,
                       struct Node **pos) {
  int exp = mono1->exp + mono2->exp;
  struct Node *node = (*pos);

  if (exp < node->exp) {
    while (node != NULL && exp < node->exp) {
      node = node->prev;
      /* ++(*contador); */
    }
  } else {
    while (node != NULL && exp > node->exp) {
      node = node->next;
      /* ++(*contador); */
    }
  }
  node->coeff += mono1->coeff * mono2->coeff;
  node->exp = exp;

  (*pos) = node;
  return;
}

/**
 *  \brief Split a polynomial in two.
 */
void splitPolynomial_DAC(struct Node *head_poly, int new_k,
                         struct Node **first_half,
                         struct Node **first_half_tail,
                         struct Node **second_half) {
  struct Node *result_tail = NULL;

  struct Node *tmp = head_poly;
  for (int i = new_k; i > 0; --i) {
    result_tail = tmp;
    tmp = tmp->next;
  }
  result_tail->next = NULL;

  *first_half = head_poly;
  *first_half_tail = result_tail;
  *second_half = tmp;

  return;
}

/**
 *  \brief Recursive auxiliar function to do Inductive Divide and Conquer.
 */
void dAC(struct Node *poly1, struct Node *poly2, struct Node **pos, int k) {
  if (k == 1) {
    return multiplyMonomials(poly1, poly2, pos);
  }

  struct Node *first_half_poly1, *first_half_poly1_tail, *second_half_poly1,
      *first_half_poly2, *first_half_poly2_tail, *second_half_poly2;

  int new_k = k / 2;
  splitPolynomial_DAC(poly1, new_k, &first_half_poly1, &first_half_poly1_tail,
                      &second_half_poly1);
  splitPolynomial_DAC(poly2, new_k, &first_half_poly2, &first_half_poly2_tail,
                      &second_half_poly2);

  dAC(first_half_poly1, first_half_poly2, pos, new_k);
  dAC(first_half_poly1, second_half_poly2, pos, new_k);
  dAC(second_half_poly1, first_half_poly2, pos, new_k);
  dAC(second_half_poly1, second_half_poly2, pos, new_k);

  first_half_poly1_tail->next = second_half_poly1;
  first_half_poly2_tail->next = second_half_poly2;

  return;
}

/**
 *  \brief Inductive Divide and Conquer Polynomial multiplication.
 */
struct Polynomial *divideAndConquer(struct Polynomial *poly1,
                                    struct Polynomial *poly2) {
  int k = poly1->degree + 1;
  struct Polynomial *result;
  result = (struct Polynomial *)malloc(sizeof(struct Polynomial));
  result->head = NULL;
  result->tail = NULL;
  result->degree = poly1->degree + poly2->degree;
  for (int i = result->degree; i >= 0; --i) {
    push(result, 0, i);
  }
  struct Node *pos = result->head;

  dAC(poly1->head, poly2->head, &pos, k);

  return result;
}

/**
 *  \brief Split a polynomial in two parts and decrease the exponents.
 *
 *  Decrease the exponents of the greatest resultant polynomial by a new_k
 *  factor.
 */
void splitPolynomial_karatsuba(struct Node *head_poly, int new_k,
                               struct Node **first_half,
                               struct Node **first_half_tail,
                               struct Node **second_half,
                               struct Node **second_half_tail) {
  struct Node *result_tail = NULL;

  struct Node *tmp = head_poly;
  for (int i = new_k; i > 0; --i) {
    result_tail = tmp;
    tmp = tmp->next;
    /* ++(*contador); */
  }
  result_tail->next = NULL;
  (*first_half) = head_poly;
  (*first_half_tail) = result_tail;
  (*second_half) = tmp;

  for (int i = new_k; i > 0; --i) {
    tmp->exp -= new_k;
    result_tail = tmp;
    tmp = tmp->next;
  }
  (*second_half_tail) = result_tail;
  return;
}

/**
 *  \brief Add Karatsuba polynomial addends.
 */
struct Node *addPolynomialNodes_karatsuba(struct Node *A0B0,
                                          struct Node *third,
                                          struct Node *A1B1, int k,
                                          int new_k) {
  struct Node *tmp0, *tmp1, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6,
      *special_tail_1, *special_tail_2;

  tmp0 = A0B0;
  while (tmp0 != NULL && tmp0->exp < third->exp + new_k) {
    special_tail_1 = tmp0;
    tmp0 = tmp0->next;
  }
  tmp1 = third;
  tmp2 = tmp0;
  while (tmp2 != NULL) {
    tmp1->coeff += tmp2->coeff;
    tmp1->exp = tmp2->exp;
    tmp1 = tmp1->next;
    tmp2 = tmp2->next;
  }
  tmp3 = tmp1;
  while (tmp3 != NULL && tmp3->exp + new_k < A1B1->exp + k) {
    tmp3->exp += new_k;
    special_tail_2 = tmp3;
    tmp3 = tmp3->next;
  }
  tmp4 = A1B1;
  tmp5 = tmp3;
  while (tmp5 != NULL) {
    tmp4->coeff += tmp5->coeff;
    tmp4->exp = tmp5->exp + new_k;
    tmp4 = tmp4->next;
    tmp5 = tmp5->next;
  }
  tmp6 = tmp4;
  while (tmp6 != NULL) {
    tmp6->exp += k;
    tmp6 = tmp6->next;
  }
  special_tail_1->next = third;
  freePolynomial_nodes(tmp0);
  special_tail_2->next = A1B1;
  freePolynomial_nodes(tmp3);

  return A0B0;
}

/**
 *  \brief Subtract A0B0 and A1B1 from poly.
 */
struct Node *subtractA0B0_A1B1(struct Node *poly, struct Node *A0B0, struct Node *A1B1){
  struct Node *tmp0, *tmp1, *tmp2;
  tmp0 = poly;
  tmp1 = A0B0;
  tmp2 = A1B1;
  while (tmp0 != NULL) {
    tmp0->coeff -= tmp1->coeff + tmp2->coeff;
    tmp0 = tmp0->next;
    tmp1 = tmp1->next;
    tmp2 = tmp2->next;
  }
  return poly;
}

/**
 *  \brief Karatsuba recursive auxiliar function.
 */
struct Node *dAC_karatsuba(struct Node *poly1, struct Node *poly2, int poly2_tail_exp, int k, int special_k) {
  if (k <= special_k) {
    return decreaseAndConquer_forDAC(poly1, poly2, poly2_tail_exp);
  }

  struct Node *first_half_poly1, *first_half_poly1_tail, *second_half_poly1,
      *second_half_poly1_tail, *first_half_poly2, *first_half_poly2_tail,
      *second_half_poly2, *second_half_poly2_tail;

  int new_k = k / 2;
  splitPolynomial_karatsuba(poly1, new_k, &first_half_poly1,
                            &first_half_poly1_tail, &second_half_poly1,
                            &second_half_poly1_tail);
  splitPolynomial_karatsuba(poly2, new_k, &first_half_poly2,
                            &first_half_poly2_tail, &second_half_poly2,
                            &second_half_poly2_tail);

  struct Node *sumA0A1 = addPolynomial_nodes(
      first_half_poly1, second_half_poly1, second_half_poly1_tail->exp);
  struct Node *sumB0B1 = addPolynomial_nodes(
      first_half_poly2, second_half_poly2, second_half_poly2_tail->exp);
  //
  int exp = first_half_poly1_tail->exp;
  struct Node *A0B0, *A1B1, *third, *result;
  A0B0 = dAC_karatsuba(first_half_poly1, first_half_poly2, exp, new_k, special_k);
  A1B1 = dAC_karatsuba(second_half_poly1, second_half_poly2, exp, new_k, special_k);
  third = subtractA0B0_A1B1(dAC_karatsuba(sumA0A1, sumB0B1, exp ,new_k, special_k), A0B0, A1B1);

  result = addPolynomialNodes_karatsuba(A0B0, third, A1B1, k, new_k);

  freePolynomial_nodes(sumA0A1);
  freePolynomial_nodes(sumB0B1);
  first_half_poly1_tail->next = second_half_poly1;
  first_half_poly2_tail->next = second_half_poly2;
  return A0B0;
}

/**
 *  \brief Karatsuba.
 */
struct Polynomial *karatsuba(struct Polynomial *poly1,
                             struct Polynomial *poly2) {
  int k = poly1->degree + 1;
  struct Polynomial *result;
  result = (struct Polynomial *)malloc(sizeof(struct Polynomial));
  result->head = NULL;
  result->tail = NULL;
  result->degree = poly1->degree + poly2->degree;

  result->head = dAC_karatsuba(poly1->head, poly2->head, poly2->degree, k, 256);

  return result;
}

#endif /* ADVANCEPOLYNOMIALARITHMETICS_H */
