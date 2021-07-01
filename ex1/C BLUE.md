[TOC]

# C BLUE 

## 词法单元

| 词法单元token  |             词法单元内容             |
| :------------: | :----------------------------------: |
|    数据类型    |       TYPE -> int\|char\|float       |
|  结构体保留字  |           STURCT -> struct           |
|   返回保留字   |           RETURN -> return           |
|    if保留字    |               IF -> if               |
|   else保留字   |             ELSE -> else             |
|  while保留字   |            WHILE -> while            |
|   void保留字   |             VOID -> void             |
| 退出循环保留字 |            BREAK -> break            |
|   继续保留字   |         CONTINUE -> continue         |
|   输出保留字   |            WRITE -> write            |
|   输入保留字   |             READ -> read             |
|     标识符     |    ID -> `[A-Za-z] [A-Za-z0-9]*`     |
|      整型      |           INT -> `[0-9]+`            |
|      字符      |      CHAR ->`\"[A-Za-z0-9]+\"`       |
|     浮点数     |      FLOAT -> `[0-9]+[.][0-9]+`      |
|     左括号     |               LP -> (                |
|     右括号     |               RP -> )                |
|    左中括号    |               LB -> [                |
|    右中括号    |               RB -> ]                |
|    左花括号    |               LC -> {                |
|    右花括号    |               RC -> }                |
| 结构体访问：点 |               DOT -> .               |
|      分号      |              SEMI -> ;               |
|      逗号      |              COMMA -> ,              |
|      赋值      |            ASSIGNOP -> =             |
|     比较符     |    RELOP -> >\|<\|>=\|<=\|==\|!=     |
|       加       |               ADD -> +               |
|       减       |               SUB -> -               |
|       乘       |               MUL -> *               |
|       除       |               DIV -> /               |
|      自增      |            ADDSELF -> ++             |
|      自减      |            SUBSELF -> --             |
|       与       |              AND -> &&               |
|       或       |              OR -> \|\|              |
|       非       |               NOT -> !               |
|   单行注释//   |              `"//".* `               |
|  多行注释/**/  | `"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" ` |

标识符:id

保留字：13个

> int、char、float、struct、void、if、else、while、return、read、write、break、continue

运算符：

> +、-、*、/、++、-- 
>
> |<|>=|<=|==|!=
>
> &&、||、！、=

界符：

> '('、')'、'['、']'、'{'、'}'、','、';'、'.'

(1) 说明语句文法；

(2) 赋值语句文法（简单赋值）；

(3) 表达式求值文法（简单算术运算，包括++， --）；

(4) 分支语句文法；

(5) 循环语句文法；

(6) 输入语句、输出语句文法 

过程或函数调用语句文法

## 语法规则

### Definitions：全局变量和函数

| 语法单元                   | 规则                                                         |
| -------------------------- | ------------------------------------------------------------ |
| 整个程序                   | Program -> ExtDefLis                                         |
| 全局变量、结构体、函数集合 | ExtDefList -> ExtDef ExtDefList\|#                           |
| 全局变量、结构体、函数     | ExtDef -> Specifier ExtDecList SEMI<br/>\|StructSpecifier SEMI<br>\|Specifier FunDec CompSt<br/>\|VOID FunDec CompSt |
| 变量定义                   | ExtDecList -> VarDec \|VarDec COMMA ExtDecList               |



### Specifiers：变量

| 语法单元   | 规则                                                         |
| ---------- | ------------------------------------------------------------ |
| 类型描述符 | Specifier -> TYPE                                            |
| 结构体     | StructSpecifier -> STRUCT OptTag LC DefList RC\|STRUCT OptTag |
| 标识符     | OptTag -> ID                                                 |



### Declarators：函数与变量定义

| 语法单元     | 规则                                        |
| ------------ | ------------------------------------------- |
| 函数头       | FunDec -> ID LP VarList RP\|ID LP RP        |
| 函数形参列表 | VarList -> ParamDec COMMA VarList\|ParamDec |
| 函数形参     | ParamDec -> Specifier VarDec                |
| 变量         | VarDec -> ID\|VarDec LB INT RB              |



### Statements：语句

| 语法单元 | 规则                                                         |
| -------- | ------------------------------------------------------------ |
| 语句块   | CompSt -> LC DefList StmtList RC                             |
| 语句列表 | StmtList -> Stmt StmtList \|#                                |
| 语句     | Stmt -> EXP SEMI\|CompSt<br/>\|RETURN EXP SEMI\|IF LP EXP RP Stmt<br/>\|IF LP EXP RP Stmt ELSE Stmt<br/>\|WHILE LP EXP RP Stmt<br/>\|READ LP ID RP\|WRITE LP ID RP<br/>\|BREAK SEMI\|CONTINUE SEMI |

### Local Definitions：局部变量

| 语法单元                 | 规则                               |
| ------------------------ | ---------------------------------- |
| 变量定义列表             | DefList -> Def DefList\|#          |
| 一条变量定义             | Def -> Specifier DecList SEMI      |
| 一条变量定义里面变量列表 | DecList -> Dec \|Dec COMMA DecList |
| 一个变量                 | Dec -> VarDec\|VarDec ASSIGNOP EXP |



### EXP：表达式

| 语法单元 | 规则                                                         |
| -------- | ------------------------------------------------------------ |
| 表达式   | EXP -> EXP ASSIGNOP EXP <br/>\|EXP AND EXP\|EXP OR EXP<br/>\|EXP RELOP EXP<br/>\|EXP ADD EXP\|EXP SUB EXP\|EXP MUL EXP\|EXP DIV EXP<br/>\|LP EXP RP\|SUB EXP\|NOT EXP\|ID LP Args RP<br/>\|ID LP RP\|EXP DOT ID\|EXP LB EXP RB<br/>\|EXP ADDSELF\|ADDSELF EXP\|EXP SUBSELF\|SUBSELF EXP<br/>\|ID\|INT\|CHAR\|FLOAT |
| 实参列表 | Args -> EXP COMMA Args\|EXP                                  |

