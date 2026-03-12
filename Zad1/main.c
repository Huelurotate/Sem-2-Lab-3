// ЗАДАНИЕ 1: Найти и вывести целое число в 2 раза меньше заданного,
// не выполняя деления и не используя операцию взятия остатка от деления.
// СТУДЕНТ: Яровиков Ю. В.
// ДАТА: 11.03.2026

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
	signed short *initial_number = malloc(sizeof(short));
	short_alloc_check(initial_number);

	menu(initial_number);

	free(initial_number);

	return 0;
}