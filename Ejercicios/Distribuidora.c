#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//Estructura para las tareas realizadas o a realizar
struct {
    int TareaID;    /* numero autoincremental comenzando por el 1000 */
    char *descripcion;  
    int duracion;   /* aleatorio entre 10 - 100 */
} typedef tarea;

//Nodo para la lista enlazada
typedef struct NodoTarea{
    tarea T;
    NodoTarea *siguiente;
} NodoTarea;

NodoTarea * listaVacia();
NodoTarea * nuevaTarea(int id);
void cargarTarea(tarea *tarea, int ID);
void insertarNodo(NodoTarea **lista, NodoTarea *nuevaTarea);


int main(){
    
    NodoTarea *tareasPendientes =  listaVacia();
    bool opcion = true;
    int ID = 1000;
    while (opcion){
        
        
        
    }
    
    return 0;
}

char *asignarMemoriaYContenido(char *texto){
    if (strlen(texto) != 0) /* control para cadena vacia */
    {
        char *retorno = (char*)malloc(strlen(texto)+1);
        if (retorno == NULL)    /* control de error al asignar memoria */
        {
            puts("ERROR en asignarMemoriaYContenido");    
        }
        strcpy(retorno,texto); /* copia de la cadena original */
        return retorno;
    }else{
        return NULL;
    }
    
}

//funcion para crear nodo/lista vacia
NodoTarea * listaVacia(){
    return NULL;
}

//funcion para llenar una tarea
void cargarTarea(tarea *tarea, int ID){
    tarea->TareaID = ID;
    tarea->duracion = (rand()%91) + 10;
    char buffer[100];
    printf("\nDescripcion de la tarea %d (Max 100 caracteres):\t", ID);
    gets(buffer);
    tarea->descripcion = asignarMemoriaYContenido(buffer);
    fflush(stdin);
}

NodoTarea *nuevaTarea(int id){
    NodoTarea * nuevaTarea = (NodoTarea*)malloc(sizeof(NodoTarea));
    if (nuevaTarea == NULL){
        puts("\t\t----Error en NodoTarea nuevaTarea---");
    }else{
        cargarTarea(&nuevaTarea->T,id);
        nuevaTarea->siguiente = listaVacia();
    }
    return nuevaTarea;
}

void insertarNodo(NodoTarea **lista, NodoTarea *nuevaTarea)
{
    nuevaTarea->siguiente = *lista;
    lista = nuevaTarea;
}