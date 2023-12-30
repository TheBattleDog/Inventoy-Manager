#include <stdio.h>
#include <string.h>
#include "dep.h"
#include "file_handling.h"
#include "menu.h"

extern struct Product products[MAX_LENGTH];
int put_Menu(const char* items[], int size)
{
	int i;
	int sel = 0;
	char u_ip = 0;
	while (TRUE)
	{
		clear_scr();
		print_Heading("INVENTORY MANAGEMENT SYSTEM");
		for (i = 0; i < size; i++)
		{
			if (sel == i)
			{
				printf("> ");
			}
			printf("%d. %s", i + 1, items[i]);
			if (sel == i)
			{
				printf(" <\n");
			}
			else printf("\n");
		}

		fflush(stdin);
		u_ip = getch();

		if (u_ip >= get_Ascii(1) && u_ip <= get_Ascii(size))
			return (to_Num(u_ip) - 1); // char to int conversion

		if (u_ip == 'x' || u_ip == 'X')
			break;

		switch (u_ip)
		{
		case ENTER: return sel; break;
		case ARROW_KEY: u_ip = getch(); break;
		}

		switch (u_ip)
		{
		case UP_ARROW: sel = sel <= 0 ? size - 1 : sel - 1; break;
		case DOWN_ARROW: sel = sel >= size - 1 ? 0 : sel + 1; break;
		}
	}
}

void add_items()
{
	prompt_User("Enter the product code");
	scanf("%d", &products[0].code);

	prompt_User("Enter the name of the item with product code %d", products[0].code);
	scanf("%10[^\n]", &products[0].name);

	prompt_User("Enter the price of %s", products[0].name);
	scanf("%lf", &products[0].price);

	prompt_User("Enter the available stock for %s >> ", products[0].name);
	scanf("%d", &products[0].stock);


	get_Inventory();
}

void update_Quantity()
{
	//print_Heading("INVENTORY MANAGEMENT SYSTEM");
	printf("Update Quantity Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void delete_Items()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	printf("Delete Items Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void view_Inventory()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	printf("View Inventory Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void generate_Reports()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	printf("Generate Reports Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void search_Items()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	printf("Search Items Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void exit_App()
{
	char bye_message[] = "Bye Bye.......";
	int i;
	for (i = 0; bye_message[i] != '\0'; i++)
	{
		putchar(bye_message[i]);
		delay(100);
	}
	exit(1);
}
