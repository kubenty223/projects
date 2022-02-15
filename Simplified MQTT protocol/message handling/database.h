#ifndef DATABASE_LIB
#define DATABASE_LIB

#include   <sys/types.h>   /* basic system data types */

void print_table(void) ;
void clear_table(void) ;
int search_topic(const char* topic) ;
int make_topic(const char* topic) ;
int search_address(int line,const char* ipaddr);
int make_address(int line,const char* ipaddr);

int add_topic(const char* ipaddr,const char* topic) ;
//int is_empty(char*row [16]);

int is_subscribed(const char* ipaddr,const char* topic) ;

int remove_topic(const char* ipaddr,const char* topic);
char* get_address(char* topic) ;
int get_topics(char* address,char* topics_string);

int check_to_send(char* ip_addr,char*text);
int write_to_send(char*topic,char* text);
void print_all(void);

#endif
