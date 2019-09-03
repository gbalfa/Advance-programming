#include <stdio.h>
#include <stdlib.h>

struct doublyLinkedList{
  struct Node* head;
  struct Node* tail;
};

/* a polynomial node of the doubly linked list */
struct Node {
  double coeff; /* coefficient */
  int exp;      /* exponent */
  struct Node *next;
  struct Node *prev;
};

/* Function to insert a polynomial node at the beginning of the Doubly Linked
 * List */
void push(struct doublyLinkedList* list,  double new_coeff,
          int new_exp) {
  /* allocate node */
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  /* put in the data  */
  new_node->coeff = new_coeff;
  new_node->exp = new_exp;

  /* since we are adding at the beginning,
     prev is always NULL */
  new_node->prev = NULL;

  /* link the old list off the new node */
  new_node->next = (list->head);

  /* change prev of head node to new node */
  if ((list->head) != NULL)
    (list->head)->prev = new_node;

  /* move the head to point to the new node */
  (list->head) = new_node;

  if(list->tail == NULL){
    list->tail = list->head;
  }
}

/* Free List */
void freeList(struct doublyLinkedList *poly) {
  struct Node *tmp;
  while (poly->head != NULL) {
    tmp = poly->head;
    poly->head = poly->head->next;
    free(tmp);
  }
  free(poly);
}

/* Function to print a polynomial representated by a doubly linked list */
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
