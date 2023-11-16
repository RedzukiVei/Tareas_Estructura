#include<stdio.h>
#include<stdlib.h>

typedef struct Binomial_Tree{
    int valor;
    int k;
    struct Binomial_Tree *hijo;
    struct Binomial_Tree *padre;
    struct Binomial_Tree *bro;

} nodo_Bt;

typedef struct _heap_{
    nodo_Bt *head;
}heap_t;

nodo_Bt *init_nodo(int valor){
    nodo_Bt *nodo = malloc(sizeof(nodo_Bt));
    nodo->valor = valor;
    nodo->k=0;
    nodo->hijo = 0;
    nodo->padre = 0;
    nodo ->bro = 0;
    return nodo;
}


heap_t *heap_ini(){
    heap_t *heap = malloc(sizeof(heap_t));
    heap->head=NULL;
    return heap;

}

void insertar(heap_t *heap, int valor){

    nodo_Bt *nuevo_nodo = init_nodo(valor);

    if (heap->head == NULL || nuevo_nodo->k < heap->head->k){
        nuevo_nodo->bro = heap->head;
        heap->head = nuevo_nodo;
    }
    else{
    nuevo_nodo->bro = heap->head->bro;
    heap->head->bro = nuevo_nodo;
    }
}
void visualizar(heap_t *heap){
    nodo_Bt *actual = heap->head;

    while (actual != NULL) {
        printf("%d ", actual->valor);
        actual = actual->bro;
        }
    printf("\n");
}

int main(){
    heap_t *heapp= heap_ini(); 
    nodo_Bt *nodo_ini = init_nodo(13);
    printf("valor del nodo es %d",nodo_ini->valor);

    insertar(heapp, 8);
    insertar(heapp, 5);
    insertar(heapp, 12);

    visualizar(heapp);
    
    return 0;

}