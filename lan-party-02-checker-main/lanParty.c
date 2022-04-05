//
// Created by Bogdan on 06.04.2021.
//
#include "exercitiul1.h"
#include "exercitiul2.h"
#include "exercitiul3.h"
#include "exercitiul4.h"
int main(/*int argc, char* argv[]*/) {
   FILE *f = NULL, *g = NULL, *out = NULL;
    //f = fopen(argv[1],"r");
   //g = fopen(argv[2],"r");
  // out = fopen(argv[3],"w");
    f = fopen("C://Users//Bogdan//CLionProjects//PC//SDA//tema_bonus//lan-party-02-checker-main//date//t10//c.in", "r");
   g = fopen("C://Users//Bogdan//CLionProjects//PC//SDA//tema_bonus//lan-party-02-checker-main//date//t10//d.in", "r");
    out = fopen("C://Users//Bogdan//CLionProjects//PC//SDA//tema_bonus//lan-party-02-checker-main//out//2.txt", "w");
    node *head = NULL;
    int n;
    int i, x, ap = 0;
    for (i = 1; i <= 5; i++) {
        fscanf(f, "%d", &x);
        ap = ap + x;
    }
    fscanf(g, "%d", &n);
    head = makeList(g, n);
    if (ap == 2 || ap == 3 ||ap ==4)
    {
        removeN(&head, n);
    }
    Queue *queue = NULL;
    Stack *stackV = NULL;
    Stack *stackP = NULL;
    //printf("aici");
    print(out, head);
    node *lista = NULL;
    if (ap == 3||ap==4 ) {
        coada(head, &queue);
        coada_finala(&queue, stackV, stackP, &lista, out);

    }

    BST*bst = NULL;
   while(lista!=NULL)
    {
//        printf("%s\n",lista->data.nume);
      bst =  insertInBST(bst,lista->data);
      lista = lista->next;
    }
    showtree(bst);

    fclose(f);
    fclose(g);
    fclose(out);
    return 0;
}


