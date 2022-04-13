#include "colection.h"
#include <stdlib.h>
#include <stdbool.h>

struct _colection
{
    int size;
    int capacity;
    int cur;
    void **item; // void item[0] = {e101, e102}
};

Colection *colCreate(int n)
{
    Colection *c;
    if (n > 0)
    {
        c = (Colection *)malloc(sizeof(Colection));
        if (c != NULL)
        {
            c->item = (void **)malloc(sizeof(void *) * n); //alocação do vetor void*
            if (c->item != NULL)
            {
                c->size = 0;
                c->capacity = n;
                return c;
            }
            free(c); //caso n conseguisse alcoar
        }
    }
    return NULL;
}

int colDestroy(Colection *c)
{
    if (c != NULL)
    {
        if (c->size == 0)
        {
            free(c->item); //limpa o vetor
            free(c);
            return true;
        }
    }
    return false;
}

int colInsert(Colection *c, void *item)
{
    if (c != NULL)
    {
        if (c->size < c->capacity)
        {
            c->item[c->size] = item; //item[0] = item, item[1] = item
            c->size++;
            return true;
        }
    }
    return false;
}

void *colGetFirst(Colection *c)
{
    if (c != NULL)
    {
        if (c->size > 0)
        {
            c->cur = 0;
            return c->item[c->cur];
        }
        return NULL;
    }
    return NULL;
}

void *colGetNext(Colection *c)
{
    if (c != NULL)
    {
        c->cur++;
        if (c->cur < c->size)
        {
            return c->item[c->cur];
        }
    }
    return NULL;
}

void *colQuery(Colection *c, void *key, int (*cmp)(void *, void *))
{
    void *data;
    int i, stat;
    if (c != NULL)
    {
        if (c->size > 0) //se tiver vazio nem procura
        {
            i = 0;
            stat = cmp(key, c->item[i]); //retorna true
            //caso key == ao item i da coleção
            while (i < c->size && stat != true)
            {
                //incrementa até ser true, porem se n for
                //passa direto e retorna null
                i++;
                stat = cmp(key, c->item[i]);
            }
            if (stat == true)
            {
                data = c->item[i];
                return data; //retorn se encontrar o item
            }
        }
    }
    return NULL;
}

void *colRemove(Colection *c, void *key, int (*cmp)(void *, void *))
{
    int i, j, stat;
    void *data;
    if (c != NULL)
    {
        if (c->size > 0)
        {
            i = 0;
            stat = cmp(key, c->item[i]);
            while (i < c->size && stat != true)
            {
                i++;
                stat = cmp(key, c->item[i]);
            }
            if (stat == true)
            {
                data = c->item[i];
                for (j = i; j < c->size; j++)
                {
                    c->item[j] = c->item[j + 1];
                }
                c->size--;
                return data;
            }
        }
        return NULL;
    }
}

void colClear(Colection *c)
{
    if (c != NULL)
    {
        if (c->size > 0)
        {
            free(c->item);
            c->size = 0;
        }
    }
}