#ifndef ADVANCEPOLYNOMIALARITHMETICS_H
#define ADVANCEPOLYNOMIALARITHMETICS_H

#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdlib.h>

/**
 *  Append a node into a polynomial.
 *
 *  Function to insert a polynomial node at the end of the Doubly Linked
 *  List.
 *
 *  @poly Polinomial struct.
 *  @new_coeff Monomial coefficient.
 *  @new_exp Monomial exponent.
 */
void append_node(struct Node **head_poly, struct Node **tail_poly,
                 double new_coeff, int new_exp) {
  /* allocate node */
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  /* put in the data  */
  new_node->coeff = new_coeff;
  new_node->exp = new_exp;

  /* since we are adding at the end,
     next is always NULL */
  new_node->next = NULL;

  /* link the old node off the new node */
  new_node->prev = (*tail_poly);

  /* change next of tail node to new node */
  if ((*tail_poly) != NULL)
    (*tail_poly)->next = new_node;

  /* move the tail to point to the new node */
  (*tail_poly) = new_node;

  /* link the head  */
  if ((*head_poly) == NULL) {
    (*head_poly) = (*tail_poly);
  }
}

/**
 *  \brief Add polynomial nodes in poly1 and delete poly2.
 *
 *  \param param
 *  \return return type
 */
struct Node *addPolynomial_nodes(struct Node *poly1, struct Node *poly2) {
  struct Node *tmp = poly1, *tmp1 = poly2;
  while (tmp != NULL && tmp1 != NULL) {
    tmp->coeff += tmp1->coeff;
    tmp = tmp->next;
    tmp1 = tmp1->next;
  }
  freePolynomial_nodes(poly2);
  return poly1;
}

/**
 *  \brief Add polynomial nodes in poly1 and delete poly2.
 *
 *  \param param
 *  \return return type
 */
struct Node *substractPolynomial_nodes(struct Node *poly1, struct Node *poly2) {
  struct Node *tmp = poly1, *tmp1 = poly2;
  while (tmp != NULL && tmp1 != NULL) {
    tmp->coeff -= tmp1->coeff;
    tmp = tmp->next;
    tmp1 = tmp1->next;
  }
  freePolynomial_nodes(poly2);
  return poly1;
}

/**
 *  \brief Add polynomial nodes in poly1 and delete poly2.
 *
 *  \param param
 *  \return return type
 */
struct Node *addIncompletePolynomial_nodes(struct Node *poly1, struct Node *poly2) {
  struct Node *tmp = poly1, *tmp1 = poly2, *tail = tmp;
  while (tmp != NULL && tmp->exp < poly2->exp ) {
    tail = tmp;
    tmp = tmp->next;
  }
  while (tmp != NULL && tmp1 != NULL) {
    tmp->coeff += tmp1->coeff;
    tmp = tmp->next;
    tmp1 = tmp1->next;
  }
  while(tmp1 != NULL){

  }
  freePolynomial_nodes(poly2);
  return poly1;
}

/**
 *  \brief Multiply two Monomials.
 *
 *  \params Node
 *  \return Node
 */
struct Node *multiplyMonomials(struct Node *mono1, struct Node *mono2) {
  struct Node *result = (struct Node *)malloc(sizeof(struct Node));
  result->coeff = mono1->coeff * mono2->coeff;
  result->exp = mono1->exp + mono2->exp;
  result->next = NULL;
  result->prev = NULL;
  /* freePolynomial_nodes(mono1); */
  /* freePolynomial_nodes(mono2); */
  return result;
}

void splitPolynomial(struct Node *head_poly, int new_k,
                     struct Node **first_half, struct Node **second_half) {
  /* printf("%d %s\n",k,"polytoSplit:"); */
  /* printPolynomial_nodes(head_poly); */
  struct Node *result_head = NULL;
  struct Node *result_tail = NULL;

  struct Node *tmp = head_poly;
  for (int i = new_k; i > 0; --i) {
    /* append */
    append_node(&result_head, &result_tail, tmp->coeff, tmp->exp);

    tmp = tmp->next;
  }

  struct Node *result_head2 = NULL;
  struct Node *result_tail2 = NULL;

  for (int i = new_k; i > 0; --i) {
    /* append */
    append_node(&result_head2, &result_tail2, tmp->coeff, tmp->exp - new_k);
    tmp = tmp->next;
  }
  *first_half = result_head;
  *second_half = result_head2;
  /* printf("%d %s\n",k,"polytoSplitResult:"); */
  /* printPolynomial_nodes(result_head); */
  /* printf("%d %s\n",k,"secondPolytoSplitResult:"); */
  /* printPolynomial_nodes(result_head2); */

  /* freePolynomial_nodes(head_poly); */
  return;
}

