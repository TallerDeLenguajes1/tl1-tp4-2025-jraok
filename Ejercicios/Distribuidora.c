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
    NodoTarea *tareasPendientes =  listaVacia();    /* inicio para la lista de tareas pendientes */
    char opcion = '1';      /* variable para el menu, es char para operar con cualquier valor delt teclado */
    int ID = 1000;      /* id para las tareas */
    while (opcion != '0'){      /* bucle para agregar las tareas */
        // solo agrego una nueva tarea si opcion = 1
        if (opcion == '1')
        {  
            // en vez de crear un nuevo nodo envio la funcion como parametro
            insertarNodoAlInicio(&tareasPendientes,nuevaTarea(ID));
            ID++;   /* autoincremento del ID */
        }
        printf("\nContinuar agregando tareas?\n\t Si = 1 / No = 0\n"); /* mensaje de opcion */
        scanf("%c",&opcion);
        fflush(stdin);
        if (opcion != '0' && opcion != '1')     /* mensaje de error para la opcion */
        {
            puts("\t\t----Opcion Invalida----");
        }
    }
    /* impresion de los nodos de la lista */
    mostrarLista(tareasPendientes);
    return 0;
}

// funcion para asignar memoria y contenido en un arreglo
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
    tarea->TareaID = ID;        /* ID recibido como parametro */
    tarea->duracion = (rand()%91) + 10;     /* duracion aleatoria entre 10 y 100 */
    char buffer[100];   /* arreglo para la descripcion */
    printf("\nDescripcion de la tarea %d (Max 100 caracteres):\t", ID);
    gets(buffer);
    tarea->descripcion = asignarMemoriaYContenido(buffer);      /* guardado de la descripcion */
    while (tarea->descripcion == NULL){     /* control para una descripcion vacia */
        puts("\t\t----Descripcion invalida, ringrese----");
        printf("\nDescripcion de la tarea %d (Max 100 caracteres):\t", ID);
        gets(buffer);
        tarea->descripcion = asignarMemoriaYContenido(buffer);
    }    
}

// funcion que crea y devuelve un nodoTarea
NodoTarea *nuevaTarea(int id){
    NodoTarea * nuevaTarea = (NodoTarea*)malloc(sizeof(NodoTarea)); /* nuevo nodo para la lista */
    if (nuevaTarea == NULL){
        puts("\t\t----Error en NodoTarea nuevaTarea---");
    }else{
        cargarTarea(&nuevaTarea->T,id);     /* carga de la informacion */
        nuevaTarea->siguiente = listaVacia();   /* aterrizo el siguiente (buena práctica) */
    }
    return nuevaTarea; /* retorno el nuevo nodo */
}

// funcion que agrega un nuevo nodo al inicio de la lista
void insertarNodoAlInicio(NodoTarea **lista, NodoTarea *nuevaTarea)
{
    /* primero dejo que el nuevo nodo mantenga al que estaba al inicio para no perderlo*/
    nuevaTarea->siguiente = *lista;
    /* luego hago que la lista ahora apunte a el */
    *lista = nuevaTarea;
    /* asi ahora la lista apunta al nuevo nodo y él apunta al nodo que ya estaba antes */
}

// funcion para mostrar la infonmacion de un nodo(tarea)
void mostrarNodo(NodoTarea nodo){
    printf("\nID:\t%d", nodo.T.TareaID);
    printf("\nDuracion:\t%dmin", nodo.T.duracion);
    printf("\nDescripcion:\t%s", nodo.T.descripcion);
};

// funcion para mostrar la lista completa
void mostrarLista(NodoTarea *lista)
{
    NodoTarea *actual = lista; /* nodo auxiliar para la reescritura de informacion */
    while (actual != NULL){
        mostrarNodo(*actual);
        puts("");
        actual = actual->siguiente;
    }
}
