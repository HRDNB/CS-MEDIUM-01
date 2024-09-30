#include <stdio.h>
#define MAX 128  // 定义最大位数为128位

int main() {
    char BigNumber[MAX + 1];  // 定义一个字符数组来存储大数，+1是为了存储字符串结束符'\0'
    printf("请输入一个不超过128位的正整数: ");
    scanf("%128s", BigNumber);  // 读取输入的数字，最多读取128个字符

    // 输出输入的数字以验证输入是否正确
    printf("您输入的数字是: %s\n", BigNumber);

    return 0;
}
