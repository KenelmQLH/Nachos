extern "C" {
#include <assert.h>
#include <cstdio>
#define ASSERT(expression)  assert(expression)
}

#include "copyright.h"
#include "dllist.h"
//const int NULL = 0;

DllElement::DllElement(void *itemPtr, int sortKey){
    item = itemPtr;
    key = sortKey;
    prev = NULL; //NULL
    next= NULL;
}


Dllist::Dllist() {
    first = last = NULL;
}


Dllist::~Dllist() {
    int *x;
    while (!isEmpty())
	   Remove(x);	 // delete all the list elements
}


void Dllist::Prepend(void *item) {

    DllElement *element = new DllElement(item,0);

    if (isEmpty()) {		// list is empty
        first = element;
        last = element;
    } else {			// else put it before first
        first->prev = element;
        element->next = first;
        element->key = first->key -1;
        first = element;
    }
}
void Dllist::Append(void *item) {
    DllElement *element = new DllElement(item,0);

    if (isEmpty()) {        // list is empty
        first = element;
        last = element;
    } else {            // else put it before first
        last->next = element;
        element->prev = last;
        element->key = last->key + 1;
        last = element;
    }
}
//从 表头 删除， 记录 优先键
void* Dllist::Remove(int *keyPtr){
    DllElement* element = first;
    
    ASSERT(!isEmpty());//isEmpty()时，终止程序。

    void* item = element->item;

    *keyPtr = element->key;

    //printf("(%d,%d)\n", *(int *)item, *keyPtr);
    if (first == last) {    // list had one item, now has none
        first = NULL;
        last = NULL;
    } else {
        //printf("[%d]]\n", first->key);
        first = element->next;
        //printf("[[%d]\n", first->key);
        first->prev = NULL;
    }

    delete element;     // deallocate list element -- no longer needed
    return item;
} 

void Dllist::SortedInsert(void *item, int sortKey){
    
    DllElement *element = new DllElement(item,sortKey);
    //printf("%d,%d|",*(int *)item,sortKey);
    
    if(isEmpty()){    //list has no element
        first = element;
        last = element;
        return;
    }

    if(first->key > element->key){
        element->next = first;
        first->prev = element;
        first = element;
        return;
    }

    DllElement* p = first->next;
    while(p){
        if(p->key >= sortKey){
            DllElement* q = p->prev;
            
            element->next = p;
            p->prev = element;
            
            q->next = element;
            element->prev = q;
            return;
        }
        p=p->next;
    }
    //若p = NULL
    last->next= element;
    element->prev = last;
    last = element;
    return ;

}    //按 优先键 插入

void Dllist::SortedRemove(int sortKey){
    DllElement* p = first;
    int isfind = 0;
    while(p){
        if(p->key == sortKey){
            if (first == last) {    // list had one item, now has none
                first = NULL;
                last = NULL;
            }else{
                DllElement* p1 = p->prev;
                DllElement* p2 = p->next;
                p1->next = p2;
                p2->prev = p1;
            }
            delete p;
            isfind = 1;
        }
        p=p->next;
    }
    //没有找到 对应优先键 的元素。
    ASSERT(isfind); //false时，终止程序。
    return;

}        // 按 优先键 删除

void Dllist::ShowAll(){
    DllElement* p = first;
    printf("Show All: ");
    while(p){
        printf("(%d,%d) ", *((int *)p->item), p->key);
        p=p->next;
    }
    printf("\n");
    return ;
}


bool Dllist::isEmpty() {
    return (first == NULL);
}
