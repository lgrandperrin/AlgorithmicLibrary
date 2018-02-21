#include "list.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>

struct list_node {
  int value;
  struct list_node *next;
  // struct list_node *prev;
};

void list_create(struct list *self) {
	assert(self);
	self->first=NULL;
}

void list_destroy(struct list *self) {
	while(!list_is_empty(self)){
		struct list_node *element = self -> first;
		self -> first = element -> next;
		free(element);
	}
}

bool list_equals(const struct list *self, const int *data, size_t size) {
	struct list_node *tmp = self->first;
	if(list_size(self) == size){
		for(size_t i=0; i<size; ++i){
			if(tmp->value != data[i]){
				return false;
			}
		tmp = tmp ->next;
		}
		return true;
	}
	return false;
}

void list_add_back(struct list *self, int value) {
	struct list_node *element = malloc(sizeof(*element));
	if(element == NULL)
		return;
	element -> value = value;
	element -> next = NULL;
	if(list_is_empty(self)==1)
		self ->first = element;
	else{
		struct list_node *tmp = self->first;
		while(tmp->next != NULL)
			tmp = tmp -> next;
		tmp->next = element;
	}
}

void list_add_front(struct list *self, int value) {
  	struct list_node *element = malloc(sizeof(struct list_node));
	if(element == NULL)
		return;
	element -> value = value;
	element -> next = self -> first;
	self -> first = element;
}

void list_insert(struct list *self, int value, size_t index) {
	struct list_node *element = malloc(sizeof(*element));
	element -> value = value;
	struct list_node *cur_element = self->first;
	struct list_node **prev_element = &self->first;
	
	int i=0;

	while(cur_element != NULL && i < index){
		prev_element = &cur_element->next;
		cur_element = cur_element ->next;
		++i;
	}

	element->next = cur_element;
	*prev_element = element;
}

void list_remove(struct list *self, size_t index) {
	struct list_node *cur_element = NULL;
	struct list_node *prev_element = NULL;
	int i =0;
	if(self->first->next != NULL && i != index){
		prev_element = self->first;
		cur_element = prev_element->next;
		++i;
		while(cur_element != NULL && i < index){
			prev_element = cur_element;
			cur_element = cur_element ->next;
			++i;
		}
		if(cur_element != NULL){
			prev_element -> next = cur_element->next;
			free(cur_element);
		}
	}
	else{
		if(self->first != NULL){
			cur_element = self->first;
			cur_element = cur_element ->next;
			free(self->first);
			self->first = cur_element;
		}
	}
}

int *list_get(const struct list *self, size_t index) {
	struct list_node *ptr;
	ptr = self -> first;
	for(size_t i = 0; i < index; ++i){
		ptr = ptr -> next;
	}
	  return &ptr -> value;
}

bool list_is_empty(const struct list *self) {
	assert(self);
	return (self -> first == NULL);
}

size_t list_size(const struct list *self) {
	if(self->first == NULL)
		return 0;
	struct list_node *ptr = self ->first;
	size_t i = 1;
	while(ptr->next != NULL){
		ptr = ptr -> next;
		++i;
	}
	return i;
}

size_t list_search(const struct list *self, int value) {
	struct list_node *ptr = self->first;
	size_t i = 0;
	while((ptr -> value != value) && (ptr -> next != NULL)){
		ptr = ptr -> next;
		++i;
	}
	if(ptr->value == value)
		return i;
	else return i+1;
}

void list_import(struct list *self, const int *other, size_t size) {
	while(!list_is_empty(self)){
		list_remove(self,0);
	}
	for(size_t i=0; i<size;++i){
		list_insert(self, other[i], i);
	}
}

void list_dump(const struct list *self) {
	struct list_node *tmp = self->first;
	while(tmp != NULL){
		printf("%d ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("---");
}



bool list_is_sorted(const struct list *self) {
	if (self->first == NULL)
		return true;
	struct list_node *ptr1 = self ->first;
	struct list_node *ptr2 = self ->first->next;
 	for(size_t i = 1; i < list_size(self); i++){
		if(ptr1 -> value > ptr2->value)
			return false;
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	return true;
}


void list_merge_sort(struct list *self) {

}
