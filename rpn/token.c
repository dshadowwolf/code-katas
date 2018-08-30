#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "token_types.h"

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

Token *tokenize(char *buffer) {
  // calloc is generally equal to "count"*size and is a bare helper
  Token *tokens = calloc(129, sizeof(Token));
  size_t csz = 128; // we allocate for 1 more so there is always room for the "END" token
  int count = 0;
  char *token = trim(strtok(buffer, " "));
  
  while(token != NULL) {
    if(isdigit(token[0])) {
      Token k;
      k.type = NUMBER;
      k.value = atoi(token);
      tokens[count++] = k;
    } else if(is_operator(token)) {
      Token l;
      l.type = OPERATOR;
      l.operator = token[0];
      tokens[count++] = l;
    } else {
      Token e;
      e.type = UNKNOWN;
      tokens[count++] = e;
    }
    
    if(count == csz) {
      size_t t = csz * 2;
      Token *new_allocation = calloc(t+1, sizeof(Token));
      bcopy(tokens, new_allocation, csz);
      free(tokens);
      tokens = new_allocation;
      csz = t;
    }

    token = trim(strtok(NULL, " "));
  }

  Token end;
  end.type = END;
  if((count + 1) > (csz+1)) {  
      size_t t2 = csz * 2;
      Token *new_allocation2 = calloc(t2+1, sizeof(Token));
      bcopy(tokens, new_allocation2, csz);
      free(tokens);
      tokens = new_allocation2;
      csz = t2;
  }
  
  tokens[count++] = end;   
  return tokens;
}
