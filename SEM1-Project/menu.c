#include <stdio.h>
#include <string.h>
#include "dep.h"
#include "file_handling.h"
#include "menu.h"
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
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	printf("Add Items Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void update_Quantity()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
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
	char bye_message[] = "Bye Bye...";
	int i;
	for (i = 0; bye_message[i] != '\0'; i++)
	{
		putchar(bye_message[i]);
		delay();
	}
	exit(1);
}
