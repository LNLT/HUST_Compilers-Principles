#include "def.h"

extern int LEV;   //层号
extern int func_size; //函数的活动记录大小

extern struct symboltable symbolTable;
extern struct symbol_scope_begin symbol_scope_TX;

char break_label[30];
char continue_label[30];
char case_temp[30];
char case_label[30];
char array_name[30];
char struct_name[33];

int struct_flag = 0;
int array_index = 0;
int struct_var_flag = 0;

void ext_var_list(struct Node *T)
{ //处理变量列表
    int rtn, num = 1;
    if (T) {
        switch (T->kind)
        {
        case EXT_DEC_LIST:
            T->ptr[0]->type = T->type;                //将类型属性向下传递变量结点
            T->ptr[0]->offset = T->offset;            //外部变量的偏移量向下传递
            if (T->ptr[1]) {
                T->ptr[1]->type = T->type;               //将类型属性向下传递变量结点
                T->ptr[1]->offset = T->offset + T->width; //外部变量的偏移量向下传递
                T->ptr[1]->width = T->width;
            }
            ext_var_list(T->ptr[0]);
            if(T->ptr[1]) {
                ext_var_list(T->ptr[1]);
                T->num = T->ptr[1]->num + 1;
            }
            break;
        case ID:
            rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset); //最后一个变量名
            if (rtn == -1)
                semantic_error(T->pos, T->type_id, "变量重复定义");
            else
                T->place = rtn;
            T->num = 1;
            break;
        case ARRAY_DEC:
            array_index = 0;
            strcpy(array_name, T->type_id);
            rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'A', T->offset);//偏移量为0
			if (rtn == -1) {
                semantic_error(T->pos,T->type_id, "变量重复定义");
            }
            else {
                T->place = rtn;
                T->num = compute_width(T->ptr[0]);
                ext_var_list(T->ptr[0]);
            }
			break;
        case ARRAY_LIST:
            rtn = searchSymbolTable(array_name);
            int length=0;
            length=symbolTable.symbols[rtn].type==INT?4:(symbolTable.symbols[rtn].type==FLOAT?8:1);
            if(rtn == -1) {
                semantic_error(T->pos, array_name, "数组未定义");
            }
            if(T->ptr[0]->type != INT) {
                semantic_error(T->pos, "", "数组定义维数需要用整型");
            }
            else{
                symbolTable.symbols[rtn].array[array_index] = T->ptr[0]->type_int*length;
                array_index++;
                T->num = compute_width(T->ptr[1]);
                ext_var_list(T->ptr[1]);
            }
            break;
        case ARRAY_LAST:
            rtn = searchSymbolTable(array_name);
            length=0;
            length=symbolTable.symbols[rtn].type==INT?4:(symbolTable.symbols[rtn].type==FLOAT?8:1);
            //printf("%d\n",length);
            if(rtn == -1) {
                semantic_error(T->pos, array_name, "数组未定义");
            }
            if(T->ptr[0]->type != INT) {
                semantic_error(T->pos, "", "数组定义维数需要用整型");
            }
            else{
                symbolTable.symbols[rtn].array[array_index] = T->ptr[0]->type_int*length;
            }
            break;
        default:
            break;
        }
    }
}

void ext_def_list(struct Node *T)
{
    if (!T->ptr[0])
        return;

    // 语义分析之前先设置偏移地址
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]); //访问外部定义列表中的第一个
    // 之后合并 code
    T->code = T->ptr[0]->code;

    // 可为空
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]); //访问该外部定义列表中的其它外部定义
        T->code = merge(2, T->code, T->ptr[1]->code);
    }
}

void ext_var_def(struct Node *T) {
    if (!strcmp(T->ptr[0]->type_id, "int"))
    {
        T->type = T->ptr[1]->type = INT;
        T->ptr[1]->width = 4;
    }
    if (!strcmp(T->ptr[0]->type_id, "float"))
    {
        T->type = T->ptr[1]->type = FLOAT;
        T->ptr[1]->width = 8;
    }
    if (!strcmp(T->ptr[0]->type_id, "char"))
    {
        T->type = T->ptr[1]->type = CHAR;
    }
    T->ptr[1]->offset = T->offset; //这个外部变量的偏移量向下传递
    // T->ptr[1]->width = T->type == INT ? 4 : 8;            //将一个变量的宽度向下传递
    ext_var_list(T->ptr[1]);                        //处理外部变量说明中的标识符序列
    T->width = (T->ptr[1]->width) * T->ptr[1]->num; //计算这个外部变量说明的宽度
    T->code = NULL;                                 //这里假定外部变量不支持初始化
}

