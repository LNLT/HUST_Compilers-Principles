#include "case.c"

void semantic_Analysis(struct Node *T)
{ //对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
    int rtn, num, width;
    struct Node *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            ext_def_list(T);
            break;
        case EXT_VAR_DEF: //处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
            ext_var_def(T);
            break;
        case EXT_STRUCT_DEF: // TODO
            ext_struct_def(T);
            break;
        case STRUCT_DEF: // TODO
            struct_def(T);
            break;
        case STRUCT_DEC: // TODO
            struct_dec(T);
            break;
        case FUNC_DEF:
            func_def(T);
            break;
        case FUNC_DEC: //根据返回类型，函数名填写符号表
            func_dec(T);
            break;
        case PARAM_LIST: //处理函数形式参数列表
            param_list(T);
            break;
        case PARAM_DEC:
            param_dec(T);
            break;
        case COMP_STM:
            comp_stm(T);
            break;
        case DEF_LIST:
            def_list(T);
            break;
        case VAR_DEF: //处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
                      //类似于上面的外部变量EXT_VAR_DEF，换了一种处理方法
            var_def(T);
            break;
        case STM_LIST:
            stm_list(T);
            break;
        case IF_THEN:
            if_then(T);
            break; //控制语句都还没有处理offset和width属性
        case IF_THEN_ELSE:
            if_then_else(T);
            break;
        case WHILE:
            while_dec(T);
            break;
        case BREAK:
            break_dec(T);
            break;
        case CONTINUE:
            continue_dec(T);
            break;
        case EXP_STMT:
            exp_stmt(T);
            break;
        case RETURN:
            return_dec(T);
            break;
        case ID:
        case INT:
        case FLOAT:
        case CHAR:
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case ADD:
        case ADDSELF:
        case SUB:
        case SUBSELF:
        case MUL:
        case DIV:
        case NOT:
        case USUB:
        case FUNC_CALL:
        case EXP_ARRAY:
        case EXP_ELE:
            Exp(T); //处理基本表达式
            break;
        }
    }
}

void semantic_Analysis0(struct Node *T) {
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
    semantic_Analysis(T);
    prnIR(T->code);
    //objectCode(T->code);
 } 