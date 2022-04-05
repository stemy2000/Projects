//
// Created by Bogdan on 13.05.2021.
//

#ifndef CERINTA1_C_EXERCITIUL4_H
#define CERINTA1_C_EXERCITIUL4_H
#include "structuri.h"
#include "exercitiul3.h"
BST* createBalanced(int N, node *head)
{
    team val;
    if (N > 0)
    {
        BST* root = (BST *) malloc(sizeof(BST));
        val = head->data;
        (root->data) = val;
        root->left = createBalanced(N / 2,head->next);
        root->right = createBalanced(N - 1 - N / 2,head->next); // un nod a fost folosit pt radacina
        return root; //si N/2.txt pt subarb. stg.
    } else return NULL;
}
BST* createBSTNode(team data)
{
    BST* node = (BST*)malloc(sizeof(BST));
    node->data = data;
    node->left = node->right = NULL;
    node->parent =  NULL;
    return node;
}
BST* insertInBST(BST* root, team data)
{
    //printf("%d ",*iter);
    if (root == NULL) return createBSTNode(data);
    if (xp(data) < xp(root->data)||(xp(data) == xp(root->data) && strcmp(data.nume,root->data.nume)<0))
    {
        BST *stanga = insertInBST(root->left, data);
        root->left  = stanga;
        stanga->parent = root;
    }
    else if (xp(data)>xp(root->data)||( strcmp(data.nume,root->data.nume)>0 && xp(data)==xp(root->data)))
    {
        BST *dreapta = insertInBST(root->right, data);
        root->right  = dreapta;
        dreapta->parent = root;
    }
    return root;
}
void showtree(BST *root) {
    if (root) {
        showtree(root->right);
        printf("%lf %s",xp(root->data), root->data.nume);
        showtree(root->left);
    }

}
#endif //CERINTA1_C_EXERCITIUL4_H
