#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "token_types.h"
#include "token_list.h"

#define skip_white(n) while (isblank (*(n))) (n)++

int is_operator(char *possible) {
  if(strlen(possible) != 1) {
    return 0;
  }
  
  switch(*possible) {
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

int valid(char x) {
  if ((x >= '0' && x <= '9') ||
      (x == '+' ||
       x == '-' ||
       x == '/' ||
       x == '*' ||
       x == '%' ||
       x == '^')) {
    return 1;
  }

  return 0;
}

char *trim(char *string) {
  if(string == NULL) return NULL;
  int len = 0; // skip the null terminator
  
  while(valid(string[len])) len++;
  
  size_t alloc_size = sizeof(char)*((len)+1);
  size_t use_size = sizeof(char)*(len);
  char *new = memset(malloc(alloc_size), 0, alloc_size);
  new = strncpy(new, string, use_size);
  
  return new;
}

Token *newToken() {
  return memset(malloc(sizeof(Token)), 0, sizeof(Token));
}

TokenList *tokenize(char *buffer) {
  TokenList *rv = newTokenList();
  
  char *token = trim(strtok(buffer, " "));
  
  while(token != NULL) {
    Token *w = newToken();
    if(isdigit(token[0])) {
      w->type = NUMBER;
      w->value = atoi(token);
    } else if(is_operator(token)) {
      w->type = OPERATOR;
      w->operator = token[0];
    } else {
      w->type = UNKNOWN;
    }
    
    push_token(w, rv);
    token = trim(strtok(NULL, " "));
  }

  Token *end = newToken();
  end->type = END;
  push_token(end, rv);

  return rv;
}

