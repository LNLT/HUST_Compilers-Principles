%locations
%define parse.error verbose
%{
    #include "c_blue.tab.h"
    #include "stdio.h"
    #include "string.h"
    #include "math.h"
    #include "def.h"
    extern int yylineno;
    extern char *yytext;
    extern FILE *yyin;
    void yyerror(const char* fmt, ...);
    void display(struct Node *,int);
%}

%union {
	int type_int;
	float type_float;
        char type_char[32];
	char type_id[32];
	struct Node *ptr;
};

%type <ptr> program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag FunDec VarList ParamDec VarDec CompSt StmtList Stmt DefList Def DecList Dec EXP Args
%token <type_int> INT
%token <type_float> FLOAT
%token <type_char> CHAR
%token <type_id> RELOP ID TYPE

%token STRUCT RETURN IF ELSE WHILE VOID BREAK CONTINUE WRITE READ 
%token LP RP LB RB DOT ADDSELF SUBSELF NOT MUL DIV SUB ADD AND OR ASSIGNOP COMMA SEMI LC RC
%token EXT_DEF_LIST EXT_VAR_DEF EXT_STRUCT_DEF FUNC_DEF VOID_FUNC_DEF EXT_DEC_LIST FUNC_DEC STRUCT_DEF STRUCT_DEC PARAM_LIST PARAM_DEC ARRAY_DEC COMP_STM  STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE DEF_LIST VAR_DEF DEC_LIST DEC_LISTS ARGS VARLIST EXP_ELE FUNC_CALL EXP_ARRAY
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left ADD SUB
%left DIV MUL
%left ADDSELF SUBSELF
%left LB RB LP RP DOT
%right USUB NOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%
program:ExtDefList {display($1,0);semantic_Analysis0($1);};
ExtDefList:{$$=NULL;}
        | ExtDef ExtDefList {$$ = mknode(2,EXT_DEF_LIST,yylineno,$1,$2);};
ExtDef:Specifier ExtDecList SEMI {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}
        | StructSpecifier SEMI {$$=mknode(1,EXT_STRUCT_DEF,yylineno,$1);}
        | Specifier FunDec CompSt {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}
        | VOID FunDec CompSt {$$=mknode(2,VOID_FUNC_DEF,yylineno,$2,$3);strcpy($$->type_id,"void");$$->type=VOID;}
        | error SEMI {$$ = NULL; printf("grammar error at %d.%d：",yylloc.first_line,yylloc.first_column);};
ExtDecList:VarDec {$$=$1;}
        | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);};
Specifier:TYPE {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);$$->type=(!strcmp($1,"int")?INT:(!strcmp($1,"float")?FLOAT:CHAR));} 
        ;
StructSpecifier:STRUCT OptTag LC DefList RC {$$=mknode(2,STRUCT_DEF,yylineno,$2,$4);} 
        | STRUCT OptTag {$$=mknode(1,STRUCT_DEC,yylineno,$2);};
OptTag: ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);};

FunDec:ID LP VarList RP {$$=mknode(1,FUNC_DEC,VARLIST,$3);strcpy($$->type_id,$1);} 
        | ID LP RP {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}
        | error RP {$$ = NULL; printf("grammar error at %d.%d：",yylloc.first_line,yylloc.first_column);};
VarList:ParamDec COMMA VarList {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);} 
        | ParamDec {$$=$1;};
ParamDec:Specifier VarDec {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);};
VarDec:ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);} 
        | OptTag LB INT RB {$$=mknode(1,ARRAY_DEC,yylineno,$1);$$->type_int=$3;$$->type=INT;}; 
CompSt:LC DefList StmtList RC {$$=mknode(2,COMP_STM,yylineno,$2,$3);};
        
StmtList:{$$=NULL;}
        | Stmt StmtList {$$=mknode(2,STM_LIST,yylineno,$1,$2);};
