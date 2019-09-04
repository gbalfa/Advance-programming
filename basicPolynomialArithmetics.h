#ifndef BASICPOLYNOMIALARITHMETICS_H
#define BASICPOLYNOMIALARITHMETICS_H

#include <stdio.h>
#include <stdlib.h>

#include "doublyLinkedListPolynomial.h"


struct doublyLinkedList* copyPolynomial(struct doublyLinkedList list) {

  struct Node* tail = list.tail;

  struct doublyLinkedList* new_list =
      (struct doublyLinkedList *)malloc(sizeof(struct doublyLinkedList));
  new_list->head = NULL;
  new_list->tail = NULL;

  while (tail != NULL) {
    push(new_list, tail->coeff, tail->exp);
    tail = tail->prev;
  }
  return new_list;
}

#endif /* BASICPOLYNOMIALARITHMETICS_H */
