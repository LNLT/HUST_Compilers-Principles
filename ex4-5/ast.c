#include "def.h"
#include "c_blue.tab.h"
#include "stdlib.h"
symbolTable myTable = {{0}, 0};
symbol_scope_TX myScope = {{0}, 0};

int i, j, t, counter = 0;
int rtn, flag1, flag2, num;
int mem, stru_dec = 0;
char struct_name[33];
int loop_flag = 0;
int left_required = 0;
int array_size = 0;

struct Node *mknode(int num, int kind, int pos, ...)
{
    struct Node *T = (struct Node *)calloc(sizeof(struct Node), 1);
    int i = 0;
    T->kind = kind;
    T->pos = pos;
    va_list pArgs;
    va_start(pArgs, pos);
    for (i = 0; i < num; i++)
        T->ptr[i] = va_arg(pArgs, struct Node *);
    while (i < 4)
        T->ptr[i++] = NULL;
    va_end(pArgs);
    return T;
}

void display(struct Node *T, int indent) //对抽象语法树的先根遍历
{
    int i = 1;
    struct Node *T0;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            display(T->ptr[0], indent); //显示该外部定义（外部变量和函数）列表中的第一个
            display(T->ptr[1], indent); //显示该外部定义列表中的其它外部定义
            break;
        case EXT_VAR_DEF:
            printf("%*c外部变量定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示外部变量类型
            printf("%*c变量名：\n", indent + 3, ' ');
            display(T->ptr[1], indent + 6); //显示变量列表
            break;
        case EXT_STRUCT_DEF:
            printf("%*c结构体定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示外部变量类型
            break;
        case TYPE:
            printf("%*c类型： %s\n", indent, ' ', T->type_id);
            break;
        case EXT_DEC_LIST:
            display(T->ptr[0], indent); //依次显示外部变量名，
            display(T->ptr[1], indent); //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
            break;
        case FUNC_DEF:
            printf("%*c函数定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示函数返回类型
            display(T->ptr[1], indent + 3); //显示函数名和参数
            display(T->ptr[2], indent + 3); //显示函数体
            break;
        case VOID_FUNC_DEF:
            printf("%*c函数定义：(%d)\n", indent, ' ', T->pos);
            printf("%*c类型：%s\n", indent + 3, ' ', T->type_id);
            display(T->ptr[0], indent + 3); //显示函数名和参数
            display(T->ptr[1], indent + 3); //显示函数体
            break;
        case STRUCT_DEF:
            printf("%*c结构定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            display(T->ptr[1], indent + 3);
            break;
        case STRUCT_DEC:
            printf("%*c结构定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            break;
        case FUNC_DEC:
            printf("%*c函数名：%s\n", indent, ' ', T->type_id);
            if (T->ptr[0])
            {
                printf("%*c函数形参：\n", indent, ' ');
                display(T->ptr[0], indent + 3); //显示函数参数列表
            }
            else
                printf("%*c无参函数\n", indent + 3, ' ');
            break;
        case PARAM_LIST:
            display(T->ptr[0], indent); //依次显示全部参数类型和名称，
            display(T->ptr[1], indent);
            break;
        case PARAM_DEC:
            printf("%*c类型：%s, 参数名：%s\n", indent, ' ', T->ptr[0]->type == CHAR ? "char":(INT ? "int" : "float"), T->ptr[1]->type_id);
            break;
        case ARRAY_DEC:
            printf("%*c数组：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent);
            printf("%*cINT：%d\n", indent, ' ', T->type_int);
            break;
        case EXP_STMT:
            printf("%*c表达式语句：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            break;
        case RETURN:
            printf("%*c返回语句：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3);
            break;
        case COMP_STM:
            printf("%*c复合语句：(%d)\n", indent, ' ', T->pos);
            printf("%*c复合语句的变量定义部分：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示定义部分
            printf("%*c复合语句的语句部分：\n", indent + 3, ' ');
            display(T->ptr[1], indent + 6); //显示语句部分
            break;
        case STM_LIST:
            display(T->ptr[0], indent); //显示第一条语句
            display(T->ptr[1], indent); //显示剩下语句
            break;
        case WHILE:
            printf("%*c循环语句：(%d)\n", indent, ' ', T->pos);
            printf("%*c循环条件：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示循环条件
            printf("%*c循环体：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[1], indent + 6); //显示循环体
            break;
        case IF_THEN:
            printf("%*c条件语句(IF_THEN)：(%d)\n", indent, ' ', T->pos);
            printf("%*c条件：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示条件
            printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[1], indent + 6); //显示if子句
            break;
        case IF_THEN_ELSE:
            printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n", indent, ' ', T->pos);
            printf("%*c条件：\n", indent + 3, ' ');
            display(T->ptr[0], indent + 6); //显示条件
            printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[1], indent + 6); //显示if子句
            printf("%*cELSE子句：(%d)\n", indent + 3, ' ', T->pos);
            display(T->ptr[2], indent + 6); //显示else子句
            break;
        case READ:
            printf("%*cREAD语句：(%d)\n", indent, ' ', T->pos);
            printf("%*cID： %s\n", indent+3, ' ', T->type_id);
            break;
        case WRITE:
            printf("%*cWRITE语句：(%d)\n", indent, ' ', T->pos);
            printf("%*cID： %s\n", indent+3, ' ', T->type_id);
            display(T->ptr[0], indent + 6);
            break;
        case BREAK:
            printf("%*cBREAK语句：(%d)\n", indent, ' ', T->pos);
            break;
        case CONTINUE:
            printf("%*cCONTINUE语句：(%d)\n", indent, ' ', T->pos);
            break;
        case DEF_LIST:
            display(T->ptr[0], indent); //显示该局部变量定义列表中的第一个
            display(T->ptr[1], indent); //显示其它局部变量定义
            break;
        case VAR_DEF:
            printf("%*c局部变量定义：(%d)\n", indent, ' ', T->pos);
            display(T->ptr[0], indent + 3); //显示变量类型
            display(T->ptr[1], indent + 3); //显示该定义的全部变量名
            break;
        case DEC_LIST:
            printf("%*c变量名：\n", indent, ' ');
            display(T->ptr[0], indent + 3);
            break;
        case DEC_LISTS:
            printf("%*c变量列表：\n", indent, ' ');
            display(T->ptr[0], indent + 3);
            display(T->ptr[1], indent + 3);
            break;
        case ID:
            printf("%*cID： %s\n", indent, ' ', T->type_id);
            break;
        case INT:
            printf("%*cINT：%d\n", indent, ' ', T->type_int);
            break;
        case CHAR:
            printf("%*cCHAR: %s\n", indent, ' ', T->type_char);
            break;
        case FLOAT:
            printf("%*cFLAOT：%f\n", indent, ' ', T->type_float);
            break;
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            printf("%*c%s\n", indent, ' ', T->type_id);
            display(T->ptr[0], indent + 3);
            display(T->ptr[1], indent + 3);
            break;
        case ADDSELF:
        case SUBSELF:
        case NOT:
        case USUB:
            printf("%*c%s\n", indent, ' ', T->type_id);
            display(T->ptr[0], indent + 3);
            break;
        case FUNC_CALL:
            printf("%*c函数调用：(%d)\n", indent, ' ', T->pos);
            printf("%*c函数名：%s\n", indent + 3, ' ', T->type_id);
            display(T->ptr[0], indent + 3);
            break;
        case EXP_ELE:
            printf("%*c结构体访问：\n", indent, ' ');
            display(T->ptr[0], indent + 3);
            printf("%*c访问成员变量：%s\n", indent + 3, ' ', T->type_id);
            break;
        case EXP_ARRAY:
            display(T->ptr[0], indent);
            printf("%*cINT：%d\n", indent, ' ', T->type_int);
            break;
        case ARGS:
            i = 1;
            while (T)
            { //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
                struct Node *T0 = T->ptr[0];
                printf("%*c第%d个实际参数表达式：\n", indent, ' ', i++);
                display(T0, indent + 3);
                T = T->ptr[1];
            }
            printf("\n");
            break;
        }
    }
}

void prn_symbol()//显示符号表
{ 
    int i;
    printf("\n***符号表***\n");
    printf("----------------------------------------------------------------------\n");
    printf("%6s\t%6s\t\t%6s\t\t%6s\t\t%6s\t\t%6s\t%6s\t%6s\n","索引","名字","层号","类型","标记","参数个数","数组大小","所属结构");
    printf("----------------------------------------------------------------------\n");
    for(i = 0;i <
     myTable.index; i++){
        printf("%-4d\t",i);
        printf("%-6s\t",myTable.symbols[i].name);
        printf("%-4d\t",myTable.symbols[i].level);
        if(myTable.symbols[i].type==INT)
               printf("%-6s\t","int");
        else if(myTable.symbols[i].type==FLOAT)
            printf("%-6s\t","float");
        else if(myTable.symbols[i].type==CHAR)
            printf("%-6s\t","char");
        else if(myTable.symbols[i].type==STRUCT)
            printf("%-6s\t", "struct");
        else
            printf("%-6s\t","void");
            
        printf("%-6c\t",myTable.symbols[i].flag);
        if(myTable.symbols[i].flag=='F')
            printf("%-4d\t\t",myTable.symbols[i].paramnum);
        else printf("null\t\t");
        if(myTable.symbols[i].flag == 'A')
            printf("%-4d\t\t", myTable.symbols[i].array_size);
        else
            printf("null\t\t");
        if(myTable.symbols[i].flag == 'M')
            printf("%-6s\n", myTable.symbols[i].struct_name);
        else
            printf("null\n");
    }
    printf("\n");
}

int searchmyTable(char *name)
{
    int i, flag = 0;
    for (i = myTable.index - 1; i >= 0; i--)
    {
        if (myTable.symbols[i].level == 0)
            flag = 1;
        if (flag && myTable.symbols[i].level == 1)
            continue; //跳过前面函数的形式参数表项
        if (!strcmp(myTable.symbols[i].name, name))
            return i;
    }
    return -1;
}

int fillmyTable(char *name, char *alias, int level, int type, char flag, int offset)
{
    //首先根据name查符号表，不能重复定义 重复定义返回-1
    int i;
    /*符号查重，考虑外部变量声明前有函数定义，
    其形参名还在符号表中，这时的外部变量与前函数的形参重名是允许的*/
    for (i = myTable.index - 1; i >= 0 && (myTable.symbols[i].level == level || level == 0); i--)
    {
        if (level == 0 && myTable.symbols[i].level == 1)
            continue; //外部变量和形参不必比较重名
        if (!strcmp(myTable.symbols[i].name, name))
            return -1;
    }
    //填写符号表内容
    strcpy(myTable.symbols[myTable.index].name, name);
    strcpy(myTable.symbols[myTable.index].alias, alias);
    myTable.symbols[myTable.index].level = level;
    myTable.symbols[myTable.index].type = type;
    myTable.symbols[myTable.index].flag = flag;
    myTable.symbols[myTable.index].offset = offset;
    return myTable.index++; //返回的是符号在符号表中的位置序号，中间代码生成时可用序号取到符号别名
}

int semantic_Analysis(struct Node *T, int type, int level, char flag, int command){
    int type1, type2;
    if(T) {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case EXT_VAR_DEF:
            type = semantic_Analysis(T->ptr[0], type, level, flag, command);
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case EXT_STRUCT_DEF:
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            break;
        case FUNC_DEF:
            type = semantic_Analysis(T->ptr[0], type, level+1, flag, command);
            flag1 = 1;
            semantic_Analysis(T->ptr[1], type, 1, flag, command);
            semantic_Analysis(T->ptr[2], type, 1, flag, command);
            num = myTable.index;
            do{
                num--;
            } while (myTable.symbols[num].flag == 'P');
            myTable.index = num+1; 
            flag1 = 0;
            flag2 = 0;
            break;
        case VOID_FUNC_DEF:
            type = semantic_Analysis(T->ptr[0], type, level+1, flag, command);
            semantic_Analysis(T->ptr[1], type, 1, flag, command);
            semantic_Analysis(T->ptr[2], type, 1, flag, command);
            num = myTable.index;
            do{
                num--;
            } while (myTable.symbols[num].flag == 'P');
            myTable.index = num+1;
            if(flag1==0 && flag2==1){
                semantic_error(T->pos, T->type_id, "函数不应该有返回值");
            }   
            flag1 = 0;
            flag2 = 0;
            break;
        case EXT_DEC_LIST:
            flag = 'V';
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case TYPE:
            return T->type;
        case STRUCT_DEF:
            rtn = searchmyTable(T->ptr[0]->type_id);
            if(rtn != -1){
                if(myTable.symbols[rtn].flag == 'S'){
                    semantic_error(T->pos, "", "结构体名重复定义");
                }
            }
            strcpy(myTable.symbols[myTable.index].name, T->ptr[0]->type_id);
            strcpy(struct_name, T->ptr[0]->type_id);
            myTable.symbols[myTable.index].level = level;
            myTable.symbols[myTable.index].flag = 'S';
            myTable.symbols[myTable.index].type = STRUCT;
            myTable.index++;
            flag = 'M';
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case STRUCT_DEC:
            rtn = searchmyTable(T->ptr[0]->type_id);
            if(rtn == -1){
                semantic_error(T->pos, T->type_id, "结构体未定义");
            }
            else{
                strcpy(struct_name, T->ptr[0]->type_id);
            }
            break;
        case ID:
            i=0;
            if(command == 0){ //定义变量
                while(i < myTable.index){
                    if(!strcmp(myTable.symbols[i].name,T->type_id) && myTable.symbols[i].level==level){
                        if(flag=='V')
                            semantic_error(T->pos, T->type_id, "全局变量重复定义");
                        else if(flag=='F')
                            semantic_error(T->pos, T->type_id, "函数名重复定义");
                        else if(flag=='T')
                            semantic_error(T->pos, T->type_id, "局部变量重复定义");
                        else if(flag=='M' && !strcmp(myTable.symbols[i].struct_name,struct_name))
                            semantic_error(T->pos, "", "成员变量重复定义");
                        else{
                            semantic_error(T->pos, "", "函数参数定义重复");
                        }
                           
                        return 0;
                    }
                    i++;
                }
                strcpy(myTable.symbols[myTable.index].name, T->type_id);
                myTable.symbols[myTable.index].level = level;
                myTable.symbols[myTable.index].flag = flag;
                myTable.symbols[myTable.index].type = type;
                if (flag=='M') {
                    strcpy(myTable.symbols[myTable.index].struct_name, struct_name);
                }
                myTable.index++;
                return type;
            }
            else{ // 使用变量
                i = myTable.index;
                while(i>= 0){
                    // printf("%d %s %d\n",i,T->type_id,myTable.symbols[i].type);
                    if(myTable.symbols[i].level <= level && !strcmp(myTable.symbols[i].name, T->type_id) && (myTable.symbols[i].flag != 'S' && myTable.symbols[i].flag != 'F'))
                    {
                        return myTable.symbols[i].type;
                    }    
                    i--;
                }
                if(i< 0){
                    semantic_error(T->pos, T->type_id, "变量未定义");
                }
            }
            break;
        case FUNC_DEC:
            rtn = searchmyTable(T->type_id);
            if(rtn != -1){
                if(myTable.symbols[rtn].flag == 'F'){
                    semantic_error(T->pos, T->type_id, "函数名重复定义");
                }
            }
            strcpy(myTable.symbols[myTable.index].name, T->type_id);
            myTable.symbols[myTable.index].flag = 'F';
            myTable.symbols[myTable.index].level = 0;
            myTable.symbols[myTable.index].type = type;
            myTable.index++;
            counter = 0;
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            myTable.symbols[myTable.index - counter - 1].paramnum = counter;
            break;
        case PARAM_LIST:
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case PARAM_DEC:
            counter++;
            flag = 'P';
            type = semantic_Analysis(T->ptr[0], type, level+1, flag, command);
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case ARRAY_DEC:
            rtn = searchmyTable(T->ptr[0]->type_id);
            if(rtn != -1 && T->ptr[0]->type==myTable.symbols[rtn].type){
                if(myTable.symbols[rtn].level == level){
                    semantic_error(T->pos, "", "数组名重复定义");
                }
            }
            else{
                strcpy(myTable.symbols[myTable.index].name, T->ptr[0]->type_id);
                myTable.symbols[myTable.index].level = level;
                myTable.symbols[myTable.index].flag = 'A';
                myTable.symbols[myTable.index].type = type;
                myTable.symbols[myTable.index].array_size = T->type_int;
                myTable.index++;
                //semantic_Analysis(T->ptr[0], type, level, 'A', 0);
            }
            break;
        case COMP_STM:
            flag = 'T';
            command = 0;
            myScope.TX[myScope.top++] = myTable.index;
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            command = 1;
            semantic_Analysis(T->ptr[1], type, level+1, flag, command);
            prn_symbol();
            myTable.index = myScope.TX[--myScope.top];
            break;
        case STM_LIST:
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            semantic_Analysis(T->ptr[1], type, level, flag, command);
            break;
        case EXP_STMT:
            semantic_Analysis(T->ptr[0], type, level, flag, command);
            break;
        case RETURN:
            flag2 = 1;
            if(flag1){
                if(!T->ptr[0]){
                    semantic_error(T->pos, "", "缺少返回值");
                    break;
                }
            }
            type = semantic_Analysis(T->ptr[0], type, level, flag, command);
            num = myTable.index;
            do{
                num--;
            }while (myTable.symbols[num].flag != 'F');
            if( !(!flag1 && !T->ptr[0]) && type != myTable.symbols[num].type){
                semantic_error(T->pos, "", "返回值类型错误");
            }
            break;
        case IF_THEN:
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            semantic_Analysis(T->ptr[1],type,level,flag,command);
            break;
        case IF_THEN_ELSE:
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            semantic_Analysis(T->ptr[1],type,level,flag,command);
            semantic_Analysis(T->ptr[2],type,level,flag,command);
            break;
        case WHILE:
            loop_flag++;
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            semantic_Analysis(T->ptr[1],type,level,flag,command);
            loop_flag--;
            break;
        case READ:
        case WRITE:
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            break;
        case BREAK:
            if(!loop_flag)
                semantic_error(T->pos, "", "break语句要在循环语句中");
            break;
        case CONTINUE:
            if(!loop_flag)
                semantic_error(T->pos, "", "continue语句要在循环语句中");
            break;
        case DEF_LIST:
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            semantic_Analysis(T->ptr[1],type,level,flag,command);
            break;
        case VAR_DEF:
            type = semantic_Analysis(T->ptr[0],type,level+1,flag,command);
            semantic_Analysis(T->ptr[1],type,level,flag,command);
            break;
        case DEC_LIST:
            if(stru_dec){
                type = STRUCT;
            }
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            break;
        case DEC_LISTS:
            if(stru_dec){
                type = STRUCT;
            }
            semantic_Analysis(T->ptr[0],type,level,flag,command);
            semantic_Analysis(T->ptr[1],type,level,flag,command);
            break;
        case ASSIGNOP:
            if(T->ptr[0]->kind != ID && T->ptr[0]->kind != EXP_ARRAY && T->ptr[0]->kind != EXP_ELE) {
                semantic_error(T->pos, "", "赋值表达式需要左值");
            }
            if(T->ptr[0]->kind == ID){
                rtn = searchmyTable(T->ptr[0]->type_id);
                if(myTable.symbols[rtn].flag=='A'){
                    semantic_error(T->pos, "", "类型不匹配");
                }
                else if(myTable.symbols[rtn].type == STRUCT){
                    semantic_error(T->pos, "", "赋值表达式左值不应该是结构体变量");
                }
                else{
                    type1 = semantic_Analysis(T->ptr[0], type, level, flag, command);
                    type2 = semantic_Analysis(T->ptr[1], type, level, flag, command);
                    if(type1 == type2)
                        return type1;
                }
            }
            else{
                type1 = semantic_Analysis(T->ptr[0], type, level, flag, command);
                type2 = semantic_Analysis(T->ptr[1], type, level, flag, command);
                // printf("%d %d\n",type1 ,type2);
                if(type1 == type2)
                    return type1;
            }
            break;
        case AND:
        case OR:
        case RELOP:
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            type1 = semantic_Analysis(T->ptr[0], type, level, flag, command);
            type2 = semantic_Analysis(T->ptr[1], type, level, flag, command);
            if(type1 == type2)
                return type1;
            break;
        case ADDSELF:
        case SUBSELF:
        case USUB:
        case NOT:
            if(T->ptr[0]->kind == ID){
                rtn = searchmyTable(T->ptr[0]->type_id);
                if(rtn == -1){
                    semantic_error(T->pos, T->ptr[0]->type_id, "变量未定义");
                }
                else{
                    if(myTable.symbols[rtn].type == STRUCT)
                        semantic_error(T->pos, T->ptr[0]->type_id, "不是左值");
                    else{
                        if(T->ptr[0]->kind != ID && T->ptr[0]->kind != EXP_ARRAY && T->ptr[0]->kind != EXP_ELE){
                            semantic_error(T->pos, "", "自增自减表达式需要左值");
                            break;
                        }
                        if(T->ptr[0]->kind == ID){
                            rtn = searchmyTable(T->ptr[0]->type_id);
                            if(myTable.symbols[rtn].type == STRUCT){
                                semantic_error(T->pos, "", "赋值表达式需要左值");
                            }
                        }
                        type1 = semantic_Analysis(T->ptr[0], type, level, flag, command);
                        return type1;
                    }
                }
            }
            else if(T->ptr[0]->kind == EXP_ELE || T->ptr[0]->kind == EXP_ARRAY || !strcmp(T->ptr[0]->type_id, "ADDSELF") || !strcmp(T->ptr[0]->type_id, "SUBSELF")){
                type1 = semantic_Analysis(T->ptr[0], type, level, flag, command);
                return type1;
            }
            else{
                semantic_error(T->pos, "", "自增自减表达式需要左值");
            }
            break;
        case FUNC_CALL:
            rtn = searchmyTable(T->type_id);
            if(rtn != -1){
                if(myTable.symbols[rtn].flag != 'F'){
                    semantic_error(T->pos, T->type_id, "不是函数");
                    return 0;
                }
                type = myTable.symbols[rtn].type;
                counter = 0;
                counter=semantic_Analysis(T->ptr[0], type, level, flag, command);
                if(myTable.symbols[rtn].paramnum != counter)
                    semantic_error(T->pos, "", "参数数量不匹配");
                return myTable.symbols[rtn].type;
            }
            else{
                semantic_error(T->pos, T->type_id, "函数未定义");
                return 0;
            }
            break;
        case EXP_ELE:
            rtn = searchmyTable(T->ptr[0]->type_id);
            if(rtn == -1){
                semantic_error(T->pos, T->ptr[0]->type_id, "结构体变量未定义");
            }
            else{
                if(myTable.symbols[rtn].type != STRUCT){
                    semantic_error(T->pos, T->ptr[0]->type_id, "不是结构体");
                }
                else{
                    rtn=0;
                    for(int i=0;i<myTable.index;i++){
                        if(strcmp(myTable.symbols[i].name,T->type_id)==0 && myTable.symbols[i].flag=='M'){
                            rtn=i;
                            break;
                        }   
                    }
                    if(myTable.symbols[rtn].flag!='M' || strcmp(myTable.symbols[rtn].struct_name, T->ptr[0]->type_id)!=0 ){
                        semantic_error(T->pos, "结构体不含成员变量", T->type_id);
                    }
                }
            }
            break;
        case EXP_ARRAY:
            rtn = searchmyTable(T->ptr[0]->type_id);
            if(rtn == -1){
                semantic_error(T->pos, T->ptr[0]->type_id, "数组未定义");
            }
            else{
                if(myTable.symbols[rtn].flag != 'A'){
                    semantic_error(T->pos,T->ptr[0]->type_id, "不是数组");
                }
                else{
                    array_size = T->type_int;
                    if(array_size >= myTable.symbols[rtn].array_size)
                        semantic_error(T->pos, T->ptr[0]->type_id, "数组index错误");
                    array_size = 0;
                }
            }
            break;
        case INT:
            return INT;
        case CHAR:
            return CHAR;
        case FLOAT:
            return FLOAT;
        case ARGS:
            counter++;
            t = semantic_Analysis(T->ptr[0], type, level, flag, command);
            if(type != t){
                semantic_error(T->pos, "", "函数调用参数类型不匹配");
            }
            type = myTable.symbols[j+counter+1].type;
            semantic_Analysis(T->ptr[1], type, level, flag, command); 
            return counter;
            break;
        }
    }
}

void semantic_Analysis0(struct Node *T)
{
    myTable.index = 0;
    fillmyTable("read", "", 0, INT, 'F', 4);
    myTable.symbols[0].paramnum = 1; //read的形参个数
    fillmyTable("x", "", 1, INT, 'P', 12);
    fillmyTable("write", "", 0, INT, 'F', 4);
    myTable.symbols[2].paramnum = 1;
    fillmyTable("y", "", 1, INT, 'P', 12);
    myScope.TX[0] = 0; //外部变量在符号表中的起始序号为0
    myScope.top = 1;
    T->offset = 0; //外部变量在数据区的偏移量
    prn_symbol();
    semantic_Analysis(T, 0, 0, ' ', 0);
    prn_symbol();
}

void semantic_error(int line, char *msg1, char *msg2)
{ //这里可以只收集错误信息，最后一次显示
    printf("error! 第%d行, %s %s\n", line, msg1, msg2);
}