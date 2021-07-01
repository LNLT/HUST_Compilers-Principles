%define parse.error verbose
%locations
%{
        #include "stdio.h"
        #include "math.h"
        #include "string.h"
        #include "def.h"
        extern int yylineno;
        extern char *yytext;
        extern FILE *yyin;
        void yyerror(const char* fmt);
        void display(struct Node *,int);
%}

%union {
	int    type_int;
	float  type_float;
	char   type_id[32];
        char   type_char[32];
        char   struct_name[32];
	struct Node *ptr;
};

//  %type 定义非终结符的语义值类型
%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args Arraylist ForDec StructSpecifier OptTag

//% token 定义终结符的语义值类型
%token <type_char> CHAR
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值*/
%token <type_id> ID  RELOP TYPE    /*指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_float> FLOAT          /*指定ID的语义值是type_id，有词法分析得到的标识符字符串*/

%token STRUCT WRITE READ
%token DPLUS LP RP LC RC LB RB SEMI COMMA DOT     /*用bison对该文件编译时，带参数-d，生成的.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token ADD SUB MUL DIV ASSIGNOP AND OR NOT ADDSELF SUBSELF IF ELSE WHILE FOR RETURN COLON DEFAULT CONTINUE BREAK VOID
/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE ARRAY_LIST ARRAY_LAST
%token FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ FOR_DEC STRUCT_DEF STRUCT_DEC STRUCT_TAG EXP_ELE
%token DEFAULT_STMT EXP_ARRAY EXT_STRUCT_DEF ARRAY_DEC ADDSELF_L ADDSELF_R SUBSELF_L SUBSELF_R

%left ASSIGNOP
%left OR
%left AND
%left RELOP
%left ADD SUB
%left MUL DIV
%left ADDSELF SUBSELF
%right USUB NOT DPLUS

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

program: ExtDefList    {display($1,0);semantic_Analysis0($1);}     //显示语法树,语义分析
         ; 
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=mknode(2,EXT_DEF_LIST,yylineno,$1,$2);}   //每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}   //该结点对应一个外部变量声明
        | StructSpecifier SEMI {$$=mknode(1,EXT_STRUCT_DEF,yylineno,$1);}
        | Specifier FuncDec CompSt    {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}         //该结点对应一个函数定义
        | error SEMI   { $$ = NULL; fprintf(stderr, "Grammar Error at Line %d Column %d：",yylloc.first_line,yylloc.first_column);}
         ;
Specifier:  TYPE    {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);$$->type=(!strcmp($1,"int"))? INT : ((!strcmp($1, "float")) ? FLOAT : ((!strcmp($1, "char")) ? CHAR : VOID));}   
          | StructSpecifier {$$=$1;}
           ;      
StructSpecifier: STRUCT OptTag LC DefList RC {$$=mknode(2, STRUCT_DEF, yylineno, $2, $4);}
               | STRUCT OptTag {$$=mknode(1, STRUCT_DEC, yylineno, $2);}
               ;
OptTag: ID {$$=mknode(0, ID, yylineno);strcpy($$->type_id, $1);}
       ;

ExtDecList:  VarDec      {$$=mknode(1,EXT_DEC_LIST,yylineno,$1);}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
           ;  

VarDec:  ID          {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}    //ID结点，标识符符号串存放结点的type_id
       | ID Arraylist {$$=mknode(1,ARRAY_DEC,yylineno,$2);strcpy($$->type_id,$1);} 
       ;

Arraylist:  LB INT RB                  {$$=mknode(0,ARRAY_LAST,yylineno);$$->type_int=$2;$$->type=INT;}
          | LB INT RB Arraylist       {$$=mknode(1,ARRAY_LIST,yylineno,$4);$$->type_int=$2;$$->type=INT;}
        ;

FuncDec: ID LP VarList RP   {$$=mknode(1,FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
       | ID LP  RP   {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}//函数名存放在$$->type_id
        ;  
VarList: ParamDec  {$$=mknode(1,PARAM_LIST,yylineno,$1);}
       | ParamDec COMMA  VarList  {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);}
        ;
ParamDec: Specifier VarDec         {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);}
         ;

CompSt: LC DefList StmList RC    {$$=mknode(2,COMP_STM,yylineno,$2,$3);}
       ;
StmList: {$$=NULL; }  
        | Stmt StmList  {$$=mknode(2,STM_LIST,yylineno,$1,$2);}
        ;
Stmt:   Exp SEMI    {$$=mknode(1,EXP_STMT,yylineno,$1);}
      | CompSt      {$$=$1;}      //复合语句结点直接最为语句结点，不再生成新的结点
      | RETURN Exp SEMI   {$$=mknode(1,RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);}
      | FOR LP ForDec RP Stmt {$$=mknode(2,FOR,yylineno,$3,$5);}
      | CONTINUE SEMI {$$=mknode(0,CONTINUE, yylineno);}
      | BREAK SEMI {$$=mknode(0,BREAK,yylineno);}
      | READ LP VarDec RP SEMI {$$=mknode(1,READ,yylineno,$3);} 
      | WRITE LP VarDec RP SEMI {$$=mknode(1,WRITE,yylineno,$3);} 
      | DEFAULT COLON Stmt {$$=mknode(1, DEFAULT_STMT, yylineno,$3);}
      ;

ForDec: Exp SEMI Exp SEMI Exp {$$=mknode(3, FOR_DEC, yylineno, $1, $3, $5);}
        ;

DefList: {$$=NULL; }
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        | error SEMI   {$$=NULL;fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);}
        ;
Def:    Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);}
        ;
DecList: Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
	   ;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
Exp:    Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}//$$结点type_id空置未用，正好存放运算符
      | Exp AND Exp   {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp ADD Exp  {$$=mknode(2,ADD,yylineno,$1,$3);strcpy($$->type_id,"ADD");}
      | Exp SUB Exp {$$=mknode(2,SUB,yylineno,$1,$3);strcpy($$->type_id,"SUB");}
      | Exp MUL Exp  {$$=mknode(2,MUL,yylineno,$1,$3);strcpy($$->type_id,"MUL");}
      | Exp DIV Exp   {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
      | Exp ADDSELF  {$$=mknode(1,ADDSELF_R,yylineno,$1);strcpy($$->type_id, "AUTO");}
      | Exp SUBSELF {$$=mknode(1,SUBSELF_R,yylineno,$1);strcpy($$->type_id,"AUTO");}
      | ADDSELF Exp  {$$=mknode(1,ADDSELF_L,yylineno,$2);strcpy($$->type_id, "AUTO");}
      | SUBSELF Exp {$$=mknode(1,SUBSELF_L,yylineno,$2);strcpy($$->type_id, "AUTO");}
      | LP Exp RP     {$$=$2;}
      | SUB Exp %prec USUB   {$$=mknode(1,USUB,yylineno,$2);strcpy($$->type_id,"USUB");}
      | NOT Exp       {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
      | ID LP Args RP {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}
      | ID LP RP      {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
      | ID            {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
      | INT           {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT         {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | CHAR        {$$=mknode(0,CHAR,yylineno);strcpy($$->type_string,$1);$$->type=CHAR;}
      | ID Arraylist  {$$=mknode(1,EXP_ARRAY,yylineno,$2);strcpy($$->type_id,$1);}
      | Exp DOT ID    {$$=mknode(1,EXP_ELE,yylineno,$1); strcpy($$->type_id,$3);}
      | {$$=NULL;}
      ;


Args:    Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
       ;
       
%%

int main(){
    yylineno=1;
    yyparse();
    return 0;
}

void yyerror(const char* fmt)
{
    printf( "Grammar Error at Line %d Column %d:", yylloc.first_line,yylloc.first_column);
    printf("%s.\n",fmt);
}
