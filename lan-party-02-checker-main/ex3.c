//
// Created by Bogdan on 23.04.2021.
//

#ifndef CERINTA1_C_EXERCITIUL3_H
#define CERINTA1_C_EXERCITIUL3_H
#include "exercitiul2.h"
//coada
void createQueue(Queue **queue)
{
    (*queue) = (Queue*)malloc(sizeof(Queue));
    (*queue)->front = (*queue)->rear = NULL;
    (*queue)->size = 0;
}
queue_node *createQueueNode(team data)
{
    queue_node* temp = (queue_node*)malloc(sizeof(queue_node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}
void en(Queue *queue, team data)
{
    queue_node* newNode = createQueueNode(data);
    if (queue->rear==NULL)
    {
        queue->rear = queue->front = newNode;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
    queue->size++;
}
bool isEmptyQueue(Queue *queue)
{
    return (queue->front==NULL);
}

team de(Queue *queue)
{
    if (isEmptyQueue(queue)) queue->rear = NULL;
    team data = queue->front->data;
    queue->front = queue->front->next;
    queue->size--;

    return data;
}
void deleteQueue(Queue *queue)
{
    queue_node* aux;
    while (!isEmptyQueue(queue))
    {
        aux=queue->front;
        queue->front=queue->front->next;
        free(aux->data.nume);
        int i;
        for(i=0;i<aux->data.n;i++)
        {

            free(aux->data.v[i].firstName);
            free(aux->data.v[i].secondName);
        }
        free(aux->data.v);
        free(aux);
    }
    free(queue);
    queue = NULL;
}
// stiva
stack_node *createStackNode(team data)
{
    // TODO1.2.txt: functie ce atribuie campului data parametru primit
    stack_node* Node = (stack_node*) malloc(sizeof(stack_node));
    Node->data = data;
    Node->next = NULL;
    return Node;
}
void createStack(Stack **stack)
{
    (*stack) = (Stack*)malloc(sizeof(Stack));
    (*stack)->head = NULL;
    (*stack)->size = 0;
}
void deleteStack(Stack *stack)
{

    Stack*copie = NULL;
    while(stack->head!=NULL)
    {
        copie = stack;
        while (copie->head->next != NULL)
        {
            copie->head = copie->head->next;
        }
        free(copie->head->data.nume);
        for(int i=0;i<copie->head->data.n;i++)
        {
            free(copie->head->data.v[i].firstName);
            free(copie->head->data.v[i].secondName);
        }
        free(copie->head->data.v);
        free(copie->head);
    }

    free(stack);
    stack = NULL;
}
void push(Stack **stack, team data)
{
    //TODO1.3: functie ce adauga un nou nod in stiva

    stack_node* stackNode = createStackNode(data);
    stackNode->next = (*stack)->head;
    (*stack)->head = stackNode;
    (*stack)->size++;
}
team pop(Stack *stack)
{
    team data;
    data.v = NULL;
    data.nume = NULL;
    data.n = 0;
    if (stack->head==NULL)
    {
        return data;
    }
    stack_node* temp = stack->head;
    stack->head = stack->head->next;
    team popped = temp->data;
    temp->next = NULL;
    stack->size--;
    return popped;
}
bool isEmptyStack(Stack *stack)
{

    if (stack->head == NULL) {
        return true;
    }
    else
        return false;
}

void coada(node*head,Queue **queue)
{
    createQueue(&(*queue));
    while(head!=NULL)
    {
        en((*queue),head->data);
        head = head->next;
    }
}
double xp(team data)
{
    int i;
    double ma = 0;
    for(i=0;i<data.n;i++)
    {
        ma = ma + data.v[i].points;
    }
    ma = ma/data.n;
    return ma;
}
node *mNode(team data, node *next)
{
    node* head;
    head = (node*)malloc(sizeof(node));
    head->data = data;
    head->next = next;
    return head;
}

void stiva(Queue *queue, Stack **stackV, Stack **stackP,node**head,int size, FILE*f)
{

    createStack(&(*stackV));

    createStack(&(*stackP));
    int i;
    int d;
    while(!isEmptyQueue(queue))
    {
        team data1 = de(queue);
        team data2 = de(queue);
        if(size==8)
        {
            //printf("%lf\n%lf\n",xp(data1),xp(data2));

            if((*head)==NULL)
            {
                (*head) = mNode(data1, NULL);
                (*head) = mNode(data2, (*head));
            }
            else
            {
                (*head) = mNode(data1, (*head));
                (*head) = mNode(data2,(*head));
            }


        }

        char *buff = (char*)malloc(sizeof(char)*(strlen(data1.nume)));
        for(d=0;d<strlen(data1.nume)-1;d++)
            buff[d] = data1.nume[d];
        buff[d] = '\0';
        fprintf(f,"%-32s - %33s",buff,data2.nume);
        free(buff);
        if(xp(data1)>xp(data2))
        {
            for( i =0;i<data1.n;i++)
            {
                data1.v[i].points++;
            }
            push(&(*stackV),data1);
            push(&(*stackP),data2);
        }
        else {
            for(i =0;i<data2.n;i++)
            {
                data2.v[i].points++;
            }
            push(&(*stackV), data2);
            push(&(*stackP), data1);
        }
        //printf("%d\n",size);



    }


}
void afisare(Queue***queue,Stack**stackV,Stack**stackP,int n,node**list,int*c,FILE*f)
{
    int ap = 0,d;
    while(ap!=n)
    {
        fprintf(f,"\n--- ROUND NO:%d\n",*c);
        stiva((**queue),&(*stackV),&(*stackP),list,ap,f);

        deleteQueue((**queue));
        createQueue(&(**queue));
        fprintf(f,"\nWINNERS OF ROUND NO:%d\n",*c);
        ap = 0;
        while(!isEmptyStack(*stackV))
        {
            ap++;

            team data = pop(*stackV);
            char *buff = (char*)malloc(sizeof(char)*(strlen(data.nume)));
            for(d=0;d<strlen(data.nume)-1;d++)
                buff[d] = data.nume[d];
            buff[d] = '\0';
            fprintf(f,"%-33s -  %.2f\n",buff,xp(data));
            free(buff);
            en((**queue),data);

        }

        (*c)++;
    }


}

void coada_finala(Queue **queue, Stack *stackV, Stack *stackP, node**head, FILE*f)
{
    int c = 1;
    (*head )= NULL;
    // printf("aici intra");
    //afisare(&queue,&stackV,&stackP,4,&(*head),&c,f);
    afisare(&queue,&stackV,&stackP,1,&(*head),&c,f);
    /*
    while((*head)!=NULL)
    {
        printf("%lf\n",medie_xp((*head)));
        (*head) = (*head)->next;
    }
     */


}


#endif //CERINTA1_C_EXERCITIUL3_H


