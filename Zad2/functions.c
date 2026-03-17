#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void menu(Bank_Info* struct_arr)
{
	int menu_choice, is_running = 1;
	int total_accounts = 0;

	while (is_running)
	{
		print_menu();
		menu_option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input_bank_info(&struct_arr, &total_accounts);
			break;
		case 2:
			if (total_accounts > 0)
				output_bank_info(struct_arr, total_accounts);
			else
				puts("\nThere are no accounts.");
			break;
		case 3:
			if (total_accounts > 0)
				count_clients_account(struct_arr, total_accounts);
			else
				puts("\nThere are no accounts.");
			break;
		case 4:
			if (total_accounts > 0)
				delete_accounts(&struct_arr, &total_accounts);
			else
				puts("\nThere are no accounts.");
			break;
		case 5:
			free_struct_array(&struct_arr, &total_accounts);
			is_running = 0;
			break;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Clients' Accounts\n"
		"2 - Output Clients' Accounts\n"
		"3 - Count All Of Client's Accounts\n"
		"4 - Delete Client's Accounts\n"
		"5 - Exit Program");
}

void menu_option_choice(int* choice)
{
	while (1)
	{
		int_input(choice);
		if (*choice < 1 || *choice > 5)
			puts("\nChoose an option(1-5).");
		else
			break;
	}
}

void input_bank_info(Bank_Info** struct_arr, int* total_accounts)
{
	int continue_choice = 0;

	if (*total_accounts > 0)
		struct_rewrite_request(struct_arr, total_accounts);

	do
	{
		*struct_arr = realloc(*struct_arr, sizeof(Bank_Info) * (*total_accounts + 1));
		struct_alloc_check(*struct_arr);

		input_passport_number(*struct_arr, *total_accounts);
		input_surname(*struct_arr, *total_accounts);
		input_account_number(*struct_arr, *total_accounts);
		input_deposit_value(*struct_arr, *total_accounts);

		(*total_accounts)++;

		printf("\nInput bank info for another client?(1 - Yes, 0 - No): ");
		choice_loop(&continue_choice);
	} while (continue_choice);
}

void struct_rewrite_request(Bank_Info** struct_arr, int* total_numbers)
{
	int rewrite_choice;
	printf("\nRewrite all the bank info?(1 - Yes, 0 - No): ");
	choice_loop(&rewrite_choice);
	if (rewrite_choice)
		free_struct_array(struct_arr, total_numbers);
}

void input_passport_number(Bank_Info* struct_arr, int array_position)
{
	puts("\nEnter a passport number:");
	while (1)
	{
		int_input(&(struct_arr[array_position].passport_number));
		if (struct_arr[array_position].passport_number < 0)
			puts("\nPassport number cannot be less than 0.");
		else
			break;
	}
}

void int_input(int* var)
{
	char buffer[100];
	char* endptr;
	long temp;

	while (1)
	{
		fgets(buffer, sizeof(buffer), stdin);

		buffer[strcspn(buffer, "\n")] = '\0';

		if (buffer[0] != '\0')
		{
			temp = strtol(buffer, &endptr, 10);

			if (*endptr == '\0')
			{
				*var = (int)temp;
				return;
			}
		}

		puts("\nInvalid Input. Please, enter a single integer.");
	}
}

void input_surname(Bank_Info* struct_arr, int array_position)
{
	puts("\nEnter a surname:");
	struct_arr[array_position].surname = NULL;
	str_input(&(struct_arr[array_position].surname));
}

void str_input(char** str)
{
	int length = 0;
	char c;

	while ((c = getchar()) == '\n')
		puts("\nYou cannot enter an empty string.");

	ungetc(c, stdin);
	while ((c = getchar()) != '\n')
	{
		length++;
		*str = realloc(*str, (length + 1) * sizeof(char));
		check_char_alloc(*str);
		(*str)[length - 1] = c;
	}
	
	(*str)[length] = '\0';
}

