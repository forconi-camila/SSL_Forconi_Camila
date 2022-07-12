%option noyywrap

%{/* ---------------------------------------- DEFINICIONES ------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include "misFunciones.h"



%}/* ---------------------------------------- ALIAS ------------------------------------------------ */

/* Constantes Enteras */
DECIMAL                 [1-9][0-9]*;
OCTAL                   0[0-7]*;
HEXADECIMAL             0[xX][0-9a-fA-F]+;

/* Constante Reales  */
REAL                    ([0-9]*\.[0-9]+([Ee](+|-)?[0-9]*)?)|([0-9].([Ee](+|-)?[0-9]*)?);

/* Constante Caracter   */
CONSTANTE_CARACTER      \x2c.\x2c;   /*    (\x2c) => '   */ 

/* Identificadores */
IDENTIFICADOR           [a-zA-Z_][a-zA-Z0-9_]*;

/* Operadores y Caracteres de Puntuacion */
PUNTUACION_OPERADOR     \x5b|\x5d|\x7b|\x7d|\x28|\x29|->|\x2f|<<=|>>=|<<|>>|<=|>=|<|>|==|!=|&&|\x7c\x7c|\+\+|--|\*=|\x2f=|%=|\+=|-=|&=|\^=|\x7c=|\?|:|;|\.\.\.|,|##|~|\^|\.|\*|\+|-|%|&|!|=|#|\x7c;
/*      { (\x5b) => '[' } - { (\x5d) => ']' } - { (\x7b) => '{' } - { (\x7d) => '}' }
        { (\x28) => '(' } - { (\x29) => ')' } - { (\x2f) => '/' } - { (\x7c) => '-' } 
*/

/* Palabras Reservadas */
TIPO_DATO               char|int|float|double|void;
ESTRUCTURA_DE_CONTROL   break|continue|do|else|for|goto|if|return|switch|while;
OTRAS_PAL_RES           auto|case|const|default|enum|extern|long|register|short|signed|sizeof|static|struct|unsigned|typedef|union|volatile;
PALABRA_RESERVADA       {TIPO_DATO}|{ESTRUCTURA_DE_CONTROL}|{OTRAS_PAL_RES};

/* Literales cadena */
LITERAL_CADENA          \x22(\\.|[^\\x22])*\x22;     /*    (\x22) => "   */

/* Comentarios */
COMENTARIO_UNA_LINEA    \x2f\x2f.*;     /*    (\x2f) => /   */
COMENTARIO_MULTILINEA   \x2f\x2a(.|[ \t]|\n)*\x2a\x2f;    /*    { (\x2f) => '/' } - { (\x2a) => '*' } - { [ \t] => tab  - { (\n) => new line }    */


%%/* ---------------------------------------- REGLAS ------------------------------------------------ */


{IDENTIFICADOR} { /* buscarInsertarIdentificador(yytext); */ }  

{LITERAL_CADENA} { /* insertarCadena(yytext,yyleng); */ }

{PALABRA_RESERVADA} { /* buscarInsertarReservada(yytext); */ }

{OCTAL} { /* insertarConstOctal(yytext); */ } 
{HEXADECIMAL} { /* insertarConstHexadecimal(yytext); */ }
{DECIMAL} { /* insertarConstDecimal(yytext); */ } 
{REAL} { /* insertarConstReal(yytext); */ }
{CONSTANTE_CARACTER} { /* insertarConstCaracter(yytext); */ }

{PUNTUACION_OPERADOR} { /* buscarInsertarPuntuacionOperador(yytext); */ }

{COMENTARIO_UNA_LINEA}  { /* insertarComentario(yytext, 1); */ }
{COMENTARIO_MULTILINEA} { /* insertarComentario(yytext, 0); */ }

. { /* insertarNoReconocido(yytext); */ }


%%/* ---------------------------------------- CODIGO DE USUARIO C ------------------------------------------------ */

int main(){
    
    yyin = fopen("entrada.txt", "r");
    yyout = fopen("salida.txt", "w");
    yylex();

    return 0;
}



    