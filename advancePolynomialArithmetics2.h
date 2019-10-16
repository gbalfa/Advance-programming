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
 *  \brief Add polynomial nodes in a polynomial passed by argument.
 *
 * poly1 degree <= poly2 degree.
 *
 *  \param param
 *  \return return type
 */
void addPolynomial_nodes_out(struct Node *poly1, struct Node *poly2,
                             struct Node **pos) {
  int exp = poly1->exp;
  struct Node *node = (*pos);

  if (exp < node->exp) {
    while (node != NULL && exp < node->exp) {
      node = node->prev;
    }
  } else {
    while (node != NULL && exp > node->exp) {
      node = node->next;
    }
  }
  (*pos) = node;

  struct Node *tmp = poly1, *tmp1 = poly2;
  while (tmp != NULL && tmp1 != NULL) {
    tmp->coeff += tmp1->coeff;
    tmp = tmp->next;
    tmp1 = tmp1->next;
  }
  return;
}

/* *
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

/* /\** */
/*  *  \brief Add polynomials poly1 and poly2 without adding extra memory. */
/*  * */
/*  *  poly1 degree <= poly2 degree */
/*  *\/ */
/* struct Node *addPolynomial_nodes(struct Node *poly1, struct Node *poly2, */
/*                                  struct Node *poly1_tail) { */
/*   struct Node *tmp0, *tmp1, *tmp2, *special_tail; */

/*   tmp0 = poly1_tail; */
/*   while (tmp0 != NULL && tmp0->exp >= poly2->exp) { */
/*     tmp0 = tmp0->prev; */
/*   } */
/*   special_tail = tmp0; */
/*   // */
/*   tmp1 = poly2; */
/*   tmp2 = tmp0->next; */
/*   while (tmp2 != NULL) { */
/*     tmp1->coeff += tmp2->coeff; */
/*     tmp1 = tmp1->next; */
/*     tmp2 = tmp2->next; */
/*   } */
/*   freePolynomial_nodes(special_tail->next); */
/*   special_tail->next = poly2; */
/*   poly2->prev = special_tail; */

/*   return poly1; */
/* } */

/**
 *  \brief Moves across a polynomial until it reaches a specific exp;
 */
void lookForExpPos(struct Node **pos, int exp) {
  struct Node *tmp = (*pos);
  //
  if (tmp->exp < exp) {
    while (tmp != NULL && tmp->exp < exp) {
      tmp = tmp->next;
      /* ++(*contador); */
    }
  } else {
    while (tmp != NULL && tmp->exp > exp) {
      tmp = tmp->prev;
      /* ++(*contador); */
    }
  }
  (*pos) = tmp;
  return;
}

void decreaseAndConquer_forDAC(struct Node *poly1, struct Node *poly2,
                               struct Node **sum_pos_ref,
                               struct Node **subtract_pos_ref, int sum_gap,
                               int subtract_gap) {
  struct Node *sum_pos, *head_sum_result, *factor1, *factor2, *start_sum_pos,
      *tail_sum;
  int sum_exp, subtract_exp;
  double multiplication;

  // If there is subtraction.
  if (subtract_gap != 0) {
    struct Node *subtract_pos, *head_subtract_result, *start_subtract_pos,
        *tail_subtract;

    // Subtract position.
    subtract_exp = (poly1->exp + poly2->exp) + subtract_gap;
    subtract_pos = (*subtract_pos_ref);
    lookForExpPos(&subtract_pos, subtract_exp);
    head_subtract_result = subtract_pos;
    // Sum position.
    sum_exp = (poly1->exp + poly2->exp) + sum_gap;
    sum_pos = (*sum_pos_ref);
    lookForExpPos(&sum_pos, sum_exp);
    head_sum_result = sum_pos;

    factor1 = poly1;
    factor2 = NULL;
    start_sum_pos = head_sum_result;
    start_subtract_pos = head_subtract_result;
    sum_pos = NULL;
    subtract_pos = NULL;
    while (factor1 != NULL) {
      sum_pos = start_sum_pos;
      subtract_pos = start_subtract_pos;
      factor2 = poly2;
      while (factor2 != NULL) {
        multiplication = factor1->coeff * factor2->coeff;
        sum_pos->coeff += multiplication;
        subtract_pos->coeff -= multiplication;
        sum_pos = sum_pos->next;
        subtract_pos = subtract_pos->next;
        factor2 = factor2->next;
      }
      factor1 = factor1->next;
      tail_sum = start_sum_pos;
      start_sum_pos = start_sum_pos->next;
      tail_subtract = start_subtract_pos;
      start_subtract_pos = start_subtract_pos->next;
    }
    (*sum_pos_ref) = tail_sum;
    (*subtract_pos_ref) = tail_subtract;

  } else {
    sum_exp = (poly1->exp + poly2->exp) + sum_gap;
    sum_pos = (*sum_pos_ref);
    lookForExpPos(&sum_pos, sum_exp);
    head_sum_result = sum_pos;

    factor1 = poly1;
    factor2 = NULL;
    start_sum_pos = head_sum_result;
    sum_pos = NULL;
    while (factor1 != NULL) {
      sum_pos = start_sum_pos;
      factor2 = poly2;
      while (factor2 != NULL) {
        multiplication = factor1->coeff * factor2->coeff;
        sum_pos->coeff += multiplication;
        sum_pos = sum_pos->next;
        factor2 = factor2->next;
      }
      factor1 = factor1->next;
      tail_sum = start_sum_pos;
      start_sum_pos = start_sum_pos->next;
    }
    (*sum_pos_ref) = tail_sum;
  }
  return;
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
    /* ++(*contador); */
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
  /* printf("%s\n", "polyss:"); */
  /* printPolynomial_nodes(poly1); */
  /* printPolynomial_nodes(poly2); */
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

  /* struct Node *extra_pos; */

  dAC(first_half_poly1, first_half_poly2, pos, new_k);
  /* extra_pos = (*pos); // */
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
  int contador = 0;

  dAC(poly1->head, poly2->head, &pos, k);

  printf("%d\n", contador);

  return result;
}

