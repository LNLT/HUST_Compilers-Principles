**%token 定义文法中使用了哪些终结符。**定义形式： %token TOKEN1 TOKEN2
终结符一般全大写；（如 TOKEN1 TOKEN2）
一行可定义多个终结符，空格分隔；

**%left、%right、%nonassoc 也是定义文法中使用了哪些终结符。**定义形式与%token类似。
先定义的优先级低，最后定义的优先级最高，同时定义的优先级想通过。
**%left表示左结合，%right表示右结合；**
**%nonassoc 表示不可结合**（即它定义的终结符不能连续出现。例如<，如果文法中不允许出现形如a<b<c的句子，则<就是不可结合的）

%left AA BB
%nonassoc CC
%right DD
表示优先级关系为：AA=BB<CC<DD，表示结核性为：AA\BB左结合， DD右结合， CC不可结合。
注意：也可以于%prec来结合使用来改变token的优先级和结合性 例如： :'-' expr %prec NEG { $$ = -$2; };

%union 声明语法符号的语义值类型的集合，
bison中每个符号包括记号和非终结符都有一个不同数据类型的语义值，并使用yylval变量在移进和归约中传递这些值，YYSTYPE（宏定义）为yylval的类型，默认为int；
我们使用%union来重新定义符号的类型
%union
{
int iValue; /* integer value */
char sIndex; /* symbol table index */
nodeType *nPtr; /* node pointer */
};

**%type 定义非终结符其属性值的类型。**
%type sym1 sym2
%type <sindex>sym3

**%start 指定文法的开始的文法符号（非终结符）**，是最终需要规约而成的符号。
定义形式为：%start startsym ， 其中startsym为文法的开始符号。
如果不使用%start定义文法开始符号，则默认在第二部分规则段中定义的第一条生产式规则的左部非终结符为开始符号。

TYPE 

STRUCT 

RETURN 

IF 

ELSE 

WHILE 

VOID 

BREAK 

CONTINUE 

WRITE 

READ 



ID 

INT [0-9]+

FLOAT 

CHAR [A-Za_z]+



LP RP 

LB RB 

DOT 

ADDSELF 

SUBSELF 

NOT 

MUL 

DIV 

SUB 

ADD 

RELOP 

AND 

OR 

ASSIGNOP 



MMH 

COMMA 

SEMI 

LC RC