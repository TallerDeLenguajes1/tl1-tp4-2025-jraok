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
void cargarTarea(tarea *tarea, int ID);


int main(){
    
    NodoTarea *tareasPendientes =  listaVacia();

        
    
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
    printf("\nDescripcion de la tarea %d (Max 100 caracteres);", ID);
    gets(buffer);
    tarea->descripcion = asignarMemoriaYContenido(buffer);
    fflush(stdin);
}