/**
 *  \brief Copy a Polynomial (only nodes from head to exp).
 *
 *  From Polynomial->head to Polynomial->n->exp. [].
 *
 *  \param Polynomial.
 *  \return Polynomial.
 */
struct Node *copyPolynomialUpToExp(struct Node *head_poly, int exp,
                                   struct Node **ref_result_tail, int i) {

  struct Node *result_head = NULL;
  struct Node *result_tail = NULL;

  struct Node *tmp = head_poly;
  // Copy until reach the monomial with exponent exp.
  while (tmp != NULL && tmp->exp <= exp) {
    /* append */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->next = NULL;
    new_node->prev = result_tail;
    new_node->coeff = tmp->coeff;
    new_node->exp = tmp->exp + i;
    if (result_head == NULL) {
      result_head = new_node;
      result_tail = result_head;
    } else {
      result_tail->next = new_node;
      result_tail = new_node;
    }
    tmp = tmp->next;
  }
  (*ref_result_tail) = result_tail;
  return result_head;
}

/**
 *  \brief Sum 4 polynomials of divide and conquer.
 *
 *  Multiply poly3 by X^k and poly21-poly22 by X^new_k while adding.
 *
 *  \return A polynomial with the Sum of the polynomials.
 */
struct Node *addPolynomialNodes_DivideAndConquer(struct Node *poly1,
                                                 struct Node *poly21,
                                                 struct Node *poly22,
                                                 struct Node *poly3, int k,
                                                 int new_k) {
  /* printf("%s\n", "polys to sum:"); */
  /* printPolynomial_nodes(poly3); */
  /* printPolynomial_nodes(poly21); */
  /* printPolynomial_nodes(poly1); */
  struct Node *tmp0, *tmp1, *tmp12, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6,
      *special_tail_1, *special_tail_2, *special_tail_3;

  tmp0 = poly1;
  while (tmp0 != NULL && tmp0->exp < poly21->exp + new_k) {
    /* printf("%d\n", poly21->exp + new_k); */
    /* printf("%d\n", tmp0->exp); */
    special_tail_1 = tmp0;
    tmp0 = tmp0->next;
  }
  //
  tmp1 = poly21;
  tmp12 = poly22;
  tmp2 = tmp0;
  while (tmp2 != NULL) {
    tmp1->coeff += tmp2->coeff + tmp12->coeff;
    tmp1->exp = tmp2->exp;
    tmp1 = tmp1->next;
    tmp12 = tmp12->next;
    tmp2 = tmp2->next;
  }
  //
  tmp3 = tmp1;
  while (tmp3 != NULL && tmp3->exp + new_k < poly3->exp + k) {
    tmp3->exp += new_k;
    tmp3->coeff += tmp12->coeff;
    special_tail_2 = tmp3;
    tmp3 = tmp3->next;
    tmp12 = tmp12->next;
  }
  //
  tmp4 = poly3;
  tmp5 = tmp3;
  while (tmp5 != NULL) {
    tmp4->coeff += tmp5->coeff + tmp12->coeff;
    tmp4->exp = tmp5->exp + new_k;
    special_tail_3 = tmp4;
    tmp4 = tmp4->next;
    tmp5 = tmp5->next;
    tmp12 = tmp12->next;
  }
  //
  tmp6 = tmp4;
  while (tmp6 != NULL) {
    tmp6->exp += k;
    tmp6 = tmp6->next;
  }

  special_tail_1->next = poly21;
  freePolynomial_nodes(tmp0);
  special_tail_2->next = poly3;
  freePolynomial_nodes(tmp3);

  freePolynomial_nodes(poly22);

  if (special_tail_3 != NULL && special_tail_3->prev != NULL) {
    special_tail_3->next = NULL;
    freePolynomial_nodes(poly3);
  }
  return poly1;
}

/**
 *  \brief Inductive Divide and Conquer Polynomial multiplication.
 */
struct Node *divAndConquer(struct Node *poly1, struct Node *poly2, int k) {
  /* printf("%s\n", "polyss:"); */
  /* printPolynomial_nodes(poly1); */
  /* printPolynomial_nodes(poly2); */
  if (k == 1) {
    return multiplyMonomials(poly1, poly2);
  }

  struct Node *first_half_poly1, *second_half_poly1, *first_half_poly2,
      *second_half_poly2;

  int new_k = k / 2;
  splitPolynomial(poly1, new_k, &first_half_poly1, &second_half_poly1);
  splitPolynomial(poly2, new_k, &first_half_poly2, &second_half_poly2);

