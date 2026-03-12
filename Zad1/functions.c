#include <stdio.h>
#include "functions.h"

void menu(short* number)
{
	int menu_choice, is_running = 1;
	int number_entered = 0;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input_number(number, &number_entered);
			break;
		case 2:
			if (number_entered)
				output_number(*number);
			else
				puts("\nNo number has been entered.");
			break;
		case 3:
			if (number_entered)
				find_smaller_number(*number);
			else
				puts("\nNo number has been entered.");
			break;
		case 4:
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Number\n"
		"2 - Print Number\n"
		"3 - Find Number 2 Times Smaller\n"
		"4 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (scanf_s("%d", choice) != 1 || *choice < 1 || *choice > 4)
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
	rewind(stdin);
}

void input_number(short* number, int* flag)
{
	printf("\nEnter a number between %d and %d:\n", MIN_INPUT, MAX_INPUT);

	int temp;
	while (scanf_s("%d", &temp) != 1 || temp > MAX_INPUT || temp < MIN_INPUT)
	{
		printf("Invalid Input.\n");
		rewind(stdin);
	}
	rewind(stdin);

	*number = temp;
	*flag = 1;
}

void output_number(short number)
{
	puts("\nYour number is:");
	printf("%d\n", number);
}

void find_smaller_number(short number)
{
	Number user_number;
	user_number.value = number;

	shift_bits(&user_number);

	puts("\nNumber 2 times smaller than the initial one:");
	printf("%d\n", user_number.value);
}

void shift_bits(Number* union_ptr)
{
	int sign_digit = 0;
	if (union_ptr->value < 0)
		sign_digit = 1;

	union_ptr->bits.b0 = union_ptr->bits.b1;
	union_ptr->bits.b1 = union_ptr->bits.b2;
	union_ptr->bits.b2 = union_ptr->bits.b3;
	union_ptr->bits.b3 = union_ptr->bits.b4;

	union_ptr->bits.b4 = union_ptr->bits.b5;
	union_ptr->bits.b5 = union_ptr->bits.b6;
	union_ptr->bits.b6 = union_ptr->bits.b7;
	union_ptr->bits.b7 = union_ptr->bits.b8;

	union_ptr->bits.b8 = union_ptr->bits.b9;
	union_ptr->bits.b9 = union_ptr->bits.b10;
	union_ptr->bits.b10 = union_ptr->bits.b11;
	union_ptr->bits.b11 = union_ptr->bits.b12;

	union_ptr->bits.b12 = union_ptr->bits.b13;
	union_ptr->bits.b13 = union_ptr->bits.b14;
	union_ptr->bits.b14 = union_ptr->bits.b15;
	union_ptr->bits.b15 = sign_digit;
}

void short_alloc_check(short* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}
