#include <stdio.h>
#include <conio.h>
#include "file_handling.h"
#include "dep.h"
#include "menu.h"

#ifndef F_OK
#define F_OK 0 
#endif

extern struct Product products[MAX_LENGTH];


void get_File_Data(const char* file_name, char data[MAX_LENGTH])
{
	FILE* fileptr;
	int byte_read;
	if (access(file_name, F_OK) != 0)
	{
		first_Init(data);
	}
	else
	{
		fileptr = open_File(file_name, "rb");
		byte_read = fread(data, sizeof(char), MAX_LENGTH, fileptr);
		if (byte_read > 0)
		{
			data[byte_read] = '\0';
			fclose(fileptr);
		}
		else
		{
			printf("ERROR READING FILE");
			fclose(fileptr);
			getch();
			exit(1);
		}
	}
}

void load_Inventory_Data(const char* file_name)
{
	FILE* fileptr;
	int byte_read;
	fileptr = open_File(file_name, "rb");
	byte_read = fread(products, sizeof(struct Product), MAX_LENGTH, fileptr);
	if (byte_read > 0)
	{
		fclose(fileptr);
	}
	else
	{
		printf("ERROR READING FILE");
		fclose(fileptr);
		getch();
		exit(1);
	}
}

void create_File(const char* file_name)
{
	FILE* new_file;

	new_file = fopen(file_name, "wb");

	if (new_file == NULL)
	{
		printf("Unable to create a new file!!\n\
			    Press any key to exit...");
		getch();
		exit(1);
	}
}

FILE* open_File(const char* file_name, const char* for_what)
{
	FILE* fileptr;

	fileptr = fopen(file_name, for_what);
	if (for_what[0] == 'r')
	{
		fseek(fileptr, 0, SEEK_SET);
	}
	if (fileptr == NULL)
	{
		printf("Unable to open %s!!!\n\
				Press any button to exit...", file_name);
		getch();
		exit(1);
	}

	return fileptr;
}

void write_to_New_File(char* file_name, char* file_input)
{
	FILE* fmaster_password;
	create_File(file_name);
	fmaster_password = open_File(file_name, "wb");

	fwrite(file_input, sizeof(file_input[0]), sizeof(file_input), fmaster_password);
	fclose(fmaster_password);
}
