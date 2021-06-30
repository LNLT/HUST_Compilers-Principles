%option yylineno
%{
    #include "c_blue.tab.h"
    #include "string.h"
    int yycolumn=1;
    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yylloc.last_column; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
    // typedef union {
    //     int type_int;
    //     float type_float;
    //     char type_char[32];
    //     char type_id[32];
    //     struct Node *ptr;
    // }YYLVAL;
    // #define YYSTYPE YYLVAL
%}

/* 相同的输入可以被多种不同的模式匹配，于是出现了二义性。flex使用以下两个原则进行解决：尽可能匹配匹配多的字符串*/
/* 关键字的匹配模式先于标识符的匹配，所以关键字会被正确的匹配。*/
TYPE int|char|float
STRUCT struct
RETURN return 
IF if
ELSE else
WHILE while
VOID void
BREAK break
CONTINUE continue
WRITE write
READ read

ID [A-Za-z][A-Za-z0-9]*
INT [0-9]+
FLOAT [0-9]+[.][0-9]+
CHAR \"[A-Za-z0-9]+\" 
/*优先级*/
LP "("
RP ")"
LB "["
RB "]"
DOT [.]
ADDSELF [+][+]
SUBSELF [-][-]
NOT [!]
MUL [*]
DIV [/]
SUB [-]
ADD [+]
RELOP [>]|[<]|[>][=]|[<][=]|(==)|[!][=]
AND [&][&]
OR [|][|]
ASSIGNOP [=]

COMMA [,]
SEMI [;] 
LC "{"
RC "}"

%%
{STRUCT} {printf("STRUCT: %s\n",yytext);return STRUCT;}
{RETURN} {printf("RETURN:%s\n",yytext);return RETURN;}
{IF} {printf("IF:%s\n",yytext);return IF;}
{ELSE} {printf("ELSE:%s\n",yytext);return ELSE;}
{WHILE} {printf("WHILE:%s\n",yytext);return WHILE;}
{VOID} {printf("VOID:%s\n",yytext);return VOID;}
{BREAK} {printf("BREAK:%s\n",yytext);return BREAK;}
{CONTINUE} {printf("CONTINUE:%s\n",yytext);return CONTINUE;}
{WRITE} {printf("WRITE:%s\n",yytext);return WRITE;}
{READ} {printf("READ:%s\n",yytext);return READ;}
{TYPE} {printf("TYPE:%s\n",yytext);strcpy(yylval.type_id,yytext);return TYPE;}

{INT} {printf("INT:%d\n",atoi(yytext));yylval.type_int=atoi(yytext);return INT;}
{FLOAT} {printf("FLOAT:%f\n",atof(yytext));yylval.type_float=atof(yytext);return FLOAT;}
{CHAR} {printf("CHAR:%s\n",yytext);strcpy(yylval.type_char,yytext);return CHAR;}
{ID} {printf("ID: %s\n",yytext);strcpy(yylval.type_id,yytext);return ID;}

{LP} {printf("LP:%s\n",yytext);return LP;}
{RP} {printf("RP:%s\n",yytext);return RP;}
{LB} {printf("LB:%s\n",yytext);return LB;}
{RB} {printf("RB:%s\n",yytext);return RB;}
{DOT} {printf("DOT:%s\n",yytext);return DOT;}

{ADDSELF} {printf("ADDSELF:%s\n",yytext);return ADDSELF;}
{SUBSELF} {printf("SUBSELF:%s\n",yytext);return SUBSELF;}
{NOT} {printf("NOT:%s\n",yytext);return NOT;}
{MUL} {printf("MUL:%s\n",yytext);return MUL;}
{DIV} {printf("DIV:%s\n",yytext);return DIV;}
{SUB} {printf("SUB:%s\n",yytext);return SUB;}
{ADD} {printf("ADD:%s\n",yytext);return ADD;}
{RELOP} {printf("RELOP:%s\n",yytext);strcpy(yylval.type_id, yytext);return RELOP;}
{AND} {printf("AND:%s\n",yytext);return AND;}
{OR} {printf("OR:%s\n",yytext);return OR;}
{ASSIGNOP} {printf("ASSIGNOP:%s\n",yytext);return ASSIGNOP;}

{COMMA} {printf("COMMA:%s\n",yytext);return COMMA;}
{SEMI} {printf("SEMI:%s\n",yytext);return SEMI;}
{LC} {printf("LC:%s\n",yytext);return LC;}
{RC} {printf("RC:%s\n",yytext);return RC;}
"//".* {}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" {}
"\n" {yycolumn = 1;}
" " {}
. {printf("error:%s\n",yytext);}
%%