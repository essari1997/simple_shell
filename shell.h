#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_S 1024
#define WRITE_S 1024
#define FLUSH -1

/* for command chaining */
#define CMD_N	0
#define CMD_O	1
#define CMD_A	2
#define CMD_C	3

/* for convert_number() */
#define CONVERT_L	1
#define CONVERT_U	2

/* 1 if using system getline() */
#define USE_G 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_b(info_t *);
void find_c(info_t *);
void fork_c(info_t *);

/* toem_parser.c */
int is_c(info_t *, char *);
char *dup_c(char *, int, int);
char *find_p(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_error.c */
void _eput(char *);
int _eputc(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string1.c */
int _strl(char *);
int _strc(char *, char *);
char *starts(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string2.c */
char *_strcp(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exit.c */
char *_strnc(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_token.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc1.c */
char *_mem(char *, char, unsigned int);
void ffree(char **);
void *_alloc(void *, unsigned int, unsigned int);

/* toem_memoire.c */
int bfree(void **);

/* toem_atoi.c */
int inte(info_t *);
int is_delim(char, char *);
int _isa(int);
int _atoi(char *);

/* toem_errors1.c */
int _err(char *);
void print_e(info_t *, char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/* toem_builtin1.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myh(info_t *);

/* toem_builtin2.c */
int _myhi(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_i(info_t *);
int _getline(info_t *, char **, size_t *);
void siginth(int);

/* toem_getinfo.c */
void clear_i(info_t *);
void set_i(info_t *, char **);
void free_i(info_t *, int);

/* toem_env.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_h(info_t *info);
int write_h(info_t *info);
int read_h(info_t *info);
int build_h(info_t *info, char *buf, int linecount);
int renumber_h(info_t *info);

/* toem_list1.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_s(const list_t *);
int delete_node(list_t **, unsigned int);
void free_list(list_t **);

/* toem_list2.c */
size_t list_len(const list_t *);
char **list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_starts(list_t *, char *, char);
ssize_t _get(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

