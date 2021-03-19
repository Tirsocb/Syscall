#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/linkage.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/printk.h>

#define bool int

/*
Se define la estructura para los nodos del stack
*/
struct stackNode 
{
    /* data */
    char data;
    struct stackNode* next;    
};

/*
Creación de los prototipos

1. Prototipo para hacer push en el stack
*/
void push(struct stackNode** top_ref, int my_data);

/*
2. Prototipo para hacer pop en el stack
*/
int pop(struct stackNode** top_ref);

/*
Función para hacer push
*/
void push(struct stackNode** top_ref, int my_data)
{
    struct stackNode* newNode = (struct stackNode*) kmalloc(sizeof(struct stackNode), GFP_KERNEL);

    if(newNode == NULL)
    {
        printk("Stack Overflow\n");
    }

    /*
    Colocar el nodo en la data
    */
    newNode->data = my_data;

    /*
    Hacer link de la lista del nuevo nodo
    */
    newNode->next = (*top_ref);

    /*
    Mover el puntero al nuevo nodo
    */
    (*top_ref) = newNode;
}

/*
Función para hacer pop
*/
int pop(struct stackNode** top_ref)
{
    char result;
    struct stackNode* top;

    if(*top_ref == NULL)
    {
        printk("Stack Overflow\n");
        return 0;
    }

    /*
    Si no hay error, entonces hacer pop del elemento correspondiente
    y reubicar el puntero.
    */
    else{
        top = *top_ref;
        result = top->data;
        *top_ref = top->next;
        kfree(top);
        return result;
    }
}

/*
Retorna 1, si el char1 y el char2 son brackets izquierdo y derecho respectivamente
*/
bool isAMatch(char char1, char char2)
{
    if((char1 == '(' && char2 == ')' ) || (char1 == '{' && char2 == '}') || (char1 == '[' && char2 == ']'))
    {
        return 1;
    }
    else
        return 0;    
}

/*
MACRO
SYSCALL_DEFINEn para verificar el string ingresado
1. Se debe ingresar el string
2. Se debe ingresar el length del string
*/
SYSCALL_DEFINE2(checkbalanced, char *, expression, int, n)
{
        printk("Int for checkbalanced syscall:  \"%d\"\n", n);
    printk("Expression: \"%c\"\n", expression[0]);
    int i = 0;

    for(i = 1; i < n; i++)
    {
        printk("Expression: \"%c\"\n", expression[i]);
    }

    i = 0;

    /*
    Se inicializa el stack
    */
    struct stackNode* stack = NULL;

    while (i < n)
    {
        /* 
        Si expression[i] es cualquiera de los brackes
        se procede a hacer push en el stack
        */
        if(expression[i] == '[' || expression[i] == '(' || expression[i] == '{')
        {
            push(&stack, expression[i]);
        }

        /*
        Si expression[i] es cualquiera de los brackes se procede a hacer push en el stack
        También se evalúa si es un match con un bracket abierto
        */
        if(expression[i] == ']' || expression[i] == ')' || expression[i] == '}')
        {
            if(stack == NULL)
            {
                return 0;
            }

            /*
            Se hace un pop del top element del stack para verificar si al mismo tiempo
            es un match con otro bracket.
            */
            else if(!isAMatch(pop(&stack), expression[i]))
            {
                return 0;
            }
        }

        i++;
    }

        printk("Syscall info\n");

    /*
    Aquí simplemente se devuelve el resultado de la función principal
    En dado caso ya no hay elementos en el stack, significa que está balanceado
    De lo contrario, no lo está
    */    
    if(stack == NULL)
    { 
        // Balanced expression
        printk("Balanced\n");
        return 1;
    }

    else
    {
        // Not balanced expression
        printk("Not balanced\n");
        return 0;
    }
}