void func_def(struct Node *T)
{
    if (!strcmp(T->ptr[0]->type_id, "int"))
    {
        T->ptr[1]->type = INT;
    }
    if (!strcmp(T->ptr[0]->type_id, "float"))
    {
        T->ptr[1]->type = FLOAT;
    }
    if (!strcmp(T->ptr[0]->type_id, "char"))
    {
        T->ptr[1]->type = CHAR;
    }
    //填写函数定义信息到符号表
    // T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT; //获取函数返回类型送到含函数名、参数的结点
    T->width = 0;                  //函数的宽度设置为0，不会对外部变量的地址分配产生影响
    T->offset = DX;                //设置局部变量在活动记录中的偏移量初值
    semantic_Analysis(T->ptr[1]);  //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
    T->offset += T->ptr[1]->width; //用形参单元宽度修改函数局部变量的起始偏移量
    T->ptr[2]->offset = T->offset;
    strcpy(T->ptr[2]->Snext, newLabel()); //函数体语句执行结束后的位置属性
    semantic_Analysis(T->ptr[2]);         //处理函数体结点
    //计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
    symbolTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
    T->code = merge(3, T->ptr[1]->code, T->ptr[2]->code, genLabel(T->ptr[2]->Snext)); //函数体的代码作为函数的代码
}

void func_dec(struct Node *T)
{
    int rtn;
    struct opn opn1, opn2, result;
    rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0); //函数不在数据区中分配单元，偏移量为0
    if (rtn == -1)
    {
        semantic_error(T->pos, T->type_id, "函数重复定义");
        return;
    }
    else
        T->place = rtn;
    result.kind = ID;
    strcpy(result.id, T->type_id);
    result.offset = rtn;
    T->code = genIR(FUNCTION, opn1, opn2, result); //生成中间代码：FUNCTION 函数名
    T->offset = DX;                                //设置形式参数在活动记录中的偏移量初值
    if (T->ptr[0])
    { //判断是否有参数
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理函数参数列表
        T->width = T->ptr[0]->width;
        symbolTable.symbols[rtn].paramnum = T->ptr[0]->num;
        T->code = merge(2, T->code, T->ptr[0]->code); //连接函数名和参数代码序列
    }
    else {
        symbolTable.symbols[rtn].paramnum = 0;
        T->width = 0;
    }
}

void ext_struct_def(struct Node *T)
{
    //填写函数定义信息到符号表
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]); //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
    T->code = T->ptr[0]->code;
}

void struct_def(struct Node *T)
{
    int rtn;
    struct opn opn1, opn2, result;

    T->width = 0;   //函数的宽度设置为0，不会对外部变量的地址分配产生影响
    T->offset = DX; //设置局部变量在活动记录中的偏移量初值
    T->type = STRUCT;
    rtn = fillSymbolTable(T->ptr[0]->type_id, newAlias(), LEV, STRUCT, 'S', 0); //函数不在数据区中分配单元，偏移量为0
    if (rtn == -1)
    {
        semantic_error(T->pos, T->ptr[0]->type_id, "结构体重复定义");
        return;
    }
    else
        T->place = rtn;

    T->ptr[1]->offset = T->offset;
    struct_flag = 1;
    semantic_Analysis(T->ptr[1]);
    struct_flag = 0;
}

void struct_dec(struct Node *T)
{
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->width = T->ptr[1]->width;
}

// void array_dec(struct Node *T){

// }

void param_list(struct Node *T)
{
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]);
        T->num = T->ptr[0]->num + T->ptr[1]->num;             //统计参数个数
        T->width = T->ptr[0]->width + T->ptr[1]->width;       //累加参数单元宽度
        T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code); //连接参数代码
    }
    else
    {
        T->num = T->ptr[0]->num;
        T->width = T->ptr[0]->width;
        T->code = T->ptr[0]->code;
    }
}

void param_dec(struct Node *T)
{
    int rtn;
    struct opn opn1, opn2, result;
    rtn = fillSymbolTable(T->ptr[1]->type_id, newAlias(), 1, T->ptr[0]->type, 'P', T->offset);
    if (rtn == -1)
        semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "参数名重复定义");
    else
        T->ptr[1]->place = rtn;
    T->num = 1;                                //参数个数计算的初始值
    // T->width = T->ptr[0]->type == INT ? 4 : (T->ptr[0]->type == FLOAT ? 8 : 1); //参数宽度
    if (T->ptr[0]->type == INT) {
        T->width = 4;
    }
    if (T->ptr[0]->type == FLOAT) {
        T->width = 8;
    }
    if (T->ptr[0]->type == CHAR) {
        T->width = 1;
    }
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[rtn].alias);
    result.offset = T->offset;
    T->code = genIR(PARAM, opn1, opn2, result); 
}

void comp_stm(struct Node *T)
{
    LEV++;
    //设置层号加1，并且保存该层局部变量在符号表中的起始位置在symbol_scope_TX
    symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
    T->width = 0;
    T->code = NULL;
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理该层的局部变量DEF_LIST
        T->width += T->ptr[0]->width;
        T->code = T->ptr[0]->code;
    }
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->width;
        strcpy(T->ptr[1]->Snext, T->Snext); //S.next属性向下传递
        semantic_Analysis(T->ptr[1]);       //处理复合语句的语句序列
        T->width += T->ptr[1]->width;
        T->code = merge(2, T->code, T->ptr[1]->code);
    }
    prn_symbol();                                                  //c在退出一个符合语句前显示的符号表
    LEV--;                                                         //出复合语句，层号减1
    symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //删除该作用域中的符号
}

