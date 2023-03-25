#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

class node{
    
    public:
        pid_t pid;
        node *leftNode, *rightNode;
        bool left, right;

        node(pid_t pid){
            this->pid=pid;
            this->left=false;
            this->right=false;
        }
        void addLeft(node *childNode){
            this->leftNode=childNode;
            this->left=true;
        }
        void addRight(node *childNode){
            this->rightNode=childNode;
            this->right=true;
        }
        pid_t getPid(){
            return this->pid;
        }
        node getLeft(){
            return *(this->leftNode);
        }
        node getRight(){
            return *(this->rightNode);
        }
};

class processTree{
    //private:
    //    node *root;
    //public:
    //    processTree(){
    //        root = NULL;
    //    }
//
    //    void addNode(pid_t pid){
    //        node *newNode = new node(pid);
//
    //        if(!root){
    //            root=newNode;
    //        }
    //    }
    //    node getTree(){
    //        return *root;
    //    }
    //    node addChild(pid_t childPid){
    //        if (!(root->left)){
    //            root->left->pid=childPid;
    //            return *(root->left);
    //        }
    //        else if(!(root->right)){
    //            root->right->pid=childPid;
    //            return *(root->right);
    //        }
    //        else{
    //            cout<<"ERROR!"<<endl;
    //        }
    //        return *root;
    //    }
};

void addNode(node *parentNode, node *childNode){
    bool left=parentNode->left;
    cout<<"Parent node left: "<<left<<endl;
    bool right=parentNode->right;
    cout<<"Parent node right: "<<right<<endl;
    
    if(!left){
        parentNode->addLeft(childNode); //Agrega al padre un nodo hijo izquierdo
        node *left_node=parentNode->leftNode;
        cout<<"Left child: "<<left_node->getPid()<<endl;
        cout<<parentNode->left<<endl;
        cout<<parentNode->right<<endl;
    }
    else if(!right){
        parentNode->addRight(childNode); //Agrega al padre el hijo derecho
        node *right_node=parentNode->rightNode;
        cout<<"Right child: "<<right_node->getPid()<<endl;
        cout<<parentNode->left<<endl;
        cout<<parentNode->right<<endl;
    }
    else{
        cout<<"ERROR\n";
    }
}

int main(void)
{
    pid_t childPid=0, pid=getpid();
    int cant=0;
    cout<<pid<<endl;
    node *parentNode=new node(pid); //crea un nodo padre
    node *newNode=NULL;
    cout<<"Ingrese cantidad de procesos hijos (numero entero mayor a 0): ";
    cin>>cant;
    cout<<"\nParent node: "<<parentNode->getPid()<<endl;

    for(int i=0; i<cant; i++){
        if(!(childPid=fork())){
            childPid=getpid();
            cout<<"Parent PID: "<<parentNode->pid<<endl;

            newNode=new node(childPid); //Crea un nodo hijo
            cout<<"Child node PID:"<<newNode->getPid()<<endl;

            addNode(parentNode, newNode);

            if(parentNode->left && parentNode->right){
                parentNode=newNode;
            }
        }
        else{
            //cout<<"\nEnd father "<<pid<<" and child "<<childPid<<"\n\n";
            wait(NULL);
            execvp("./end", NULL);
        }
        
    }
    
    
    return 0;
}