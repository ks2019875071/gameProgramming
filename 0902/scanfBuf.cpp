#include <stdio.h>

int main()
{
        char string[20];
        char c;
		
		printf("문자열 입력");
        fgets(string, sizeof(string), stdin);
		//이 사이에 입력버퍼를 비우는 코드를 쓰지 않으면 
		//문자열(string)만 입력받고 끝남.

		printf("문자 입력");
        scanf(" %c", &c);

        printf("%s\n", string);
        printf("!!%c!!\n", c);

        return 0;
}
