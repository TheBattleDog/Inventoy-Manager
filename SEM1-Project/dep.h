#ifndef DEP_H
#define DEP_H

#define BOOL int
#define TRUE 1
#define FALSE 0
#define PASS_SIZE 100

#define ENTER 13
#define BACKSPACE 8
#define UP_ARROW 72
#define DOWN_ARROW 80
#define ARROW_KEY 224

#ifdef _MSC_VER
#define getch _getch
#else
#define getch getch
#endif

BOOL authenticate_User();
void prompt_User(const char* str);
void print_Heading(const char* heading);
void first_Init(char master_password[PASS_SIZE]);
void encrypt(char* message, int shift, int is_decrypt); // Third parameter is used to check if the function is called from decrypt function. Set it to 1 only when calling from decrypt function.
void decrypt(char* message);
void get_Inventory();
void clear_scr();
void get_password(char password[PASS_SIZE]);
void clear_input();
int get_Ascii(int num);
int to_Num(char ch);
void delay(int milliseconds);
int generate_Rand(int min_range, int max_range);
#endif
