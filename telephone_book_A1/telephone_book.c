#include "telephone_book.h"


static size_t str_length(char *str_ptr) {
	size_t length = 0;

	while (str_ptr[length] != '\0') {
		length++;
	}

	length++;

	return length;
}







static size_t num_of_people_in_a_list(list name_of_list) {
	size_t num_of_el = 0;

	while (name_of_list != NULL) {
		num_of_el++;
		name_of_list = name_of_list->next_person;
	}

	return num_of_el;
}







static list divide_list(list name_of_list) {
	if (name_of_list == NULL) {
		return NULL;
	}

	size_t num_of_people = num_of_people_in_a_list(name_of_list);
	person* first_person_in_a_half_of_list = name_of_list->next_person;

	for (size_t i = 0; i < num_of_people / 2 - 1; i++) {
		first_person_in_a_half_of_list = first_person_in_a_half_of_list->next_person;
		name_of_list = name_of_list->next_person;
	}

	name_of_list->next_person = NULL;	
	return first_person_in_a_half_of_list;
}








static list merge_lists(list first_list,
	list second_list,
	int sort_direcrion,
	int comparison_func (person, person)) {

	if (first_list == NULL) {
		return second_list;
	}
	else {
		if (second_list == NULL) {
			return first_list;
		}
	}
	
	list res_list;

	if ((sort_direcrion * comparison_func(*first_list, *second_list)) > 0) {
		res_list = first_list;
		first_list = first_list->next_person;
	}
	else {
		res_list = second_list;
		second_list = second_list->next_person;
	}
	
	person *tmp_person = res_list;

	while (first_list != NULL && second_list != NULL) {
		if ((sort_direcrion * comparison_func(*first_list, *second_list)) > 0) {
			tmp_person->next_person = first_list;
			tmp_person = first_list;
			first_list = first_list->next_person;
		}
		else {
			tmp_person->next_person = second_list;
			tmp_person = second_list;
			second_list = second_list->next_person;
		}
	}

	if (first_list == NULL) {
		tmp_person->next_person = second_list;
	}
	else {
		tmp_person->next_person = first_list;
	}

	return res_list;
}








static int comparison_of_strings(char *first_string, char *second_string) {
	if (first_string == NULL || second_string == NULL) {
		return 0;
	}

	size_t i = 0;

	while (first_string[i] == second_string[i] && first_string[i] != '\0') {
		i++;
	}

	if (first_string[i] > second_string[i]) {
		return 1;
	}
	else {
		if(first_string[i] < second_string[i]) {
			return -1;
		}
	}

	return 0;
}








static int comparison_by_surname(person first_person,person second_person) {
	return comparison_of_strings(first_person.surname, second_person.surname);
}








static int comparison_by_name(person first_person, person second_person) {
	return comparison_of_strings(first_person.name, second_person.name);
}








static int comparison_by_number(person first_person, person second_person) {
	return comparison_of_strings(first_person.number, second_person.number);
}







static int comparison_by_birthday(person first_person, person second_person) {
	return comparison_of_strings(first_person.birthday, second_person.birthday);
}








static list sorting_ (list name_of_list,
	int sort_direction,
	int comparison_func(person, person)) {

	if(name_of_list == NULL ||
		name_of_list->next_person == NULL) {
		return name_of_list;
	}
	else {
		list first_part = sorting_(divide_list(name_of_list),
			sort_direction,
			comparison_func);

		list second_part = sorting_(name_of_list,
			sort_direction,
			comparison_func);

		return merge_lists(first_part,
			second_part,
			sort_direction,
			comparison_func);
	}
}








static void copy_strings(char *input_string, char **output_string) {
	if (input_string == NULL) {
		*output_string = NULL;
		return;
	}

	size_t input_str_length = str_length(input_string);

	*output_string = (char *)malloc(input_str_length * sizeof(char));

	for (size_t i = 0; ((*output_string)[i] = input_string[i]) != '\0'; i++);
	return;
}








static person **find_(list *name_of_list_ptr, char* surname, char* name) {
	while (*name_of_list_ptr != NULL &&
		(comparison_of_strings((*name_of_list_ptr)->surname, surname) ||
			comparison_of_strings((*name_of_list_ptr)->name, name))) {

		name_of_list_ptr = &((*name_of_list_ptr)->next_person);
	}

	return name_of_list_ptr;
}








