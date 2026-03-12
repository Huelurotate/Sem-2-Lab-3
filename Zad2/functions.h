#define ACC_NUM_LEN 5

typedef struct
{
	int passport_number;
	char* surname;

	struct
	{
		char account_number[ACC_NUM_LEN + 2];
		int deposit_value;
	} Account_info;
} Bank_Info;

// MENU
void menu(Bank_Info* struct_arr);
void print_menu();
void menu_option_choice(int* choice);

// INPUT
void input_bank_info(Bank_Info** struct_arr, int* total_accounts);
void struct_rewrite_request(Bank_Info** struct_arr, int* total_numbers);

void input_passport_number(Bank_Info* struct_arr, int array_position);
void int_input(int* var);

void input_surname(Bank_Info* struct_arr, int array_position);
void str_input(char** str);

void input_account_number(Bank_Info* struct_arr, int array_position);

void input_deposit_value(Bank_Info* struct_arr, int array_position);

void choice_loop(int* choice_var);

//OUTPUT
void output_bank_info(Bank_Info* struct_arr, int total_accounts);

// COUNT ACCOUNTS
void count_clients_account(Bank_Info* struct_arr, int total_accounts);

// DELETE ACCOUNTS
void delete_accounts(Bank_Info** struct_arr, int* total_accounts);

// MEMORY ALLOCATION CHECKS AND FREEING
void struct_alloc_check(Bank_Info* memory_block);
void check_char_alloc(char* memory_block);
void free_struct_array(Bank_Info** struct_arr, int* total_accounts);