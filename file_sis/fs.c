#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


// 


typedef struct node{
    char* name;
    unsigned short int type;
    struct node* next;
    struct node* child;
    char* path;





}node_t;
typedef struct lista{
    node_t* root;
    node_t* current;
}lista_t;








void crearcarpeta(lista_t alist, char* name){
    
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    int carpeta= mkdir(path,0777);
    if (carpeta==-1){
        perror("No se pudo crear la carpeta");
        return;
    }
    if(alist.current->child==NULL){
        node_t child={
            .name = name,
            .type=0,
            .path=path,
            .next=NULL,
            .child=NULL,
        };
        alist.current->child =&child;
    }
}
void moverme(lista_t alist, char* name){
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    while(1){
        if (alist.current->path==path){
            break;
        }else{
            alist.current->next;
           
        }
    }
}

void borrarcarpeta(lista_t alist, char* name){
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    int result= rmdir(path);
    if (result==-1){
        perror("No se pudo eliminar la carpeta");
        return;

    }
    if (alist.root!=NULL){
        node_t child={
            .name = NULL,
            .type=-1,
            .path=NULL,
            .next=NULL,
            .child=NULL,
            

        };
        alist.root=NULL;

    }

}

void crear(lista_t alist, char* name){
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    int result= open(path,0777);
    
    if (result==-1){
        perror("No se pudo crear el archivo");
        return;
    }

    if(alist.current->child==NULL){
        node_t child={
            .name=name,
            .type=0,
            .path=path,
            .next=NULL,
            .child=NULL,
        };
        alist.current->child =&child;
    }
    close(result);

}
void borrar(lista_t alist, char* name){ //revisar esta
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    int result= unlink(path);
    if (result==-1){
        perror("No se pudo eliminar el archivo");
        return;

        
    }
    while(1){ //aqui para abajo puede estar malardo 
        if (alist.current->path==path){
            node_t current={
                .name = NULL,
                .type=-1,
                .path=NULL,
                .next=NULL,
                .child=NULL,
            
            };
           
            break;

        }else{
            if (alist.current->next==NULL){ 
                alist.current=alist.root;
            }else{
                alist.current=alist.current->next;
            }
            
        }
    }

}
void mover(lista_t alist, char* name, char* topath){
    
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    int result=link(path,topath);
    if(result==-1){
        perror("No se puede mover el archivo");
    }else{
          if (alist.current->path==path){
            node_t current={
                .name = NULL,
                .type=-1,
                .path=NULL,
                .next=NULL,
                .child=NULL,
            
            };
        }


    }
}
void archivar(lista_t alist, char* name){
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path,"archivados");
    int result=open(path,0777);
    if (result==-1){
        printf("No se pudo archivar");
    }else{
        mover(alist,name, path);
    }
}
void modificar(lista_t alist, char* name, const char *str){
    char* path;
    path=alist.current->path;
    strcat(path,"/");
    strcat(path, name);
    int result=open(path,0777);
    if (result==-1){
        perror("Error al abrir el archivo");
        return;

    }else{
        write(result, str, strlen(str));
        printf("Se modifico correctamente");
        close(result);
        
    }
}
lista_t lista_start(){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    node_t root={
        .name="root",
        .type=0,
        .child=NULL,
        .next=NULL,
        .path=&cwd[0],
    };
    lista_t lista={
        .root=&root,
        .current=&root,
    };

    return lista;
}
int main(){
    lista_t lista=lista_start();
    printf("%s\n%s\n", lista.root->name, lista.root->path);
    printf("%s\n", lista.current->path);

    
    int i=0;
    char nombreDirectorio[10];
    char nombredir[10];
    char cadena[50];
    while(i==0){
        printf("%s\n%s\n", lista.root->name, lista.root->path);
        printf("%s\n", lista.current->path);
        printf("1.- Crear carpeta en el directorio actual\n");
        printf("2.- Borrar carpeta\n");
        printf("3.- Crear archivo\n");
        printf("4.- Borrar archivo\n");
        printf("5.- Modificar archivo\n");
        printf("6.- Archivar\n");
        printf("7.- Mover archivo\n");
        printf("8.- Acceder a carpeta\n");
        
        printf("0.- salir\n");
        int opcion;
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
                printf("ingrese el nombre de la carpeta: ");
                scanf("%s", nombreDirectorio);
                crearcarpeta(lista, nombreDirectorio); 
                break;
            case 2:
                printf("ingrese el nombre de la carpeta: ");
                scanf("%s", nombreDirectorio);
                borrarcarpeta(lista, nombreDirectorio); 
                break;
            case 3: 
                printf("ingrese el nombre del archivo: ");
                scanf("%s", nombreDirectorio);
                crear(lista, nombreDirectorio); 
                break;
            case 4:
                printf("ingrese el nombre de la carpeta: ");
                scanf("%s", nombreDirectorio);
                borrar(lista, nombreDirectorio); 
                break;
            case 5:
                
                printf("ingrese el nombre del archivo ");
                scanf("%s", nombreDirectorio);
                printf("ingrese lo que desea escribir\n");
                scanf("%s",cadena);
                modificar(lista, nombreDirectorio, cadena); 
                break;
            case 6:
                printf("ingrese el nombre del archivo ");
                scanf("%s", nombreDirectorio);
                archivar(lista,nombreDirectorio);
                break;
            case 7:
                printf("ingrese el nombre del archivo: ");
                scanf("%s", nombreDirectorio);
                printf("ingrese el directorio de destino: ejemplo /home/user/... : \n");
                scanf("%s",nombredir);
                mover(lista, nombreDirectorio,nombredir); 
                break;
            case 8:
                printf("ingrese el nombre de la carpeta: ");
                scanf("%s", nombreDirectorio);
                moverme(lista, nombreDirectorio); 
                break;
            case 9:
                
                break;
            case 0:
                i=1;
                break;
        }
    }
    
   return 0;
    
}