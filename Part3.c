#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 函数声明
void tiqu(char *expression, char *num1, char *num2, char *operator);

int main() {
    char expression[666];
    char num1[66];
    char num2[66];
    char operator;

    // 输入表达式
    printf("请输入表达式:");
    scanf("%[^\n]", expression);  // 使用 scanf 读取整行输入

    // 提取操作数和操作符
    tiqu(expression, num1, num2, &operator);

    // 输出结果
    printf("操作数1:%s\n", num1);
    printf("操作数2:%s\n", num2);
    printf("操作符:%c\n", operator);

    return 0;
}

// 提取操作数和操作符的函数
void tiqu(char *expression, char *num1, char *num2, char *operator) {
    int i = 0;
    int j = 0;
    int len = strlen(expression);
    // 提取第一个操作数
    while ((i < len && isdigit(expression[i])) ) {
        num1[j++] = expression[i++];
    }
    num1[j] = '\0';

    // 跳过空格
    while (i < len && isspace(expression[i])) {
        i++;
    }
    // 提取操作符
    if (i < len) {
        *operator = expression[i++];
    }
    // 跳过空格
    while (i < len && isspace(expression[i])) {
        i++;
    }
    // 处理括号内的负号
    j=0;
    if (i < len && expression[i] == '('){
        i++;  // 跳过左括号
        if (expression[i] == '-') {
            num2[j++] = '-';  // 处理负号
            i++;
        }
    }

    // 提取第二个操作数
    while (i < len && isdigit(expression[i]) ) {
        num2[j++] = expression[i++];
    }
    num2[j] = '\0';


}
