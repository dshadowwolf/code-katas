#include <stdlib.h>

typedef struct stack_node_s stack_node_t;

struct stack_node_s {
  int value;
  stack_node_t *next;
};

typedef struct stack_s {
  stack_node_t *head;
  int count;
} stack_t;

void push(int val, stack_t *stack) {
  stack_node_t *temp = stack->head;
  stack_node_t *new = malloc(sizeof(stack_node_t));
  new->value = val;
  new->next = temp;
  stack->head = new;
  stack->count++;
}

int pop(stack_t *stack) {
  if(stack->count == 0) return 0;
  stack_node_t *temp = stack->head->next;
  stack_node_t *to_free = stack->head;
  int rv = to_free->value;
  stack->head = temp;
  free(to_free);
  stack->count--;
  return rv;
}

stack_t *new_stack() {
  stack_t *rv = malloc(sizeof(stack_t));
  rv->head = NULL;
  rv->count = 0;
  return rv;
}


