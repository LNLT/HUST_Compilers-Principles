#include "def.h"
#include "c_blue.tab.h"
#define OFFSET 3
#define MAX_LOOP 100

struct Node * mknode(int num,int kind,int pos,...){
    struct Node *T=(struct Node *)calloc(sizeof(struct Node),1);
    int i=0;
    T->kind=kind;
    T->pos=pos;
    va_list pArgs;
    va_start(pArgs, pos);
    for(i=0;i<num;i++)
        T->ptr[i]= va_arg(pArgs, struct Node *);
    while (i<4) T->ptr[i++]=NULL;
    va_end(pArgs);
    return T;
}


void display(struct Node *T,int indent)
{//对抽象语法树的先根遍历
  int i=1;
  struct Node *T0;
  if (T)
	{
	switch (T->kind) {
    case EXT_DEF_LIST:  
        display(T->ptr[0],indent);    //显示该外部定义（外部变量和函数）列表中的第一个
        display(T->ptr[1],indent);    //显示该外部定义列表中的其它外部定义
        break;
    case EXT_VAR_DEF:   
        printf("%*c外部变量定义：(%d)\n",indent,' ',T->pos);
        display(T->ptr[0],indent+OFFSET);        //显示外部变量类型
        printf("%*c变量名：\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);        //显示变量列表
        break;
    case TYPE:          
        printf("%*c类型： %s\n",indent,' ',T->type_id);
        break;
    case EXT_DEC_LIST:  
        if(T->ptr[0]->ptr[0] != NULL)
        {
            printf("%*c数组名：%s\n", indent, ' ', T->ptr[0]->type_id);
            printf("%*c数组大小：\n", indent, ' ');
        }
        display(T->ptr[0],indent);     //依次显示外部变量名，
        display(T->ptr[1],indent);     //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
        break;
    case FUNC_DEF:      
        printf("%*c函数定义：(%d)\n",indent,' ',T->pos);
        display(T->ptr[0],indent+OFFSET);      //显示函数返回类型
        display(T->ptr[1],indent+OFFSET);      //显示函数名和参数
        display(T->ptr[2],indent+OFFSET);      //显示函数体
        break;
    case FUNC_DEC:      
        printf("%*c函数名：%s\n",indent,' ',T->type_id);
        if (T->ptr[0]) {
            printf("%*c函数形参：\n",indent,' ');
            display(T->ptr[0],indent+OFFSET);  //显示函数参数列表
        }
        else printf("%*c无参函数\n",indent+OFFSET,' ');
        break;
    case PARAM_LIST:    
        display(T->ptr[0],indent);     //依次显示全部参数类型和名称，
        display(T->ptr[1],indent);
        break;
    case PARAM_DEC:     
        printf("%*c类型：%s, 参数名：%s\n",indent,' ',T->ptr[0]->type==INT?"int":"float",T->ptr[1]->type_id);
        break;
    case EXP_STMT:      
        printf("%*c表达式语句：(%d)\n",indent,' ',T->pos);
        display(T->ptr[0],indent+OFFSET);
        break;
    case RETURN:        
        printf("%*c返回语句：(%d)\n",indent,' ',T->pos);
        display(T->ptr[0],indent+OFFSET);
        break;
    case COMP_STM:      
        printf("%*c复合语句：(%d)\n",indent,' ',T->pos);
        printf("%*c复合语句的变量定义部分：\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示定义部分
        printf("%*c复合语句的语句部分：\n",indent+OFFSET,' ');
        display(T->ptr[1],indent+OFFSET*2);      //显示语句部分
        break;
    case STM_LIST:      
        display(T->ptr[0],indent);      //显示第一条语句
        display(T->ptr[1],indent);        //显示剩下语句
        break;
    case WHILE:         
        printf("%*c循环语句(WHILE)：(%d)\n",indent,' ',T->pos);
        printf("%*c循环条件(WHILE)：\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示循环条件
        printf("%*c循环体(WHILE)：(%d)\n",indent+OFFSET,' ',T->pos);
        display(T->ptr[1],indent+OFFSET*2);      //显示循环体
        break;
    case FOR:
        printf("%*c循环语句(FOR)：(%d)\n",indent,' ',T->pos);
        printf("%*c循环条件(FOR)：\n", indent+OFFSET, ' ');
        display(T->ptr[0], indent+OFFSET*2);
        printf("%*c循环体(FOR)：(%d)\n",indent+OFFSET,' ',T->pos);
        display(T->ptr[1], indent+OFFSET*2);
        break;
    case FOR_DEC:
        display(T->ptr[0], indent+OFFSET*2);
        display(T->ptr[1], indent+OFFSET*2);
        display(T->ptr[2], indent+OFFSET*2);
        break;
    case CONTINUE:
        printf("%*cCONTINUE语句：(%d)\n", indent, ' ', T->pos);
        break;
    case BREAK:
        printf("%*cBREAK语句：(%d)\n", indent, ' ', T->pos);
        break;
    case IF_THEN:       
        printf("%*c条件语句(IF_THEN)：(%d)\n",indent,' ',T->pos);
        printf("%*c条件：\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示条件
        printf("%*cIF子句：(%d)\n",indent+OFFSET,' ',T->pos);
        display(T->ptr[1],indent+OFFSET*2);      //显示if子句
        break;
    case IF_THEN_ELSE:  
        printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n",indent,' ',T->pos);
        printf("%*c条件：\n",indent+OFFSET,' ');
        display(T->ptr[0],indent+OFFSET*2);      //显示条件
        printf("%*cIF子句：(%d)\n",indent+OFFSET,' ',T->pos);
        display(T->ptr[1],indent+OFFSET*2);      //显示if子句
        printf("%*cELSE子句：(%d)\n",indent+OFFSET,' ',T->pos);
        display(T->ptr[2],indent+OFFSET*2);      //显示else子句
        break;
    case DEF_LIST:     
        display(T->ptr[0],indent);    //显示该局部变量定义列表中的第一个
        display(T->ptr[1],indent);    //显示其它局部变量定义
        break;
    case VAR_DEF:       
        printf("%*c局部变量定义：(%d)\n",indent,' ',T->pos);
        display(T->ptr[0],indent+OFFSET);   //显示变量类型
        display(T->ptr[1],indent+OFFSET);   //显示该定义的全部变量名
        break;
    case DEC_LIST:      
        printf("%*c变量名：\n",indent,' ');
        T0=T;
        while (T0) {
            if (T0->ptr[0]->kind==ID)
                printf("%*c %s\n",indent+OFFSET*2,' ',T0->ptr[0]->type_id);
            else if (T0->ptr[0]->kind==ASSIGNOP)
            {
                printf("%*c %s ASSIGNOP\n ",indent+OFFSET*2,' ',T0->ptr[0]->ptr[0]->type_id);
                display(T0->ptr[0]->ptr[0],indent+OFFSET*2);
                display(T0->ptr[0]->ptr[1],indent+strlen(T0->ptr[0]->ptr[0]->type_id)+7);        //显示初始化表达式
            }
            else if (T0->ptr[0]->kind==ARRAY_DEC)
            {
                //printf("%d %d\n",T0->ptr[0]->ptr[0]->kind,ARRAY_LAST);
                printf("%*c %s\n",indent+OFFSET*2,' ',T0->ptr[0]->type_id);
                display(T0->ptr[0]->ptr[0],indent+OFFSET*2);
            }
            T0=T0->ptr[1];
        }
        break;
    case ARRAY_LIST:
        printf("%*cINT：%d\n",indent,' ',T->type_int);
        display(T->ptr[0], indent);
        break;
    case ARRAY_LAST:
        printf("%*cINT：%d\n",indent,' ',T->type_int);
        break;
    case STRUCT_DEF:
        printf("%*c结构定义：(%d)\n", indent, ' ',T->pos);
        display(T->ptr[0], indent+OFFSET);
        display(T->ptr[1], indent+OFFSET);
        break;
    case STRUCT_TAG:
        printf("%*c结构名：%s\n", indent, ' ', T->struct_name);
        break;
    case ID:	        
        printf("%*cID： %s\n",indent,' ',T->type_id);
        break;
    case INT:	     
        printf("%*cINT：%d\n",indent,' ',T->type_int);
        break;
    case FLOAT:	        
        printf("%*cFLAOT：%f\n",indent,' ',T->type_float);
        break;
    case CHAR:
        printf("%*cCHAR: %s\n", indent, ' ', T->type_char);
        break;
	case ASSIGNOP:
    case AND:
    case OR:
    case RELOP:
    case ADD:
    case ADDSELF_L:
    case ADDSELF_R:
    case SUBSELF_L:
    case SUBSELF_R:
    case SUB:
    case MUL:
    case DIV:
        printf("%*c%s\n",indent,' ',T->type_id);
        display(T->ptr[0],indent+OFFSET);
        display(T->ptr[1],indent+OFFSET);
        break;
    case EXP_ELE:
        printf("%*c结构体访问：\n", indent, ' ');
        display(T->ptr[0], indent+OFFSET);
        printf("%*c访问成员变量：%s\n", indent+OFFSET, ' ',T->type_id);
        break;
    case EXP_ARRAY:
        printf("%*c数组访问：\n", indent, ' ');
        printf("%*c%s\n",indent+OFFSET,' ',T->type_id);
        display(T->ptr[0], indent+OFFSET);
        break;
    case NOT:
    case USUB:    
        printf("%*c%s\n",indent,' ',T->type_id);
        display(T->ptr[0],indent+OFFSET);
        break;
    case FUNC_CALL: 
        printf("%*c函数调用：(%d)\n",indent,' ',T->pos);
        printf("%*c函数名：%s\n",indent+OFFSET,' ',T->type_id);
        display(T->ptr[0],indent+OFFSET);
        break;
    case ARGS:      
        i=1;
        while (T) {  //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
            struct Node *T0=T->ptr[0];
            printf("%*c第%d个实际参数表达式：\n",indent,' ',i++);
            display(T0,indent+OFFSET);
            T=T->ptr[1];
        }
        // printf("%*c第%d个实际参数表达式：\n",indent,' ',i);
        // display(T,indent+OFFSET);
        // printf("\n");
        break;
        }
    }
}

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
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("v", s);
}

char *newLabel()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("label", s);
}

char *newTemp()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("temp", s);
}

//生成一条TAC代码的结点组成的双向循环链表，返回头指针
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = op;
    h->opn1 = opn1;
    h->opn2 = opn2;
    h->result = result;
    h->next = h->prior = h;
    return h;
}

