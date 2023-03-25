//g++ -pthread -o tarea2 tarea2.cpp
//RUN ./tarea2
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

using namespace std;

pthread_cond_t empty = PTHREAD_COND_INITIALIZER, full = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex;
int valuea,valueb,valuec;

#define BUFFER_SIZE (1<<16)
int definevalues(){
    srand(time(NULL));
    while(true){
        #define ncarabineros valuea
        #define mfiscalias valueb
        #define karrestos valuec
        if(valuea>valueb && valueb>valuec){
            break;
        }else{
            valuea=rand()%100;  //para efectos de prueba se limito la cantidad a ser creada
            valueb=rand()%100;  //ya que si dejamos numeros random puede dar cantidades muy grandes
            valuec=rand()%100;   

        }
    }
    return 0;
}

int arrestos, formalizados; //cantidad de arrestados, cantidad de formalizados
int buffer[BUFFER_SIZE];
int head,size,tail;

void *carabineros(void *arg){
    printf("En fiscalia: \n");
    //printf("Arrestos: %d - KArrestos: %d\n", arrestos, karrestos);
    for(arrestos=0; arrestos<karrestos; arrestos++){
       
        pthread_mutex_lock(&mutex);
        
        
        if (size< BUFFER_SIZE){
            //sleep(1);
            
            buffer[tail++] = 1;     //La siguiente posición en el buffer se llena con un arresto (valor 1)
            tail %= BUFFER_SIZE;    
            ++size;
            printf("Reteniendo y amonestando %d\n", arrestos);
            pthread_cond_signal(&empty);
        }else{
            
            printf("No se pueden arrestar mas, centro de deteencion lleno!\n");
            printf("Esperando por que se desocupe una celda...\n");
            pthread_cond_wait(&full, &mutex);
        }
        
        pthread_mutex_unlock(&mutex);
       
    }
    pthread_exit(NULL);

}

    

void *fiscalia(void *arg){
    printf("En fiscalia: \n");
   
    for(formalizados=0; formalizados<karrestos; formalizados++){
        
        pthread_mutex_lock(&mutex);
        
        
        
        if (size>0){
            //sleep(1);
            
            buffer[head] = 0;   //Posicion en el buffer pasa de "arrestado" a "formalizado" (valor 0)
            head %= BUFFER_SIZE;
            --size;
            printf("Formalizando %d\n", formalizados);
            karrestos=karrestos-1;
            pthread_cond_signal(&full);
        }else{
            
            printf("No hay juergueros que formalizar!\n");
            printf("Esperando por giles...\n");
            pthread_cond_wait(&empty, &mutex); 

        }
        
        pthread_mutex_unlock(&mutex);
         
    }
    pthread_exit(NULL);

    
}

    





int main(void)
{
    definevalues();
    

    printf("--- init main -----\n");
   
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    pthread_mutex_init(&mutex,NULL);
    
    pthread_t pid, cid;
    
    for (long int i=0; i<ncarabineros; i++){
       
        pthread_create(&pid, NULL, carabineros, (void*)i);
    }
    
    for (long int j=0; j<mfiscalias; j++){  
        
        pthread_create(&cid, NULL, fiscalia, (void*)j);
    }
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    sem_unlink("empty");
    sem_unlink("full");
    //pthread_exit(NULL);
    return 0;
}