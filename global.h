typedef union {
  double dval;
  char* cval;
} TokenType;

#define YYSTYPE TokenType
extern YYSTYPE yylval;

void parseExpr(char* my_string);
