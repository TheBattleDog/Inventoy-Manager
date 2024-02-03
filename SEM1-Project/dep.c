#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dep.h"
#include "file_handling.h"
#include "menu.h"

extern struct Product gProducts[MAX_LENGTH];
extern int gCurrent_product_selected;
extern int gProduct_size;

bool authenticate_User()
{
	char ui_master_password[MAX_LENGTH] = { "" }; // ui - user input
	char stored_master_password[MAX_LENGTH] = { "" };
	static int count = 0;

	get_File_Data(PASS_FILENAME, stored_master_password);
	decrypt(stored_master_password);
	load_Inventory_Data(DATA_FILENAME);
	clear_scr();

	print_Heading("INVENTORY MANAGEMENT SYSTEM");

	if (count > 4)
		printf("STOP... GO GET SOME HELP\n\n");
	else if (count > 0)
		printf("You are kinda sus mate... ReEnter the Password...\n");


	prompt_User("Password");
	get_Password(ui_master_password);

	if (strcmp(ui_master_password, stored_master_password))
	{
		count++;
		return false;
	}
	else
	{
		count = 0;
		return true;
	}
}


void get_Inventory()
{
	const char* menu_items[] = { "Add Items", "Update Quantity", "Delete Items",
								 "View Inventory", "Generate Reports", "Search Items", "Change Master Password","Exit"};
	const int no_items = sizeof(menu_items) / sizeof(menu_items[0]);

	int sel = put_Menu(menu_items, no_items);

	clear_scr();

	switch (sel)
	{
	case 0: add_items(); break;
	case 1: update_Quantity(); break;
	case 2: delete_Items(); break;
	case 3: view_Inventory(); break;
	case 4: generate_Reports(); break;
	case 5: search_Items(); break;
	case 6: change_Master_Password(); break;
	case 7: exit_App(); break;
	}
	getch();
}

void init_Products()
{
	int i = 0;
	for (i = 0; i < MAX_LENGTH; i++)
	{
		gProducts[i].code = -1;
		gProducts[i].name[0] = '\0';
		gProducts[i].price = -1;
		gProducts[i].stock = -1;
	}
}

void clear_scr()
{
	printf("\033[2J\033[H");
}

void get_Password(char password[MAX_LENGTH])
{
	int i = 0;
	char input;

	while (i < MAX_LENGTH)
	{
		input = getch();

		if (input == ENTER)
		{
			password[i] = '\0';
			break;
		}
		else if (input == BACKSPACE)
		{
			if (i > 0)
			{
				--i;
				printf("\b \b"); //This is pretty Darn Epic
			}
		}
		else
		{
			password[i] = input;
			putchar('*');
			i++;
		}
	}
	putchar('\n');
}

void print_Success_Message(const char* message, const char* v_indent, int duration)
{
	int size = strlen(message);
	int i;
	printf("%s", v_indent);
	for (i = 0; i < size; i++)
	{
		printf("%c\x1b[B\b-\x1b[A", message[i]); // Prints in two lines Two lines (\x1b[B) - used to go to down a line (\x1b[A) used to go up a line
		delay(duration);
	}
	printf("\n\n");
}

void clear_Input_Buffer()
{
	char c;
	while ((c = getch()) != '\n' && c != EOF);
}

int get_Ascii(int num)
{
	return num + '0';
}

int to_Num(char ch)
{
	return ch - '0';
}

int calc_Product_Char_count(struct Product prd)
{
	char prd_string[200];
	sprintf(prd_string, "%d%s%.2lf%d", prd.code, prd.name, prd.price, prd.stock);
	return strlen(prd_string);
}

void delay(int milliseconds)
{
	clock_t start_time = clock();

	while (clock() < (start_time + milliseconds));
}

int generate_Rand(int min_range, int max_range)
{
	srand(time(NULL));

	return ((rand() % (max_range - min_range + 1)) + min_range);
}


void prompt_User(const char* format_str, ...)
{
	fflush(stdin);
	va_list args;
	va_start(args, format_str);

	char sformat[120];
	strcpy(sformat, format_str);
	strcat(sformat, " >> ");

	vprintf(sformat, args);

	va_end(args);
	fflush(stdin);
}

void print_Heading(const char* heading)
{
	int i;
	int heading_size = strlen(heading);

	puts(heading);
	for (i = 0; i < heading_size; i++)
	{
		putchar('_');
	}

	puts("\n\n");
}

void first_Init(char master_password[MAX_LENGTH])
{
	char master_password_re_enter[MAX_LENGTH] = { "" };

	while (true)
	{
		print_Heading("Dependencies not found, enter new login credentials.");
		prompt_User("Set a Password to Login");
		get_Password(master_password);
		prompt_User("Re-Enter the Password");
		get_Password(master_password_re_enter);

		if (strcmp(master_password, master_password_re_enter))
		{
			printf("\n\nThe password does not match!!\n\
					Press any key to ReEnter the password...");
			getch();
		}
		else
		{
			break;
		}
	}

	encrypt(master_password, 0, 0);
	write_to_File(PASS_FILENAME, master_password);
	create_File(DATA_FILENAME);
}

void encrypt(char* message, int shift, int is_decrypt)
{
	int i;
	int ch;
	int initial_ch;
	int size = 0;;

	if (shift == 0)
		shift = generate_Rand(3, 9);

	for (i = 0; message[i] != '\0'; i++)
	{
		ch = message[i];
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			initial_ch = ch;
			ch = ch + shift;


			if (((ch > 'Z' && ch < 'a') || ch > 'z') && is_decrypt == 0)
			{
				ch -= 26;
			}
			else if ((islower((char)initial_ch) && !(islower((char)ch))) || (isupper((char)initial_ch) && !(isupper((char)ch))) && !isdigit(ch))
			{
				ch += 26;
			}

			message[i] = ch;
		}
		else
		{
			ch = ch + shift;
			message[i] = ch;
		}

	}

	if (!is_decrypt)
	{
		size = strlen(message);
		message[size] = get_Ascii(shift);
		message[size + 1] = '\0';
	}
}

void decrypt(char* message)
{
	int size = strlen(message);
	int shift = to_Num(message[size - 1]);
	message[--size] = '\0';
	encrypt(message, -shift, 1);
}
