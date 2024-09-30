#include <stdio.h>
#include <string.h>

#define MAX 40  // 假设最大位数为40

// 实现大数加法
void addBN(char *num1, char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen;
    if (len1 > len2) {
        maxLen = len1;
    } else {
        maxLen = len2;
    }

    // 初始化结果数组
    memset(result, '0', maxLen + 1);
    result[maxLen + 1] = '\0';  // 字符串结束符

    int c = 0;
    int i, j, k;

    // 从最低位开始逐位相加
    for (i = len1 - 1, j = len2 - 1, k = maxLen; k >= 0; i--, j--, k--) {
        int digit1 = 0;
        int digit2 = 0;
        //从字符变成数 
        if (i >= 0) {
            digit1 = num1[i] - '0';
        }

        if (j >= 0) {
            digit2 = num2[j] - '0';
        }

        int sum = digit1 + digit2 + c;  // 当前位的和

        c = sum / 10;  // 计算进位
        result[k] = (sum % 10) + '0';  // 当前位的结果
    }

    // 如果最高位有进位，需要处理
    if (c > 0) {
        result[0] = c + '0';  // 最高位设置为进位值
    } else {
        // 如果没有进位，结果数组的第一位是'0'，需要去掉
        memmove(result, result + 1, maxLen + 1);
    }
}

int main() {
    char num1[MAX + 1];
    char num2[MAX + 1];
    char result[MAX + 2];  // +2 因为可能会有进位

    // 输入两个大数
    printf("输入第一个大数: ");
    scanf("%s", num1);
    printf("输入第二个大数: ");
    scanf("%s", num2);

    // 调用函数进行加法运算
    addBN(num1, num2, result);

    // 输出结果
    printf("Sum: %s\n", result);

    return 0;
}


