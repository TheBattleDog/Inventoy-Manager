#ifndef _MENU_
#define _MENU_

struct Product
{
	int code;
	int name[100];
	double price;
	int stock;
};

int put_Menu(const char* items[], int size);
void add_items();
void update_Quantity();
void delete_Items();
void view_Inventory();
void generate_Reports();
void search_Items();
void exit_App();
#endif // MENU
