typedef enum TokenType_e {
			   OPERATOR,
			   NUMBER,
			   END,
			   UNKNOWN
} TokenType;

typedef struct token_s {
  int value;
  char operator;
  TokenType type;
} Token;
