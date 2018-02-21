#include "array.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void array_create(struct array *self) {
	self->capacity = 0;
	self->size = 0;
	int *data = calloc(self->capacity, sizeof(int));
	self->data = data;
}

void array_destroy(struct array *self) {
	free(self->data);
}

bool array_equals(const struct array *self, const int *content, size_t size) {
	if(self->size == size){
		for(size_t i=0; i<size; ++i){
			if(self->data[i] != content[i]){
				return false;
			}
		}
		return true;
	}
	return false;
}

void array_add(struct array *self, int value) {
	if(self->capacity==self->size){
		self->capacity +=2;
		int *data = calloc(self->capacity, sizeof(int));
		memcpy(data, self->data, self->size *sizeof(int));
		free(self->data);
		self->data=data;
	}
	self->data[self->size]=value;
	self -> size +=1;
}

void array_insert(struct array *self, int value, size_t index) {
	if(self->capacity==self->size){
		self->capacity +=1;
		int *data = calloc(self->capacity, sizeof(int));
		memcpy(data, self->data, self->size *sizeof(int));
		free(self->data);
		self->data=data;
	}
	for (size_t i = self->size; i > index; --i) {
		self->data[i] = self->data[i - 1];
	}
	self->data[index] = value;
	self->size += 1;
}

void array_remove(struct array *self, size_t index) {
	for (size_t i = index + 1; i < self->size; ++i) {
		self->data[i - 1] = self->data[i];
	}
	self->size -= 1;
}

int *array_get(const struct array *self, size_t index) {
	if(self->size == 0)
		return NULL;
	return &(self->data[index]);
}

bool array_is_empty(const struct array *self) {
	if(self->size ==0)
		return true;
  	return false;
}

size_t array_size(const struct array *self) {
	return self->size;
}

size_t array_search(const struct array *self, int value) {
	size_t i = 0;
	while((i < self->size) && (self->data[i] != value)){
		i++;
	}
	return i;
}

size_t array_search_sorted(const struct array *self, int value){
	return array_binary_search(self, value, 0, self->size);
}

size_t array_binary_search(const struct array *self, int e, size_t bot, size_t top){
	if (bot == top)
		return self->size;
	size_t mid = (bot + top) / 2;
	if (e < self->data[mid])
		return array_binary_search(self, e, bot, mid);
	if (self->data[mid] < e)
		return array_binary_search(self, e, mid + 1, top);
	return mid;
}

void array_import(struct array *self, const int *other, size_t size) {
	if(!array_is_empty(self)){
		size_t i = array_size(self);
		for(size_t j = 0; j<i; j++){
			array_remove(self,j);
		}
	}
	for(int i = 0; i<size; i++){
		array_add(self,other[i]);
	}
}

void array_dump(const struct array *self) {
	for(size_t i = 0; i<self->size; i++){
		printf("%d ", self -> data[i]);
	}
}

bool array_is_sorted(const struct array *self) {
	if(self->size ==0)
		return true;
	for (size_t i = 1; i < self->size; ++i){
		if (self->data[i - 1] > self->data[i]){
			return false;
		}
	}
	return true;
}

void array_swap(struct array *self, size_t i, size_t j) {
	int tmp = self->data[i];
	self->data[i] = self->data[j];
	self->data[j] = tmp;
}

void array_selection_sort(struct array *self) {
	for (size_t i=0; i < self->size-1; ++i) {
		size_t j = i;
		for (size_t k=j+1; k<self->size; ++k) {
			if (self->data[k]<self->data[j]) {
				j=k;
			}
		}
	array_swap(self, i, j);
	}
}

void array_bubble_sort(struct array *self) {
	for (size_t i=0; i<self->size-1; ++i) {
		for (size_t j = self->size-1; j > i; --j) {
			if (self->data[j] < self->data[j-1]) {
				array_swap(self, j, j-1);
			}
		}
	}
}

void array_insertion_sort(struct array *self) {
	for (size_t i=1; i < self->size; ++i) {
		int x=self->data[i];
		size_t j=i;
		while (j > 0 && self->data[j-1] > x) {
			self->data[j] = self->data[j-1];
			j--;
		}
	self->data[j]=x;
	}
}

ssize_t array_partition(struct array *self, ssize_t i, ssize_t j) {
	ssize_t pivot_index = i;
	const int pivot = self->data[pivot_index];
	array_swap(self, pivot_index, j);
	ssize_t l = i;
	for (ssize_t k = i; k < j; ++k) {
		if (self->data[k] < pivot) {
			array_swap(self, k, l);
			l++;
		}
	}
	array_swap(self, l, j);
	return l;
}

void array_quick_sort_partial(struct array *self, ssize_t i, ssize_t j) {
	if (i < j) {
		ssize_t p = array_partition(self, i, j);
		array_quick_sort_partial(self, i, p - 1);
		array_quick_sort_partial(self, p + 1, j);
	}
}

void array_quick_sort(struct array *self) {
	array_quick_sort_partial(self, 0, self->size - 1);
}


void array_heap_sort(struct array *self) {

}

bool array_is_heap(const struct array *self) {

}

void array_heap_add(struct array *self, int value) {

}

int array_heap_top(const struct array *self) {
return 0;
}

void array_heap_remove_top(struct array *self) {

}


