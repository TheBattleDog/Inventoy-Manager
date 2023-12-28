#ifndef _FILE_HANDLING_
#define _FILE_HANDLING_
void get_File_Data(const char* file_name, char master_password[100]);
FILE* create_File(const char* file_name, const char* for_what);
FILE* open_File(const char* file_name, const char* for_what);
void write_to_New_File(char* file_name, char* file_input);
#endif