int add_person(list *name_of_list_ptr,
	char *surname,
	char *name,
	char *number,
	char *birthday) {
	
	if (*(find_(name_of_list_ptr, surname, name)) != NULL ||
		surname == NULL || *surname == '\0' ||
		name == NULL || *name == '\0' ||
		number == NULL || *number == '\0' ||
		birthday == NULL || *birthday == '\0') {
		
		return 0;
	}

	person *new_person = (person *)malloc(sizeof(person));

	copy_strings(surname, &(new_person->surname));
	copy_strings(name, &(new_person->name));
	copy_strings(number, &(new_person->number));
	copy_strings(birthday, &(new_person->birthday));
	new_person->next_person = NULL;

	if (*name_of_list_ptr == NULL) {
		*name_of_list_ptr = new_person;
		return;
	}

	person *tmp_person = *name_of_list_ptr;

	while (tmp_person->next_person != NULL) {
		tmp_person = tmp_person->next_person;
	}

	tmp_person->next_person = new_person;
	return 1;
}








person find(list name_of_list, char *surname, char *name) {
	person *searching_person_ptr = *(find_(&name_of_list, surname, name));

	if(searching_person_ptr == NULL) {

		person err_person;

		err_person.surname = NULL;
		return err_person;
	}

	return *searching_person_ptr;
}








void delete_person(list *name_of_list, char *surname, char *name) {
	person **deleting_person_ptr_ptr = find_(name_of_list, surname, name);
		
	free((*deleting_person_ptr_ptr)->surname);
	free((*deleting_person_ptr_ptr)->name);
	free((*deleting_person_ptr_ptr)->number);
	free((*deleting_person_ptr_ptr)->birthday);
	
	person *tmp_person = *deleting_person_ptr_ptr;

	*deleting_person_ptr_ptr = (*deleting_person_ptr_ptr)->next_person;
	free(tmp_person);
	return;
}








void sort_list (list *list_name, int component, int direction) {
	if (*list_name == NULL ||
		component > 3 ||
		component < 0 ||
		direction > 1 ||
		direction == 0 ||
		direction < -1) {
		
		return;
	}

	list res_list = NULL;

	switch (component) {
	case 0:
		res_list = sorting_(*list_name, direction, comparison_by_surname);
		break;
	case 1:
		res_list = sorting_(*list_name, direction, comparison_by_name);
		break;
	case 2:
		res_list = sorting_(*list_name, direction, comparison_by_number);
		break;
	case 3:
		res_list = sorting_(*list_name, direction, comparison_by_birthday);
		break;
	}

	*list_name = res_list;
	return;
}







void print_person_to_stream(FILE *stream, person person_name) {
	if(person_name.surname == NULL) {
		fprintf_s(stream, "\nThere is no a such person.\n");
		return;
	}

	fprintf_s(stream,
		"\n\nSurname: %s\nName: %s\nNumber: %s\nBirthday: %s\n",
		person_name.surname,
		person_name.name,
		person_name.number,
		person_name.birthday);

	return;
}








void print_person(person person_name) {
	print_person_to_stream(stdout, person_name);
	return;
}








void print_list_to_stream(FILE *stream, list name_of_list) {
	while(name_of_list != NULL) {
		print_person_to_stream(stream, *name_of_list);
		name_of_list = name_of_list->next_person;
	}

	return;
}








void print_list(list name_of_list){
	print_list_to_stream(stdout, name_of_list);
	return;
}








void delete_list (list *name_of_list) {
	while (*name_of_list != NULL) {
		free((*name_of_list)->surname);
		free((*name_of_list)->name);
		free((*name_of_list)->number);
		free((*name_of_list)->birthday);
		
		person *tmp_person_ptr = *name_of_list;

		*name_of_list = (*name_of_list)->next_person;
		free(tmp_person_ptr);
	}

	return;
}








list open_list(FILE* file_ptr) {
	list res_list = NULL;
	char surname[256];
	char name[256];
	char number[256];
	char birthday[256];

	while(!feof(file_ptr)) {
		fscanf_s(file_ptr,
			"\n\nSurname: %s\nName: %s\nNumber: %s\nBirthday: %s\n",
			surname, _countof(surname),
			name, _countof(name),
			number, _countof(number),
			birthday, _countof(birthday));

		add_person(&res_list, surname, name, number, birthday);
	}

	return res_list;
}