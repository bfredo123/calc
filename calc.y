%{

#include "global.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

%}

%token  NOMBRE
%token  PLUS  MOINS FOIS  DIVISE  PUISSANCE
%token  PARENTHESE_GAUCHE PARENTHESE_DROITE
%token  FIN
%token  SYMBOLE

%left PLUS  MOINS
%left FOIS  DIVISE
%left NEG
%right  PUISSANCE

%start Input
%%

Input:
Ligne
  ;

Ligne:
  Expression    { /*printf("Resultat : %f\n",$1); */}
  ;

Expression:
NOMBRE      { /*$$=$1; */ /* printf("NOMBRE:(%f)\n", $1.dval); */ push($1.dval);}
| SYMBOLE PARENTHESE_GAUCHE Expression PARENTHESE_DROITE { /* printf("$1='%s' $2='%s'\n", $1.cval, $2.cval); */ functionCall($1.cval); }
| SYMBOLE      { /*$$=3.14;*/ /*printf("pushX());\n");*/ pushVariable($1.cval); }
| Expression PLUS Expression  { /*$$=$1+$3;*/ /*printf("add();\n");*/ add();}
| Expression MOINS Expression { /*$$=$1-$3; */ /*printf("sub();\n");*/ sub();}
| Expression FOIS Expression  { /*$$=$1*$3; */ /*printf("mul();\n");*/ mul();}
| Expression DIVISE Expression  { /*$$=$1/$3; */ /*printf("div();\n");*/ gendiv();}
| MOINS Expression %prec NEG  { /*$$=-$2; */ /*printf("neg();\n");*/ neg();}
| Expression PUISSANCE Expression { /*$$=pow($1,$3); */ /*printf("pow();\n");*/ genpow();}
| PARENTHESE_GAUCHE Expression PARENTHESE_DROITE  { $$=$2; /*printf("nop();\n");*/}
  ;

%%

int yyerror(char *s) {
  printf("%s\n",s);
}


/*
int main(void) {
  yyparse();
}

*/
