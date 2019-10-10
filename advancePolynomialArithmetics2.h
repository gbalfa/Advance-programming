#ifndef ADVANCEPOLYNOMIALARITHMETICS_H
#define ADVANCEPOLYNOMIALARITHMETICS_H

#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdlib.h>

/* /\** */
/*  *  \brief Add polynomial nodes in poly1 and delete poly2. */
/*  * */
/*  *  \param param */
/*  *  \return return type */
/*  *\/ */
/* struct Node *addPolynomial_nodes(struct Node *poly1, struct Node *poly2) { */
/*   struct Node *tmp = poly1, *tmp1 = poly2; */
/*   while (tmp != NULL && tmp1 != NULL) { */
/*     tmp->coeff += tmp1->coeff; */
/*     tmp = tmp->next; */
/*     tmp1 = tmp1->next; */
/*   } */
/*   freePolynomial_nodes(poly2); */
/*   return poly1; */
/* } */

/* /\** */
/*  *  \brief Add polynomial nodes in poly1 and delete poly2. */
/*  * */
/*  *  \param param */
/*  *  \return return type */
/*  *\/ */
/* struct Node *substractPolynomial_nodes(struct Node *poly1, struct Node *poly2) { */
/*   struct Node *tmp = poly1, *tmp1 = poly2; */
/*   while (tmp != NULL && tmp1 != NULL) { */
/*     tmp->coeff -= tmp1->coeff; */
/*     tmp = tmp->next; */
/*     tmp1 = tmp1->next; */
/*   } */
/*   freePolynomial_nodes(poly2); */
/*   return poly1; */
/* } */

/**
 *  \brief Multiply two Monomials.
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
    }
  } else {
    while (node != NULL && exp > node->exp ) {
      node = node->next;
    }
  }
  node->coeff += mono1->coeff * mono2->coeff;
  node->exp = exp;

  (*pos) = node;
  return;
}

void splitPolynomial(struct Node *head_poly, int new_k,
                     struct Node **first_half, struct Node **first_half_tail,
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
 *  \brief Inductive Divide and Conquer Polynomial multiplication.
 */
void dAC(struct Node *poly1, struct Node *poly2, struct Node **pos, int k) {
  /* printf("%s\n", "polyss:"); */
  /* printPolynomial_nodes(poly1); */
  /* printPolynomial_nodes(poly2); */
  if (k == 1) {
    return multiplyMonomials(poly1, poly2, pos);
  }

  struct Node *first_half_poly1, *first_half_poly1_tail, *second_half_poly1,
      *first_half_poly2, *first_half_poly2_tail, *second_half_poly2;

  int new_k = k / 2;
  splitPolynomial(poly1, new_k, &first_half_poly1, &first_half_poly1_tail,
                  &second_half_poly1);
  splitPolynomial(poly2, new_k, &first_half_poly2, &first_half_poly2_tail,
                  &second_half_poly2);

  struct Node *extra_pos;

  dAC(first_half_poly1, first_half_poly2, pos, new_k);
  extra_pos = (*pos); //
  dAC(first_half_poly1, second_half_poly2, &extra_pos, new_k);
  dAC(second_half_poly1, first_half_poly2, pos, new_k);
  dAC(second_half_poly1, second_half_poly2, pos, new_k);

  first_half_poly1_tail->next = second_half_poly1;
  first_half_poly2_tail->next = second_half_poly2;

  return;
}

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
 *  \brief Create Node.
 */
struct Node *createNode(double new_coeff, int new_exp){
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  /* put in the data  */
  new_node->coeff = new_coeff;
  new_node->exp = new_exp;
  return new_node;
}

/**
 *  \brief Push_nodes
 */
