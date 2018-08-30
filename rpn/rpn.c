#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "token_types.h"

stack_t *stack;
extern Token *tokenize(char *);

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
  char *temp = buffer;
  char *buff;
  Token *tokens = tokenize(temp);
  int i = 0;

  while(tokens[i].type != END) {
    Token token = tokens[i++];

    if(token.type == OPERATOR) {
      temp++;
      if(*temp == token.operator) temp++;
      do_operation(token.operator);
    } else if(token.type == NUMBER) {
      sprintf(buff, "%u", token.value);
      temp += strlen(buff);
      push(token.value, stack);
    }
  }

  int result = pop(stack);
  printf("\nresult is: %d\n", result);
}

int main(int argc, char *argv[], char *envp[]) {
  size_t buffsz = (sizeof(char)*4097);
  size_t buffszp = (sizeof(char)*4096);
  char *line_buffer = memset(malloc(buffsz), 0, buffsz); // 4k characters should be enough
  stack = new_stack();
  
  while(1) {
    getline(&line_buffer, &buffszp, stdin);
    
    if(strncmp(line_buffer, "quit", sizeof(char)*4)==0) exit(0);

    parse_line(line_buffer);
    memset(line_buffer, 0, buffsz);
  }
}
