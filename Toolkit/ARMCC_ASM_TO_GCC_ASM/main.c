#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GNUStartupASMGenerator.h"

#define VECTOR_START_TOKEN "\n__Vectors"

static NVIC_VectorItem_T VectorTable;
char IRQHandler[256];
char Comment[256];


static size_t GetFileSize(FILE* fp){
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}

int main(int argc, char** argv){
    
    VectorTable.prev = VectorTable.next = &VectorTable;
    
    if(argc<3){
        printf("usage: %s <ARMCC_Startup_ASM.s> <GCC_Startup_ASM.s>\n", argv[0]);
        return 1;
    }
    
    FILE* fp = fopen(argv[1], "r");
    if(!fp){
        fprintf(stderr, "Can not open %s\n", argv[1]);
        return 1;
    }
    size_t file_size = GetFileSize(fp);
    char* buffer = malloc(file_size);
    fread(buffer, file_size, 1, fp);
    fclose(fp);
    
    char* VectorStart_P = strstr(buffer, VECTOR_START_TOKEN);
    if(!VectorStart_P){
        fprintf(stderr, "Can not find Vector start token: %s\n", VECTOR_START_TOKEN);
        return 1;
    }
    
    VectorStart_P+=strlen(VECTOR_START_TOKEN);
    if(strstr(VectorStart_P, VECTOR_START_TOKEN)==0){
        fprintf(stderr, "Can not find Vector start token: %s\n", VECTOR_START_TOKEN);
        return 1;
    }
    
    VectorStart_P+=strlen(VECTOR_START_TOKEN);
    char * p = VectorStart_P;
    while(*p!='\r' && *p!='\n'){
        p++;
    }
    p+=1;
    
    char* start = 0;
    do {
        p = strstr(p, "DCD");
        if(!p){
            break;
        }
        p+=3;
        while(isspace(*p)){
            p++;
        }
        start = p;
        while(!isspace(*p)){
            p++;
        }
        memcpy(IRQHandler, start, p-start);
        IRQHandler[p-start]='\0';
        start = 0;
        while(*p!='\n' && *p!='\r'){
            if(*p==';'){
                p = p+1;
                while(isspace(*p)){
                    p++;
                }
                start = p;
                break;
            }
            p++;
        }
        if(start){
            while(*p!='\r' && *p!='\n'){
                p++;
            }
            memcpy(Comment, start, p-start);
            Comment[p-start]='\0';
        }else{
            Comment[0]='\0';
        }
        
        NVIC_Vector_AddItem(&VectorTable, IRQHandler, Comment);
        
    }while(1);
    
    NVIC_VectorItem_T * node;
    for(node = VectorTable.next; node!=&VectorTable; node=node->next){
        printf("%s(%s)\n", node->IRQHandler, node->Comment);
    }
    
    
    if(argc==3){
        GNUStartupASMGenerator_Generate(&VectorTable, "cortex-m3", 0, argv[2]);
    }else if(argc==4){
        GNUStartupASMGenerator_Generate(&VectorTable, argv[2], 0, argv[3]);
    }else if(argc==5){
        GNUStartupASMGenerator_Generate(&VectorTable, argv[2], argv[3], argv[4]);
    }
    
    NVIC_Vector_Release(&VectorTable);
    
    return 0;
}