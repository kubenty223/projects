#include <stdio.h>
#include <stdlib.h>
#include "stdio.h"
#include "string.h"

#define LETTERS 16
#define TOPICS 8
#define CLIENTS 4

#include "database.h"

char database[TOPICS][CLIENTS+1][LETTERS];
char to_send [CLIENTS+1][LETTERS];
char message[255];

FILE* fptr;


void read_database(){
	fptr = fopen("database.bin","rb");
	fread(database,sizeof(database),1,fptr);
	fclose(fptr);
}

void save_database(){
	fptr = fopen("database.bin","wb");
	fwrite(database,sizeof(database),1,fptr);
	fclose(fptr);
}
void read_all(){
	fptr = fopen("database.bin","rb");
	fread(database,sizeof(database),1,fptr);
	fread(to_send,sizeof(to_send),1,fptr);
	fread(message,sizeof(message),1,fptr);
	fclose(fptr);
}
void save_all(){
	fptr = fopen("database.bin","wb");
	fwrite(database,sizeof(database),1,fptr);
	fwrite(to_send,sizeof(to_send),1,fptr);
	fwrite(message,sizeof(message),1,fptr);
	fclose(fptr);
}

void print_table(void) {
    for(int i=0; i<TOPICS; i++) {
        for(int j=0; j<CLIENTS+1; j++) {
            printf("%s\t",database[i][j]);
        }
        printf("\n\r");
    }
    printf("\n\r");
}
void clear_table(void) {
    for(int i=0; i<TOPICS; i++) {
        for(int j=0; j<CLIENTS+1; j++) {
            for(int k=0; k<LETTERS; k++) {
                database[i][j][k]=0;
            }
        }
    }
	for(int j=0; j<CLIENTS+1; j++) {
		for(int k=0; k<LETTERS; k++) {
			to_send[j][k]=0;
		}
	}
	
	for(int i=0;i<255;i++){
		message[i]=0;
	}
	save_all();
}
int search_topic(const char* topic) {
    for(int i=0; i<TOPICS; i++) {
        if(!strcmp(database[i][0],topic)) {
            return i;
        }
    }
    //not found
    return -1;
}
int make_topic(const char* topic) {

    int result=search_topic(topic);
    if(result!=-1)
        return result;
    //if not found
    for(int i=0; i<TOPICS; i++) {
        if(database[i][0][0]==0) {
            strcpy(database[i][0],topic);
            return i;
        }
    }
	
    //error
    return -1;
}
int search_address(int line,const char* ipaddr) {
    for(int i=1; i<CLIENTS+1; i++) {
        if(!strcmp(database[line][i],ipaddr)) {
            return i;
        }
    }
    //not found
    return -1;
}
int make_address(int line,const char* ipaddr) {

    int result=search_address(line,ipaddr);
    if(result!=-1)
        return result;
    //if not found
    for(int i=1; i<CLIENTS+1; i++) {
        if(database[line][i][0]==0) {
            strcpy(database[line][i],ipaddr);
            return i;
        }
    }
    //error
    return -1;
}

int is_empty(int line) {
    for(int i=1; i<CLIENTS+1; i++) {
        if(database[line][i][0]!=0) {
            return 0;
        }
    }
    return 1;
}
int is_empty2(void) {
    for(int i=1; i<CLIENTS+1; i++) {
        if(to_send[i][0]!=0) {
            return 0;
        }
    }
    return 1;
}

int is_subscribed(const char* ipaddr,const char* topic) {
    int line=search_topic(topic);
    if(line==-1)
        return -1; //not found topic
    int column=search_address(line,ipaddr);
    if(column==-1)
        return -2; //not found address

    return 1;//found topic and address
}

int add_topic(const char* ipaddr,const char* topic) {
	read_database();
    int line=make_topic(topic);
    make_address(line,ipaddr);
	save_database();
    return 0;
}

int remove_topic(const char* ipaddr,const char* topic) {
	read_database();
    int line=search_topic(topic);
    if(line==-1)
        return -1; //not found topic
    int column=search_address(line,ipaddr);
    if(column==-1)
        return -2; //not found address

    for(int i=0; i<LETTERS; i++) {
        database[line][column][i]=0;
    }
    if(is_empty(line)) {
        for(int i=0; i<LETTERS; i++) {
            database[line][0][i]=0;
        }
    }
	save_database();
    return 0;//removed topic
}

char* get_address(char* topic) { //jeśli zwróci topic, to znaczy że wszystkie adresy zostały zwrócone
	read_database();
    static int client_number=1;
    int line=search_topic(topic);
    if(line<0)
        return topic;
    while(1) {
        if(client_number<CLIENTS+1) {
            if(database[line][client_number][0]!=0) {
                client_number++;
                return database[line][client_number-1];               
            } else {
                client_number++;
            }

        } else {
            break;
        }
    }
    client_number=1;
    return database[line][0];
}
int get_topics(char* address,char* topics_string){
	read_database();
    int result=0;
    int pos=0;
    for(int i=0;i<TOPICS;i++){
        if(database[i][0][0]!=0){
            if(search_address(i,address)!=-1){
                pos+=sprintf(&(topics_string[pos]),"%s\n\r",database[i][0]);
                result++;
            }
        }
    }
    return result;
}
int check_to_send(char* ip_addr,char*text){
	int result=0;
	read_all();	
	if(to_send[0][0]!=0){
		while(1) {
			char address[16];
			strcpy(address,get_address(to_send[0]));
			if(!strcmp(address,to_send[0])) {				
				break; //koniec adresów
			}
			if(!strcmp(address,ip_addr)){				
				for(int i=1;i<CLIENTS+1;i++){
					if(strcmp(ip_addr,to_send[i])==0){
						result=1;
						to_send[i][0]=0;
						
						if(is_empty2()){
							to_send[0][0]=0;
						}
					}
				}				
				strcpy(text,message);				
				break;				
			}
		}	
		save_all();			
	}	
	return result;
}
int write_to_send(char*topic,char*text){	
	read_all();
	if(to_send[0][0]!=0) return 1;
	
	for(int i=0;i<TOPICS;i++){
		if(strcmp(database[i][0],topic)==0){
			memcpy ( to_send, database[i], sizeof(to_send) );
		}
	}
	strcpy(message,text);
	save_all();	
	return 0;
}
	
void print_all(void){
	printf("tablica:\n\r");
	read_all();
	print_table();
	printf("kolejka do wysłania:\n\r");
	for(int j=0; j<CLIENTS+1; j++) {
		printf("%s\t",to_send[j]);
	}
	printf("\n\r");
	printf("tresc wiadomosci:\n\r");
	printf("%s\n\r",message);
}
	
