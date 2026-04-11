#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	// TODO: 在这里添加你的代码
    for (int i = 0; source[i] != '\0'; i++) {
        destination[i] = source[i];
    }
    destination[100] = '\0'; // 确保目标字符串以 null结尾
    
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}