#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node
{
    void * data;
    Node * next;
    Node * prev;
};

struct List
{
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data)
{
    Node * new = (Node *) malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList()
{
    List *lista = (List *) malloc(sizeof(List));
    if (lista == NULL)
    {
        exit(1);
    }

    lista->current = NULL;
    lista->head = NULL;
    lista->tail = NULL;

    return lista;
}

void * firstList(List * list)
{
    if (list->head != NULL && list->head->data != NULL)
    {
        list->current = list->head;
        return list->head->data;
    }

    return NULL;
}

void * nextList(List * list)
{
    if (list->current != NULL && list->current->data != NULL && list->current->next != NULL)
    {
        list->current = list->current->next;
        return list->current->data;
    }

    return NULL;
}

void * lastList(List * list)
{
    while (list->current != NULL && list->current->data != NULL)
    {
        if (list->current->next == NULL)
        {
            return list->current->data;
        }
        
        list->current = list->current->next;
    }
    return NULL;
}

void * prevList(List * list)
{
    if (list->current != NULL && list->current->next == NULL)
    {
        list->current = list->current->prev;
        return list->current->data;
    }

    return NULL;
}

void pushFront(List * list, void * data)
{
    Node *nodoNuevo = createNode(data);
    if (list->head != NULL)
    {
       list->head->prev = nodoNuevo;
       nodoNuevo->next = list->head;
       list->head = nodoNuevo;
    }
    
    if (list->head == NULL)
    {
        list->head = nodoNuevo;
        list->tail = list->head;
    }
}

void pushBack(List * list, void * data)
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data)
{
    Node *nodoNuevo = createNode(data);
    if (list->current->next != NULL)
    {
        list->current->next->prev = nodoNuevo;
        nodoNuevo->next = list->current->next;
    }

    list->current->next = nodoNuevo;
    nodoNuevo->prev = list->current;
    if (nodoNuevo->next == NULL)
    {
        list->tail = nodoNuevo;
    }
}

void * popFront(List * list)
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list)
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list)
{
    if(list->current->prev == NULL)
    {
        list->current->next->prev = NULL;
        list->head = list->current->next;
        return list->current->data;
    }

    if (list->current->next == NULL)
    {
        list->current->prev->next = NULL;
        list->tail = list->current->prev;
        return list->current->data;
    }

    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    return list->current->data;
}

void cleanList(List * list) 
{
    while (list->head != NULL) 
    {
        popFront(list);
    }
}