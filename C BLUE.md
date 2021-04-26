## C BLUE 

### token：词法

|    词法单元    |              词法单元内容              |
| :------------: | :------------------------------------: |
|     标识符     |  ID$\rightarrow$[A-Za-z] [A-Za-z0-9]*  |
|      整型      |         INT$\rightarrow$[0-9]+         |
|      字符      |       CHAR$\rightarrow$[A-Za-z]+       |
|      分号      |           SEMI$\rightarrow$;           |
|      逗号      |          COMMA$\rightarrow$,           |
|      赋值      |         ASSIGNOP$\rightarrow$=         |
|     比较符     | RELOP$\rightarrow$>\|<\|>=\|<=\|==\|!= |
|       加       |           ADD$\rightarrow$+            |
|       减       |           SUB$\rightarrow$-            |
|       乘       |           MUL$\rightarrow$*            |
|       除       |           DIV$\rightarrow$/            |
|      自增      |         ADDSELF$\rightarrow$++         |
|      自减      |         SUBSELF$\rightarrow$--         |
|       与       |           AND$\rightarrow$&&           |
|       或       |          OR$\rightarrow$\|\|           |
|       非       |           NOT$\rightarrow$!            |
|    数据类型    |       TYPE$\rightarrow$int\|char       |
|     左括号     |            LP$\rightarrow$(            |
|     右括号     |            RP$\rightarrow$)            |
|    左中括号    |            LB$\rightarrow$[            |
|    右中括号    |            RB$\rightarrow$]            |
|    左花括号    |            LC$\rightarrow${            |
|    右花括号    |            RC$\rightarrow$}            |
|  结构体保留字  |       STURCT$\rightarrow$struct        |
|   返回保留字   |       RETURN$\rightarrow$return        |
|    if保留字    |           IF$\rightarrow$if            |
|   else保留字   |         ELSE$\rightarrow$else          |
|  while保留字   |        WHILE$\rightarrow$while         |
|                |                                        |
|   常量保留字   |        CONST$\rightarrow$const         |
| 退出循环保留字 |        BREAK$\rightarrow$break         |
|   继续保留字   |     CONTINUE$\rightarrow$continue      |
|   输出保留字   |        WRITE$\rightarrow$write         |
|   输入保留字   |         READ$\rightarrow$read          |

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

| 语法单元   | 规则                                                         |
| ---------- | ------------------------------------------------------------ |
| 类型描述符 | Specifier$\rightarrow$TYPE\|StructSpecifier                  |
| 结构体     | StructSpecifier$\rightarrow$STRUCT OptTag LC DefList RC\|STRUCT Tag |
| 结构体名   | OptTag$\rightarrow$ID\| #                                    |
| 标识符     | Tag$\rightarrow$ID                                           |



### Declarators：函数与变量定义

| 语法单元     | 规则                                                 |
| ------------ | ---------------------------------------------------- |
| 函数头       | FunDec$\rightarrow$ID LP VarList RP\|ID LP RP        |
| 函数形参列表 | VarList$\rightarrow$ParamDec COMMA VarList\|ParamDec |
| 函数形参     | ParamDec$\rightarrow$Specifier VarDec                |
| 变量         | VarDec$\rightarrow$ID\|VarDec LB INT RB              |



### Statements：语句

| 语法单元 | 规则                          |
| -------- | ----------------------------- |
| 语句块   | CompSt$\rightarrow$LC DefList |
| 语句列表 | StmtList                      |
| 语句     | Stmt                          |



### Local Definitions：局部变量

| 语法单元                 | 规则 |
| ------------------------ | ---- |
| 变量定义列表             |      |
| 一条变量定义             |      |
| 一条变量定义里面变量列表 |      |
| 一个变量                 |      |



### EXP：表达式

| 语法单元 | 规则                                             |
| -------- | ------------------------------------------------ |
| 表达式   | EXP$\rightarrow$EXP ASSIGNOP EXP \|EXP AND EXP\| |
| 实参列表 |                                                  |



### Commons：注释