//
// Created by Bogdan on 23.04.2021.
//

#ifndef CERINTA1_C_EXERCITIUL1_H
#define CERINTA1_C_EXERCITIUL1_H
#include "structuri.h"
// cerinta 1
node *makeNode(int numar,char*nume,int*points,char*first[],char*second[], node *next)
{
    //TODO1.1: primul pas in implementarea cerintei 1
    node* head;
    head = (node*)malloc(sizeof(node));
    head->data.n = numar;
    head->data.nume = (char*)malloc(sizeof(char)*(strlen(nume)+1));
    strcpy(head->data.nume,nume);
    head->data.v = (struct Player*)malloc(sizeof(struct Player)*numar);
    for(int i=0;i<numar;i++)
    {
        head->data.v[i].points = points[i];
        head->data.v[i].firstName = (char*) malloc(sizeof(char) * (strlen(first[i]) + 1));
        strcpy(head->data.v[i].firstName, first[i]);
        head->data.v[i].secondName = (char *) malloc(sizeof(char) * (strlen(second[i]) + 1));
        strcpy(head->data.v[i].secondName, second[i]);
    }
    head->next = next;
    return head;
}
node *makeList(FILE *file,int n)
{
    //TODO1.2.txt: al doilea pas in implementarea cerintei 1â
    int points[50];
    char**first;
    char**second;
    team aux;
    char nume[50];
    int  numar;
    node *head=NULL;
    int i;
    int ap = 0;

    if(fscanf(file,"%d ",&numar)!=EOF && ap!=n)
    {
        ap++;
        fflush(stdin);
        fgets(nume,50,file);
        first = (char**)malloc(sizeof(char*)*numar);
        second = (char**)malloc(sizeof(char*)*numar);
        for( i=0;i<numar;i++)
        {
            first[i] = (char*)malloc(sizeof(char)*50);
            second[i] = (char*)malloc(sizeof(char)*50);
            fflush(stdin);
            fscanf(file,"%s ",first[i]);
            fflush(stdin);
            fscanf(file,"%s ",second[i]);
            fscanf(file,"%d ",&points[i]);

        }
        head = makeNode(numar,nume,points,first,second,NULL);
        node *temp;
        aux.v = (struct Player*) malloc(sizeof(struct Player) * numar);
        for( i=0;i<numar;i++)
        {
            aux.n = head->data.n;
            aux.v[i].firstName = (char*)malloc(sizeof(char)*(strlen(first[i])+1));
            strcpy(aux.v[i].firstName, first[i]);
            aux.v[i].secondName = (char *) malloc(sizeof(char) * (strlen(second[i]) + 1));
            strcpy(aux.v[i].secondName, second[i]);
        }
        fflush(stdin);
        while (fscanf(file, "%d ",&numar) != EOF && ap!=n)
        {
            fflush(stdin);
            fgets(nume,50,file);
            for( i=0;i<numar;i++)
            {
                fflush(stdin);
                fscanf(file,"%s ",first[i]);
                fflush(stdin);
                fscanf(file,"%s ",second[i]);
                fscanf(file,"%d ",&points[i]);
            }
            temp = makeNode(numar,nume,points,first,second, head);
            head = temp;
            for(i=0;i<numar;i++) {
                aux.v[i].points = points[i];
                aux.v[i].points = head->data.v[i].points;
                aux.v[i].firstName = (char *) malloc(sizeof(char) * (strlen(first[i]) + 1));
                strcpy(aux.v[i].firstName, first[i]);
                aux.v[i].secondName = (char *) malloc(sizeof(char) * (strlen(second[i]) + 1));
                strcpy(aux.v[i].secondName, second[i]);
            }
            ap++;
        }
    }
    return head;
}
void print(FILE*f, node *head)
{


    while(head!=NULL)
    {
        fprintf(f,"%s",head->data.nume);

        head=head->next;
    }
}

#endif //CERINTA1_C_EXERCITIUL1_H
