#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../librerias/MisFunciones.h"

//Estructura para las tareas realizadas o a realizar
struct {
    int TareaID;    /* numero autoincremental comenzando por el 1000 */
    char *descripcion;  
    int duracion;   /* aleatorio entre 10 - 100 */
} typedef tarea;

//Nodo para la lista enlazada
struct{
    tarea T;
    NodoTarea *siguiente;
}typedef NodoTarea;

NodoTarea *listaVacia(){
    return NULL;
}

void cargarTarea(tarea tarea, int ID){
    tarea.TareaID = ID;
    tarea.duracion = (rand()%91) + 10;
    char buffer[100];
    printf("\nDescripcion de la tarea (Max 100 caracteres);");
    gets(buffer);
    tarea.descripcion = asignarMemoriaYContenido(buffer);
}

int main(){
    


    
    return 0;
}

