#include "inputing.h"








void clean_stdin() {
	ungetc('~', stdin);

	while (getchar() != '\n');

	return;
}








void scaning_int_with_limits(int *value_ptr, int lower_limit, int upper_limit) {

	for (int err = 0; (err = (scanf_s("%d", value_ptr) != 1)) ||
		*value_ptr < lower_limit || *value_ptr > upper_limit;) {

		clean_stdin();

		if (err) {
			printf("\nYou have input not a number. Please, try again...\n");
		}
		else {
			printf("\nYou have input invalid number. It must be more than %d and less than %d. Please, try again...\n", lower_limit - 1, upper_limit + 1);
		}
	}

	clean_stdin();
	return;
}








void scaning_two_int_with_a_lower_limit(int *first_value_ptr,
	int *second_value_ptr,
	int lower_limit) {

	for (int err = 0; (err = 
		(scanf_s("%d %d", first_value_ptr, second_value_ptr) != 2)) ||
		*first_value_ptr < lower_limit || *second_value_ptr < lower_limit;) {

		clean_stdin();

		if (err) {
			printf("\nYou have input not a number. Please, try again...\n");
		}
		else {
			printf("\nYou have input invalid numbers. They must be more than %d. Please, try again...\n", lower_limit - 1);
		}

	}

	clean_stdin();
	return;
}








void scaning_a_string_of_long_doubles(long double *string_ptr, size_t num_of_el) {
	for (int j = 0; j < num_of_el; j++) {
		long double el = 0;

		if (scanf_s("%Lf", &el) != 1) {

			clean_stdin();

			printf("\nYou have input not a number. All input elements of this string will be ignored. Please, try again...\n");
			j = -1;
		}
		else {
			string_ptr[j] = el;
		}
	}

	clean_stdin();
	return;
}