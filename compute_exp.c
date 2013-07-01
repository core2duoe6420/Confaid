/* 早期作品:-) */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define _ERROR NULL

struct _element {
    int isDouble;
    int isOperator;
    double data;
    struct _operator* op;
};

typedef struct _element* ELEMENT;

struct _operator {
    char name;
    int priority;
    int operand;
    double(*doCal)(double, double);
};

typedef struct _operator* OPERATOR;

struct _table {
    ELEMENT* _table_head;
    int _length;
    int _max_length;
};
typedef struct _table* MYSTABLE;
typedef struct _table* MYSTACK;

static ELEMENT newElementData(double data)
{
    ELEMENT temp;
    temp = (ELEMENT)malloc(sizeof(struct _element));
    if(temp == NULL)
        return _ERROR;
    temp->isDouble = 1;
    temp->isOperator = 0;
    temp->data = data;
    temp->op = NULL;
    return temp;
}

static double doAdd(double a, double b)
{
    return a + b;
}

static double doMinus(double a, double b)
{
    return a - b;
}

static double doMultipy(double a, double b)
{
    return a * b;
}

static double doDivide(double a, double b)
{
    return a / b;
}

static double doPower(double a, double b)
{
    return pow(a, b);
}

static double doRetrieve(double a, double b)
{
    if((int)a == 0)
        return 1.;
    else
        return 0.;
}

static ELEMENT newElementOp(char op)
{
    ELEMENT temp;
    temp = (ELEMENT)malloc(sizeof(struct _element));
    if(temp == NULL)
        return _ERROR;
    temp->isDouble = 0;
    temp->isOperator = 1;
    temp->data = 0;
    temp->op = (OPERATOR)malloc(sizeof(struct _operator));
    if(temp->op == NULL)
        return _ERROR;
    temp->op->name = op;
    switch(op) {
    case '+':
        temp->op->operand = 2;
        temp->op->priority = 4;
        temp->op->doCal = doAdd;
        break;
    case '-':
        temp->op->operand = 2;
        temp->op->priority = 4;
        temp->op->doCal = doMinus;
        break;
    case '*':
        temp->op->operand = 2;
        temp->op->priority = 3;
        temp->op->doCal = doMultipy;
        break;
    case '/':
        temp->op->operand = 2;
        temp->op->priority = 3;
        temp->op->doCal = doDivide;
        break;
    case '^':
        temp->op->operand = 2;
        temp->op->priority = 2;
        temp->op->doCal = doPower;
    case '~':
        temp->op->operand = 1;
        temp->op->priority = 2;
        temp->op->doCal = doRetrieve;
        break;
    case '(':
        temp->op->operand = 0;
        temp->op->priority = 7;
        temp->op->doCal = NULL;
        break;
    case ')':
        temp->op->operand = 0;
        temp->op->priority = 7;
        temp->op->doCal = NULL;
        break;
    default:
        break;
    }
    return temp;
}

static MYSTABLE assign(const int maxlen, ELEMENT init)
{
    MYSTABLE temp;
    if((temp = (MYSTABLE)malloc(sizeof(struct _table))) != NULL) {
        temp->_max_length = maxlen;
        temp->_length = 0;
        if((temp->_table_head = (ELEMENT *)malloc(sizeof(ELEMENT) * maxlen)) != NULL)
            for(int i = 0; i < maxlen; i++)
                *(temp->_table_head + i) = init;
        else
            return NULL;
        return temp;
    }
    return NULL;
}

static int setAll(const MYSTABLE table, int n, ELEMENT x, ...)
{
    ELEMENT *p = &x;
    if(table == NULL)
        return -1;
    if(n > table->_max_length)
        return 0;
    for(int i = 0; i < n; i++) {
        *(table->_table_head + i) = *p;
        p++;
    }
    table->_length = n;
    return 1;
}

static int locate(const MYSTABLE table, ELEMENT x)
{
    if(table == NULL)
        return -1;
    for(int i = 0; i < table->_length; i++)
        if(*(table->_table_head + i) == x)
            return i;
    return -2;
}

