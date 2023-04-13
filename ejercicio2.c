#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion;
int Duracion; // entre 10 – 100
}tarea;

int main(){
    //Desarrollar una interfaz por consola donde se solicite al usuario (es decir el empleado) cuantas tareas debe cargar.
    int cantidadDeTareasACargar;
    printf("=========================================\n");
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantidadDeTareasACargar);
    fflush(stdin);
    printf("=========================================\n");

    //2. Tendrá que generar un arreglo de doble punteros dinámicamente del tipo Tarea con la cantidad de tareas solicitadas en el punto anterior.Recuerde inicializar los arreglos apuntando a NULL.
    tarea **listaDeTareas;
    listaDeTareas = (tarea**)malloc(cantidadDeTareasACargar*sizeof(tarea*));

    for (int i = 0; i < cantidadDeTareasACargar; i++){
        listaDeTareas[i] = NULL;
    }

    //3. Desarrolle una interfaz de consola para cargar las tareas, ingresando su descripción y duración. Recuerde utilizar reserva de memoria dinámica para la carga de la descripción.
    char* buffer;
    buffer = (char*)malloc(100*sizeof(char));
    tarea *tareaIndividual;
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
        printf("Duracion: ");
        scanf("%d", &tareaIndividual->Duracion);
        fflush(stdin);
    }

    // 4. Una vez cargada todas las tareas. Irá listando de a una las tareas y preguntando si se realizó o no la misma. Si la respuesta es Si tiene que “mover” dicha tarea a otro arreglo denominado tareas realizadas que tendrá el mismo tamaño que el anterior. Una vez movida la tarea ese casillero del vector tiene que apuntar a null. Como se muestra en la gráfica a continuación.

    tarea **tareasRealizadas;
    tareasRealizadas = (tarea**)malloc(cantidadDeTareasACargar*sizeof(tarea*));

    // printf("\nLISTADO DE TAREAS PENDIENTES");
    // for (int i = 0; i < cantidadDeTareasACargar; i++){
    //     printf("\n_________________________________________\n");
    //     printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
    //     printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
    //     printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);
    //     printf("¿Realizo esta tarea? (s/n)");
    // }

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
    
    printf("\n\n\nLISTADO DE TAREAS REALIZADAS");
    for (int i = 0; i < cantidadDeTareasACargar; i++){
        if (tareasRealizadas[i] != NULL){
            printf("\n_________________________________________\n");
            printf("TAREA %d \r\n", tareasRealizadas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", tareasRealizadas[i]->TareaID, tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\r\n", tareasRealizadas[i]->Duracion);   
        }
    }

    printf("\n\nLISTADO DE TAREAS PENDIENTES");
    for (int i = 0; i < cantidadDeTareasACargar; i++){
        if (listaDeTareas[i] != NULL){
            printf("\n_________________________________________\n");
            printf("TAREA %d \r\n", listaDeTareas[i]->TareaID);
            printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
            printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);
            printf("¿Realizo esta tarea? (s/n): ");
        }
    }


    return 0;
}