#include <stdio.h>
#include "dep.h"

int main()
{
	print_Heading("INVENTORY MANAGEMENT SYSTEM");
	while (TRUE)
	{
		if (authenticate_User())
			get_Inventory();
	}

	return 0;
}