void def_list(struct Node *T)
{
    T->code = NULL;
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理一个局部变量定义
        T->code = T->ptr[0]->code;
        T->width = T->ptr[0]->width;
    }
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]); //处理剩下的局部变量定义
        T->code = merge(2, T->code, T->ptr[1]->code);
        T->width += T->ptr[1]->width;
    }
}

void var_def(struct Node *T)
{
    int rtn, num, width;
    struct Node *T0;
    struct opn opn1, opn2, result;
    T->code = NULL;
    if (!strcmp(T->ptr[0]->type_id, "int"))
    {
        T->ptr[1]->type = INT;
        width = 4;
    }
    else if (!strcmp(T->ptr[0]->type_id, "float"))
    {
        T->ptr[1]->type = FLOAT;
        width = 8;
    }
    else if (!strcmp(T->ptr[0]->type_id, "char"))
    {
        T->ptr[1]->type = CHAR;
    }
    else{
        T->ptr[1]->type = STRUCT;
        strcpy(struct_name, T->ptr[0]->ptr[0]->type_id);
        struct_var_flag = 1;
    }
    // T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT; //确定变量序列各变量类型
    T0 = T->ptr[1]; //T0为变量名列表子树根指针，对ID、ASSIGNOP类结点在登记到符号表，作为局部变量 DEC_LIST
    num = 0;
    T0->offset = T->offset;
    T->width = 0;
    // width = T->ptr[1]->type == INT ? 4 : 8; //一个变量宽度
    while (T0)
    { //处理所以DEC_LIST结点
        num++;
        T0->ptr[0]->type = T0->type; //类型属性向下传递
        if (T0->ptr[1])
            T0->ptr[1]->type = T0->type;

        T0->ptr[0]->offset = T0->offset; //类型属性向下传递
        if (T0->ptr[1])
            T0->ptr[1]->offset = T0->offset + width;
        if (T0->ptr[0]->kind == ID)
        {
            if(!struct_flag)
                rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
            else {
                rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV+1, T0->ptr[0]->type, 'M', T->offset + T->width); //此处偏移量未计算，暂时为0
            }
            if (rtn == -1)
                semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
            else
                T0->ptr[0]->place = rtn;
            T->width += width;
        }
        else if (T0->ptr[0]->kind == ARRAY_DEC)
        {
            int length=0;
            length=(T0->ptr[0]->type==INT)?4:(T0->ptr[0]->type==FLOAT?8:1);
            //printf("%d\n",length);
            rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'A', T->offset + T->width); //此处偏移量未计算，暂时为0
            if (rtn == -1)
                semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
            else
            {
                T0->ptr[0]->place = rtn;
                T0->ptr[0]->ptr[0]->offset = T->offset + T->width + width;
                Exp(T0->ptr[0]->ptr[0]);
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T0->ptr[0]->ptr[0]->place].alias);
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                T->code = merge(3, T->code, T0->ptr[0]->ptr[0]->code, genIR(ASSIGNOP, opn1, opn2, result));
            }
            T0->ptr[0]->ptr[0]->width=T0->ptr[0]->ptr[0]->type_int*length;
            //printf("%d\n",T0->ptr[0]->ptr[0]->width);
            T->width = T0->ptr[0]->ptr[0]->width;
        }
        else if (T0->ptr[0]->kind == ASSIGNOP)
        {
            // rtn = fillSymbolTable(T0->ptr[0]->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
             if(!struct_flag)
                rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
            else {
                rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'M', T->offset + T->width); //此处偏移量未计算，暂时为0
                // struct_flag = 0;
            }
            if (rtn == -1)
                semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
            else
            {
                T0->ptr[0]->place = rtn;
                T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
                Exp(T0->ptr[0]->ptr[1]);
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T0->ptr[0]->ptr[1]->place].alias);
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                T->code = merge(3, T->code, T0->ptr[0]->ptr[1]->code, genIR(ASSIGNOP, opn1, opn2, result));
            }
            T->width += width + T0->ptr[0]->ptr[1]->width;
        }
        T0 = T0->ptr[1];
    }
}

