#pragma once


#include <stdio.h>
#include <stdlib.h>


typedef struct person_ {
	struct person_ *next_person;
	char *surname;
	char *name;
	char *number;
	char *birthday;
} person;


typedef person *list;


int add_person(list *name_of_list,											//	Returns 0, if inputing data is incorrect or that person has alredy added.
	char *surname,															//	Returns 1, if inputing person has successfully added.
	char *name,
	char *number,
	char *birthday);

person find(list name_of_list, char *surname, char *name);

void delete_person(list *name_of_list, char *surname, char *name);

void sort_list(list *list_name, int component, int direction);				// If component is 0 list will be sorted by surname, if 1 by name, if 2 by number, if 3 by birthday.
																			// If direction is 1 list will be sorted in ascending order, if -1 in descending order.
																			// If something is incorrect does nothing.

void print_person_to_stream(FILE* stream, person person_name);

void print_person(person person_name);

void print_list_to_stream(FILE* stream, list name_of_list);
 
void print_list(list list_name);

void delete_list(list *list_name);

list open_list(FILE *file_ptr);