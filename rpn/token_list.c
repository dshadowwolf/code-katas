#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "token_types.h"

typedef struct token_list_s TokenList;

struct token_list_s {
  Token *current;
  TokenList *next;
};

TokenList *newTokenList() {
  return memset(malloc(sizeof(TokenList)), 0, sizeof(TokenList));
}

TokenList *findEnd(TokenList *list) {
  TokenList *rv = list;

  while(rv->next != NULL) rv = rv->next;

  return rv;
}

void push_token(Token *token, TokenList *list) {
  if(list->current == NULL) {
    list->current = token;
  } else {
    TokenList *newNode = newTokenList();
    TokenList *insert_point = list->next == NULL?list:findEnd(list);
    newNode->current = token;
    newNode->next = NULL;
    insert_point->next = newNode;
  }
}

Token *pop_token(TokenList *list) {
  TokenList *newHead = list->next;
  Token *rv = list->current;

  if (newHead == NULL) {
    newHead = newTokenList();
  }

  list = newHead;

  if (rv == NULL) {
    rv = malloc(sizeof(Token));
    rv->type = END;
  }

  return rv;
}
