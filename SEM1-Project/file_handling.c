#include <stdio.h>
#include <conio.h>
#include "file_handling.h"
#include "dep.h"
#include "menu.h"

#ifndef F_OK
#define F_OK 0 
#endif

extern struct Product gProducts[MAX_LENGTH];
extern int gCurrent_product_selected;
extern int gProduct_size;


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

void load_Inventory_Data()
{
	FILE* fileptr;
	int byte_read;
	int i;
	fileptr = open_File(DATA_FILENAME, "rb");
	byte_read = fread(gProducts, sizeof(struct Product), MAX_LENGTH, fileptr);
	
	if (ferror(fileptr))
	{
		perror("ERROR READING FILE");
		fclose(fileptr);
		getch();
		exit(1);
	}

	fclose(fileptr);

	for (i = 0, gProduct_size = 0; gProducts[i].price != -1; i++, gProduct_size++);
}

void update_Inventory_Data()
{
	FILE* fileptr = open_File(DATA_FILENAME, "wb");

	fwrite(gProducts, sizeof(struct Product), MAX_LENGTH, fileptr);
	fclose(fileptr);
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
	fclose(new_file);
}

FILE* open_File(const char* file_name, const char* for_what)
{
	FILE* fileptr;

	fileptr = fopen(file_name, for_what);
	if (fileptr == NULL)
	{
		printf("Unable to open %s!!!\nPress any button to exit...", file_name);
		getch();
		exit(1);
	}
	if (for_what[0] == 'r')
	{
		fseek(fileptr, 0, SEEK_SET);
	}
	return fileptr;
}

void write_to_File(char* file_name, char* file_input)
{
	FILE* fileptr;
	create_File(file_name);
	fileptr = open_File(file_name, "wb");

	fwrite(file_input, sizeof(file_input[0]), sizeof(file_input), fileptr);
	fclose(fileptr);
}
