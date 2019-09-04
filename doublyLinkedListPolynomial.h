#ifndef DOUBLYLINKEDLISTPOLYNOMIAL_H
#define DOUBLYLINKEDLISTPOLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>

/* Doubly linked list polynomial with head and tail */
struct Polynomial {
  struct Node *head;
  struct Node *tail;
};

/* A node of the doubly linked list polynomial */
struct Node {
  double coeff; /* coefficient */
  int exp;      /* exponent */
  struct Node *next;
  struct Node *prev;
};

/**
 *  \brief Push a node into a polynomial.
 *
 *  Function to insert a polynomial node at the beginning of the Doubly Linked
 *  List.
 *
 *  \param Polinomial struct, monomial coefficient, monomial exponent.
 */
void push(struct Polynomial *poly, double new_coeff, int new_exp) {
  /* allocate node */
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  /* put in the data  */
  new_node->coeff = new_coeff;
  new_node->exp = new_exp;

  /* since we are adding at the beginning,
     prev is always NULL */
  new_node->prev = NULL;

  /* link the old node off the new node */
  new_node->next = (poly->head);

  /* change prev of head node to new node */
  if (poly->head != NULL)
    (poly->head)->prev = new_node;

  /* move the head to point to the new node */
  poly->head = new_node;

  /* link the tail  */
  if (poly->tail == NULL) {
    poly->tail = poly->head;
  }
}

/**
 *  \brief Generates the polynomial.
 *
 *  Constructs the polynomial pushing the nodes into the doublylinked list,
 *  pushing at last the degree of the polinomial.
 *
 *  \param n: Polynomial degree.
 *  \return return type
 */
//////////

/**
 *  \brief Frees the polynomial memory.
 *
 *  \param List's head.
 */
void freeList(struct Polynomial *poly) {
  struct Node *tmp;
  while (poly->head != NULL) {
    tmp = poly->head;
    poly->head = poly->head->next;
    free(tmp);
  }
  free(poly);
}

/**
 *  \brief Prints a polynomial.
 *
 *  Function to print a polynomial representated by a doubly linked list.
 *
 *  \param List's head.
 */
void printPolynomial(struct Node *node) {
  if (node == NULL)
    return;

  /* first node */
  printf("%f", node->coeff);
  node = node->next;

  /* the rest of the nodes */
  while (node != NULL) {
    printf(" + %f*X^%d", node->coeff, node->exp);
    node = node->next;
  }
  printf("\n");
  return;
}

#endif /* DOUBLYLINKEDLISTPOLYNOMIAL_H */
