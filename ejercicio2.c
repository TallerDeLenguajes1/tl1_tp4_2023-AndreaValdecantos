#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion;
int Duracion; // entre 10 – 100
}tarea;

void cargarListaDeTareas(tarea **listaDeTareas, int cantidadDeTareasACargar);
void marcarTareasRealizadas(tarea** listaDeTareas, tarea** tareasRealizadas, int cantidadDeTareasACargar);
void mostrarTareas(tarea** listaDeTareas, int cantidadDeTareas);
void buscarTareaPorID(tarea** listaDeTareas, tarea** tareasRealizadas, int cantidadDeTareas);
void buscarTareaPorPalabraClave(tarea** listaDeTareas, tarea** tareasRealizadas, int cantidadDeTareas);
void consultarTareas(tarea** tareasPendientes, tarea** tareasRealizadas, int cantidadDeTareas);

int main(){
    //Desarrollar una interfaz por consola donde se solicite al usuario (es decir el empleado) cuantas tareas debe cargar.
    int cantidadDeTareasACargar;
    printf("=========================================\n");
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantidadDeTareasACargar);
    fflush(stdin);
    printf("=========================================\n");

    //2. Tendrá que generar un arreglo de doble punteros dinámicamente del tipo Tarea con la cantidad de tareas solicitadas en el punto anterior.Recuerde inicializar los arreglos apuntando a NULL.
    //3. Desarrolle una interfaz de consola para cargar las tareas, ingresando su descripción y duración. Recuerde utilizar reserva de memoria dinámica para la carga de la descripción.
    tarea **listaDeTareas;
    listaDeTareas = (tarea**)malloc(cantidadDeTareasACargar*sizeof(tarea*));
    cargarListaDeTareas(listaDeTareas, cantidadDeTareasACargar);

    // 4. Una vez cargada todas las tareas. Irá listando de a una las tareas y preguntando si se realizó o no la misma. Si la respuesta es Si tiene que “mover” dicha tarea a otro arreglo denominado tareas realizadas que tendrá el mismo tamaño que el anterior. Una vez movida la tarea ese casillero del vector tiene que apuntar a null. Como se muestra en la gráfica a continuación.

    tarea **tareasRealizadas;
    tareasRealizadas = (tarea**)malloc(cantidadDeTareasACargar*sizeof(tarea*));
    marcarTareasRealizadas(listaDeTareas, tareasRealizadas, cantidadDeTareasACargar);
    
    //5. Mostrar por pantalla todas las tareas realizadas y luego listar las tareas pendientes.
    printf("\n\n\nLISTADO DE TAREAS REALIZADAS");
    mostrarTareas(listaDeTareas, cantidadDeTareasACargar);

    printf("\n\nLISTADO DE TAREAS PENDIENTES");
    mostrarTareas(tareasRealizadas, cantidadDeTareasACargar);
    
    //6. Implemente una función de búsqueda de tarea por nro. de id de nombre BuscarTarea. La misma devuelve la tarea solicitada.
    buscarTareaPorID(listaDeTareas, tareasRealizadas, cantidadDeTareasACargar);

    //7. Implemente una función BuscarTarea en donde la misma sea por palabra clave en vez de por Id. (uno le manda una palabra y te tiene que devolver la primera tarea que contenga dicha palabra). Nota: Para realizar este punto, investigue el uso de la función strstr.
    buscarTareaPorPalabraClave(listaDeTareas, tareasRealizadas, cantidadDeTareasACargar);

    // 9. Agregue una interfaz de usuario al programa principal que permita consultar tareas por id y palabra clave y mostrarlas por pantalla.

    consultarTareas(listaDeTareas, tareasRealizadas, cantidadDeTareasACargar);


    return 0;
}

void cargarListaDeTareas(tarea **listaDeTareas, int cantidadDeTareasACargar){
    char* buffer;
    buffer = (char*)malloc(100*sizeof(char));
    tarea *tareaIndividual;
    
    for (int i = 0; i < cantidadDeTareasACargar; i++){
        listaDeTareas[i] = NULL;
    }

    for (int i = 0; i < cantidadDeTareasACargar; i++){
        tareaIndividual = (tarea*)malloc(sizeof(tarea));
        listaDeTareas[i] = tareaIndividual;
        tareaIndividual->TareaID = i+1;
        printf("\n_________________________________________\n");
        printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
        printf("Descripcion: ");
        gets(buffer);
        fflush(stdin);
        tareaIndividual->Descripcion = (char*)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(tareaIndividual->Descripcion, buffer);
        do{
            printf("Duracion: ");
            scanf("%d", &tareaIndividual->Duracion);
            fflush(stdin);
        } while (tareaIndividual->Duracion < 10 || tareaIndividual->Duracion > 100);
    }

    free(buffer);
}