void stm_list(struct Node *T)
{
    if (!T->ptr[0])
    {
        T->code = NULL;
        T->width = 0;
        return;
    }              //空语句序列
    if (T->ptr[1]) //2条以上语句连接，生成新标号作为第一条语句结束后到达的位置
        strcpy(T->ptr[0]->Snext, newLabel());
    else //语句序列仅有一条语句，S.next属性向下传递
        strcpy(T->ptr[0]->Snext, T->Snext);
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->code = T->ptr[0]->code;
    T->width = T->ptr[0]->width;
    if (T->ptr[1])
    { //2条以上语句连接,S.next属性向下传递
        strcpy(T->ptr[1]->Snext, T->Snext);
        T->ptr[1]->offset = T->offset; //顺序结构共享单元方式
                                       //                  T->ptr[1]->offset=T->offset+T->ptr[0]->width; //顺序结构顺序分配单元方式
        semantic_Analysis(T->ptr[1]);
        //序列中第1条为表达式语句，返回语句，复合语句时，第2条前不需要标号
        if (T->ptr[0]->kind == RETURN || T->ptr[0]->kind == EXP_STMT || T->ptr[0]->kind == COMP_STM)
            T->code = merge(2, T->code, T->ptr[1]->code);
        else
            T->code = merge(3, T->code, genLabel(T->ptr[0]->Snext), T->ptr[1]->code);
        if (T->ptr[1]->width > T->width)
            T->width = T->ptr[1]->width; //顺序结构共享单元方式
                                         //                        T->width+=T->ptr[1]->width;//顺序结构顺序分配单元方式
    }
}

void if_then(struct Node *T)
{
    strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
    strcpy(T->ptr[0]->Efalse, T->Snext);
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    boolExp(T->ptr[0]);
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, T->Snext);
    semantic_Analysis(T->ptr[1]); //if子句
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
}

void if_then_else(struct Node *T)
{
    strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
    strcpy(T->ptr[0]->Efalse, newLabel());
    T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
    boolExp(T->ptr[0]); //条件，要单独按短路代码处理
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, T->Snext);
    semantic_Analysis(T->ptr[1]); //if子句
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    strcpy(T->ptr[2]->Snext, T->Snext);
    semantic_Analysis(T->ptr[2]); //else子句
    if (T->width < T->ptr[2]->width)
        T->width = T->ptr[2]->width;
    T->code = merge(6, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code,
                    genGoto(T->Snext), genLabel(T->ptr[0]->Efalse), T->ptr[2]->code);
}

void while_dec(struct Node *T)
{
    strcpy(T->ptr[0]->Etrue, newLabel()); //子结点继承属性的计算
    strcpy(T->ptr[0]->Efalse, T->Snext);
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    boolExp(T->ptr[0]); //循环条件，要单独按短路代码处理
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, newLabel());
    strcpy(break_label, T->Snext);
    strcpy(continue_label, T->ptr[1]->Snext);
    semantic_Analysis(T->ptr[1]); //循环体
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    T->code = merge(5, genLabel(T->ptr[1]->Snext), T->ptr[0]->code,
                    genLabel(T->ptr[0]->Etrue), T->ptr[1]->code, 
                    genGoto(T->ptr[1]->Snext));
}

void for_stmt(struct Node *T) {
    LEV++;
    // 处理循环初始语句
    T->ptr[0]->offset = T->offset;
    T->ptr[0]->ptr[0]->offset = T->ptr[0]->offset;
    Exp(T->ptr[0]->ptr[0]);
    T->ptr[0]->width = T->ptr[0]->ptr[0]->width;
    // 处理循环条件
    strcpy(T->ptr[0]->ptr[1]->Etrue, newLabel()); //子结点继承属性的计算
    strcpy(T->ptr[0]->ptr[1]->Efalse, T->Snext);
    T->ptr[0]->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
    boolExp(T->ptr[0]->ptr[1]);
    if(T->ptr[0]->width < T->ptr[0]->ptr[1]->width)
        T->ptr[0]->width = T->ptr[0]->ptr[1]->width;
    // 循环体
    strcpy(T->ptr[1]->Snext, newLabel());
    strcpy(break_label, T->Snext);
    strcpy(continue_label, T->ptr[1]->Snext);
    semantic_Analysis(T->ptr[1]);
    // 自动运算条件
    T->ptr[0]->ptr[2]->offset = T->ptr[0]->offset + T->ptr[0]->width;
    strcpy(T->ptr[0]->ptr[2]->Snext, newLabel());
    Exp(T->ptr[0]->ptr[2]);
    if(T->ptr[0]->width < T->ptr[0]->ptr[2]->width)
        T->ptr[0]->width = T->ptr[0]->ptr[2]->width;
    T->width = T->ptr[0]->width >= T->ptr[1]->width ? T->ptr[0]->width : T->ptr[1]->width;
    T->code = merge(8, T->ptr[0]->ptr[0]->code, 
                    genLabel(T->ptr[0]->ptr[2]->Snext), 
                    T->ptr[0]->ptr[1]->code,
                    genLabel(T->ptr[0]->ptr[1]->Etrue),
                    T->ptr[1]->code,
                    genLabel(T->ptr[1]->Snext),
                    T->ptr[0]->ptr[2]->code,
                    genGoto(T->ptr[0]->ptr[2]->Snext));
}

void break_dec(struct Node *T) {
    T->code = merge(2, T->code, genGoto(break_label));
}

void continue_dec(struct Node *T) {
    T->code = merge(2, T->code, genGoto(continue_label));
}

void exp_stmt(struct Node *T)
{
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->code = T->ptr[0]->code;
    T->width = T->ptr[0]->width;
}