void input_account_number(Bank_Info* struct_arr, int array_position)
{
	char* temp = (struct_arr[array_position].Account_info.account_number);
	
	int is_running = 1;
	while (is_running)
	{
		printf("\nEnter a %d-digit account number:\n", ACC_NUM_LEN);
		fgets(temp, ACC_NUM_LEN + 2, stdin);
		temp[strcspn(temp, "\n")] = '\0';
		rewind(stdin);
		
		if (strlen(temp) == ACC_NUM_LEN)
		{
			check_unique_acc_num(struct_arr, array_position, &is_running, temp);
			continue;
		}
		
		puts("\nInvalid Input.");
	}
}

void check_unique_acc_num(Bank_Info* struct_arr, int total_accounts, int* flag, char* new_num)
{
	for (int i = 0; i < total_accounts; i++)
	{
		if (strcmp(new_num, struct_arr[i].Account_info.account_number) == 0)
		{
			puts("\nThis account number already exist.");
			return;
		}
	}

	*flag = 0;
}

void input_deposit_value(Bank_Info* struct_arr, int array_position)
{
	puts("\nEnter a deposit value:");
	while (1)
	{
		int_input(&(struct_arr[array_position].Account_info.deposit_value));
		if (struct_arr[array_position].Account_info.deposit_value < 0)
			puts("\nDeposit value cannot be less than 0.");
		else
			break;
	}
}

void choice_loop(int* choice_var)
{
	while (1)
	{
		int_input(choice_var);
		if (*choice_var != 1 && *choice_var != 0)
			puts("\nInvalid Input. Please, choose an option(1 or 0).");
		else
			break;
	}
}

void output_bank_info(Bank_Info* struct_arr, int total_accounts)
{
	for (int i = 0; i < total_accounts; i++)
	{
		printf("\nClient %d:\n", i + 1);
		printf("Passport number: %d\n", struct_arr[i].passport_number);
		printf("Surname: %s\n", struct_arr[i].surname);
		printf("Account number: %s\n", struct_arr[i].Account_info.account_number);
		printf("Deposit value: %d\n", struct_arr[i].Account_info.deposit_value);
	}
}

void count_clients_account(Bank_Info* struct_arr, int total_accounts)
{
	int target_passport_number;
	puts("\nEnter a passport number to count client's accounts:");
	while (1)
	{
		int_input(&target_passport_number);
		if (target_passport_number < 0)
			puts("\nPassport number cannot be less than 0.");
		else
			break;
	}

	int total = 0;
	for (int i = 0; i < total_accounts; i++)
		if (struct_arr[i].passport_number == target_passport_number)
			total++;

	if (total)
		printf("\nNumber of accounts with this passport number: %d\n", total);
	else
		puts("\nThere are no accounts with this passport number.");
}

void delete_accounts(Bank_Info** struct_arr, int* total_accounts)
{
	char* target_surname = NULL;
	puts("\nEnter accounts' surname to delete:");
	str_input(&target_surname);
	check_char_alloc(target_surname);

	int is_found = 0, total = 0;

	for (int i = 0; i < *total_accounts; i++)
	{
		if (strcmp((*struct_arr)[i].surname, target_surname) == 0)
		{
			free((*struct_arr)[i].surname);

			for (int j = i; j < *total_accounts - 1; j++)
			{
				(*struct_arr)[j] = (*struct_arr)[j + 1];
			}

			(*total_accounts)--;
			*struct_arr = realloc(*struct_arr, sizeof(Bank_Info) * (*total_accounts));
			i--;

			is_found = 1;
			total++;
		}
	}

	if (is_found)
		printf("\nDeleted %d account(s) with %s surname.\n", total, target_surname);
	else
		printf("\nNo accounts with %s surname found.\n", target_surname);
	free(target_surname);
}

void struct_alloc_check(Bank_Info* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void check_char_alloc(char* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void free_struct_array(Bank_Info** struct_arr, int* total_accounts)
{
	for (int i = 0; i < *total_accounts; i++)
		free((*struct_arr)[i].surname);

	free(*struct_arr);
	*struct_arr = NULL;
	*total_accounts = 0;
}