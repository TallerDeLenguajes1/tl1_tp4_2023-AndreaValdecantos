#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cree un nuevo branch llamado lista-enlazada donde tendrá que reemplazar la implementación que realizó con listas enlazadas, para ello en vez de tener 2 arreglos de tareas ahora tendrá 2 listas enlazadas (una para las tareas pendientes y otra para las tareas realizadas) y cada vez que se marque como realizada tendrá que mover la tarea de la lista de tareas pendientes a la lista de tareas realizada

typedef struct Tarea{
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea tarea;
    struct Nodo *Siguiente;
}Nodo;

Nodo* crearNodo(int id, char* descripcion, int duracion);
Nodo* crearNodo(int id, char* descripcion, int duracion){
    Nodo* nodoNuevo = NULL;
    nodoNuevo = (Nodo*)malloc(sizeof(Nodo));

    if (nodoNuevo != NULL){
        nodoNuevo->tarea.TareaID = id;
        nodoNuevo->tarea.Descripcion = descripcion;
        nodoNuevo->tarea.Duracion = duracion;
        nodoNuevo->Siguiente = NULL;
    }

    return nodoNuevo;
}

void insertarNodo(Nodo** nodoInicial, int id, char* descripcion, int duracion);
void insertarNodo(Nodo** nodoInicial, int id, char* descripcion, int duracion){
    Nodo* nodoNuevo = NULL;
    nodoNuevo = crearNodo(id, descripcion, duracion);

    if (nodoNuevo != NULL){
        nodoNuevo->Siguiente = *nodoInicial;
        *nodoInicial = nodoNuevo;
    }
}

void cargarListaDeTareas(Nodo** nodoInicial, int cantidadDeTareasACargar);
void cargarListaDeTareas(Nodo** nodoInicial, int cantidadDeTareasACargar){
    char* buffer;
    buffer = (char*)malloc(100*sizeof(char));
    int duracion;

    for (int i = 0; i < cantidadDeTareasACargar; i++){
        printf("\n_________________________________________\n");
        printf("TAREA %d \r\n", i+1);
        printf("Descripcion: ");
        gets(buffer);
        fflush(stdin);
        char *descripcion = (char*)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(descripcion, buffer);
        do{
            printf("Duracion: ");
            scanf("%d", &duracion);
            fflush(stdin);
        } while (duracion < 10 || duracion > 100);
        insertarNodo(nodoInicial, i+1, descripcion, duracion);
    }

    free(buffer);
}

void mostrarLista(Nodo* nodoInicial);
void mostrarLista(Nodo* nodoInicial){
    Nodo* nodoAux = nodoInicial;

    while (nodoAux != NULL){
        printf("\nTarea id = %d\ndescripcion: %s\nduracion = %d\n", nodoAux->tarea.TareaID, nodoAux->tarea.Descripcion, nodoAux->tarea.Duracion);
        nodoAux = nodoAux->Siguiente;
    } 

    free(nodoAux);
}

int main(){

    Nodo* inicioPendientes = NULL;
    Nodo* inicioRealizadas = NULL;

    int cantidadDeTareasACargar;
    printf("=========================================\n");
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantidadDeTareasACargar);
    fflush(stdin);
    printf("=========================================\n");

    // 1. Reimplemente los puntos 1 a 5 del punto anterior utilizando las listas enlazadas. Modifique la interfaz de carga de tareas para que en vez de solicitar la cantidad de tareas al comienzo, al cabo de cada tarea pregunte al usuario si desea ingresar una nueva tarea o finalizar la carga.
    cargarListaDeTareas(&inicioPendientes, cantidadDeTareasACargar);
    printf("\n__________________________");
    printf("\nLISTA DE TAREAS PENDIENTES\n");
    mostrarLista(inicioPendientes);

    //2. Implemente también las funciones de búsquedas para que devuelvan el nodo correspondiente a la tarea solicitada Cree también la interfaz de usuario de consulta de tareas.

    return 0;
}