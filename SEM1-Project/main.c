#include <stdio.h>
#include <stdlib.h>
#include "dep.h"
#include "file_handling.h"
#include "menu.h"

struct Product gProducts[MAX_LENGTH];
int gCurrent_product_selected = 0;
int gProduct_size = MAX_LENGTH;

int main()
{
	init_Products();
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	while (true)
	{
		if (authenticate_User())
		{
			get_Inventory();
		}
	}

	return 0;
}