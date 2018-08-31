#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "token_types.h"
#include "token_list.h"

stack_t *stack;
extern TokenList *tokenize(char *);

int char_is_oper(char pos) {
  switch(pos) {
  case '+':
  case '-':
  case '/':
  case '*':
  case '%':
  case '^':
    return 1;
  default:
    return 0;
  }

  return 0;
}

char *trim_ws(char *str) {
  char *s = str;
  int len = 0;
  
  while(isdigit(*s) || *s == ' ' || char_is_oper(*s)) {
    len++;
    s++;
  }
  
  size_t asz = sizeof(char)*(len+1);
  size_t csz = sizeof(char)*len;
  
  char *buff = memset(malloc(asz), 0, asz);
  buff = strncpy(buff, str, csz);

  return buff;
}

int *get_top() {
  int *top_two = malloc(sizeof(int)*2);
  top_two[0] = pop(stack);
  top_two[1] = pop(stack);
  return top_two;
}

int pow_i(int val, int power) {
  if(power == 0) return 1;
  if(power == 1) return val;
  return val * pow_i(val, power-1);
}

void do_operation(char oper) {
  int *operands = get_top();
  // no default - if we hit an unknown operator, we just consume the operands
  switch(oper) {
  case '+':
    push(operands[1]+operands[0], stack);
    break;
  case '-':
    push(operands[1]-operands[0], stack);
    break;
  case '/':
    push(operands[1]/operands[0], stack);
    break;
  case '*':
    push(operands[1]*operands[0], stack);
    break;
  case '%':
    push(operands[1]%operands[0], stack);
    break;
  case '^':
    push(pow_i(operands[1],operands[0]), stack);
    break;
  }
}

void parse_line(char *buffer) {
  TokenList *tokens = tokenize(buffer);
  
  Token *work = pop_token(tokens);
  
  while(work->type != END && tokens != NULL) {
    if(work->type == OPERATOR) {
      do_operation(work->operator);
    } else if(work->type == NUMBER) {
      push(work->value, stack);
    }

    TokenList *t = tokens->next;
    free(work);
    free(tokens);
    if(t != NULL) {
      work = t->current;
    }
    tokens = t;
  }

  int result = pop(stack);
  printf("\n%d\n", result);
}

int main(int argc, char *argv[], char *envp[]) {
  size_t buffsz = (sizeof(char)*4097);
  size_t buffszp = (sizeof(char)*4096);
  char *line_buffer = memset(malloc(buffsz), 0, buffsz); // 4k characters should be enough
  stack = new_stack();
  
  while(1) {
    getline(&line_buffer, &buffszp, stdin);
    
    if(strncmp(line_buffer, "quit", sizeof(char)*4)==0) exit(0);

    parse_line(trim_ws(line_buffer));
    memset(line_buffer, 0, buffsz);
  }
}
