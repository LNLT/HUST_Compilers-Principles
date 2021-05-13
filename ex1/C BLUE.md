## C BLUE 

### token：词法

|    词法单元    |         词法单元内容          |
| :------------: | :---------------------------: |
|     标识符     |  ID -> [A-Za-z] [A-Za-z0-9]*  |
|      整型      |         INT -> [0-9]+         |
|      字符      |       CHAR -> [A-Za-z]+       |
|      分号      |           SEMI -> ;           |
|      逗号      |          COMMA -> ,           |
|      赋值      |         ASSIGNOP -> =         |
|     比较符     | RELOP -> >\|<\|>=\|<=\|==\|!= |
|       加       |           ADD -> +            |
|       减       |           SUB -> -            |
|       乘       |           MUL -> *            |
|       除       |           DIV -> /            |
|      自增      |         ADDSELF -> ++         |
|      自减      |         SUBSELF -> --         |
|       与       |           AND -> &&           |
|       或       |          OR -> \|\|           |
|       非       |           NOT -> !            |
|    数据类型    |       TYPE -> int\|char       |
|     左括号     |            LP -> (            |
|     右括号     |            RP -> )            |
|    左中括号    |            LB -> [            |
|    右中括号    |            RB -> ]            |
|    左花括号    |            LC -> {            |
|    右花括号    |            RC -> }            |
|  结构体保留字  |       STURCT -> struct        |
|   返回保留字   |       RETURN -> return        |
|    if保留字    |           IF -> if            |
|   else保留字   |         ELSE -> else          |
|  while保留字   |        WHILE -> while         |
|                |                               |
|   常量保留字   |        CONST -> const         |
| 退出循环保留字 |        BREAK -> break         |
|   继续保留字   |     CONTINUE -> continue      |
|   输出保留字   |        WRITE -> write         |
|   输入保留字   |         READ -> read          |

标识符:id

保留字：const、int、char、if、else、while、struct、return、printf、scanf、for

运算符：+、-、*、/、++、--； >|<|>=|<=|==|!=；&&、||、！；=

界符：(、)、[、]、{、}、，、；、

(1) 说明语句文法；

(2) 赋值语句文法（简单赋值）；

(3) 表达式求值文法（简单算术运算，包括++， --）；

(4) 分支语句文法；

(5) 循环语句文法；

(6) 输入语句、输出语句文法 

过程或函数调用语句文法

### Specifiers：变量

| 语法单元   | 规则                                                       |
| ---------- | ---------------------------------------------------------- |
| 类型描述符 | Specifier -> TYPE\|StructSpecifier                         |
| 结构体     | StructSpecifier -> STRUCT OptTag LC DefList RC\|STRUCT Tag |
| 结构体名   | OptTag -> ID\| #                                           |
| 标识符     | Tag -> ID                                                  |



### Declarators：函数与变量定义

| 语法单元     | 规则                                        |
| ------------ | ------------------------------------------- |
| 函数头       | FunDec -> ID LP VarList RP\|ID LP RP        |
| 函数形参列表 | VarList -> ParamDec COMMA VarList\|ParamDec |
| 函数形参     | ParamDec -> Specifier VarDec                |
| 变量         | VarDec -> ID\|VarDec LB INT RB              |



### Statements：语句

| 语法单元 | 规则                 |
| -------- | -------------------- |
| 语句块   | CompSt -> LC DefList |
| 语句列表 | StmtList             |
| 语句     | Stmt                 |



### Local Definitions：局部变量

| 语法单元                 | 规则 |
| ------------------------ | ---- |
| 变量定义列表             |      |
| 一条变量定义             |      |
| 一条变量定义里面变量列表 |      |
| 一个变量                 |      |



### EXP：表达式

| 语法单元 | 规则                                    |
| -------- | --------------------------------------- |
| 表达式   | EXP -> EXP ASSIGNOP EXP \|EXP AND EXP\| |
| 实参列表 |                                         |



### Commons：注释