  struct Node *result = addPolynomialNodes_DivideAndConquer(
      divAndConquer(first_half_poly1, first_half_poly2, new_k),
      divAndConquer(first_half_poly1, second_half_poly2, new_k),
      divAndConquer(second_half_poly1, first_half_poly2, new_k),
      divAndConquer(second_half_poly1, second_half_poly2, new_k), k, new_k);

  freePolynomial_nodes(first_half_poly1);
  freePolynomial_nodes(second_half_poly1);
  freePolynomial_nodes(first_half_poly2);
  freePolynomial_nodes(second_half_poly2);

  return result;
}

/**
 *  \brief Sum 3 polynomials of divide and conquer.
 *
 *  Multiply poly1 by X^k and poly21-poly22 by X^new_k while adding.
 *
 *  \return A polynomial with the Sum of the polynomials.
 */
struct Node *addPolynomialNodes_karatsuba(struct Node *poly1,
                                          struct Node *poly21,
                                          struct Node *poly22,
                                          struct Node *poly3, int k,
                                          int new_k) {
  /* printf("%s\n", "polys to sum:"); */
  /* printPolynomial_nodes(poly3); */
  /* printPolynomial_nodes(poly21); */
  /* printPolynomial_nodes(poly1); */
  struct Node *tmp0, *tmp1, *tmp12, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6,
      *special_tail_1, *special_tail_2, *special_tail_3;

  tmp0 = poly1;
  while (tmp0 != NULL && tmp0->exp < poly21->exp + new_k) {
    /* printf("%d\n", poly21->exp + new_k); */
    /* printf("%d\n", tmp0->exp); */
    special_tail_1 = tmp0;
    tmp0 = tmp0->next;
  }
  //
  tmp1 = poly21;
  tmp12 = poly22;
  tmp2 = tmp0;
  while (tmp2 != NULL) {
    tmp1->coeff += tmp2->coeff + tmp12->coeff;
    tmp1->exp = tmp2->exp;
    tmp1 = tmp1->next;
    tmp12 = tmp12->next;
    tmp2 = tmp2->next;
  }
  //
  tmp3 = tmp1;
  while (tmp3 != NULL && tmp3->exp + new_k < poly3->exp + k) {
    tmp3->exp += new_k;
    tmp3->coeff += tmp12->coeff;
    special_tail_2 = tmp3;
    tmp3 = tmp3->next;
    tmp12 = tmp12->next;
  }
  //
  tmp4 = poly3;
  tmp5 = tmp3;
  while (tmp5 != NULL) {
    tmp4->coeff += tmp5->coeff + tmp12->coeff;
    tmp4->exp = tmp5->exp + new_k;
    special_tail_3 = tmp4;
    tmp4 = tmp4->next;
    tmp5 = tmp5->next;
    tmp12 = tmp12->next;
  }
  //
  tmp6 = tmp4;
  while (tmp6 != NULL) {
    tmp6->exp += k;
    tmp6 = tmp6->next;
  }

  special_tail_1->next = poly21;
  freePolynomial_nodes(tmp0);
  special_tail_2->next = poly3;
  freePolynomial_nodes(tmp3);

  freePolynomial_nodes(poly22);

  if (special_tail_3 != NULL && special_tail_3->prev != NULL) {
    special_tail_3->next = NULL;
    freePolynomial_nodes(poly3);
  }
  return poly1;
}

/**
 *  \brief Variant of Divide and Conquer algorithm for Polynomial
 * multiplication.
 */
struct Node *karatsuba(struct Node *poly1, struct Node *poly2, int k) {
  /* printf("%s\n", "polyss:"); */
  /* printPolynomial_nodes(poly1); */
  /* printPolynomial_nodes(poly2); */
  if (k == 1) {
    return multiplyMonomials(poly1, poly2);
  }

  struct Node *first_half_poly1, *second_half_poly1, *first_half_poly2,
      *second_half_poly2;

  int new_k = k / 2;
  splitPolynomial(poly1, new_k, &first_half_poly1, &second_half_poly1);
  splitPolynomial(poly2, new_k, &first_half_poly2, &second_half_poly2);

  struct Node *productA0B0 = karatsuba(first_half_poly1, first_half_poly2, k);
  struct Node *productA1B1 = karatsuba(second_half_poly1, second_half_poly2, k);
  struct Node *productOfsumsA0A1_B0B1 = karatuba(

  /* struct Node *result = addIncompletePolynomialNodes_x( */

  freePolynomial_nodes(first_half_poly1);
  freePolynomial_nodes(second_half_poly1);
  freePolynomial_nodes(first_half_poly2);
  freePolynomial_nodes(second_half_poly2);

  return result;
}

#endif /* ADVANCEPOLYNOMIALARITHMETICS_H */