void pushNode(struct Node **head_ref, double new_coeff, int new_exp){
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
 *  \brief Karatsuba.
 */
void dAC_karatsuba(struct Node *poly1, struct Node *poly2, struct Node **pos, int k) {
  /* printf("%s\n", "polyss:"); */
  /* printPolynomial_nodes(poly1); */
  /* printPolynomial_nodes(poly2); */
  if (k == 1) {
    return multiplyMonomials(poly1, poly2, pos);
  }

  struct Node *first_half_poly1, *first_half_poly1_tail, *second_half_poly1,
      *first_half_poly2, *first_half_poly2_tail, *second_half_poly2;

  int new_k = k / 2;
  splitPolynomial(poly1, new_k, &first_half_poly1, &first_half_poly1_tail,
                  &second_half_poly1);
  splitPolynomial(poly2, new_k, &first_half_poly2, &first_half_poly2_tail,
                  &second_half_poly2);

  struct Node *extra_pos;

  dAC(first_half_poly1, first_half_poly2, pos, new_k);
  extra_pos = (*pos); //
  dAC(first_half_poly1, second_half_poly2, &extra_pos, new_k);
  dAC(second_half_poly1, first_half_poly2, pos, new_k);
  dAC(second_half_poly1, second_half_poly2, pos, new_k);

  first_half_poly1_tail->next = second_half_poly1;
  first_half_poly2_tail->next = second_half_poly2;

  return;
}

struct Polynomial *karatsuba(struct Polynomial *poly1,
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

  dAC_karatsuba(poly1->head, poly2->head, &pos, k);

  return result;
}

/* /\** */
/*  *  \brief Sum 4 polynomials of divide and conquer. */
/*  * */
/*  *  Multiply poly3 by X^k and poly21-poly22 by X^new_k while adding. */
/*  * */
/*  *  \return A polynomial with the Sum of the polynomials. */
/*  *\/ */
/* struct Node *addPolynomialNodes_DivideAndConquer( */
/*     struct Node *poly1, struct Node *tail_poly1, struct Node *poly21, */
/*     struct Node *tail_poly21, struct Node *poly22, struct Node
 * *tail_poly22,
 */
/*     struct Node *poly3) { */
/*   /\* printf("%s\n", "polys to sum:"); *\/ */
/*   /\* printPolynomial_nodes(poly3); *\/ */
/*   /\* printPolynomial_nodes(poly21); *\/ */
/*   /\* printPolynomial_nodes(poly22); *\/ */
/*   /\* printPolynomial_nodes(poly1); *\/ */
/*   struct Node *tmp0, *tmp1, *tmp12, *tmp2, *tmp3, *tmp4, *tmp5,
 * *special_tail_1, */
/*       *special_tail_2, *special_tail_3; */

/*   tmp0 = tail_poly1; */
/*   while (tmp0 != NULL && tmp0->exp >= poly21->exp) { */
/*     /\* printf("%d\n", poly21->exp + new_k); *\/ */
/*     /\* printf("%d\n", tmp0->exp); *\/ */
/*     tmp0 = tmp0->prev; */
/*   } */
/*   special_tail_1 = tmp0; */
/*   // */
/*   tmp1 = poly21; */
/*   tmp12 = poly22; */
/*   tmp2 = tmp0->next; */
/*   while (tmp2 != NULL) { */
/*     tmp1->coeff += tmp2->coeff + tmp12->coeff; */
/*     /\* tmp1->exp = tmp2->exp; *\/ */
/*     tmp1 = tmp1->next; */
/*     tmp12 = tmp12->next; */
/*     tmp2 = tmp2->next; */
/*   } */
/*   // */
/*   tmp3 = tmp1; */
/*   while (tmp3 != NULL && tmp3->exp < poly3->exp) { */
/*     /\* tmp3->exp += new_k; *\/ */
/*     tmp3->coeff += tmp12->coeff; */
/*     special_tail_2 = tmp3; */
/*     tmp3 = tmp3->next; */
/*     tmp12 = tmp12->next; */
/*   } */
/*   // */
/*   // */
/*   tmp4 = poly3; */
/*   tmp5 = tmp3; */
/*   while (tmp5 != NULL) { */
/*     tmp4->coeff += tmp5->coeff + tmp12->coeff; */
/*     /\* tmp4->exp = tmp5->exp + new_k; *\/ */
/*     special_tail_3 = tmp4; */
/*     tmp4 = tmp4->next; */
/*     tmp5 = tmp5->next; */
/*     tmp12 = tmp12->next; */
/*   } */
/*   // */
/*   /\* tmp6 = tmp4; *\/ */
/*   /\* while (tmp6 != NULL) { *\/ */
/*   /\*   /\\* tmp6->exp += k; *\\/ *\/ */
/*   /\*   tmp6 = tmp6->next; *\/ */
/*   /\* } *\/ */
/*   /\* printPolynomial_nodes(special_tail_1); *\/ */
/*   /\* printPolynomial_nodes(special_tail_2); *\/ */
/*   /\* printPolynomial_nodes(poly21); *\/ */

/*   freePolynomial_nodes(special_tail_1->next); */
/*   special_tail_1->next = poly21; */
/*   poly21->prev = special_tail_1; */

/*   freePolynomial_nodes(special_tail_2->next); */
/*   special_tail_2->next = poly3; */
/*   poly3->prev = special_tail_2; */

/*   freePolynomial_nodes(poly22); */

/*   /\* if (special_tail_3 != NULL && special_tail_3->prev != NULL) { *\/ */
/*   /\*   if (special_tail_3->next != NULL) { *\/ */
/*   /\*     special_tail_3->next->prev = NULL; *\/ */
/*   /\*   } *\/ */
/*   /\*   special_tail_3->next = NULL; *\/ */
/*   /\*   freePolynomial_nodes(poly3); *\/ */
/*   /\* } *\/ */
/*   /\* printPolynomial_nodes(poly1); *\/ */
/*   /\* printPolynomial_nodes(poly3); *\/ */

/*   return poly1; */
/* } */

/* /\** */
/*  *  \brief Sum 3 polynomials of divide and conquer. */
/*  * */
/*  *  Multiply poly1 by X^k and poly21-poly22 by X^new_k while adding. */
/*  * */
/*  *  \return A polynomial with the Sum of the polynomials. */
/*  *\/ */
/* struct Node *addPolynomialNodes_karatsuba(struct Node *poly1, */
/*                                           struct Node *poly21, */
/*                                           struct Node *poly22, */
/*                                           struct Node *poly3, int k, */
/*                                           int new_k) { */
/*   /\* printf("%s\n", "polys to sum:"); *\/ */
/*   /\* printPolynomial_nodes(poly3); *\/ */
/*   /\* printPolynomial_nodes(poly21); *\/ */
/*   /\* printPolynomial_nodes(poly1); *\/ */
/*   struct Node *tmp0, *tmp1, *tmp12, *tmp2, *tmp3, *tmp4, *tmp5, *tmp6, */
/*       *special_tail_1, *special_tail_2, *special_tail_3; */

/*   tmp0 = poly1; */
/*   while (tmp0 != NULL && tmp0->exp < poly21->exp + new_k) { */
/*     /\* printf("%d\n", poly21->exp + new_k); *\/ */
/*     /\* printf("%d\n", tmp0->exp); *\/ */
/*     special_tail_1 = tmp0; */
/*     tmp0 = tmp0->next; */
/*   } */
/*   // */
/*   tmp1 = poly21; */
/*   tmp12 = poly22; */
/*   tmp2 = tmp0; */
/*   while (tmp2 != NULL) { */
/*     tmp1->coeff += tmp2->coeff + tmp12->coeff; */
/*     tmp1->exp = tmp2->exp; */
/*     tmp1 = tmp1->next; */
/*     tmp12 = tmp12->next; */
/*     tmp2 = tmp2->next; */
/*   } */
/*   // */
/*   tmp3 = tmp1; */
/*   while (tmp3 != NULL && tmp3->exp + new_k < poly3->exp + k) { */
/*     tmp3->exp += new_k; */
/*     tmp3->coeff += tmp12->coeff; */
/*     special_tail_2 = tmp3; */
/*     tmp3 = tmp3->next; */
/*     tmp12 = tmp12->next; */
/*   } */
/*   // */
/*   tmp4 = poly3; */
/*   tmp5 = tmp3; */
/*   while (tmp5 != NULL) { */
/*     tmp4->coeff += tmp5->coeff + tmp12->coeff; */
/*     tmp4->exp = tmp5->exp + new_k; */
/*     special_tail_3 = tmp4; */
/*     tmp4 = tmp4->next; */
/*     tmp5 = tmp5->next; */
/*     tmp12 = tmp12->next; */
/*   } */
/*   // */
/*   tmp6 = tmp4; */
/*   while (tmp6 != NULL) { */
/*     tmp6->exp += k; */
/*     tmp6 = tmp6->next; */
/*   } */

/*   special_tail_1->next = poly21; */
/*   freePolynomial_nodes(tmp0); */
/*   special_tail_2->next = poly3; */
/*   freePolynomial_nodes(tmp3); */

/*   freePolynomial_nodes(poly22); */

/*   if (special_tail_3 != NULL && special_tail_3->prev != NULL) { */
/*     special_tail_3->next = NULL; */
/*     freePolynomial_nodes(poly3); */
/*   } */
/*   return poly1; */
/* } */

/* /\** */
/*  *  \brief Variant of Divide and Conquer algorithm for Polynomial */
/*  * multiplication. */
/*  *\/ */
/* struct Node *karatsuba(struct Node *poly1, struct Node *poly2, int k) { */
/*   /\* printf("%s\n", "polyss:"); *\/ */
/*   /\* printPolynomial_nodes(poly1); *\/ */
/*   /\* printPolynomial_nodes(poly2); *\/ */
/*   if (k == 1) { */
/*     return multiplyMonomials(poly1, poly2); */
/*   } */

/*   struct Node *first_half_poly1, *second_half_poly1, *first_half_poly2, */
/*       *second_half_poly2; */

/*   int new_k = k / 2; */
/*   splitPolynomial(poly1, new_k, &first_half_poly1, &second_half_poly1); */
/*   splitPolynomial(poly2, new_k, &first_half_poly2, &second_half_poly2); */

/*   struct Node *productA0B0 = karatsuba(first_half_poly1, first_half_poly2,
 * k); */
/*   struct Node *productA1B1 = karatsuba(second_half_poly1,
 * second_half_poly2, k); */
/*   struct Node *productOfsumsA0A1_B0B1 = karatuba( */

/*   /\* struct Node *result = addIncompletePolynomialNodes_x( *\/ */

/*   freePolynomial_nodes(first_half_poly1); */
/*   freePolynomial_nodes(second_half_poly1); */
/*   freePolynomial_nodes(first_half_poly2); */
/*   freePolynomial_nodes(second_half_poly2); */

/*   return result; */
/* } */

#endif /* ADVANCEPOLYNOMIALARITHMETICS_H */
