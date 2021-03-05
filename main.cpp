#include <iostream>

//libreria del stack, archivo sacado de github
#include "stdc++.h"
using namespace std;

//funcion principal que chequea si la expresion esta balanceada, retorna true o false
// toma un string que es la expresion
bool checkArithmetic(string expression)
{
    //stack donde se ingresan los brackets de la expresion
    stack<char> symbolStack;
    char x;

    //recorrer expresion
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '(' || expression[i] == '['
            || expression[i] == '{')
        {
            //si algun simbolo (que abre) hace match lo metemos al stack
            symbolStack.push(expression[i]);
            continue;
        }


        //a este punto el stack debe de tener todos los que abren, si no encuentra ninguno
        //que abre, entonces tiene que ser un simbolo que cierra
        //el stack no tendria por que estar vacio a este punto, si esta vacio entonces la
        //expresion esta mal balanceada y retornamos falso
        if (symbolStack.empty())
            return false;

        //switch para verificar los simbolos que cierran
        // se hace pop del stack y se verifica que el simbolo haga match con el simbolo de cierre que corresponde
        switch (expression[i]) {
        case ')':
           x = symbolStack.top();
            symbolStack.pop();
            if (x == '{' || x == '[')
                return false;
            break;

        case '}':
            x = symbolStack.top();
            symbolStack.pop();
            if (x == '(' || x == '[')
                return false;
            break;

        case ']':
            x = symbolStack.top();
            symbolStack.pop();
            if (x == '(' || x == '{')
                return false;
            break;
        }
    }

    // retorna true si el stack esta vacio, el stack va a estar vacio si solo si
    // todos los simbolos que abren tienen un simbolo de cierre que le corresponde
    return (symbolStack.empty());
}

// Driver code
int main()
{
    string expr = "[(1+1)*(2+2)]";

    // Function call
    if (checkArithmetic(expr))
        cout << "Balanced";
    else
        cout << "Not Balanced";
    return 0;
}
