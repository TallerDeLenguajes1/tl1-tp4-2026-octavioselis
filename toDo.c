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
void transferirTareas(Lista *pendientes, Lista *realizadas);
void mostrarTareas(Lista *lista);
Nodo *buscarPorID(Lista *lista, int id);
Nodo *buscarPalabraClave(Lista *lista, char *clave);

int main(){

    srand(time(NULL));

    Lista TareasPendientes,TareasRealizadas;

    TareasPendientes.L = NULL;
    TareasRealizadas.L = NULL;
    TareasPendientes.cantidad=0;
    TareasRealizadas.cantidad=0;

    int pedirOtra=1,opcion;

    int id=1000;

    do{
        cargarTareasPendientes(&TareasPendientes,&id);
        printf("\nSi desea agregar otra tarea, presione '1': ");
        fflush(stdin);
        scanf("%d",&pedirOtra);
    }while(pedirOtra==1);
    
    do{
        transferirTareas(&TareasPendientes,&TareasRealizadas);
        printf("\nSi desea transferir otra tarea, presione '1': ");
        fflush(stdin);
        scanf("%d",&pedirOtra);
    }while(pedirOtra==1);

    printf("\nPresione 'S' si desea ver en una lista las tareas pendientes y realizadas: ");
    char verTareas;
    fflush(stdin);
    scanf("%c", &verTareas);
    if(verTareas == 's' || verTareas == 'S'){
        printf("\n------ Tareas Pendientes ------\n");
        mostrarTareas(&TareasPendientes);
        printf("--------------------------------------\n");
        printf("------ Tareas Realizadas ------\n");
        mostrarTareas(&TareasRealizadas);
        printf("--------------------------------------\n");
    }

    printf("\n--- MENU DE BUSQUEDA ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por Palabra Clave\n");
    printf("Elija una opcion (1 o 2): ");
    scanf("%d", &opcion);

    int idBuscado;
    char claveBuscada[100],*estado;
    switch(opcion) {
        case 1:
            printf("\nIngrese el ID (Debe ser mayor a 1000): ");
            fflush(stdin);
            scanf("%d", &idBuscado);
            Nodo *encontrado = buscarPorID(&TareasPendientes,idBuscado);
            estado="PENDIENTE";
            if(encontrado==NULL){
                encontrado = buscarPorID(&TareasRealizadas,idBuscado);
                estado="REALIZADA";
            }
            if(encontrado!=NULL){
                printf(" -------ID #%d ENCONTRADO -------\n\n", encontrado->T.TareaID);
                    printf("Descripcion: %s\n", encontrado->T.Descripcion);
                    printf("Duracion: %d\n", encontrado->T.Duracion);
                    printf("ID: %d\n", encontrado->T.TareaID);
                    printf("Estado de la tarea: %s\n", estado);
                printf("--------------------------------------\n");
            }
        break;

        case 2:
            printf("\nIngrese la palabra clave: ");
            fflush(stdin);
            scanf("%s", claveBuscada); 
            
            Nodo *encontradoConClave = buscarPalabraClave(&TareasPendientes,claveBuscada);
            estado="PENDIENTE";
            if(encontradoConClave==NULL){
                encontradoConClave = buscarPalabraClave(&TareasRealizadas,claveBuscada);
                estado="REALIZADA";
            }
            if(encontradoConClave!=NULL){
                printf(" -------CLAVE ENCONTRADA -------\n\n", encontradoConClave->T.TareaID);
                    printf("Descripcion: %s\n", encontradoConClave->T.Descripcion);
                    printf("Duracion: %d\n", encontradoConClave->T.Duracion);
                    printf("ID: %d\n", encontradoConClave->T.TareaID);
                    printf("Estado de la tarea: %s\n", estado);
                printf("--------------------------------------\n");
            }
        break;

        default:
            printf("\nOpcion no valida.\n");
        break;
    }



return 0;
}

void cargarTareasPendientes(Lista *lista, int *id){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T.TareaID = *id;
    (*id)++;

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

void transferirTareas(Lista *pendientes, Lista *realizadas){
    if(pendientes->cantidad == 0){
        printf("No hay tareas para transferir a 'REALIZADAS'\n");
    }
    else{
        int idBuscado;
        printf("\nIngrese el ID de la tarea que desea transferir a 'REALIZADAS': ");
        fflush(stdin);
        scanf("%d",&idBuscado);

        Nodo *buscado = pendientes->L;
        Nodo *ant = NULL;

        while(buscado!=NULL && buscado->T.TareaID != idBuscado){
            ant = buscado;
            buscado = buscado->Siguiente;
        }
        if(buscado == NULL){
            printf("ID= %d NO ENCONTRADO\n" , idBuscado);
        }
        else if(ant == NULL){
            pendientes->L = buscado->Siguiente;
        }
        else{
            ant->Siguiente = buscado->Siguiente;
        }
        if(buscado != NULL){
            pendientes->cantidad--;

            buscado->Siguiente = realizadas->L;
            realizadas->L = buscado;
            realizadas->cantidad++;
        }     
    }
}

void mostrarTareas(Lista *lista){
    if(lista->cantidad == 0){
        printf("NO HAY TAREAS PARA MOSTRAR\n");
    }
    else{ 
        Nodo *aux = lista->L;
        for(int i=0;i<lista->cantidad;i++){
            printf("---------- TAREA ID: %d ----------\n", aux->T.TareaID);
            printf("Descripcion: %s\n", aux->T.Descripcion);
            printf("Duracion: %d\n", aux->T.Duracion);
            printf("ID: %d\n", aux->T.TareaID);
            aux = aux->Siguiente;
        }
        if(aux == NULL){
            free(aux);
        }
    }
}

Nodo *buscarPorID(Lista *lista, int id){
    if(id<1000){
        printf("ID NO ENCONTRADO\n");
    }
    else{
        Nodo *buscado = lista->L;
        for(int i = 0; i<lista->cantidad;i++){
            if(id == buscado->T.TareaID){
                return buscado;
            }
            buscado = buscado->Siguiente;
        }
    }
    return NULL;
}
Nodo *buscarPalabraClave(Lista *lista, char *clave){
    Nodo *buscado = lista->L;
    for(int i=0;i<lista->cantidad;i++){
        if(strstr(buscado->T.Descripcion,clave)!=NULL){
            return buscado;
        }
        buscado=buscado->Siguiente;
    }
        return NULL;
}