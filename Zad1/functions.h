#define MAX_INPUT 32767
#define MIN_INPUT -32767

typedef union
{
	signed short value;
	struct
	{
		unsigned short b0 : 1;
		unsigned short b1 : 1;
		unsigned short b2 : 1;
		unsigned short b3 : 1;
		unsigned short b4 : 1;
		unsigned short b5 : 1;
		unsigned short b6 : 1;
		unsigned short b7 : 1;
		unsigned short b8 : 1;
		unsigned short b9 : 1;
		unsigned short b10 : 1;
		unsigned short b11 : 1;
		unsigned short b12 : 1;
		unsigned short b13 : 1;
		unsigned short b14 : 1;
		unsigned short b15 : 1;
	} bits;
} Number;

void menu(short* number);
void print_menu();
void menu_option_choice(int* choice);

void input_number(short* number, int* flag);

void output_number(short number);

void find_smaller_number(short number);
void shift_bits(Number* union_ptr);

void int_input(int* var);
void short_alloc_check(short* memory_block);