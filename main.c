//
//  main.c
//  FileEncrypter
//

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

char    *GetStartingDirectory(void);
char    *GetKey(void);
void    EncryptFiles(List *files, char *key);
void    EncryptFile(char *path, char *key);
char    *Encrypt(char *msg, int size, char *key);
void    GetFiles(char *directory, List *files);
void    PrintFileList(List *files);

int main(int argc, const char * argv[]) {
    char    *directory = NULL;
    List    *files = NULL;
    char    *key = NULL;
    directory = GetStartingDirectory();
    files = list_init();
    key = GetKey();
    
    GetFiles(directory, files);
    PrintFileList(files);
    EncryptFiles(files, key);
    return 0;
}

char* GetStartingDirectory() {
    char    *input = NULL;
    int     len = 0;
    printf("Enter the Full Path of the Starting Directory:\n");
    input = malloc(sizeof(char) * 255);
    fgets(input, 255, stdin);
    len = (int)strlen(input);
    if(input[len - 1] == '\n') {
        input[len - 1] = '\0';  // Replace \n with null terminator
    }
    return input;
}

char* GetKey() {
    char    *input = NULL;
    int     len = 0;
    printf("Enter the encryption key you wish the use:\n");
    input = malloc(sizeof(char) * 1024);
    fgets(input, 1024, stdin);
    len = (int)strlen(input);
    if(len >= 1023) {
        printf("Max Length for Key Exceeded\n");
        return GetKey();
    }
    if(input[len - 1] == '\n') {
        input[len - 1] = '\0';  // Replace \n with null terminator
    }
    return input;
}

void GetFiles(char *directory, List *files) {
    DIR             *dp;
    struct dirent   *ep;
    dp = opendir(directory);
    if(dp == NULL) {
        return;
    }
    while((ep = readdir(dp))) {
        if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) {
            continue;
        }
        char    *path = NULL;
        int     path_size;
        path_size = (int)strlen(directory) + (int)strlen(ep->d_name) + 2;
        path = malloc(sizeof(char) * path_size);
        strcpy(path, directory);
        strcat(path, "/");
        strcat(path, ep->d_name);
        if(ep->d_type == 8) {
            list_Push(files, path);
        }
        else if(ep->d_type == 4) {
            GetFiles(path, files);
        }
    }
}

void EncryptFiles(List *files, char *key) {
    Node    *files_node = NULL;
    char    *file = NULL;
    files_node = files->head;
    while(files_node) {
        file = files_node->data;
        EncryptFile(file, key);
        files_node = files_node->next;
    }
}

void EncryptFile(char *path, char *key) {
    char    *buff = NULL;
    int     size = 0;
    FILE    *readp = NULL;
    char    *encrypted = NULL;
    
    readp = fopen(path, "rb");
    if(readp == NULL) {
        perror("Error Opening File");
        return;
    }
    fseek(readp, 0, SEEK_END);
    size = (int)ftell(readp);
    rewind(readp);
    buff = malloc(sizeof(char) * size);
    if(buff == NULL) {
        perror("Malloc Error");
        return;
    }
    fread(buff, size, 1, readp);
    fclose(readp);
    
    printf("Encrypting  %s\n", path);
    encrypted = Encrypt(buff, size, key);
    
    FILE    *writep = NULL;
    writep = fopen(path, "wb");
    fwrite(encrypted, size, 1, writep);
    fclose(writep);
}

char *Encrypt(char *msg, int size, char *key) {
    int     len_msg = size;
    int     len_key = (int)strlen(key);
    char    *encrypted = NULL;
    encrypted = malloc(sizeof(char) * (len_msg + 1));
    for(int i=0; i<len_msg; i++) {
        encrypted[i] = msg[i] ^ key[i % len_key];
    }
    return encrypted;
}

void PrintFileList(List *files) {
    Node    *files_node = NULL;
    char    *file = NULL;
    files_node = files->head;
    while(files_node) {
        file = files_node->data;
        printf("Found File  %s\n", file);
        files_node = files_node->next;
    }
}

