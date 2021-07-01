#include "def.h"
#include "c_blue.tab.h"

int i, t;
int num;

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
	case EXT_DEF_LIST:  display(T->ptr[0],indent);    //显示该外部定义（外部变量和函数）列表中的第一个
                        display(T->ptr[1],indent);    //显示该外部定义列表中的其它外部定义
                        break;
	case EXT_VAR_DEF:   printf("%*c外部变量定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);        //显示外部变量类型
                        printf("%*c变量名：\n",indent+3,' ');
                        display(T->ptr[1],indent+6);        //显示变量列表
                        break;
    case EXT_STRUCT_DEF:printf("%*c结构体定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);        //显示外部变量类型
                        break;
	case TYPE:          printf("%*c类型： %s\n",indent,' ',T->type_id);
                        break;
    case EXT_DEC_LIST:  display(T->ptr[0],indent);     //依次显示外部变量名，
                        display(T->ptr[1],indent);     //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
                        break;
	case FUNC_DEF:      printf("%*c函数定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);      //显示函数返回类型
                        display(T->ptr[1],indent+3);      //显示函数名和参数
                        display(T->ptr[2],indent+3);      //显示函数体
                        break;
    case VOID_FUNC_DEF: printf("%*c函数定义：(%d)\n",indent,' ',T->pos);
                        printf("%*c类型：%s\n",indent+3,' ',T->type_id);
                        display(T->ptr[0],indent+3);      //显示函数名和参数
                        display(T->ptr[1],indent+3);      //显示函数体
                        break;
    case STRUCT_DEF:    printf("%*c结构定义：(%d)\n", indent, ' ',T->pos);
                        display(T->ptr[0], indent+3);
                        display(T->ptr[1], indent+3);
                        break;
    case STRUCT_DEC:    printf("%*c结构定义：(%d)\n", indent, ' ',T->pos);
                        display(T->ptr[0], indent+3);
                        break;
	case FUNC_DEC:      printf("%*c函数名：%s\n",indent,' ',T->type_id);
                        if (T->ptr[0]) {
                                printf("%*c函数形参：\n",indent,' ');
                                display(T->ptr[0],indent+3);  //显示函数参数列表
                                }
                        else printf("%*c无参函数\n",indent+3,' ');
                        break;
	case PARAM_LIST:    display(T->ptr[0],indent);     //依次显示全部参数类型和名称，
                        display(T->ptr[1],indent);
                        break;
	case PARAM_DEC:     printf("%*c类型：%s, 参数名：%s\n",indent,' ',T->ptr[0]->type==INT?"int":"float",T->ptr[1]->type_id);
                        break;
    case ARRAY_DEC:     printf("%*c数组：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0], indent);
                        printf("%*cINT：%d\n",indent,' ',T->type_int);
                        break;
	case EXP_STMT:      printf("%*c表达式语句：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);
                        break;
	case RETURN:        printf("%*c返回语句：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);
                        break;
	case COMP_STM:      printf("%*c复合语句：(%d)\n",indent,' ',T->pos);
                        printf("%*c复合语句的变量定义部分：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示定义部分
                        printf("%*c复合语句的语句部分：\n",indent+3,' ');
                        display(T->ptr[1],indent+6);      //显示语句部分
                        break;
	case STM_LIST:      display(T->ptr[0],indent);      //显示第一条语句
                        display(T->ptr[1],indent);        //显示剩下语句
                        break;
	case WHILE:         printf("%*c循环语句：(%d)\n",indent,' ',T->pos);
                        printf("%*c循环条件：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示循环条件
                        printf("%*c循环体：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //显示循环体
                        break;
	case IF_THEN:       printf("%*c条件语句(IF_THEN)：(%d)\n",indent,' ',T->pos);
                        printf("%*c条件：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示条件
                        printf("%*cIF子句：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //显示if子句
                        break;
	case IF_THEN_ELSE:  printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n",indent,' ',T->pos);
                        printf("%*c条件：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示条件
                        printf("%*cIF子句：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //显示if子句
                        printf("%*cELSE子句：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[2],indent+6);      //显示else子句
                        break;
    case READ:          printf("%*cREAD语句：(%d)\n", indent, ' ', T->pos);
                        printf("%*cREAD 变量：(%d)\n", indent+3, ' ', T->pos);
                        display(T->ptr[0],indent+6);
                        break;
    case WRITE:         printf("%*cWRITE语句：(%d)\n", indent, ' ', T->pos);
                        printf("%*cWRITE 变量：(%d)\n", indent+3, ' ', T->pos);
                        display(T->ptr[0],indent+6);
                        break;
    case BREAK:         printf("%*cBREAK语句：(%d)\n", indent, ' ', T->pos);
                        break;
    case CONTINUE:      printf("%*cCONTINUE语句：(%d)\n", indent, ' ', T->pos);
                        break;
    case DEF_LIST:      display(T->ptr[0],indent);    //显示该局部变量定义列表中的第一个
                        display(T->ptr[1],indent);    //显示其它局部变量定义
                        break;
    case VAR_DEF:       printf("%*c局部变量定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);   //显示变量类型
                        display(T->ptr[1],indent+3);   //显示该定义的全部变量名
                        break;
    case DEC_LIST:      printf("%*c变量名：\n",indent,' ');
                        display(T->ptr[0],indent+3);
                        break;
    case DEC_LISTS:     printf("%*c变量列表：\n",indent,' ');
                        display(T->ptr[0],indent+3);
                        display(T->ptr[1],indent+3);
                        break;
	case ID:	        printf("%*cID： %s\n",indent,' ',T->type_id);
                        break;
	case INT:	        printf("%*cINT：%d\n",indent,' ',T->type_int);
                        break;
    case CHAR:          printf("%*cCHAR: %s\n", indent, ' ', T->type_char);
                        break;
	case FLOAT:	        printf("%*cFLAOT：%f\n",indent,' ',T->type_float);
                        break;
	case ASSIGNOP:      
	case AND:           
	case OR:            
	case RELOP:         
	case ADD:           
	case SUB:           
	case MUL:           
	case DIV:
                    printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    display(T->ptr[1],indent+3);
                    break;
    case ADDSELF:
    case SUBSELF:
	case NOT:       printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
	case USUB:      printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
    case FUNC_CALL: printf("%*c函数调用：(%d)\n",indent,' ',T->pos);
                    printf("%*c函数名：%s\n",indent+3,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
    case EXP_ELE:   printf("%*c结构体访问：\n", indent, ' ');
                    display(T->ptr[0], indent+3);
                    printf("%*c访问成员变量：%s\n", indent+3, ' ',T->type_id);
                    break;
    case EXP_ARRAY: display(T->ptr[0],indent);
                    display(T->ptr[1],indent);
                    break;
	case ARGS:      i=1;
                    while (T) {  //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
                        struct Node *T0=T->ptr[0];
                        printf("%*c第%d个实际参数表达式：\n",indent,' ',i++);
                        display(T0,indent+3);
                        T=T->ptr[1];
                        }
//                    printf("%*c第%d个实际参数表达式：\n",indent,' ',i);
  //                  display(T,indent+3);
                    printf("\n");
                    break;
         }
      }
}