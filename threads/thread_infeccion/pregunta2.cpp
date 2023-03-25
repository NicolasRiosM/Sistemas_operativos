#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;


float infeccion(){
    srand(time(NULL));
    double a = rand();
    double b = rand();
    float probabilidad = abs(((a-b)/b) - 1);
    cout<<"Probabilidad de contagio "<< probabilidad<<endl;
    return probabilidad;
}

int main(){
    float me = getpid();
    //cout<<me<<endl;

    if(me > 0){
        cout<< "Inicia Proceso: Persona ------"<< endl;
        cout<< "Fulanite nace..."<< endl;
        cout<< "Fulanite come..."<< endl;
        cout<< "Fulanite duerme..."<< endl;
        cout<< "Fulanite crece..."<< endl;
        cout<< "Fulanite celebra el nuevo año 2019..."<< endl;
        cout<<"PANDEMIA!"<<endl;
        cout<<"..."<<endl;

        float probabilidadVirus = infeccion();
        if(probabilidadVirus >= 0.5){
            me = fork();
            wait(nullptr);
        }
        else{
            cout<<"Fulanite sigue su vida."<<endl;
        }
        
        cout<<"\n";
    }
    if(me == 0){
        cout<<"¡Contagio por COVID-19!"<<endl;
        cout<<"En Cuarentena ------"<<endl;
        cout<<"Fulanite se aburre..."<<endl;
        cout<<"Fulanite tiene fiebre..."<<endl;
        cout<<"Fulanite tose..."<<endl;
        cout<<"Fulanite se siente como el @|##@¢!..."<<endl;
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}