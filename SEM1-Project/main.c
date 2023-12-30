#include <stdio.h>
#include <stdlib.h>
#include "dep.h"

char gMaster_password[100];


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