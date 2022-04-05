//
// Created by Bogdan on 23.04.2021.
//

#ifndef CERINTA1_C_EXERCITIUL2_H
#define CERINTA1_C_EXERCITIUL2_H
#include "structuri.h"
double medie_xp(node*head)
{
    int i;
    double ma = 0;
    for(i=0;i<head->data.n;i++)
    {
        ma = ma + head->data.v[i].points;
    }
    ma = ma/head->data.n;
    return ma;
}
node*minimum(node*head)
{

    double m = medie_xp(head);
    node*copie = head;
    while( copie!=NULL)
    {
        if(medie_xp(copie)<m)
        {
            m = medie_xp(copie);
            head = copie;
        }
        copie = copie->next;
    }

    return head;

}
int egalitate(node*nod1,node*nod2)
{
    int i;
    if(strcmp(nod1->data.nume,nod2->data.nume)==0 && nod1->data.n == nod2->data.n)
    {
        for(i=0;i<nod1->data.n;i++)
        {
            if(strcmp(nod1->data.v[i].firstName,nod2->data.v[i].firstName)==0 && strcmp(nod1->data.v[i].secondName,nod2->data.v[i].secondName)==0 && nod1->data.v[i].points == nod2->data.v[i].points)
                return 1;
        }
    }
    return 0;
}
void stergere(node**head)
{
    int i;
    for(i=0;i<(*head)->data.n;i++) {
        free((*head)->data.v[i].firstName);
        free((*head)->data.v[i].secondName);
    }
    free((*head)->data.v);
    free((*head)->data.nume);
    free((*head));
    (*head) = NULL;

}
int putere(int n)
{
    int p=0;
    int c = 2;
    int i =2;
    while(p<=n)
    {
        p = c*i;
        c = c*i;
    }
    return p/2;
}

void stergere_nod(node**head,node*val) {
    if (*head == NULL) return;
    node *headcopy = *head;
    node *aux = *head;
    if (egalitate(headcopy, val) == 1)
    {
        (*head) = (*head)->next;
        stergere(&headcopy);
        return;
    }

    while (headcopy != NULL) {
        if (egalitate(headcopy, val) != 1) {
            aux = headcopy;
            headcopy = headcopy->next;
        }
        else
        {
            aux->next = headcopy->next;
            stergere(&headcopy);
            return;
        }

    }
}
void removeN(node**list,int n) {
    int count = 0;
    int i = n - putere(n);
    node *copie = (*list);
    if (n == i) return;
    while (count < i) {
        *list = copie;
        node *m = minimum(*list);
        stergere_nod(&copie, m);
        count++;
    }

}
#endif //CERINTA1_C_EXERCITIUL2_H
