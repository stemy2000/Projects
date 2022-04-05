//
// Created by Bogdan on 23.04.2021.
//

#ifndef CERINTA1_C_STRUCTURI_H
#define CERINTA1_C_STRUCTURI_H
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <limits.h>
#include <stdbool.h>
struct Player
{
    char* firstName;
    char* secondName;
    int points;
};
typedef struct team
{
    int n;
    char* nume;
    struct Player*v;
}team;
typedef struct node
{
    team data;
    struct node *next;
} node;
typedef struct queue_node
{
    team data;
    struct queue_node *next;
} queue_node;
typedef struct queue
{
    queue_node *front, *rear;
    int size;
} Queue;
typedef struct stack_node
{
    team data;
    struct stack_node *next;
} stack_node;
typedef struct stack
{
    stack_node *head;
    int size;
}Stack;
typedef struct binary_search_tree{

    team data;
    struct binary_search_tree *left, *right;
    struct binary_search_tree *parent;

}BST;

#endif //CERINTA1_C_STRUCTURI_H
