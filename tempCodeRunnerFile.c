#include <stdio.h>
#include <stdlib.h>
char* my_str_copy(char* destination, const char* source){
    int index = 0;
    while(1){
        
        destination[index] = source[index];
        if(source[index] == '\0'){
            return destination;
        }
    }
}
int main(void){
    char str[20] = "hello";
    char str_2[20] = "bello";
    my_str_copy(str_2,str);
    printf("%s", str);
    printf("%s", str);

    
    return 0;
}