void return_dec(struct Node *T)
{
    int rtn, num;
    struct opn opn1, opn2, result;
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        Exp(T->ptr[0]);
        num = symbolTable.index;
        do
            num--;
        while (symbolTable.symbols[num].flag != 'F');
        if (T->ptr[0]->type != symbolTable.symbols[num].type)
        {
            semantic_error(T->pos, "返回值类型错误", "");
            T->width = 0;
            T->code = NULL;
            return;
        }
        T->width = T->ptr[0]->width;
        result.kind = ID;
        strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
        result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
        T->code = merge(2, T->ptr[0]->code, genIR(RETURN, opn1, opn2, result));
    }
    else
    {
        T->width = 0;
        result.kind = 0;
        T->code = genIR(RETURN, opn1, opn2, result);
    }
}

extern char case_temp[30];

void Exp(struct Node *T)
{ //处理基本表达式，参考文献[2]p82的思想
    int rtn, num, width;
    struct Node *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case ID: //查符号表，获得符号表中的位置，类型送type
            id_exp(T);
            break;
        case INT:
            int_exp(T);
            break;
        case FLOAT:
            float_exp(T);
            break;
        case CHAR: // new
            char_exp(T);
            break;
        case ASSIGNOP:
            assignop_exp(T);
            break;
        case SUBSELF_L: // TODO
        case SUBSELF_R:
        case ADDSELF_L:
        case ADDSELF_R:
            auto_op_exp(T);
            break;
        case AND:   //按算术表达式方式计算布尔值，未写完
        case OR:    //按算术表达式方式计算布尔值，未写完
        case RELOP: //按算术表达式方式计算布尔值，未写完
            relop_exp(T);
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            op_exp(T);
            break;
        case NOT: //未写完整
            not_exp(T);
            break;
        case USUB: //未写完整
            // uminus_exp(T);
            break;
        case FUNC_CALL: //根据T->type_id查出函数的定义，如果语言中增加了实验教材的read，write需要单独处理一下
            func_call_exp(T);
            break;
        case ARGS: //此处仅处理各实参表达式的求值的代码序列，不生成ARG的实参系列
            args_exp(T);
            break;
        case EXP_ARRAY: // TODO
            exp_array(T);
            break;
        case EXP_ELE:
            exp_ele(T);
            break;
        }
    }
}

//布尔表达式
void boolExp(struct Node *T)
{
    struct opn opn1, opn2, result;
    int op;
    int rtn;
    if (T)
    {
        switch (T->kind)
        {
            case INT:
                if (T->type_int != 0)
                    T->code = genGoto(T->Etrue);
                else
                    T->code = genGoto(T->Efalse);
                T->width = 0;
                break;
            case FLOAT:
                if (T->type_float != 0.0)
                    T->code = genGoto(T->Etrue);
                else
                    T->code = genGoto(T->Efalse);
                T->width = 0;
                break;
            case ID: //查符号表，获得符号表中的位置，类型送type
                rtn = searchSymbolTable(T->type_id);
                if (rtn == -1)
                    semantic_error(T->pos, T->type_id, "变量为定义");
                if (symbolTable.symbols[rtn].flag == 'F')
                    semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
                else{
                    opn1.kind = ID;
                    strcpy(opn1.id, symbolTable.symbols[rtn].alias);
                    opn1.offset = symbolTable.symbols[rtn].offset;
                    opn2.kind = INT;
                    opn2.const_int = 0;
                    result.kind = ID;
                    strcpy(result.id, T->Etrue);
                    T->code = genIR(NEQ, opn1, opn2, result);
                    T->code = merge(2, T->code, genGoto(T->Efalse));
                }
                T->width = 0;
                break;
            case RELOP: //处理关系运算表达式,2个操作数都按基本表达式处理
                T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
                Exp(T->ptr[0]);
                T->width = T->ptr[0]->width;
                Exp(T->ptr[1]);
                if (T->width < T->ptr[1]->width)
                    T->width = T->ptr[1]->width;
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
                opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
                opn2.kind = ID;
                strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
                opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
                result.kind = ID;
                strcpy(result.id, T->Etrue);
                if (strcmp(T->type_id, "<") == 0)
                    op = JLT;
                else if (strcmp(T->type_id, "<=") == 0)
                    op = JLE;
                else if (strcmp(T->type_id, ">") == 0)
                    op = JGT;
                else if (strcmp(T->type_id, ">=") == 0)
                    op = JGE;
                else if (strcmp(T->type_id, "==") == 0) {
                    op = EQ;
                } 
                else if (strcmp(T->type_id, "!=") == 0)
                    op = NEQ;
                T->code = genIR(op, opn1, opn2, result);
                T->code = merge(4, T->ptr[0]->code, T->ptr[1]->code, T->code, genGoto(T->Efalse));
                break;
            case AND:
            case OR:
                if (T->kind == AND)
                {
                    strcpy(T->ptr[0]->Etrue, newLabel());
                    strcpy(T->ptr[0]->Efalse, T->Efalse);
                }
                else
                {
                    strcpy(T->ptr[0]->Etrue, T->Etrue);
                    strcpy(T->ptr[0]->Efalse, newLabel());
                }
                strcpy(T->ptr[1]->Etrue, T->Etrue);
                strcpy(T->ptr[1]->Efalse, T->Efalse);
                T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
                boolExp(T->ptr[0]);
                T->width = T->ptr[0]->width;
                boolExp(T->ptr[1]);
                if (T->width < T->ptr[1]->width)
                    T->width = T->ptr[1]->width;
                if (T->kind == AND)
                    T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
                else
                    T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Efalse), T->ptr[1]->code);
                break;
            case NOT:
                strcpy(T->ptr[0]->Etrue, T->Efalse);
                strcpy(T->ptr[0]->Efalse, T->Etrue);
                boolExp(T->ptr[0]);
                T->code = T->ptr[0]->code;
                break;
            default:
                break;
        }
    }
}