/**
 *  \brief Split in two parts a polynomial.
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
 *  \brief Karatsuba recursive auxiliar function.
 *
 *  \param pos: used to save positions of the resultant polynomial (that is
 *  passed by reference) and therefore decrease the linked list travels.
 *
 *  \param gaps: used to save the resultant polynomial in the right position
 *  according to the multiplying factors.
 */
void dAC_karatsuba(struct Node *poly1, struct Node *poly2,
                   struct Node **sum_pos_ref, struct Node **subtract_pos_ref,
                   int sum_gap, int subtract_gap, int k) {
  /* printf("%s\n", "polyss:"); */
  /* printPolynomial_nodes(poly1); */
  /* printPolynomial_nodes(poly2); */
  if (k == 4) {
    return decreaseAndConquer_forDAC(poly1, poly2, sum_pos_ref,
                                     subtract_pos_ref, sum_gap, subtract_gap);
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
  dAC_karatsuba(first_half_poly1, first_half_poly2, sum_pos_ref,
                subtract_pos_ref, sum_gap, subtract_gap + new_k, new_k);
  dAC_karatsuba(sumA0A1, sumB0B1, sum_pos_ref,
                subtract_pos_ref, sum_gap + new_k, subtract_gap, new_k);
  dAC_karatsuba(second_half_poly1, second_half_poly2, sum_pos_ref,
                subtract_pos_ref, sum_gap + k, subtract_gap + new_k, new_k);

  freePolynomial_nodes(sumA0A1);
  freePolynomial_nodes(sumB0B1);
  first_half_poly1_tail->next = second_half_poly1;
  first_half_poly2_tail->next = second_half_poly2;
  return;
}

/**
 *  \brief Karatsuba
 */
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
  struct Node *sum_pos = result->head;
  struct Node *subtract_pos = result->head;

  dAC_karatsuba(poly1->head, poly2->head, &sum_pos, &subtract_pos, 0, 0, k);

  return result;
}

void test() {
  int n = 5368299;
  struct Polynomial *test = generatePolynomial(n);

  double time_spent = 0.0;

  clock_t begin = clock();

  /* struct Polynomial *copy = copyPolynomial(test); */

  clock_t end = clock();
  /* time_spent += (double)(end - begin) / CLOCKS_PER_SEC; */
  /* printf("time elapsed is %f seconds\n", time_spent); */

  time_spent = 0.0;
  begin = clock();

  struct Node *node = test->head;
  int exp = n - 1;
  for (int i = 0; i < 1000; ++i) {
    node = test->head;
    while (node != NULL && exp > node->exp) {
      node = node->next;
    }
  }

  end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time elapsed is %f seconds\n", time_spent);

  freePolynomial(test);
}

#endif /* ADVANCEPOLYNOMIALARITHMETICS_H */
