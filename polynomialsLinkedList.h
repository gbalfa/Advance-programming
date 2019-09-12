#ifndef POLYNOMIALSLINKEDLIST_H
#define POLYNOMIALSLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#include "doublyLinkedListPolynomial.h"

/* Link list node */
struct PolynomialsLinkedListNode {
  struct Polynomial *poly;
  struct PolynomialsLinkedListNode *next;
};

/* Given a reference (pointer to pointer) to the head
  of a list and a polynomial, push a new node on the front
  of the list. */
void push2(struct PolynomialsLinkedListNode **head_ref, struct Polynomial *new_poly) {
  /* allocate node */
  struct PolynomialsLinkedListNode *new_node =
      (struct PolynomialsLinkedListNode *)malloc(
          sizeof(struct PolynomialsLinkedListNode));

  /* put in the data  */
  new_node->poly = new_poly;

  /* link the old list off the new node */
  new_node->next = (*head_ref);

  /* move the head to point to the new node */
  (*head_ref) = new_node;
}

/**
 *  \brief Frees the polynomial memory.
 *
 *  \param Polynomial struct.
 */
void freePolynomialsList(struct PolynomialsLinkedListNode *plist) {
  struct PolynomialsLinkedListNode *tmp;
  while (plist != NULL) {
    freePolynomial(plist->poly);
    tmp = plist;
    plist = plist->next;
    free(tmp);
  }
}

#endif /* POLYNOMIALSLINKEDLIST_H */
