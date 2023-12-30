#ifndef _MENU_
#define _MENU_


struct Product
{
	int code;
	char name[100];
	double price;
	int stock;
};

int put_Menu(const char* items[], int size);
int put_Table_View_Menu(); // To be implemented

void add_items();
void update_Quantity();
void delete_Items();
void view_Inventory();
void generate_Reports();
void search_Items();
void change_Master_Password();
void exit_App();

void table_View(int start, int end, BOOL heading);

BOOL valid_Inputs(struct Product prdct);
#endif // MENU