Stmt:EXP SEMI {$$=mknode(1,EXP_STMT,yylineno,$1);} 
        | CompSt {$$=$1;} 
        | RETURN EXP SEMI {$$=mknode(1,RETURN,yylineno,$2);} 
        | IF LP EXP RP Stmt %prec LOWER_THEN_ELSE {$$=mknode(2,IF_THEN,yylineno,$3,$5);} 
        | IF LP EXP RP Stmt ELSE Stmt {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);} 
        | WHILE LP EXP RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);} 
        | READ LP ID RP SEMI {$$=mknode(1,READ,yylineno,$3);strcpy($$->type_id,$3);} 
        | WRITE LP ID RP SEMI {$$=mknode(1,WRITE,yylineno,$3);strcpy($$->type_id,$3);} 
        | BREAK SEMI {$$=mknode(0,BREAK, yylineno);} 
        | CONTINUE SEMI {$$=mknode(0,CONTINUE, yylineno);}
        | error SEMI {$$ = NULL; printf("grammar error at %d.%d：",yylloc.first_line,yylloc.first_column);};
DefList:{$$=NULL;} 
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        | error SEMI {$$ = NULL; printf("grammar error at %d.%d：",yylloc.first_line,yylloc.first_column);};
Def:Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);};
DecList:Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);} 
        | Dec COMMA DecList {$$=mknode(2,DEC_LISTS,yylineno,$1,$3);};
Dec:VarDec {$$=$1;} 
        | VarDec ASSIGNOP EXP {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP:=");};

EXP:EXP ASSIGNOP EXP  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP:=");} 
        | EXP AND EXP {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND:&&");} 
        | EXP OR EXP {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR:||");} 
        | EXP RELOP EXP {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);} 
        | EXP ADD EXP {$$=mknode(2,ADD,yylineno,$1,$3);strcpy($$->type_id,"ADD:+");} 
        | EXP SUB EXP {$$=mknode(2,SUB,yylineno,$1,$3);strcpy($$->type_id,"SUB:-");} 
        | EXP MUL EXP {$$=mknode(2,MUL,yylineno,$1,$3);strcpy($$->type_id,"MUL:*");} 
        | EXP DIV EXP {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV:/");} 
        | LP EXP RP {$$=$2;} 
        | SUB EXP %prec USUB{$$=mknode(1,USUB,yylineno,$2);strcpy($$->type_id,"USUB:-");} 
        | NOT EXP {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT:!");} 
        | ID LP Args RP {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);} 
        | ID LP RP {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);} 
        | EXP DOT ID {$$=mknode(1,EXP_ELE,yylineno,$1); strcpy($$->type_id,$3);} 
        | OptTag LB INT RB {$$=mknode(1,EXP_ARRAY,yylineno,$1);$$->type_int=$3;$$->type=INT;} 
        | EXP ADDSELF {$$=mknode(1,ADDSELF,yylineno,$1);strcpy($$->type_id,"ADDSELF(E++):++");}
        | ADDSELF EXP {$$=mknode(1,ADDSELF,yylineno,$2);strcpy($$->type_id,"ADDSELF(++E):++");}
        | EXP SUBSELF {$$=mknode(1,SUBSELF,yylineno,$1);strcpy($$->type_id,"SUBSELF(E--):--");}
        | SUBSELF EXP {$$=mknode(1,SUBSELF,yylineno,$2);strcpy($$->type_id,"SUBSELF(--E):--");}
        | ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);} 
        | INT {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;} 
        | CHAR {$$=mknode(0,CHAR,yylineno);strcpy($$->type_char,$1);$$->type=CHAR;} 
        | FLOAT {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
        | error RP {$$ = NULL; printf("grammar error at %d.%d：",yylloc.first_line,yylloc.first_column);};
Args:EXP COMMA Args {$$=mknode(2,ARGS,yylineno,$1,$3);} 
        | EXP {$$=mknode(1,ARGS,yylineno,$1);};

%%
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf( "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    printf(".\n");
}
int main(int argc,char **argv){
    yyin = fopen(argv[1],"r");
    if(!yyin){
        return 1;
    }
    yylineno=1;
	yyparse();
	return 0;
    return 0;
}