static int isEmpty(const MYSTABLE table)
{
    if(table == NULL)
        return -1;
    if(table->_length == 0)
        return 1;
    return 0;
}

static int isFull(const MYSTABLE table)
{
    if(table == NULL)
        return -1;
    if(table->_length == table->_max_length)
        return 1;
    return 0;
}

static int set(const MYSTABLE table, int position, ELEMENT data)
{
    if(position > table->_length - 1 || position < 0)
        return 0;
    *(table->_table_head + position) = data;
    return 1;
}

static ELEMENT get(const MYSTABLE table, int position)
{
    if(position > table->_length - 1 || position < 0)
        return _ERROR;
    return *(table->_table_head + position);
}

static int getLength(const MYSTABLE table)
{
    if(table == NULL)
        return -1;
    return table->_length;
}

static int table_remove(const MYSTABLE table, int position)
{
    int i = 0;
    if(table == NULL)
        return -1;
    if(position > table->_length - 1 || position < 0)
        return 0;
    for(i = position; i < table->_length - 1; i++)
        *(table->_table_head + i) = *(table->_table_head + (i + 1));
    table->_length--;
    return 1;
}

static int insert(MYSTABLE table, int position, ELEMENT data)
{
    int i = 0;
    if(table == NULL)
        return -1;
    if(position > table->_length || position < 0)
        return 0;
    if(isFull(table) == 0) {
        for(i = table->_length; i > position; i--)
            *(table->_table_head + i) = *(table->_table_head + (i - 1));
        *(table->_table_head + i) = data;
        table->_length++;
    } else {
        MYSTABLE temp;
        if((temp = (MYSTABLE)malloc(sizeof(struct _table))) == NULL)
            return -1;
        if((temp->_table_head = (ELEMENT *)malloc(sizeof(ELEMENT)
                                * (table->_max_length + 1))) == NULL)
            return -1;
        temp->_length = table->_max_length + 1;
        temp->_max_length = table->_max_length + 1;
        for(i = 0; i < position; i++)
            *(temp->_table_head + i) = *(table->_table_head + i);
        *(temp->_table_head + i) = data;
        for(i++; i < temp->_length; i++)
            *(temp->_table_head + i) = *(table->_table_head + (i - 1));
        free(table->_table_head);
        free(table);
        table = temp;
    }
    return 1;
}

static int add(const MYSTABLE table, ELEMENT x)
{
    return insert(table, table->_length, x);
}

static int del(const MYSTABLE table)
{
    free(table->_table_head);
    free(table);
    return 1;
}

static int elementNum(const MYSTABLE table, ELEMENT x)
{
    if(table == NULL)
        return -1;
    int num = 0;
    for(int i = 0; i < table->_length; i++)
        if(*(table->_table_head + i) == x)
            num++;
    return num;
}

static int clear(const MYSTABLE table)
{
    return setAll(table, 0, 0);
}


static MYSTACK initial()
{
    return assign(100, 0);
}


static ELEMENT pop(MYSTACK stack)
{
    if(stack == NULL)
        return _ERROR;
    if(isEmpty(stack))
        return _ERROR;
    ELEMENT data;
    data = get(stack, stack->_length - 1);
    table_remove(stack, stack->_length - 1);
    return data;
}

static ELEMENT peek(MYSTACK stack)
{
    if(stack == NULL)
        return _ERROR;
    if(isEmpty(stack))
        return _ERROR;
    ELEMENT data;
    data = get(stack, stack->_length - 1);
    return data;
}

static int push(MYSTACK stack, ELEMENT x)
{
    return insert(stack, stack->_length, x);
}

static int makeEmpty(MYSTACK stack)
{
    if(stack == NULL)
        return -1;
    stack->_length = 0;
    return 0;
}

