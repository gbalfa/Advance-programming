#ifndef DOUBLYLINKEDLISTPOLYNOMIAL_H
#define DOUBLYLINKEDLISTPOLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Doubly linked list polynomial with head and tail */
struct Polynomial {
  struct Node *head;
  struct Node *tail;
  int degree;
};

/* A node of the doubly linked list polynomial */
struct Node {
  double coeff; /* coefficient */
  int exp;      /* exponent */
  struct Node *next;
  struct Node *prev;
};

/**
 *  Push a node into a polynomial.
 *
 *  Function to insert a polynomial node at the beginning of the Doubly Linked
 *  List.
 *
 *  @poly Polinomial struct.
 *  @new_coeff Monomial coefficient.
 *  @new_exp Monomial exponent.
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
 *  Append a node into a polynomial.
 *
 *  Function to insert a polynomial node at the end of the Doubly Linked
 *  List.
 *
 *  @poly Polinomial struct.
 *  @new_coeff Monomial coefficient.
 *  @new_exp Monomial exponent.
 */
void append(struct Polynomial *poly, double new_coeff, int new_exp) {
  /* allocate node */
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  /* put in the data  */
  new_node->coeff = new_coeff;
  new_node->exp = new_exp;

  /* since we are adding at the end,
     next is always NULL */
  new_node->next = NULL;

  /* link the old node off the new node */
  new_node->prev = (poly->tail);

  /* change next of tail node to new node */
  if (poly->tail != NULL)
    (poly->tail)->next = new_node;

  /* move the tail to point to the new node */
  poly->tail = new_node;

  /* link the head  */
  if (poly->head == NULL) {
    poly->head = poly->tail;
  }
}

/**
 *  \brief Generates the polynomial.
 *
 *  Generates a random polynomial pushing (n+1) nodes into a doublylinkedlist.
 *
 *  \param n: Polynomial degree.
 */
struct Polynomial *generatePolynomial(int n) {
  /* Intializes polynomial */
  struct Polynomial *new_polynomial =
      (struct Polynomial *)malloc(sizeof(struct Polynomial));
  new_polynomial->head = NULL;
  new_polynomial->tail = NULL;
  new_polynomial->degree = n;

  int i;
  double a = 10.0; /* --> range of rand generation [0,a] */
  time_t t;

  /* Intializes random number generator */
  srand((unsigned)time(&t));

  /* Generates the polynomial */
  for (i = new_polynomial->degree; i >= 0; --i)
    push(new_polynomial, (((double)rand() / (double)(RAND_MAX)) * a), i);

  return new_polynomial;
}

/**
 *  \brief Frees the polynomial memory.
 *
 *  \param Polynomial struct.
 */
void freePolynomial(struct Polynomial *polynomial) {
  struct Node *tmp;
  while (polynomial->head != NULL) {
    tmp = polynomial->head;
    polynomial->head = polynomial->head->next;
    free(tmp);
  }
  free(polynomial);
}

/**
 *  \brief Frees the polynomial nodes memory.
 *
 *  \param Node struct.
 */
void freePolynomial_nodes(struct Node *head_polynomial) {
  struct Node *tmp;
  while (head_polynomial != NULL) {
    tmp = head_polynomial;
    head_polynomial = head_polynomial->next;
    free(tmp);
  }
}

/**
 *  \brief Print the polynomial nodes.
 *
 *  \param Node struct.
 */
void printPolynomial_nodes(struct Node *node) {
  if(node == NULL) return;
  /* first node */
  printf("%f*X^%d", node->coeff, node->exp);
  node = node->next;
  /* the rest of the nodes */
  while (node != NULL) {
    printf(" + %f*X^%d", node->coeff, node->exp);
    node = node->next;
  }
  printf("\n");
}

/**
 *  \brief Prints a polynomial.
 *
 *  Function to print a polynomial representated by a doubly linked list.
 *
 *  \param List's head.
 */
void printPolynomial(struct Polynomial *poly) {
  struct Node *node = poly->head;

  if (node == NULL || poly->degree > 10)
    return;

  /* first node */
  printf("%f*X^%d", node->coeff, node->exp);
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
