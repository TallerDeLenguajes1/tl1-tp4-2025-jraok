#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estructura para las tareas realizadas o a realizar
struct {
    int TareaID;    /* numero autoincremental comenzando por el 1000 */
    char *descripcion;  
    int duracion;   /* aleatorio entre 10 - 100 */
} typedef tarea;

//Nodo para la lista enlazada
typedef struct NodoTarea{
    tarea T;
    struct NodoTarea *siguiente;
} NodoTarea;

char *asignarMemoriaYContenido(char *texto);
NodoTarea * listaVacia();
void cargarTarea(tarea *tarea, int ID);
NodoTarea * nuevaTarea(int id);
void insertarNodoAlInicio(NodoTarea **lista, NodoTarea *nuevaTarea);
void mostrarLista(NodoTarea *lista);
void mostrarNodo(NodoTarea nodo);

int main(){
    srand(time(NULL));
    NodoTarea *tareasPendientes =  listaVacia();
    char opcion = '1';
    int ID = 1000;
    while (opcion != '0'){
        if (opcion == '1')
        {
            insertarNodoAlInicio(&tareasPendientes,nuevaTarea(ID));
            ID++;
        }
        
        printf("\nContinuar agregando tareas?\n\t Si = 1 / No = 0\n");
        scanf("%c",&opcion);
        fflush(stdin);
        if (opcion != '0' && opcion != '1')
        {
            puts("\t\t----Opcion Invalida----");
        }
    }
    
    mostrarLista(tareasPendientes);
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
    while (tarea->descripcion == NULL){
        puts("\t\t----Descripcion invalida, ringrese----");
        printf("\nDescripcion de la tarea %d (Max 100 caracteres):\t", ID);
        gets(buffer);
        tarea->descripcion = asignarMemoriaYContenido(buffer);
    }    
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

void insertarNodoAlInicio(NodoTarea **lista, NodoTarea *nuevaTarea)
{
    nuevaTarea->siguiente = *lista;
    *lista = nuevaTarea;
}

void mostrarNodo(NodoTarea nodo){
    printf("\nID:\t%d", nodo.T.TareaID);
    printf("\nDuracion:\t%dmin", nodo.T.duracion);
    printf("\nDescripcion:\t%s", nodo.T.descripcion);
};

void mostrarLista(NodoTarea *lista)
{
    NodoTarea *actual = lista;
    while (actual != NULL){
        mostrarNodo(*actual);
        puts("");
        actual = actual->siguiente;
    }
}
