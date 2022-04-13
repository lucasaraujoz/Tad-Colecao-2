#ifndef _COLECTION_H_
#define _COLECTION_H_
typedef struct _colection Colection;
Colection *colCreate(int max_items);
int colDestroy(Colection *c);
int colInsert(Colection *c, void *item);
void *colGetFirst(Colection *c);
void *colGetNext(Colection *c);
void *colQuery(Colection *c, void *key, int(*cmp)(void *, void *));
void *colRemove(Colection *c, void *key, int(*cmp)(void *, void *));
void colClear(Colection *c);

#endif