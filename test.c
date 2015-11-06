#include <stdio.h>
#include <stdlib.h>

struct alpha_list {
    char c;
    struct alpha_list *next;
};

void append(struct alpha_list *old_list, struct alpha_list *new_element);
void print_all(struct alpha_list *old_list);

int main(){
    printf("success = %i\n",EXIT_SUCCESS);
    exit(1);
//    exit(1);
//    struct alpha_list *x = malloc(sizeof(struct alpha_list *));
//    struct alpha_list *y = malloc(sizeof(struct alpha_list *));
//    struct alpha_list *z = malloc(sizeof(struct alpha_list *));
//    x->c = 'a';
//    x->next = y;
//    y->c = 'b';
//    y->next = z;
//    z->c = 'c';
//    z->next = 0;
//
//    struct alpha_list *w = malloc(sizeof(struct alpha_list *));
//    w->c = 'd';
//    append(x, w);
//    struct alpha_list *u = malloc(sizeof(struct alpha_list *));
//    append(x, u);
//    u->c = 'e';
//    print_all(x);
}

void append(struct alpha_list *old_list, struct alpha_list *new_element){
    if (old_list->next!=0){
        append(old_list->next, new_element);
    } else {
        old_list->next = new_element;
        new_element->next = 0;
        return;
    }
}

void print_all(struct alpha_list *old_list){
    printf("character = %c\n",old_list->c);
    if (old_list->next==0){
        return;
    } else {
        print_all(old_list->next);
    }
}
