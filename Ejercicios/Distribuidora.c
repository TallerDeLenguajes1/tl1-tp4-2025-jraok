#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct 
{
    int TareaID;    /* numero autoincremental comenzando por el 1000 */
    char *descripcion;  
    int duracion;   /* aleatorio entre 10 - 100 */
} typedef tarea;

struct
{
    tarea T;
    NodoTarea *siguiente;
}typedef NodoTarea;

int main(){
    
    return 0;
}

