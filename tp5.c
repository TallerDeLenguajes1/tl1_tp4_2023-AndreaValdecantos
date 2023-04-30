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

// crear listas vacías
Nodo *lista = NULL;           // puntero a nodo
Nodo *listaHechas = NULL;     // puntero a nodo
Nodo *tareasEnProceso = NULL; // puntero a nodo
int indice = 0; // para controlar los ids

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
void cargarLista(Nodo **lista, int *indice);

// consultar tarea realizada
bool consultarTareaRealizada(Tarea *tarea);

// eliminar tarea
void eliminarTarea(Tarea *tarea);

// mostrar datos
void mostrarDatos(Nodo *lista);

// borrar nodo por id
void borrarNodoEspecifico(Nodo **inicio, int numero);

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
void operacionMenuSegunOpcion(int opcion, Nodo **lista, Nodo **listaHechas, Nodo **tareasEnProceso);

//mover tareas entre listas
void moverTareas(Nodo **listaOrigen, Nodo **listaDestino, int id);

//averiguar si existe una tarea con un id específico y devuelve bool
bool idEncontrado(Nodo *lista, int idEncontrado);

int main()
{
    mostrarMenu();
    int opcion = pedirOpcionMenu();

    while (opcion != 0)
    {
        operacionMenuSegunOpcion(opcion, &lista, &listaHechas, &tareasEnProceso);
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
    }
    else
    {
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

bool idEncontrado(Nodo *lista, int idEncontrado)
{
    Nodo *aux = lista;

    if (lista != NULL)
    {
        while (aux != NULL && aux->tarea.TareaID != idEncontrado)
        {
            aux = aux->Siguiente;
        }
        if (aux)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void mostrarDatos(Nodo *lista)
{
    // int cantidadTareas = longitudLista(lista);
    Nodo *aux = lista;
    int tiempoLista = 0;
    int cantidadTareas = 0;

    if (aux != NULL)
    {
        while (aux != NULL)
        {
            cantidadTareas++;
            tiempoLista += aux->tarea.Duracion;
            aux = aux->Siguiente;
        }
    }

    free(aux);

    printf("\nCantidad de tareas: %d\nTiempo total para las tareas: %d\n", cantidadTareas, tiempoLista);
}

void cargarLista(Nodo **lista, int *indice)
{
    // int cantidadDeNodos;
    int respuesta;
    int duracion;
    char *descripcion = (char *)malloc(100 * sizeof(char));
    // scanf("%d", &cantidadDeNodos);
    printf("\nCARGAR LISTA DE TAREAS PENDIENTES\n");
    printf("Ingresar nueva tarea? (1:si, 0:no): ");
    scanf("%d", &respuesta);
    fflush(stdin);

    while (respuesta == 1)
    {
        (*indice) = (*indice) + 1;
        printf("DESCRIPCION: ");
        gets(descripcion);
        do
        {
            printf("DURACION: ");
            scanf("%d", &duracion);
            fflush(stdin);
        } while (duracion <= 10 || duracion >= 100);

        Tarea *tarea = crearTarea(*indice, duracion, descripcion);
        insertarNodo(lista, tarea);
        printf("\nIngresar nueva tarea? (1:si, 0:no): ");
        scanf("%d", &respuesta);
        fflush(stdin);
    }
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

void eliminarTarea(Tarea *tarea)
{
    free(tarea->Descripcion);
    free(tarea);
}

void borrarNodoEspecifico(Nodo **inicio, int numero)
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
                // eliminarTarea(&(aux->tarea));
                free(aux);
            }
        }
    }
}

void cargarTareasRealizadas(Nodo **lista, Nodo **listaHechas, int cantidad)
{
    Nodo *auxLista = *lista;
    int *arregloDeIDs = (int *)malloc(cantidad * sizeof(int));
    int i = 0;

    printf("\nCARGAR LISTA DE TAREAS REALIZADAS\n");

    if (lista)
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
    free(auxLista);

    // printf("\n\nARREGLO DE IDs\n");
    for (int i = 0; i < cantidad; i++)
    {
        // printf("%d \t", arregloDeIDs[i]);
        borrarNodoEspecifico(lista, arregloDeIDs[i]);
    }
}

void moverTareas(Nodo **listaOrigen, Nodo **listaDestino, int id)
{
    Nodo *auxLista = *listaOrigen;

    if (listaOrigen)
    {
        while (auxLista != NULL)
        {
            if (auxLista->tarea.TareaID == id)
            {
                insertarNodo(listaDestino, &auxLista->tarea);
            }
            auxLista = auxLista->Siguiente;
        }
    }
    free(auxLista);

    borrarNodoEspecifico(listaOrigen, id);
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
    printf("2_ MODIFICAR TAREAS PENDIENTES\n");
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

void operacionMenuSegunOpcion(int opcion, Nodo **lista, Nodo **listaHechas, Nodo **tareasEnProceso)
{
    int idBuscar;
    int idCambiar;
    int opcionEntreListas;
    int numeroDeLista;
    int opcionContinuar = 1;
    char *bufferPalabraClave = (char *)malloc(100 * sizeof(char));

    switch (opcion)
    {
    case 1:
        cargarLista(lista, &indice);
        break;
    case 2:
        while (opcionContinuar == 1)
        {
            printf("\nMODIFICAR TAREAS PENDIENTES\n");
            printf("\n -----------------\n");
            printf("|TAREAS PENDIENTES|");
            printf("\n -----------------");
            mostrarLista(*lista);
            printf("\n -----------------\n");
            printf("|TAREAS EN PROCESO|");
            printf("\n -----------------");
            mostrarLista(*tareasEnProceso);
            printf("\n -----------------\n");
            printf("|TAREAS REALIZADAS|");
            printf("\n -----------------");
            mostrarLista(*listaHechas);

            printf("\n\nSeleccionar tarea con id: ");
            scanf("%d", &idCambiar);
            fflush(stdin);

            if (idEncontrado(*lista, idCambiar) == true || idEncontrado(*listaHechas, idCambiar) == true || idEncontrado(*tareasEnProceso, idCambiar) == true)
            {
                printf("\n1:Mover tarea\n2:Eliminar tarea\n3:Nada\n_________\nOpcion: ");
                scanf("%d", &opcionEntreListas);
                fflush(stdin);

                switch (opcionEntreListas)
                {
                case 1:
                    printf("\nMover a lista (1: pendientes, 2: en proceso, 3: realizada): ");
                    scanf("%d", &numeroDeLista);
                    fflush(stdin);
                    switch (numeroDeLista)
                    {
                    case 1:
                        if (idEncontrado(*listaHechas, idCambiar))
                        {
                            moverTareas(listaHechas, lista, idCambiar);
                        }
                        else if (idEncontrado(*tareasEnProceso, idCambiar))
                        {
                            moverTareas(tareasEnProceso, lista, idCambiar);
                        } else {
                            continue;
                        }
                        break;
                    case 2:
                        if (idEncontrado(*lista, idCambiar))
                        {
                            moverTareas(lista, tareasEnProceso, idCambiar);
                        }
                        else if (idEncontrado(*listaHechas, idCambiar))
                        {
                            moverTareas(listaHechas, tareasEnProceso, idCambiar);
                        } else {
                            continue;
                        }
                        break;
                    case 3:
                        if (idEncontrado(*lista, idCambiar))
                        {
                            moverTareas(lista, listaHechas, idCambiar);
                        }
                        else if (idEncontrado(*tareasEnProceso, idCambiar))
                        {
                            moverTareas(tareasEnProceso, listaHechas, idCambiar);
                        } else {
                            continue;
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case 2:
                    if (idEncontrado(*lista, idCambiar))
                    {
                        borrarNodoEspecifico(lista, idCambiar);
                    }
                    else if (idEncontrado(*listaHechas, idCambiar))
                    {
                        borrarNodoEspecifico(listaHechas, idCambiar);
                    }
                    else
                    {
                        borrarNodoEspecifico(tareasEnProceso, idCambiar);
                    }

                    break;

                default:
                    break;
                }
            }
            else
            {
                printf("\nID no encontrado\n");
            }

            printf("\n\nQUIERE MODIFICAR OTRA TAREA? (1:si, 0:no): ");
            scanf("%d", &opcionContinuar);
            fflush(stdin);
        }

        printf("\nMODIFICAR TAREAS PENDIENTES\n");
        printf("\n -----------------\n");
        printf("|TAREAS PENDIENTES|");
        printf("\n -----------------");
        mostrarLista(*lista);
        mostrarDatos(*lista);
        printf("\n -----------------\n");
        printf("|TAREAS EN PROCESO|");
        printf("\n -----------------");
        mostrarLista(*tareasEnProceso);
        mostrarDatos(*tareasEnProceso);
        printf("\n -----------------\n");
        printf("|TAREAS REALIZADAS|");
        printf("\n -----------------");
        mostrarLista(*listaHechas);
        mostrarDatos(*listaHechas);

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
        mostrarDatos(*lista);
        break;
    case 6:
        printf("\n -----------------\n");
        printf("|TAREAS REALIZADAS|");
        printf("\n -----------------");
        mostrarLista(*listaHechas);
        mostrarDatos(*listaHechas);
        break;

    default:
        break;
    }
}