void id_exp(struct Node *T)
{
    int rtn, num, width;

    rtn = searchSymbolTable(T->type_id);
    if (rtn == -1)
        semantic_error(T->pos, T->type_id, "变量未定义");
    if (symbolTable.symbols[rtn].flag == 'F')
        semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
    else
    {
        T->place = rtn; //结点保存变量在符号表中的位置
        T->code = NULL; //标识符不需要生成TAC
        T->type = symbolTable.symbols[rtn].type;
        T->offset = symbolTable.symbols[rtn].offset;
        T->width = 0; //未再使用新单元
    }
}

void int_exp(struct Node *T){
    struct opn opn1, opn2, result;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为整常量生成一个临时变量
    T->type = INT;
    opn1.kind = INT;
    opn1.const_int = T->type_int;
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
    T->width = 4;
}

void float_exp(struct Node *T)
{
    int rtn, num, width;
    struct opn opn1, opn2, result;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为浮点常量生成一个临时变量
    T->type = FLOAT;
    opn1.kind = FLOAT;
    opn1.const_float = T->type_float;
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
    T->width = 4;
}

void char_exp(struct Node *T)
{
    int rtn, num, width;
    struct opn opn1, opn2, result;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为整常量生成一个临时变量
    T->type = CHAR;
    opn1.kind = CHAR;
    // strcpy(opn1.const_string, T->type_string);
    opn1.const_string = T->type_string;
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    T->code = genIR(ASSIGNOP, opn1, opn2, result);
    // T->width = 1;
}

void assignop_exp(struct Node *T)
{
    int rtn, num, width;
    struct opn opn1, opn2, result;
    if (T->ptr[0]->kind != ID && T->ptr[0]->kind != EXP_ELE && T->ptr[0]->kind != EXP_ARRAY)
    {
        semantic_error(T->pos, "", "赋值语句需要左值");
    }
    else
    {
        Exp(T->ptr[0]); //处理左值，例中仅为变量
        T->ptr[1]->offset = T->offset;
        Exp(T->ptr[1]);
        if(T->ptr[0]->type != T->ptr[1]->type){
            semantic_error(T->pos,"", "赋值运算左右类型不匹配");
            return;
        }
        if (T->ptr[0]->type==CHAR && T->kind!=ASSIGNOP){
            semantic_error(T->pos,T->ptr[0]->type_id,"是字符类型变量，不能参与运算");
            return;
        }
        if (T->ptr[1]->type==CHAR && T->kind!=ASSIGNOP){
            semantic_error(T->pos,T->ptr[1]->type_id,"是字符类型变量，不能参与运算");
            return;
        }

        if (symbolTable.symbols[T->ptr[0]->place].type == INT) {
            symbolTable.symbols[T->ptr[0]->place].const_int = T->ptr[1]->type_int;
        }

        T->type = T->ptr[0]->type;
        T->width = T->ptr[1]->width;
        T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);

        if(T->ptr[1]->kind != EXP_ARRAY && T->ptr[1]->kind != EXP_ELE) {
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias); //右值一定是个变量或临时变量
            opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
        }
        else{
            opn1.kind=ID;
			char s[10];
			char str[80];
			strcpy (str,symbolTable.symbols[T->ptr[1]->place].alias);
			strcat (str," offset ");
			//ito(T->ptr[0]->offset,s,0);
            sprintf(s,"%d",T->ptr[1]->offset);
            //itoa(no++,s,10);
            //sprintf(s, "%d", no++);
			strcat (str,s);

			strcpy(opn1.id,str);
			opn1.offset=T->ptr[1]->offset;
        }

        if(T->ptr[0]->kind != EXP_ARRAY && T->ptr[0]->kind != EXP_ELE) {
            // printf("%s\n",symbolTable.symbols[T->ptr[0]->place].alias);
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
            result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
        }
        else if(T->ptr[0]->kind == EXP_ARRAY){ 
            result.kind=ID;
			char s[10];
			char str[80];
            T->ptr[0]->width=symbolTable.symbols[T->ptr[0]->place].type==INT?4:(symbolTable.symbols[T->ptr[0]->place].type==FLOAT?8:1);
			strcpy (str,symbolTable.symbols[T->ptr[0]->place].alias);
			strcat (str," offset ");
            sprintf(s,"%d",T->ptr[0]->type_int*T->ptr[0]->width+T->ptr[0]->offset);
			strcat (str,s);

			strcpy(result.id,str);
			result.offset=T->ptr[0]->type_int;
        }
        else{
            result.kind=ID;
			char s[10];
			char str[80];
			strcpy (str,symbolTable.symbols[T->ptr[0]->place].alias);
			strcat (str," offset ");
			sprintf(s,"%d",T->ptr[0]->offset);
            strcat (str,s);

			strcpy(result.id,str);
			result.offset=T->ptr[0]->offset;
        }
        
        T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
    }
}


