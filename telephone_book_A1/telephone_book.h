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


typedef person list;


list create_list();

person *finde(list name_of_list, char *surname, char *name);

void add_person(list name_of_list,
	char* surname,
	char* name,
	char* number,
	char* birthday);

void delete_person(char *surname, char *name);

void sort_list(list list_name, int component, int direction);

void save_list(list list_name);

list open_list(FILE *file_ptr);