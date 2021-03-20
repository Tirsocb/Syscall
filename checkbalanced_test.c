#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <string.h>

/*
Función principal para hacer el llamado al sistema
*/ 
int main()
{
    /*
    Insertar el char a evaluar.
    */
    char expression[100];
    printf("Insert expression: ");
    scanf("%s", expression);

    /*
    Insertar el length del char que se evalúa
    */
    int n = strlen(expression);

    // Para verificar el syscall
    long int res;
    
    /*
    El syscall es el 441, se le envían la expresión y el length
    */
    res = syscall(441, expression, n); 
    printf("Returned: %ld.\n", res);

    /*
    Mostrar el resultado en pantalla
    */
    if(res == 1)
    {
        printf("Is balanced\n");
    }
    else
    {
        printf("Not balanced\n");
    }
 
    return 0;
}