void auto_op_exp(struct Node *T) {
    int rtn, num, width;
    struct opn opn1, opn2, result;
    struct opn result2;
    if (T->ptr[0]->kind != ID){
        semantic_error(T->pos, "", "赋值语句需要左值");
    }
    else {
        T->ptr[0]->offset = T->offset;
        Exp(T->ptr[0]);
        T->type = T->ptr[0]->type;
        T->width = T->ptr[0]->width;

        T->place = T->ptr[0]->place;

        opn1.kind = INT;
        opn1.const_int = 1;
        result.kind = ID;
        strcpy(result.id, newTemp());
        T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));

        opn1.kind = ID;
        strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
        result2.kind = ID;
        strcpy(result2.id, newTemp());
        if (T->kind == ADDSELF_L || T->kind == ADDSELF_R)
            T->code = merge(2, T->code, genIR(ADD, opn1, result, result2));
        else if(T->kind == SUBSELF_L || T->kind == SUBSELF_R)
            T->code = merge(2, T->code, genIR(SUB, opn1, result, result2));

        T->code = merge(2, T->code, genIR(ASSIGNOP, result2, opn2, opn1));
    }
}

void relop_exp(struct Node *T)
{
    T->type = INT;
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    Exp(T->ptr[0]);
    Exp(T->ptr[1]);
}

void args_exp(struct Node *T)
{
    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
    T->type = T->ptr[0]->type;
    T->width = T->ptr[0]->width;
    T->code = T->ptr[0]->code;
    if (T->ptr[1]) {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        Exp(T->ptr[1]);
        T->width += T->ptr[1]->width;
        T->code = merge(2, T->code, T->ptr[1]->code);
    }
}

// 算数运算：加减乘除
void op_exp(struct Node *T)
{
    int rtn, num, width;
    struct opn opn1, opn2, result;
    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
    T->ptr[1]->offset = T->offset + T->ptr[0]->width;
    Exp(T->ptr[1]);
    //判断T->ptr[0]，T->ptr[1]类型是否正确，可能根据运算符生成不同形式的代码，给T的type赋值
    //下面的类型属性计算，没有考虑错误处理情况
    if (T->ptr[0]->type == FLOAT || T->ptr[1]->type == FLOAT)
        T->type = FLOAT, T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
    else
        T->type = INT, T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
    
    opn1.kind = ID;
    strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
    opn1.type = T->ptr[0]->type;
    opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;

    opn2.kind = ID;
    strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
    opn2.type = T->ptr[1]->type;
    opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;

    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.type = T->type;
    result.offset = symbolTable.symbols[T->place].offset;

    T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(T->kind, opn1, opn2, result));
    if (T->type == INT) {
        T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
    }
    else if(T->type == FLOAT) {
        T->width = T->ptr[0]->width + T->ptr[1]->width + 8;
    }
    else if(T->type == CHAR) {
        T->width = T->ptr[0]->width + T->ptr[1]->width + 1;
    }
}

void func_call_exp(struct Node *T)
{
    int rtn, num, width;
    int count = 0, param_num;
    struct Node *T0;
    struct Node *T1;
    struct opn opn1, opn2, result;
    rtn = searchSymbolTable(T->type_id);
    if (rtn == -1)
    {
        semantic_error(T->pos, T->type_id, "函数未定义");
        return;
    }
    if (symbolTable.symbols[rtn].flag != 'F')
    {
        semantic_error(T->pos, T->type_id, "不是一个函数");
        return;
    }
    T->type = symbolTable.symbols[rtn].type;
    // 存放函数返回值的单数字节数
    if(T->type == INT) {
        width = 4;
    }
    else if(T->type == FLOAT) {
        width = 8;
    }
    else if(T->type == CHAR) {
        width = 1;
    }
    if (T->ptr[0]) {
        T->ptr[0]->offset = T->offset;
        Exp(T->ptr[0]);                      //处理所有实参表达式求值，及类型
        T->width = T->ptr[0]->width + width; //累加上计算实参使用临时变量的单元数
        T->code = T->ptr[0]->code;
    }
    else{
        T->width = width;
        T->code = NULL;
    }
    T1 = T->ptr[0];
    while(T1 != NULL) {
        count++;
        num = rtn;
        if(symbolTable.symbols[rtn+count].flag == 'P' && T1->type != symbolTable.symbols[rtn+count].type){
            semantic_error(T1->pos, "", "实参与形参类型不符");
        }
        T1 = T1->ptr[1];
    }
    param_num = symbolTable.symbols[rtn].paramnum;
    if (count > param_num) {
        semantic_error(T->pos, "", "函数参数数量太多");
    }
    else if(count < param_num) {
        semantic_error(T->pos, "", "函数参数数量太少");
    }
    else
        match_param(rtn, T->ptr[0]); //处理所以参数的匹配
    //处理参数列表的中间代码
    T0 = T->ptr[0];
    while (T0){
        result.kind = ID;
        strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
        result.offset = symbolTable.symbols[T0->ptr[0]->place].offset;
        T->code = merge(2, T->code, genIR(ARG, opn1, opn2, result));
        T0 = T0->ptr[1];
    }
    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
    opn1.kind = ID;
    strcpy(opn1.id, T->type_id); //保存函数名
    opn1.offset = rtn;           //这里offset用以保存函数定义入口,在目标代码生成时，能获取相应信息
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[T->place].alias);
    result.offset = symbolTable.symbols[T->place].offset;
    T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result)); //生成函数调用中间代码
}

