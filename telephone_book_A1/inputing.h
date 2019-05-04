#pragma once


#include <stdio.h>


void scaning_int_with_limits(int *value_ptr, int lower_limit, int upper_limit);

void clean_stdin();

void scaning_two_int_with_a_lower_limit(int *first_value_ptr,
	int *second_value_ptr,
	int lower_limit);

void scaning_a_string_of_long_doubles(long double *string_ptr, size_t num_of_el);