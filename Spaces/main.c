#include <stdio.h>
#include <stdlib.h>

#define N 100
#define STR_LEN 500

void clearMemory(char** str, int n) {
    int i;
    for(i = 0; i < n; i++) {
        free(str[i]);
    }
    
    free(str);
}

char* tr(char* str) {
    char* newStr = calloc(STR_LEN, sizeof(char));
    int i = 0; // итератор старой строки
    int j = 0; // итератор новой строки
    unsigned int wasSpace = 0;
    while( str[i] != '\0' ) {
        if(str[i] != ' ') {
            newStr[j] = str[i];
            wasSpace = 0;
            i++;
            j++;
        } else {
            if(!wasSpace) {
                newStr[j] = str[i];
                wasSpace = 1;
                i++;
                j++;
            } else {
                i++;
            }

        }
    }
    
    return newStr;
}

char** trim(char** str, int n) {
    
    char** nStr = calloc(N, sizeof(char*));
    int i;
    
    for( i = 0; i<n; n++)
        if(str[i] == NULL) {
            return NULL;
        } else {
            nStr[i] = tr(str[i]);
        }
    
    return nStr;
}

int main(void)
{
    //выделяем память
    char** str = calloc(N, sizeof(char*));
    
    if(str == NULL) {
        //free(str);
        printf("[error]");
        return 0;
    }
    
    size_t i = 0;
    for( ; i < N; i++) {
        str[i] = calloc(STR_LEN, sizeof(char));
    }
    
    int k = 0;
    int status = 0;
    
    //считываем строки
    while((status = scanf("%s", str[k])) != EOF) {
        if(status == 1) {
            
        } else {
            printf("[error]");
        }
        k++;
    }
    
    //выделяем новый массив, в который попадают обработанные строки
    char** new_addr = trim(str, k);
    
    if(new_addr == NULL) {
        printf("[error]");
    }
    
    
    //печатаем
    
    for(i = 0; i < k; i++) {
        printf("%s", str[i]);
    }

    clearMemory(new_addr, k);
    clearMemory(str, k);
    
    return 0;
}
