#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "dep.h"
#include "file_handling.h"

BOOL authenticate_User()
{
	char ui_master_password[PASS_SIZE] = { "" }; // ui - user input
	char stored_master_password[PASS_SIZE] = { "" };
	const char* file_name = "Pass.bin";
	static int count = 0;

	get_File_Data(file_name, stored_master_password);
	clear_scr();

	print_Heading("INVENTORY MANAGEMENT SYSTEM");

	if (count > 4)
	{
		printf("STOP... GO GET SOME HELP\n\n");
	}
	else if (count > 0)
		printf("You are kinda sus mate... ReEnter the Password...\n");


	prompt_User("Password");
	get_password(ui_master_password);

	if (strcmp(ui_master_password, stored_master_password))
	{
		count++;
		return FALSE;
	}
	else
	{
		count = 0;
		return TRUE;
	}
}


void get_Inventory()
{
	const char* menu_items[] = { "Add Items", "Update Quantity", "Delete Items",
								 "View Inventory", "Generate Reports", "Search Items", "Exit" };
	const int no_items = sizeof(menu_items) / sizeof(menu_items[0]);

	int sel = put_Menu(menu_items, no_items);
	clear_scr();
	print_Heading("INVENTORY MANAGEMENT SYSTEM");

	switch (sel)
	{
	case 0: add_items();
	case 1: update_Quantity();
	case 2: delete_Items();
	case 3: view_Inventory();
	case 4: generate_Reports();
	case 5: search_Items();
	case 6: exit_App();
	}
	getch();
}

void clear_scr()
{
	printf("\033[2J\033[H");
}

void get_password(char password[PASS_SIZE])
{
	int i = 0;
	char input;

	while (i < PASS_SIZE)
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

void clear_input()
{
	while (getch() != '\n' && getch() != EOF);
}

int get_Ascii(int num)
{
	return num + '0';
}

int to_Num(char ch)
{
	return ch - '0';
}

void delay()
{
#include <time.h>
	clock_t start_time = clock();



	do
	{
		//time(&current_time);
	} while (clock() < (start_time + 200));
}


void prompt_User(const char* str)
{
	fflush(stdin);
	printf("\n%s >> ", str);
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

void first_Init(char master_password[PASS_SIZE])
{
	char master_password_re_enter[100] = { "" };

	while (1)
	{
		prompt_User("Set a Password to Login");
		get_password(master_password);
		prompt_User("Re-Enter the Password");
		get_password(master_password_re_enter);

		if (strcmp(master_password, master_password_re_enter))
		{
			printf("\n\nThe password does not match!!\n\
					Press any key to reenter the password...");
		}
		else
		{
			break;
			getch();
		}
	}

	encrypt(master_password, 0, 0);
	write_to_New_File("Pass.bin", master_password);
}

void encrypt(char* message, int shift, int is_decrypt)
{
	int i;
	int ch;
	int initial_ch;
	int size = 0;
	int min_range = 1;
	int max_range = 9;

	srand((unsigned int)time(NULL));

	if (shift == 0)
		shift = ((rand() % (max_range - min_range + 1)) + min_range);

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
		message[size] = shift + '0'; // Number to character conversion
		message[size + 1] = '\0';
	}
}

void decrypt(char* message)
{
	int size = strlen(message);
	int shift = message[size - 1] - '0';
	message[--size] = '\0';
	encrypt(message, -shift, 1);
}