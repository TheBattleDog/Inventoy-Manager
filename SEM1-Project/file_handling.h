#ifndef _FILE_HANDLING_
#define _FILE_HANDLING_
#include "dep.h"
void get_File_Data(const char* file_name, char data[MAX_LENGTH]);
void load_Inventory_Data(const char* file_name);
void create_File(const char* file_name);
FILE* open_File(const char* file_name, const char* for_what);
void write_to_New_File(char* file_name, char* file_input);
#endif
