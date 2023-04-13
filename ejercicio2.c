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
    printf("Ingrese la cantidad de tareas a cargar: \n");
    scanf("%d", &cantidadDeTareasACargar);

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
        printf("Descripcion: ");
        gets(buffer);
        tareaIndividual->Descripcion = (char*)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(tareaIndividual->Descripcion, buffer);
        printf("Duracion: ");
        scanf("%d", tareaIndividual->Duracion);
    }

    for (int i = 0; i < cantidadDeTareasACargar; i++){
        printf("ID de tarea: %d \r\n", listaDeTareas[i]->TareaID);
        printf("Descripcion de tarea %d: %s \r\n", listaDeTareas[i]->TareaID, listaDeTareas[i]->Descripcion);
        printf("Duracion: %d\r\n", listaDeTareas[i]->Duracion);
    }

    return 0;
}