//生成一条标号语句，返回头指针
struct codenode *genLabel(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = LABEL;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

//生成GOTO语句，返回头指针
struct codenode *genGoto(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = GOTO;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

// 合并多个中间代码的双向循环链表，首尾相连
struct codenode *merge(int num, ...)
{
    struct codenode *h1, *h2, *p, *t1, *t2;
    va_list ap;
    va_start(ap, num);
    h1 = va_arg(ap, struct codenode *);
    while (--num > 0)
    {
        h2 = va_arg(ap, struct codenode *);
        if (h1 == NULL)
            h1 = h2;
        else if (h2)
        {
            t1 = h1->prior;
            t2 = h2->prior;
            t1->next = h2;
            t2->next = h1;
            h1->prior = t2;
            h2->prior = t1;
        }
    }
    va_end(ap);
    return h1;
}

//输出中间代码
void prnIR(struct codenode *head)
{
    char opnstr1[32], opnstr2[32], resultstr[32];
    struct codenode *h = head;
    if(h) {
    do
    {
        if (h->opn1.kind == INT)
            sprintf(opnstr1, "#%d", h->opn1.const_int);
        if (h->opn1.kind == CHAR)
            sprintf(opnstr1, "#%c", h->opn1.const_char);
        if (h->opn1.kind == FLOAT)
            sprintf(opnstr1, "#%f", h->opn1.const_float);
        if (h->opn1.kind == ID)
            sprintf(opnstr1, "%s", h->opn1.id);
        if (h->opn2.kind == INT)
            sprintf(opnstr2, "#%d", h->opn2.const_int);
        if (h->opn2.kind == CHAR)
            sprintf(opnstr2, "#%c", h->opn2.const_char);
        if (h->opn2.kind == FLOAT)
            sprintf(opnstr2, "#%f", h->opn2.const_float);
        if (h->opn2.kind == ID)
            sprintf(opnstr2, "%s", h->opn2.id);
        sprintf(resultstr, "%s", h->result.id);
        switch (h->op)
        {
        case ASSIGNOP:
            printf("  %s := %s\n", resultstr, opnstr1);
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            printf("  %s := %s %c %s\n",resultstr,opnstr1, \
                      h->op==ADD?'+':h->op==SUB?'-':h->op==MUL?'*':'\\',opnstr2);
                      break;
        case FUNCTION:
            printf("\nFUNCTION %s :\n", h->result.id);
            break;
        case PARAM:
            printf("  PARAM %s\n", h->result.id);
            break;
        case LABEL:
            printf("LABEL %s :\n", h->result.id);
            break;
        case GOTO:
            printf("  GOTO %s\n", h->result.id);
            break;
        case JLE:
            printf("  IF %s <= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case JLT:
            printf("  IF %s < %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case JGE:
            printf("  IF %s >= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case JGT:
            printf("  IF %s > %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case EQ:
            printf("  IF %s == %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case NEQ:
            printf("  IF %s != %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case ARG:
            printf("  ARG %s\n", h->result.id);
            break;
        case CALL:
            printf("  %s := CALL %s\n", resultstr, opnstr1);
            break;
        case RETURN:
            if (h->result.kind)
                printf("  RETURN %s\n", resultstr);
            else
                printf("  RETURN\n");
            break;
        }
        h = h->next;
    } while (h != head);
    }
}