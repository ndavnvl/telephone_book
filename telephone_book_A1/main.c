#include <stdio.h>
#include "telephone_book.h"
#include "inputing.h"


int main() {
	printf("This program create telephone book.\n");

	while(1) {
		printf("\n0 - exit\n1 - create new phonebook\n2 - open phonebook\n");;

		int main_menu_variants;
		list new_list = NULL;

		scaning_int_with_limits(&main_menu_variants, 0, 2);

		if (main_menu_variants == 0) {
			break;
		}
		else {
			if (main_menu_variants == 2) {
				printf("\nInput name of a file with a phonebook. It must be less than 255 symbols.\n");
				
				char name_of_file[256];
				FILE *file_ptr;

				scanf_s("%s", name_of_file, _countof(name_of_file));
				clean_stdin();
				
				if(!fopen_s(&file_ptr, name_of_file, "r") && file_ptr != NULL) {
					new_list = open_list(file_ptr);
					fclose(file_ptr);
				}
				else {
					printf("\nFile is not opened, error code: %d\n", errno);
				}
			}
		}

		while (1) {
			printf("\n\n\n0 - add person\n1 - delete person\n2 - sort phonebook\n3 - find person\n4 - print phonebook\n5 - save phonebook and go back\n6 - go back without saving\n");

			int mode;

			scaning_int_with_limits(&mode, 0, 6);

			switch (mode) {
			case 0:
				printf("\nInput a surname, a name, a number, a birthday through the gap. Each of them must be less than 255 symbols.\n");

				char surname[256];
				char name[256];
				char number[256];
				char birthday[256];

				scanf_s("%s %s %s %s",
					surname, _countof(surname),
					name, _countof(name),
					number, _countof(number),
					birthday, _countof(birthday));
				
				add_person(&new_list, surname, name, number, birthday);
				clean_stdin();
				break;

			case 1:
				printf("\nInput a surname, a name through the gap. Each of them must be less than 255 symbols.\n");

				char del_surname[256];
				char del_name[256];

				scanf_s("%s %s",
					surname, _countof(surname),
					name, _countof(name));
				clean_stdin();
				delete_person(&new_list, surname, name);
				break;

			case 2:
				printf("\n0 - sort by surname\n1 - sort by name\n2 - sort by number\n3 - sort by birthday\n");

				int sort_mode;

				scaning_int_with_limits(&sort_mode, 0, 3);
				printf("\n0 - sort in ascending order\n1 - in descending order\n");

				int sort_direction;

				scaning_int_with_limits(&sort_direction, 0, 1);
				sort_list(&new_list, sort_mode, -1 + 2 * sort_direction);
				break;

			case 3:
				printf("\nInput a surname, a name through the gap. Each of them must be less than 255 symbols.\n");

				char searching_surname[256];
				char searching_name[256];
				
				scanf_s("%s %s",
					searching_surname, _countof(searching_surname),
					searching_name, _countof(searching_name));

				clean_stdin();
				print_person(find(new_list, searching_surname, searching_name));
				break;

			case 4:
				print_list(new_list);
				break;

			case 5:
				printf("\nInput name of a file. It must be less than 255 symbols.\n");

				char name_of_output_file[256];
				FILE* output_file_ptr;

				scanf_s("%s", name_of_output_file, _countof(name_of_output_file));
				clean_stdin();

				if(!fopen_s(&output_file_ptr, name_of_output_file, "w")) {
					print_list_to_stream(output_file_ptr, new_list);
					fclose(output_file_ptr);
				}
				break;
			}

			if (mode == 5 || mode == 6) {
				delete_list(&new_list);
				break;
			}
		}
	}

	return 0;
}