#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// LISTA DE TAREAS

typedef struct Tarea
{
    int TareaID;       // por iteración
    char *Descripcion; // entre 10-100
    int Duracion;
} Tarea;

typedef struct Nodo
{
    Tarea tarea;            // guarda una tarea
    struct Nodo *Siguiente; // puntero a la siguiente tarea
} Nodo;

// crear lista vacía
Nodo * lista = NULL;       // puntero a nodo
Nodo * listaHechas = NULL; // puntero a nodo

// crear tarea
Tarea *crearTarea(int id, int duracion, char *descripcion);

// crear nodo
Nodo *crearNodo(Tarea *tarea);

// insertar nodo
void insertarNodo(Nodo **lista, Tarea *tarea); // doble puntero para modificar la lista

void mostrarTarea(Tarea *tarea);

// mostrar lista
void mostrarLista(Nodo *lista);

// longitud lista
int longitudLista(Nodo *lista);

// cargar lista
void cargarLista(Nodo **lista);

// consultar tarea realizada
bool consultarTareaRealizada(Tarea *tarea);

//eliminar tarea
void eliminarTarea(Tarea * tarea);

// borrar nodo por id
void borrarNodoEspecifico(Nodo ** inicio, int numero);

// lista tareas realizadas
void cargarTareasRealizadas(Nodo **lista, Nodo **listaHechas, int cantidad);

// buscar tarea por id
void buscarTareaPorID(Nodo *lista, int idBuscar);

// buscar tarea por palabra clave
void buscarTareaPorPalabraClave(Nodo *lista, char *bufferPalabraClave);

// mostrar opciones del menú
void mostrarMenu();

// pedir opcion para menú
int pedirOpcionMenu();

// realizar lo pedido
void operacionMenuSegunOpcion(int opcion, Nodo **lista, Nodo **listaHechas);


int main()
{
    mostrarMenu();
    int opcion = pedirOpcionMenu();

    while (opcion != 0)
    {
        operacionMenuSegunOpcion(opcion, &lista, &listaHechas);
        mostrarMenu();
        opcion = pedirOpcionMenu();
        if (opcion == 0)
        {
            printf("\n\nFIN DEL PROGRAMA\n\n");
        }
    }

    return 0;
}


Tarea *crearTarea(int id, int duracion, char *descripcion)
{
    Tarea *tarea = (Tarea *)malloc(sizeof(Tarea));
    tarea->TareaID = id;
    tarea->Duracion = duracion;
    tarea->Descripcion = (char *)malloc((strlen(descripcion) + 1) * sizeof(char));
    strcpy(tarea->Descripcion, descripcion);

    return tarea;
}

Nodo *crearNodo(Tarea *tarea)
{
    Nodo *nodoNuevo = (Nodo *)malloc(sizeof(Nodo)); // reservo memoria para nodo nuevo
    nodoNuevo->tarea.TareaID = tarea->TareaID;
    nodoNuevo->tarea.Duracion = tarea->Duracion;
    nodoNuevo->tarea.Descripcion = tarea->Descripcion;
    nodoNuevo->Siguiente = NULL;

    return nodoNuevo;
}

void insertarNodo(Nodo **lista, Tarea *tarea)
{
    Nodo *nuevoNodo = crearNodo(tarea);
    nuevoNodo->Siguiente = *lista;
    *lista = nuevoNodo;
}

void mostrarTarea(Tarea *tarea)
{
    printf("\nID: %d, DURACION: %d, DESCRIPCION: %s\n", tarea->TareaID, tarea->Duracion, tarea->Descripcion);
}

void mostrarLista(Nodo *lista)
{
    Nodo *auxRecorrerLista = lista;
    printf("\n");

    if (lista)
    {
        while (auxRecorrerLista != NULL)
        {
            mostrarTarea(&auxRecorrerLista->tarea);
            auxRecorrerLista = auxRecorrerLista->Siguiente;
        }
    } else {
        printf("LISTA VACIA\n");
    }
    free(auxRecorrerLista);
}

int longitudLista(Nodo *lista)
{
    Nodo *auxRecorrerLista = lista;
    int longitud = 0;

    if (lista)
    {
        while (auxRecorrerLista != NULL)
        {
            longitud++;
            auxRecorrerLista = auxRecorrerLista->Siguiente;
        }
    }
    free(auxRecorrerLista);

    return longitud;
}

void cargarLista(Nodo **lista)
{
    // int cantidadDeNodos;
    int respuesta;
    int i = 0;
    int duracion;
    char *descripcion = (char *)malloc(100 * sizeof(char));
    // scanf("%d", &cantidadDeNodos);
    printf("\nCARGAR LISTA DE TAREAS PENDIENTES\n");
    printf("Ingresar nueva tarea? (1:si, 0:no): ");
    scanf("%d", &respuesta);
    fflush(stdin);

    while (respuesta == 1)
    {
        i++;
        printf("DESCRIPCION: ");
        gets(descripcion);
        do
        {
            printf("DURACION: ");
            scanf("%d", &duracion);
            fflush(stdin);
        } while (duracion <= 10 || duracion >= 100);

        Tarea *tarea = crearTarea(i, duracion, descripcion);
        insertarNodo(lista, tarea);
        printf("\nIngresar nueva tarea? (1:si, 0:no): ");
        scanf("%d", &respuesta);
        fflush(stdin);
    }

    // for (int i = 0; i < cantidadDeNodos; i++){
    // printf("DESCRIPCION: ");
    // gets(descripcion);
    // Tarea * tarea = crearTarea(i+1, rand() % 99 + 1, descripcion);
    // insertarNodo(lista, tarea);
    // }
}

