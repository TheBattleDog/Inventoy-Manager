#include <stdio.h>
#include <string.h>
#include "dep.h"
#include "file_handling.h"
#include "menu.h"
#include <wchar.h>

extern struct Product gProducts[MAX_LENGTH];
extern int gCurrent_product_selected;
extern int gProduct_size;

int put_Menu(const char* items[], int size)
{
	int i;
	int sel = 0;
	char u_ip = 0;
	while (true)
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
	bool invalid_input = false;
	bool current_input_invalid = false;
	char ch;

	do 
	{
		clear_scr();
		print_Heading("INVENTORY MANAGEMENT SYSTEM - ADD ITEM");
		if (invalid_input)
		{
			fflush(stdin);
			printf("The inputs are invalid!!\n\n\n");
			prompt_User("Would you like to ReEnter the item details (Y/N)");
			ch = getch();
			putchar(ch);
			if (ch == 'Y' || ch == 'y')
			{
				invalid_input = false;
				current_input_invalid = true;
			}
			else if (ch == 'N' || ch == 'n')
			{
				get_Inventory();
				return;
			}
			continue;
		}
		fflush(stdin);

		prompt_User("Enter the product code");
		scanf(" %d", &gProducts[gProduct_size].code);

		prompt_User("Enter the name of the item with product code %d", gProducts[gProduct_size].code);
		scanf(" %99[^\n]", gProducts[gProduct_size].name);

		prompt_User("Enter the price of %s", gProducts[gProduct_size].name);
		scanf("%lf", &gProducts[gProduct_size].price);

		prompt_User("Enter the available stock for %s", gProducts[gProduct_size].name);
		scanf("%d", &gProducts[gProduct_size].stock);

		invalid_input = !(valid_Inputs(gProducts[gProduct_size]));
		current_input_invalid = invalid_input;
	} while (invalid_input || current_input_invalid);

	print_Success_Message("New item added Successfully!!", "\n\n", 50);
	++gProduct_size;

	update_Inventory_Data();
	printf("\n\nPress any key to go back...");
	getch();
	get_Inventory();
}

void update_Quantity()
{
	printf("Update Quantity Selected\n\nPress any Key to go back...");
	getch();
	get_Inventory();
}

void delete_Items()
{
	int sel = 0;
	struct Product temp[100];
	int original_position[100];
	int temp_size = 0;
	int itemp = -1;
	bool selected = false;
	bool run = true;

	while (run)
	{
		
		put_Table_View_Menu(gProducts, sel, gProduct_size, true);
		itemp = menu_User_Input(sel, gProduct_size);
		selected = (sel == itemp);
		sel = itemp;
		if (sel == -1)
		{
			run = false;
			break;
		}
		else
		{
			if (selected)
			{
				if (sel < gProduct_size)
				{
					int i = 0;
					for (i = sel; i < gProduct_size; i++)
					{
						gProducts[i] = gProducts[i + 1];
					}
				}
				--gProduct_size;
				print_Success_Message("Item deleted Successfully!!", "\n\n", 50);
				printf("\n\n\nPress any key to continue...");
				run = false;
			}
		}
		clear_scr();
	}

	update_Inventory_Data();

	get_Inventory();
}

void view_Inventory()
{
	table_View(0, gProduct_size, true);

	printf("\n\n\nPress any button to go back...");
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
	
	getch();
	get_Inventory();
}


void change_Master_Password()
{
	char ui_master_password[MAX_LENGTH] = { '\0' };
	char stored_master_password[MAX_LENGTH] = { '\0' };
	get_File_Data(PASS_FILENAME, stored_master_password);
	decrypt(stored_master_password);

	int count = 0;

	do 
	{
		if (count > 0)
		{
			print_Heading("\n\nWRONG PASSWORD... Are you the right guy?! -_-");
		}
		prompt_User("Enter the old password");
		get_Password(ui_master_password);
		count++;
	} while (strcmp(ui_master_password, stored_master_password));

	if (count > 4)
	{
		print_Heading("\n\nFinally...");
	}
	count = 0;

	do {
		if (count > 0) 
		{
			print_Heading("\n\nTHE PASSWORDS DOES NOT MATCH!!");
		}
		prompt_User("\n\nEnter the new password");
		get_Password(ui_master_password);

		prompt_User("\nReEnter the password");
		get_Password(stored_master_password);
		count++;
	} while (strcmp(ui_master_password, stored_master_password));

	encrypt(ui_master_password, 0, 0);
	write_to_File(PASS_FILENAME, ui_master_password);

	if (count > 4)
	{
		print_Heading("\n\nDamn finally... Thank You...");
	}


	print_Success_Message("The PASSWORD has been successfully changed :)", "\n\n", 50);
	printf("\n\nPress any key to go back...");
	getch();
	get_Inventory();
}

void exit_App()
{
	print_Success_Message("Bye Bye.......", "", 100);
	exit(1);
}

bool valid_Inputs(struct Product prdct)
{
	return !(prdct.code < 0 || prdct.price < 0 || prdct.stock < 0 || prdct.name[0] == '\0');
}

void table_View(int start, int end, bool heading)
{
	if (heading)
	{
		printf("%-20s %-20s %-20s %-20s\n", "PRODUCT CODE", "PRODUCT NAME", "PRICE", "STOCK");
		printf("%-20s %-20s %-20s %-20s\n", "------------", "------------", "-----", "-----");
	}
	int i;
	for (i = start; i < end; i++)
	{
		printf("%-20d %-20s %-20.2lf %-20d\n", gProducts[i].code, gProducts[i].name, gProducts[i].price, gProducts[i].stock);
	}

}

int put_Table_View_Menu(struct Product products[], int sel, int size, bool heading)
{
	int i;
	bool selector = false;
	int selector_size = 83;
	if (heading)
	{
		printf("%-20s %-20s %-20s %-20s\n", "PRODUCT CODE", "PRODUCT NAME", "PRICE", "STOCK");
		printf("%-20s %-20s %-20s %-20s\n", "------------", "------------", "-----", "-----");
	}
	
	for (i = 0; i < size; i++)
	{
		if (sel == i)
		{
			selector = true;
			int temp = calc_Product_Char_count(products[i]) + 40;
			selector_size = temp > selector_size ? temp : selector_size;
			printf("+");
			for (int j = 0; j < selector_size; j++)
				printf("-");
			printf("+\n");
		}
		printf("%-20d %-20s %-20.2lf %-20d\n", products[i].code, products[i].name, products[i].price, products[i].stock);
		if (selector)
		{
			selector = false;
			printf("+");
			for (int j = 0; j < selector_size; j++)
				printf("-");
			printf("+\n");
		}
	}
	return sel;
}

int menu_User_Input(int sel, int size)
{
	int u_ip;

	fflush(stdin);
	u_ip = getch();

	if (u_ip >= get_Ascii(1) && u_ip <= get_Ascii(size))
		return (to_Num(u_ip) - 1); // char to int conversion

	if (u_ip == 'x' || u_ip == 'X')
		return -1;

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

	
	return sel;
}
