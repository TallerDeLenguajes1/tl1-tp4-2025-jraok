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

char * asignarMemoriaYContenido(char *texto);
NodoTarea * listaVacia();
void cargarTarea(tarea *tarea, int ID);
NodoTarea * nuevaTarea(int id);
void insertarTarea(NodoTarea **lista, NodoTarea *nuevaTarea);
void mostrarLista(NodoTarea *lista);
void mostrarTodasLasTareas(NodoTarea *pendientes, NodoTarea *realizadas);
void mostrarNodo(NodoTarea nodo);
void menuDeOpciones();
NodoTarea * extraerTarea(NodoTarea **lista, int ID);
void marcarComoRealizada();

int main(){
    puts("\n\t\tTdLI -- TRABAJO PRACTICO 4\n");
    srand(time(NULL));
    NodoTarea *tareasPendientes =  listaVacia();    /* inicio para la lista de tareas pendientes */
    NodoTarea *tareasRealizadas =  listaVacia();    /* inicio para la lista de tareas realizadas */
    char opcion = '0', continuar = '1';      /* variable para el menu, es char para operar con cualquier valor delt teclado */
    int ID = 1000;      /* id para las tareas */
    while (opcion != '6'){      /* bucle para el menu de opciones */   
        menuDeOpciones();
        fflush(stdin);
        scanf("%c",&opcion);
        switch (opcion)
        {
        case '1':{  
                    while (continuar = '1')
                    {
                        if (continuar == '1')
                        {  
                            // en vez de crear un nuevo nodo envio la funcion como parametro
                            insertarTarea(&tareasPendientes,nuevaTarea(ID));
                            ID++;   /* autoincremento del ID */
                        }
                        printf("\nContinuar agregando tareas?\n\t Si = 1 / No = 0\n"); /* mensaje de continuar */
                        scanf("%c",&continuar);
                        fflush(stdin);
                        if (continuar != '0' && continuar != '1')     /* mensaje de error */
                        {
                            puts("\t\t----Opcion Invalida----");
                        }
                    }
                }

            break;

        case '2':
            mostrarTodasLasTareas(tareasPendientes,tareasRealizadas);
            break;

        case '3':{
                    puts("\t\t----Lista de Tareas Pendientes----");
                    mostrarLista(tareasPendientes);
                    int bandera = 1;
                    while (bandera)
                    {
                        char buffer[100];
                        printf("\n\tIngrese el ID de la tarea (Enter para cancelar):  ");
                        fflush(stdin);
                        gets(buffer);
                        if (buffer[0] == '\0')
                        {
                            break;
                        }else{
                            NodoTarea * extraida = extraerTarea(&tareasPendientes, atoi(buffer));
                            if (extraida != NULL)
                            {
                                insertarTarea(&tareasRealizadas, extraida);
                                break;
                            }else{
                                puts("----ID invalido, reingrese----");
                            }
                        }
                    } 
                }
            break;

        case '4':
            
            break;
        case '5':
            
            break;
        
        default:
            break;
        }
    }
    /* impresion de los nodos de la lista */
    mostrarLista(tareasPendientes);
    return 0;
}

// funcion para asignar memoria y contenido en un arreglo
char * asignarMemoriaYContenido(char *texto)
{
    if (strlen(texto) != 0) /* control para cadena vacia */
    {
        char *retorno = (char*)malloc(strlen(texto)+1);
        if (retorno == NULL)    /* control de error al asignar memoria */
        {
            puts("ERROR en asignarMemoriaYContenido");    
        }
        strcpy(retorno,texto); /* copia de la cadena original */
        return retorno;
    }
    return NULL;
}

//funcion para crear nodo/lista vacia
NodoTarea * listaVacia()
{
    return NULL;
}

//funcion para llenar una tarea
void cargarTarea(tarea *tarea, int ID)
{
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
NodoTarea *nuevaTarea(int id)
{
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
void insertarTarea(NodoTarea **lista, NodoTarea *nuevaTarea)
{
    /* primero dejo que el nuevo nodo mantenga al que estaba al inicio para no perderlo*/
    nuevaTarea->siguiente = *lista;
    /* luego hago que la lista ahora apunte a el */
    *lista = nuevaTarea;
    /* asi ahora la lista apunta al nuevo nodo y él apunta al nodo que ya estaba antes */
}

// funcion para quitar una tarea
NodoTarea * extraerTarea(NodoTarea **lista, int ID)
{
    NodoTarea * temporal = (*lista), *anterior = NULL;
    while (temporal != NULL && temporal->T.TareaID != ID)
    {
        anterior = temporal;
        temporal = temporal->siguiente;
    }

    if (temporal != NULL)
    {
        if (temporal == (*lista))
        {
            (*lista) = temporal->siguiente;
        }else{
            anterior->siguiente = temporal->siguiente;
        }
        temporal->siguiente = NULL;    
    }
    return temporal;
}

// funcion para mostrar la infonmacion de un nodo(tarea)
void mostrarNodo(NodoTarea nodo)
{
    printf("\nID:\t%d", nodo.T.TareaID);
    printf("\nDuracion:\t%dmin", nodo.T.duracion);
    printf("\nDescripcion:\t%s", nodo.T.descripcion);
}

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

// funcion para mostrar todas las tareas por orden de ID
void mostrarTodasLasTareas(NodoTarea *pendientes, NodoTarea *realizadas)
{
    NodoTarea *auxPendiente = pendientes;
    NodoTarea *auxRealizada = realizadas;
    // se mostrarán los nodos siempre que alguno de las dos listas sea distinta de null
    while (auxPendiente != NULL || auxRealizada != NULL)
    {
        // para mostrar las tareas pendientes tengo dos situaciones, que realizadas ya esté en null o que la pendiente sea mayor
        if ((auxPendiente != NULL && auxRealizada == NULL) && (auxPendiente->T.TareaID > auxRealizada->T.TareaID))
        {
            // muestro y me muevo al sieguiente nodo
            mostrarNodo(*auxPendiente);
            auxPendiente = auxPendiente->siguiente;
            puts("Estado: Pendiente");
        }else if (auxRealizada != NULL){ /* solo lo muestro su la realizadas no es null */
            // muestro y me muevo al sieguiente nodo
            mostrarNodo(*auxRealizada);
            auxRealizada = auxRealizada->siguiente;
            puts("Estado: Realizada");
        }
    }
}

// mensaje para mostrar el menu de opciones
void menuDeOpciones()
{
    puts("\t---MENU DE OPCIONES---\n");
    puts("\t1-Agregar tarea pendiente");
    puts("\t2-Listar todas las tareas");
    puts("\t3-Marcar tarea como realizada");
    puts("\t4-Buscar por ID");
    puts("\t5-Buscar por palabra clave");
    puts("\t6-Salir");
}

