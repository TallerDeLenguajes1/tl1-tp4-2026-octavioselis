#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;
    int Duracion; // entre 10 – 100  
} Tarea;  

typedef struct Nodo{ 
    Tarea T;  
    struct Nodo *Siguiente;  
} Nodo;

typedef struct Lista{
    struct Nodo* L;
    int cantidad;
}Lista;

void cargarTareasPendientes(Lista *lista, int *id);

int main(){

    srand(time(NULL));

    Lista TareasPendientes,TareasRealizadas;

    TareasPendientes.L = NULL;
    TareasRealizadas.L = NULL;
    TareasPendientes.cantidad=0;
    TareasRealizadas.cantidad=0;

    int pedirOtra=1;

    int id=1000;

    do{
        cargarTareasPendientes(&TareasPendientes,&id);
        printf("\nSi desea agregar otra tarea, presione '1': ");
        fflush(stdin);
        scanf("%d",&pedirOtra);
    }while(pedirOtra==1);
    


return 0;
}

void cargarTareasPendientes(Lista *lista, int *id){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T.TareaID = *id;
    *id++;

    char buff[100];
    printf("Ingrese la descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
    
    nuevoNodo->T.Descripcion = (char*)malloc((strlen(buff)+1)*(sizeof(char)));
    strcpy(nuevoNodo->T.Descripcion,buff);
    nuevoNodo->T.Duracion = rand() % 91 + 10;

    nuevoNodo->Siguiente = lista->L;
    lista->L=nuevoNodo;
    lista->cantidad++;
}