static MYSTABLE CharToInfix(char ex[], int length)
{
    MYSTABLE infix = assign(length, NULL);
    char* numtemp = (char *)malloc(sizeof(char) * length);
    int p = 0;
    int isCharBeforeOperator = 1;
    double temp;
    for(int i = 0; i < length; i++) {
        if(ex[i] == ' ' || ex[i] == '\n' || ex[i] == '\r' ||
           ex[i] == '\t')
            continue;
        if((ex[i] >= '0' && ex[i] <= '9') || ex[i] == '.' ||
           (isCharBeforeOperator == 1 && (ex[i] == '-' || ex[i] == '+'))) {
            //处理数字 正负号
            numtemp[p++] = ex[i];
            isCharBeforeOperator = 0;
            continue;
        }
        if(p != 0) {
            temp = atof(numtemp);
            for(int k = 0; k < length; k++)
                numtemp[k] = '\0';
            p = 0;
            add(infix, newElementData(temp));
            add(infix, newElementOp(ex[i]));
        } else {
            add(infix, newElementOp(ex[i]));
        }
        if(ex[i] != '(' && ex[i] != ')' && ex[i] != '!')
            isCharBeforeOperator = 1;
    }
    if(p != 0) {
        temp = atof(numtemp);
        for(int k = 0; k < length; k++)
            numtemp[k] = '\0';
        p = 0;
        add(infix, newElementData(temp));
    }
    return infix;
}

static MYSTABLE InfixToPostfix(MYSTABLE infix)
{
    MYSTACK stack = initial();
    MYSTABLE postfix = assign(getLength(infix), NULL);
    OPERATOR opS = NULL, opF = NULL;
    for(int i = 0; i < getLength(infix); i++) {
        if(get(infix, i)->isDouble == 1)
            add(postfix, get(infix, i));
        if(get(infix, i)->isOperator == 1) {
            opF = get(infix, i)->op;
            if(getLength(stack) == 0) {
                push(stack, get(infix, i));
            } else if(opF->name == '(') {
                push(stack, get(infix, i));
            } else if(opF->name == ')') {
                do {
                    opS = peek(stack)->op;
                    if(opS->name != '(')
                        add(postfix, pop(stack));
                    else
                        pop(stack);
                } while(opS->name != '(');
            } else {
                do {
                    opS = peek(stack)->op;
                    if(opF->priority >= opS->priority)
                        add(postfix, pop(stack));
                    else
                        break;
                } while(getLength(stack) != 0);
                push(stack, get(infix, i));
            }
        }
    }
    while(getLength(stack) != 0)
        add(postfix, pop(stack));
    //释放括号占用的内存
    for(int i = 0; i < getLength(infix); i++) {
        ELEMENT temp;
        if((temp = get(infix, i))->isOperator == 1) {
            if(temp->op->name == '(' || temp->op->name == ')') {
                free(temp->op);
                free(temp);
            }
        }
    }
    //释放栈占用的内存
    del(stack);
    //释放掉前缀表达式占用的内存
    del(infix);
    return postfix;
}

static double CalPostfix(MYSTABLE postfix)
{
    MYSTACK stack = initial();
    double first, second;
    ELEMENT efirst, esecond;
    for(int i = 0; i < getLength(postfix); i++) {
        if(get(postfix, i)->isDouble == 1)
            push(stack, get(postfix, i));
        if(get(postfix, i)->isOperator == 1) {
            OPERATOR op = get(postfix, i)->op;
            if(op->operand == 1) {
                efirst = pop(stack);
                first = efirst->data;
                //从栈中弹出的数据，释放掉
                free(efirst);
                push(stack, newElementData(op->doCal(first, 0)));
            }
            if(op->operand == 2) {
                efirst = pop(stack);
                esecond = pop(stack);
                second = efirst->data;
                first = esecond->data;
                //从栈中弹出的数据，释放掉
                free(efirst);
                free(esecond);
                push(stack, newElementData(op->doCal(first, second)));
            }
            //释放掉运算符元素占用的内存
            free(op);
            free(get(postfix, i));
        }
    }
    if(getLength(stack) != 1)
        return DBL_MIN;
    efirst = pop(stack);
    double data = efirst->data;
    //释放掉保存结果的元素的内存
    free(efirst);
    //释放栈占用的内存
    del(stack);
    //释放掉逆波兰表达式占用的内存
    del(postfix);
    return data;
}

double compute_expression(char * exp)
{
    int len = strlen(exp);
    return CalPostfix(InfixToPostfix(CharToInfix(exp, len)));
}