#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
#include <time.h>
#include <vector>
using namespace std;

int *crearRegiones(void){
    int n,p,x,suma=0,l;
    
    static int numps5[16], numps[16];
    int fd[2];
    int readbuffer[90]; 
    pipe(fd);
    int i=0, num=0;
    srand(time(NULL));
    while(i<17){ //se crean las 16 regiones,se pasa el arreglo numps5 por las pipes
        if(!fork()){
            i++;
            if (i!=17 && i!=0){
                printf("region: %d\n",i);
            }
            
            //printf("Padre: %d | Hijo: %d\n",getppid(),getpid());
            num=rand()%1000;
            //printf("%d\n",num);
            
            close(fd[1]);
            write(fd[0], &num,sizeof(num));
            
            //printf("valor enviado %d\n",num);
            
        }else{//proceso centralizado (el padremaximo xd)7
            //int num=0;
            
            close(fd[0]);
           
            p=read(fd[1],&num,sizeof(num));
            
            if (i!=0){
                printf("valor recibido %d: %d\n", i, num);
            }
            
            
            //guardar en numps5
            
            
            wait(NULL);
            execv("./end", NULL);
            exit(0);
            //break;
        }
        suma+=num;
        printf("Suma acumulada: %d\n", suma);
        
    }
    
    return numps;//retornar sumatoria de numps5 owo
}   
int main(int argc, char *argv[]){
    int x;
    int *puntoarr=crearRegiones();
    
    //for (int i=0; i<16; i++){
    //    cout<< *(puntoarr+i)<< endl;
    //}
    //printf("esta malo esto XD Total PS5 vendidas en el pais: %d\n",crearRegiones());

    









    return 0;
}