%{

#include "global.h"
#include "calc.h"

#include <stdlib.h>

%}

blancs    [ \t]+

chiffre   [0-9]
entier    {chiffre}+
exposant  [eE][+-]?{entier}

reel    {entier}("."{entier})?{exposant}?

%%

{blancs}  { /* On ignore */ }

{reel}    {
      yylval.dval=atof(yytext);
      return(NOMBRE);
    }

"+"   return(PLUS);
"-"   return(MOINS);

"*"   return(FOIS);
"/"   return(DIVISE);

"^"   return(PUISSANCE);

"("   return(PARENTHESE_GAUCHE);
")"   return(PARENTHESE_DROITE);

"\n"  return(FIN);

[_a-zA-Z][_a-zA-Z0-9]*   {
  yylval.cval = strdup(yytext);
  //  printf("found symbole: '%s'\n", yytext);
  return(SYMBOLE);
}

%%

void parseExpr(char* my_string) {
    YY_BUFFER_STATE my_string_buffer = yy_scan_string (my_string);
    /*    my_parse_result  = */
      yyparse ();
    yy_delete_buffer (my_string_buffer);
}