void not_exp(struct Node *T)
{
    T->type = INT;
    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
}

void unminus_exp(struct Node *T)
{
    T->type = T->ptr[0]->type;
    T->ptr[0]->offset = T->offset;
    Exp(T->ptr[0]);
}

void exp_array(struct Node *T){
    int rtn;
    struct Node *T0;
    rtn=searchSymbolTable(T->type_id);
	if (rtn==-1)
        semantic_error(T->pos,T->type_id, "变量未定义");
    else if(symbolTable.symbols[rtn].flag != 'A')
        semantic_error(T->pos,T->type_id, "变量不是数组");
    else {
        int index = 0;
		T0 = T->ptr[0];
        T->place = rtn;       //结点保存变量在符号表中的位置
        T->code = NULL;       //标识符不需要生成TAC
        T->type = symbolTable.symbols[rtn].type; // 标记ID类型
        T->offset = (T->type == INT ? 4 : (T->type == FLOAT ? 8 : 1)) * compute_width0(T->ptr[0], symbolTable.symbols[rtn].array, 0); // 内存中偏移值
        T->width = symbolTable.symbols[rtn+1].offset-symbolTable.symbols[rtn].offset;   //未再使用新单元
		// while(T0->kind==ARRAY_LIST){
		// 	Exp(T0->ptr[0]);
		// 	if(T0->ptr[0]->type != INT){
        //         semantic_error(T->pos,"", "数组维数需要整型");
        //         break;                      
        //     }
		// 	if(index == 8){
		// 		semantic_error(T->pos,"", "数组维度超过最大值");
		// 		break;
		// 	}
		// 	else if(symbolTable.symbols[rtn].array[index] <= T0->type_int){
		// 		semantic_error(T->pos,"", "数组维度超过定义值");
		// 		break;
        //     }
		// 	index++;
		// 	T0=T0->ptr[1];
		// }
        //处理最后一维
        //printf("%d %d\n",T->width,rtn);
		if(T0->kind == ARRAY_LAST){
            T->type_int=T0->type_int;
            if(T0->type!=INT){
                semantic_error(T->pos,"", "数组需要整型");                     
            }
            else if(T0->type_int >=(symbolTable.symbols[rtn+1].offset-symbolTable.symbols[rtn].offset-4)){
                semantic_error(T->pos,"", "数组维度超过最大值");
            }
	    }
        
    }
}

void exp_ele(struct Node *T)
{
    int rtn,flag=0;
    int rtn2;
    rtn=searchSymbolTable(T->type_id);
    Exp(T->ptr[0]);
    if (symbolTable.symbols[T->ptr[0]->place].type != STRUCT) {
        semantic_error(T->pos, symbolTable.symbols[T->ptr[0]->place].name, "变量不是结构");
    }
    rtn = searchSymbolTable(symbolTable.symbols[T->ptr[0]->place].struct_name);
    rtn2 = searchSymbolTable(symbolTable.symbols[T->ptr[0]->place].name);
    if(rtn == -1) {
        semantic_error(T->pos, symbolTable.symbols[T->ptr[0]->place].struct_name, "结构为定义");
        return;
    }

    T->place = rtn2;
    
    for(rtn=0;rtn < symbolTable.index;rtn++){
        //printf("%d %s %s\n",rtn,symbolTable.symbols[rtn].name,T->type_id);
        if(!strcmp(symbolTable.symbols[rtn].name, T->type_id)&& symbolTable.symbols[rtn].flag == 'M') {
            flag = 1;
            break;
        }
    } 

    if(!flag) {
        semantic_error(T->pos, T->type_id, "不是该结构的成员变量");
    }
    else{
        T->type = symbolTable.symbols[rtn].type;
        T->offset = symbolTable.symbols[rtn].offset;
    }
}