#include "def.h"
#include "c_blue.tab.h"
#include "stdlib.h"
symbolTable myTable = {{0}, 0};
symbol_scope_TX myScope = {{0}, 0};

int i, j, t, counter = 0;
int rtn, flag1, flag2, num;
int mem, stru_dec = 0;
int rtn2;
char struct_name[33];
int switch_flag = 0, loop_flag = 0;
int left_required = 0;
int array_size = 0;
int struct_flag=0;


char *strcat0(char *s1, char *s2)
{
    static char result[10];
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
char *newAlias()
{
    static int no = 1;
    char s[10]="";
    //itoa(no++, s, 10);
    return strcat0("v", s);
}
char *newLabel()
{
    static int no = 1;
    char s[10]="";
    //itoa(no++, s, 10);
    return strcat0("label", s);
}
char *newTemp()
{
    static int no = 1;
    char s[10]="";
    //itoa(no++, s, 10);
    return strcat0("temp", s);
}

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

void prn_symbol()
{ //显示符号表
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

int fill_Temp(char *name, int level, int type, char flag, int offset)//填写临时变量到符号表，返回临时变量在符号表中的位置
{
    strcpy(myTable.symbols[myTable.index].name, "");
    strcpy(myTable.symbols[myTable.index].alias, name);
    myTable.symbols[myTable.index].level = level;
    myTable.symbols[myTable.index].type = type;
    myTable.symbols[myTable.index].flag = flag;
    myTable.symbols[myTable.index].offset = offset;
    return myTable.index++; //返回的是临时变量在符号表中的位置序号
}

int match_param(int i, struct Node *T)
{
    int j, num = myTable.symbols[i].paramnum;
    int type1, type2, pos = T->pos;
    T = T->ptr[0];
    if (num == 0 && T == NULL)
        return 1;
    for (j = 1; j <= num; j++)
    {
        if (!T)
        {
            semantic_error(pos, "", "函数调用参数太少!");
            return 0;
        }
        type1 = myTable.symbols[i + j].type; //形参类型
        type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
            semantic_error(pos, "", "参数类型不匹配");
            return 0;
        }
        T = T->ptr[1];
    }
    if (T)
    { //num个参数已经匹配完，还有实参表达式
        semantic_error(pos, "", "函数调用参数太多!");
        return 0;
    }
    return 1;
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
                    if(!strcmp(myTable.symbols[i].name,T->type_id) && myTable.symbols[i].type==T->type && (myTable.symbols[i].flag==flag) && myTable.symbols[i].level==level){
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
                i = myTable.index - 1;
                while(i >= 0){
                    if(myTable.symbols[i].level <= level && !strcmp(myTable.symbols[i].name, T->type_id) && (myTable.symbols[i].flag == 'T' || myTable.symbols[i].flag == 'V' || myTable.symbols[i].flag == 'P'))
                    {
                        return myTable.symbols[i].type;
                    }    
                    i--;
                }
                if(i < 0){
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
            if(!switch_flag && !loop_flag)
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
                if(myTable.symbols[rtn].type == STRUCT){
                    semantic_error(T->pos, "", "赋值表达式需要左值");
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
                semantic_Analysis(T->ptr[0], type, level, flag, command);
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
            break;
        }
    }
}


// void semantic_Analysis(struct Node *T)
// { //对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
//     int rtn, num, width;
//     struct Node *T0;
//     struct opn opn1, opn2, result;
//     if (T)
//     {
//         switch (T->kind)
//         {
//         case EXT_DEF_LIST:
//             if (!T->ptr[0])
//                 break;
//             T->ptr[0]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]); //访问外部定义列表中的第一个
//             if (T->ptr[1])
//             {
//                 T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
//                 semantic_Analysis(T->ptr[1]); //访问该外部定义列表中的其它外部定义
//             }
//             break;
//         case EXT_VAR_DEF: //处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
//             T->type = T->ptr[1]->type = (!strcmp(T->ptr[0]->type_id,"int")?INT:(!strcmp(T->ptr[0]->type_id,"float")?FLOAT:CHAR));
//             T->ptr[1]->offset = T->offset;                        //这个外部变量的偏移量向下传递
//             T->ptr[1]->width = T->type == INT ? 4 : 8;            //将一个变量的宽度向下传递
//             semantic_Analysis(T->ptr[1]);                              //处理外部变量说明中的标识符序列
//             T->width = (T->type == INT ? 4 : 8) * T->ptr[1]->num; //计算这个外部变量说明的宽度
//             break;
//         case EXT_STRUCT_DEF:
//             T->ptr[0]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]); //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
//             break;
//         case TYPE:      
//             break;
//         case VOID_FUNC_DEF:
//             T->ptr[1]->type = (!strcmp(T->ptr[0]->type_id,"int")?INT:(!strcmp(T->ptr[0]->type_id,"float")?FLOAT:CHAR)); //获取函数返回类型送到含函数名、参数的结点
//             T->width = 0;                                                       //函数的宽度设置为0，不会对外部变量的地址分配产生影响
//             T->offset = DX;                                                     //设置局部变量在活动记录中的偏移量初值
//             semantic_Analysis(T->ptr[1]);                                       //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
//             T->offset += T->ptr[1]->width;                                      //用形参单元宽度修改函数局部变量的起始偏移量
//             T->ptr[2]->offset = T->offset;
//             strcpy(T->ptr[2]->Snext, newLabel()); //函数体语句执行结束后的位置属性
//             semantic_Analysis(T->ptr[2]);         //处理函数体结点
//             //计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
//             myTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
//             break;
//         case EXT_DEC_LIST:
//             T->ptr[0]->type = T->type;                //将类型属性向下传递变量结点
//             T->ptr[0]->offset = T->offset;            //外部变量的偏移量向下传递
//             if (T->ptr[1]) {
//                 T->ptr[1]->type = T->type;               //将类型属性向下传递变量结点
//                 T->ptr[1]->offset = T->offset + T->width; //外部变量的偏移量向下传递
//                 T->ptr[1]->width = T->width;
//             }
//             semantic_Analysis(T->ptr[0]);
//             if(T->ptr[1]) {
//                 semantic_Analysis(T->ptr[1]);
//                 T->num = T->ptr[1]->num + 1;
//             }
//             break;
//         case FUNC_DEF:                                                          //填写函数定义信息到符号表
//             T->ptr[1]->type = (!strcmp(T->ptr[0]->type_id,"int")?INT:(!strcmp(T->ptr[0]->type_id,"float")?FLOAT:CHAR)); //获取函数返回类型送到含函数名、参数的结点
//             T->width = 0;                                                       //函数的宽度设置为0，不会对外部变量的地址分配产生影响
//             T->offset = DX;                                                     //设置局部变量在活动记录中的偏移量初值
//             semantic_Analysis(T->ptr[1]);                                       //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
//             T->offset += T->ptr[1]->width;                                      //用形参单元宽度修改函数局部变量的起始偏移量
//             T->ptr[2]->offset = T->offset;
//             strcpy(T->ptr[2]->Snext, newLabel()); //函数体语句执行结束后的位置属性
//             semantic_Analysis(T->ptr[2]);         //处理函数体结点
//             //计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
//             myTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
//             break;
//         case FUNC_DEC:                                                       //根据返回类型，函数名填写符号表
//             rtn = fillmyTable(T->type_id, newAlias(), LEV, T->type, 'F', 0); //函数不在数据区中分配单元，偏移量为0
//             if (rtn == -1)
//             {
//                 semantic_error(T->pos, T->type_id, "函数重复定义");
//                 break;
//             }
//             else
//                 T->place = rtn;
//             result.kind = ID;
//             strcpy(result.id, T->type_id);
//             result.offset = rtn;
//             T->offset = DX;                                //设置形式参数在活动记录中的偏移量初值
//             if (T->ptr[0])
//             { //判断是否有参数
//                 T->ptr[0]->offset = T->offset;
//                 semantic_Analysis(T->ptr[0]); //处理函数参数列表
//                 T->width = T->ptr[0]->width;
//                 myTable.symbols[rtn].paramnum = T->ptr[0]->num;
//                 // T->code = merge(2, // T->code, T->ptr[0]->code); //连接函数名和参数代码序列
//             }
//             else
//                 myTable.symbols[rtn].paramnum = 0, T->width = 0;
//             break;
//         case STRUCT_DEF:
//             T->width = 0;   //函数的宽度设置为0，不会对外部变量的地址分配产生影响
//             T->offset = DX; //设置局部变量在活动记录中的偏移量初值
//             T->type = STRUCT;
//             rtn = fillmyTable(T->ptr[0]->type_id, newAlias(), LEV, STRUCT, 'S', 0); //函数不在数据区中分配单元，偏移量为0
//             if (rtn == -1)
//             {
//                 semantic_error(T->pos, T->ptr[0]->type_id, "结构体重复定义");
//                 return;
//             }
//             else
//                 T->place = rtn;
//             T->ptr[1]->offset = T->offset;
//             struct_flag = 1;
//             semantic_Analysis(T->ptr[1]);
//             struct_flag = 0;
//             break;
//         case STRUCT_DEC:
//             T->ptr[0]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]);
//             T->width = T->ptr[1]->width;
//             break;
//         case PARAM_LIST: //处理函数形式参数列表
//             T->ptr[0]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]);
//             if (T->ptr[1])
//             {
//                 T->ptr[1]->offset = T->offset + T->ptr[0]->width;
//                 semantic_Analysis(T->ptr[1]);
//                 T->num = T->ptr[0]->num + T->ptr[1]->num;             //统计参数个数
//                 T->width = T->ptr[0]->width + T->ptr[1]->width;       //累加参数单元宽度
//             }
//             else
//             {
//                 T->num = T->ptr[0]->num;
//                 T->width = T->ptr[0]->width;
//             }
//             break;
//         case PARAM_DEC:
//             rtn = fillmyTable(T->ptr[1]->type_id, newAlias(), 1, T->ptr[0]->type, 'P', T->offset);
//             if (rtn == -1)
//                 semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "参数名重复定义");
//             else
//                 T->ptr[1]->place = rtn;
//             T->num = 1;                                //参数个数计算的初始值
//             T->width = T->ptr[0]->type == INT ? 4 : 8; //参数宽度
//             result.kind = ID;
//             strcpy(result.id, myTable.symbols[rtn].alias);
//             result.offset = T->offset;
//             break;
//         // case READ:
//         // case WRITE:
//         case BREAK:
//             break;
//         case CONTINUE:
//             break;
//         case COMP_STM:
//             LEV++;
//             //设置层号加1，并且保存该层局部变量在符号表中的起始位置在myScope
//             myScope.TX[myScope.top++] = myTable.index;
//             T->width = 0;
//             if (T->ptr[0])
//             {
//                 T->ptr[0]->offset = T->offset;
//                 semantic_Analysis(T->ptr[0]); //处理该层的局部变量DEF_LIST
//                 T->width += T->ptr[0]->width;
//             }
//             if (T->ptr[1])
//             {
//                 T->ptr[1]->offset = T->offset + T->width;
//                 strcpy(T->ptr[1]->Snext, T->Snext); //S.next属性向下传递
//                 semantic_Analysis(T->ptr[1]);       //处理复合语句的语句序列
//                 T->width += T->ptr[1]->width;
//             }
// #if (DEBUG)
//             prn_symbol(); //c在退出一个符合语句前显示的符号表
//             system("pause");
// #endif
//             LEV--;                                     //出复合语句，层号减1
//             myTable.index = myScope.TX[--myScope.top]; //删除该作用域中的符号
//             break;
//         case DEF_LIST:
//             if (T->ptr[0])
//             {
//                 T->ptr[0]->offset = T->offset;
//                 semantic_Analysis(T->ptr[0]); //处理一个局部变量定义
//                 T->width = T->ptr[0]->width;
//             }
//             if (T->ptr[1])
//             {
//                 T->ptr[1]->offset = T->offset + T->ptr[0]->width;
//                 semantic_Analysis(T->ptr[1]); //处理剩下的局部变量定义
//                 T->width += T->ptr[1]->width;
//             }
//             break;
//         case VAR_DEF: //处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
//                       //类似于上面的外部变量EXT_VAR_DEF，换了一种处理方法
//             T->ptr[1]->type = !strcmp(T->ptr[0]->type_id, "int") ? INT : FLOAT; //确定变量序列各变量类型
//             T0 = T->ptr[1];                                                     //T0为变量名列表子树根指针，对ID、ASSIGNOP类结点在登记到符号表，作为局部变量
//             num = 0;
//             T0->offset = T->offset;
//             T->width = 0;
//             width = T->ptr[1]->type == INT ? 4 : 8; //一个变量宽度
//             while (T0)
//             { //处理所以DEC_LIST结点
//                 num++;
//                 T0->ptr[0]->type = T0->type; //类型属性向下传递
//                 if (T0->ptr[1])
//                     T0->ptr[1]->type = T0->type;
//                 T0->ptr[0]->offset = T0->offset; //类型属性向下传递
//                 if (T0->ptr[1])
//                     T0->ptr[1]->offset = T0->offset + width;
//                 if (T0->ptr[0]->kind == ID)
//                 {
//                     rtn = fillmyTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
//                     if (rtn == -1)
//                         semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
//                     else
//                         T0->ptr[0]->place = rtn;
//                     T->width += width;
//                 }
//                 else if (T0->ptr[0]->kind == ASSIGNOP)
//                 {
//                     rtn = fillmyTable(T0->ptr[0]->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
//                     if (rtn == -1)
//                         semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
//                     else
//                     {
//                         T0->ptr[0]->place = rtn;
//                         T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
//                         semantic_Analysis(T0->ptr[0]->ptr[1]);
//                         opn1.kind = ID;
//                         strcpy(opn1.id, myTable.symbols[T0->ptr[0]->ptr[1]->place].alias);
//                         result.kind = ID;
//                         strcpy(result.id, myTable.symbols[T0->ptr[0]->place].alias);
//                     }
//                     T->width += width + T0->ptr[0]->ptr[1]->width;
//                 }
//                 T0 = T0->ptr[1];
//             }
//             break;
//         case DEC_LIST:
//             break;
//         case DEC_LISTS:
//             break;
//         case VARLIST:
//             rtn = fillmyTable(T->type_id, newAlias(), LEV, T->type, 'F', 0); //函数不在数据区中分配单元，偏移量为0
//             if (rtn == -1)
//             {
//                 semantic_error(T->pos, T->type_id, "函数重复定义");
//                 return;
//             }
//             else
//                 T->place = rtn;
//             result.kind = ID;
//             strcpy(result.id, T->type_id);
//             result.offset = rtn;
//             T->offset = DX;                                //设置形式参数在活动记录中的偏移量初值
//             if (T->ptr[0])
//             { //判断是否有参数
//                 T->ptr[0]->offset = T->offset;
//                 semantic_Analysis(T->ptr[0]); //处理函数参数列表
//                 T->width = T->ptr[0]->width;
//                 myTable.symbols[rtn].paramnum = T->ptr[0]->num;
//             }
//             else {
//                 myTable.symbols[rtn].paramnum = 0;
//                 T->width = 0;
//             }
//             break;
//         case STM_LIST:
//             if (!T->ptr[0])
//             {
//                 T->width = 0;
//                 break;
//             }              //空语句序列
//             if (T->ptr[1]) //2条以上语句连接，生成新标号作为第一条语句结束后到达的位置
//                 strcpy(T->ptr[0]->Snext, newLabel());
//             else //语句序列仅有一条语句，S.next属性向下传递
//                 strcpy(T->ptr[0]->Snext, T->Snext);
//             T->ptr[0]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]);
//             T->width = T->ptr[0]->width;
//             if (T->ptr[1])
//             { //2条以上语句连接,S.next属性向下传递
//                 strcpy(T->ptr[1]->Snext, T->Snext);
//                 T->ptr[1]->offset = T->offset; //顺序结构共享单元方式
//                                                //                  T->ptr[1]->offset=T->offset+T->ptr[0]->width; //顺序结构顺序分配单元方式
//                 semantic_Analysis(T->ptr[1]);
//                 if (T->ptr[1]->width > T->width)
//                     T->width = T->ptr[1]->width; //顺序结构共享单元方式
//                                                  //                        T->width+=T->ptr[1]->width;//顺序结构顺序分配单元方式
//             }
//             break;
//         case IF_THEN:
//             strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
//             strcpy(T->ptr[0]->Efalse, T->Snext);
//             T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]);
//             T->width = T->ptr[0]->width;
//             strcpy(T->ptr[1]->Snext, T->Snext);
//             semantic_Analysis(T->ptr[1]); //if子句
//             if (T->width < T->ptr[1]->width)
//                 T->width = T->ptr[1]->width;
//             break; //控制语句都还没有处理offset和width属性
//         case IF_THEN_ELSE:
//             strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
//             strcpy(T->ptr[0]->Efalse, newLabel());
//             T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]); //条件，要单独按短路代码处理
//             T->width = T->ptr[0]->width;
//             strcpy(T->ptr[1]->Snext, T->Snext);
//             semantic_Analysis(T->ptr[1]); //if子句
//             if (T->width < T->ptr[1]->width)
//                 T->width = T->ptr[1]->width;
//             strcpy(T->ptr[2]->Snext, T->Snext);
//             semantic_Analysis(T->ptr[2]); //else子句
//             if (T->width < T->ptr[2]->width)
//                 T->width = T->ptr[2]->width;
//             break;
//         case WHILE:
//             strcpy(T->ptr[0]->Etrue, newLabel()); //子结点继承属性的计算
//             strcpy(T->ptr[0]->Efalse, T->Snext);
//             T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]); //循环条件，要单独按短路代码处理
//             T->width = T->ptr[0]->width;
//             strcpy(T->ptr[1]->Snext, newLabel());
//             semantic_Analysis(T->ptr[1]); //循环体
//             if (T->width < T->ptr[1]->width)
//                 T->width = T->ptr[1]->width;
//             break;
//         case EXP_STMT:
//             T->ptr[0]->offset = T->offset;
//             semantic_Analysis(T->ptr[0]);
//             T->width = T->ptr[0]->width;
//             break;
//         case RETURN:
//             if (T->ptr[0])
//             {
//                 T->ptr[0]->offset = T->offset;
//                 semantic_Analysis(T->ptr[0]);
//                 /*需要判断返回值类型是否匹配*/
//                 T->width = T->ptr[0]->width;
//                 result.kind = ID;
//                 strcpy(result.id, myTable.symbols[T->ptr[0]->place].alias);
//                 result.offset = myTable.symbols[T->ptr[0]->place].offset;
//             }
//             else
//             {
//                 T->width = 0;
//                 result.kind = 0;
//             }
//             break;
//         case FUNC_CALL:
//             semantic_Analysis(T); //处理基本表达式
//             break;
//         }
//     }
// }

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