typedef struct token_list_s TokenList;

struct token_list_s {
  Token *current;
  TokenList *next;
};

TokenList *newTokenList();
void push_token(Token *token, TokenList *list);
Token *pop_token(TokenList *list);
