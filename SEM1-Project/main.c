#include <stdio.h>
#include <stdlib.h>
#include "dep.h"
#include "file_handling.h"
#include "menu.h"

struct Product products[MAX_LENGTH];

int main()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	while (TRUE)
	{
		if (authenticate_User())
		{
			load_data();
			get_Inventory();
		}
	}

	return 0;
}