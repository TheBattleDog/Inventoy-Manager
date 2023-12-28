#include <stdio.h>
#include <conio.h>
#include "file_handling.h"
#include "dep.h"

#ifndef F_OK
#define F_OK 0 
#endif

void get_File_Data(const char* file_name, char master_password[100])
{
	FILE* fmaster_password;
	int byte_read;
	if (access(file_name, F_OK) != 0)
	{
		first_Init(master_password);
		decrypt(master_password);
	}
	else
	{
		fmaster_password = open_File(file_name, "rb");
		byte_read = fread(master_password, sizeof(char), sizeof(master_password), fmaster_password);
		if (byte_read > 0)
		{
			master_password[byte_read] = '\0';
			decrypt(master_password);
		}
		else
		{
			printf("ERROR READING FILE");
			fclose(fmaster_password);
			getch();
			exit(1);
		}

	}
}

FILE* create_File(const char* file_name, const char* for_what)
{
	FILE* new_file;

	new_file = fopen(file_name, for_what);

	if (new_file == NULL)
	{
		printf("Unable to create a new file!!\n\
			    Press any key to exit...");
		getch();
		exit(1);
	}

	return new_file;
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
		exit(1);
	}

	return fileptr;
}

void write_to_New_File(char* file_name, char* file_input)
{
	FILE* master_password;
	master_password = create_File(file_name, "wb");

	fprintf(master_password, "%s", file_input);
	fclose(master_password);
}