bool consultarTareaRealizada(Tarea *tarea)
{
    int respuesta;

    printf("\nHizo la tarea %d (%s)? (1:si, 0: no): ", tarea->TareaID, tarea->Descripcion);
    scanf("%d", &respuesta);
    fflush(stdin);

    if (respuesta == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void eliminarTarea(Tarea * tarea){
    free(tarea->Descripcion);
    free(tarea);
}

void borrarNodoEspecifico(Nodo ** inicio, int numero)
{
    if (inicio != NULL)
    {
        Nodo *aux = *inicio;
        Nodo *auxAnterior = NULL;

        if (aux->tarea.TareaID == numero)
        { // SI EL PRIMER NODO TIENE EL DATO QUE SE BUSCA
            *inicio = (*inicio)->Siguiente;
            free(aux);
        }
        else
        {
            while (aux != NULL && aux->tarea.TareaID != numero)
            { // PARA BUSCAR EN LOS SIGUIENTES NODOS
                auxAnterior = aux;
                aux = aux->Siguiente;
            }
            if (aux != NULL && aux->tarea.TareaID == numero)
            {
                auxAnterior->Siguiente = aux->Siguiente;
                eliminarTarea(&(aux->tarea));
                free(aux);
            }
        }
    }
}

void cargarTareasRealizadas(Nodo **lista, Nodo **listaHechas, int cantidad)
{
    Nodo *auxLista = *lista;
    int *arregloDeIDs = (int *)malloc(cantidad * sizeof(int));

    printf("\nCARGAR LISTA DE TAREAS REALIZADAS\n");

    if (lista)
    {
        for (int i = 0; i < cantidad; i++)
        {
            while (auxLista != NULL)
            {
                if (consultarTareaRealizada(&auxLista->tarea))
                {
                    insertarNodo(listaHechas, &auxLista->tarea);
                    arregloDeIDs[i] = auxLista->tarea.TareaID;
                }
                else
                {
                    arregloDeIDs[i] = 0;
                }
                i++;
                auxLista = auxLista->Siguiente;
            }
        }
    }
    free(auxLista);

    // printf("\n\nARREGLO DE IDs\n");
    for (int i = 0; i < cantidad; i++)
    {
        // printf("%d \t", arregloDeIDs[i]);
        borrarNodoEspecifico(lista, arregloDeIDs[i]);
    }
}

void buscarTareaPorID(Nodo *lista, int idBuscar)
{
    if (lista != NULL)
    {
        Nodo *aux = lista;

        while (aux != NULL && aux->tarea.TareaID != idBuscar)
        {
            aux = aux->Siguiente;
        }
        if (aux != NULL && aux->tarea.TareaID == idBuscar)
        {
            printf("\nTAREA ENCONTRADA: ");
            mostrarTarea(&aux->tarea);
        }
    }
}

void buscarTareaPorPalabraClave(Nodo *lista, char *bufferPalabraClave)
{
    char *palabraClave;
    palabraClave = (char *)malloc((strlen(bufferPalabraClave) + 1) * sizeof(char));
    strcpy(palabraClave, bufferPalabraClave);

    if (lista != NULL)
    {
        Nodo *aux = lista;

        while (aux != NULL && strstr(aux->tarea.Descripcion, palabraClave) == NULL)
        {
            aux = aux->Siguiente;
        }
        if (aux != NULL && strstr(aux->tarea.Descripcion, palabraClave) != NULL)
        {
            printf("\nTAREA ENCONTRADA: ");
            mostrarTarea(&aux->tarea);
        }
    }
}

void mostrarMenu()
{
    printf("\n\n==============================================");
    printf("\n                     MENU\n");
    printf("==============================================\n");
    printf("1_ CARGAR LISTA DE PENDIENTES\n");
    printf("2_ MOVER TAREAS REALIZADAS\n");
    printf("3_ BUSCAR TAREA POR ID\n");
    printf("4_ BUSCAR TAREA POR PALABRA CLAVE\n");
    printf("5_ MOSTRAR LISTA DE TAREAS PENDIENTES\n");
    printf("6_ MOSTRAR LISTA DE TAREAS REALIZADAS\n");
    printf("0_ SALIR\n");
    printf("==============================================\n");
}

int pedirOpcionMenu()
{
    int opcion;
    printf("                             ELEGIR OPCION: ");
    scanf("%d", &opcion);
    printf("==============================================\n");
    fflush(stdin);

    return opcion;
}

void operacionMenuSegunOpcion(int opcion, Nodo **lista, Nodo **listaHechas)
{
    int idBuscar;
    char *bufferPalabraClave = (char *)malloc(100 * sizeof(char));

    switch (opcion)
    {
    case 1:
        cargarLista(lista);
        break;
    case 2:
        cargarTareasRealizadas(lista, listaHechas, longitudLista(*lista));
        break;
    case 3:
        printf("\nBUSCAR TAREA POR ID\n");
        printf("ID de tarea a buscar: ");
        scanf("%d", &idBuscar);
        fflush(stdin);
        buscarTareaPorID(*lista, idBuscar);
        buscarTareaPorID(*listaHechas, idBuscar);
        break;
    case 4:
        printf("\nBUSCAR TAREA POR PALABRA CLAVE\n");
        printf("Palabra clave de la tarea a buscar: ");
        gets(bufferPalabraClave);
        fflush(stdin);
        buscarTareaPorPalabraClave(*lista, bufferPalabraClave);
        buscarTareaPorPalabraClave(*listaHechas, bufferPalabraClave);
        break;
    case 5:
        printf("\n -----------------\n");
        printf("|TAREAS PENDIENTES|");
        printf("\n -----------------");
        mostrarLista(*lista);
        break;
    case 6:
        printf("\n -----------------\n");
        printf("|TAREAS REALIZADAS|");
        printf("\n -----------------");
        mostrarLista(*listaHechas);
        break;

    default:
        break;
    }
}