void marcarTareasRealizadas(tarea** listaDeTareas, tarea** tareasRealizadas, int cantidadDeTareasACargar){
    char respuesta;
    printf("\nLISTADO DE TAREAS CARGADAS");
    for (int i = 0; i < cantidadDeTareasACargar; i++){
        printf("\n_________________________________________\n");
        printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
        printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
        printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);
        printf("¿Realizo esta tarea? (s/n): ");
        scanf("%c", &respuesta);
        fflush(stdin);

        tareasRealizadas[i] = NULL;
        if (respuesta == 's'){
            tareasRealizadas[i] = listaDeTareas[i];
            listaDeTareas[i] = NULL;
            printf("La tarea se movio a realizadas");
        } else {
            printf("La tarea sigue pendiente");
        }
    }
}

void mostrarTareas(tarea** listaDeTareas, int cantidadDeTareas){
    for (int i = 0; i < cantidadDeTareas; i++){
        if (listaDeTareas[i] != NULL){
            printf("\n_________________________________________\n");
            printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
            printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);   
        }
    }
}

void buscarTareaPorID(tarea** listaDeTareas, tarea** tareasRealizadas, int cantidadDeTareas){
    printf("\nBUSCAR TAREA POR ID\n");
    int idBuscar;
    printf("ID de tarea a buscar: ");
    scanf("%d", &idBuscar);
    fflush(stdin);

    for (int i = 0; i < cantidadDeTareas; i++){
        if (listaDeTareas[i] != NULL && listaDeTareas[i]->TareaID == idBuscar){
            printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
            printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);
        } else if (tareasRealizadas[i] != NULL && tareasRealizadas[i]->TareaID == idBuscar){
            printf("TAREA %d \r\n", tareasRealizadas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", tareasRealizadas[i]->TareaID, tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\r\n", tareasRealizadas[i]->Duracion);
        }
    }
}

void buscarTareaPorPalabraClave(tarea** listaDeTareas, tarea** tareasRealizadas, int cantidadDeTareas){
    printf("\nBUSCAR TAREA POR PALABRA CLAVE\n");
    char *bufferPalabraClave;
    bufferPalabraClave = (char*)malloc(100*sizeof(char));
    printf("Palabra clave de la tarea a buscar: ");
    gets(bufferPalabraClave);
    fflush(stdin);
    char *palabraClave;
    palabraClave = (char*)malloc((strlen(bufferPalabraClave)+1)*sizeof(char));
    strcpy(palabraClave, bufferPalabraClave);

    for (int i = 0; i < cantidadDeTareas; i++){
        if (listaDeTareas[i] != NULL && strstr(listaDeTareas[i]->Descripcion, palabraClave) != NULL){
            printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
            printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);
        } else if (tareasRealizadas[i] != NULL && strstr(tareasRealizadas[i]->Descripcion, palabraClave) != NULL){
            printf("TAREA %d \r\n", tareasRealizadas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", tareasRealizadas[i]->TareaID, tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\r\n", tareasRealizadas[i]->Duracion);
        }
    }
}

void consultarTareas(tarea** tareasPendientes, tarea** tareasRealizadas, int cantidadDeTareas){
    int opcion;
    printf("\n:::::::::::::::::::::::::::::::::::\nElija una opcion (para salir presione 0)\n\t1.Buscar tarea por ID\n\t2.Buscar tarea por palabra clave\n\n");

    printf("Opcion: ");
    scanf("%d", &opcion);
    fflush(stdin);
    while (opcion != 0){
        if (opcion == 1){
            buscarTareaPorID(tareasPendientes, tareasRealizadas, cantidadDeTareas);
        } else {
            buscarTareaPorPalabraClave(tareasPendientes, tareasRealizadas, cantidadDeTareas);
        }

        printf("\nOpcion: ");
        scanf("%d", &opcion);
        fflush(stdin);
    }
}