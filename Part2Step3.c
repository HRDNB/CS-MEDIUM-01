#include <stdio.h>
#include <string.h>
#define MAX 40  // 假设最大位数为40
// 比较两个大数的大小
int compareBN(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 > len2) {
        return 1;
    } else if (len1 < len2) {
        return -1;
    } else {
    	int i;
        for (i = 0; i < len1; i++) {
            if (num1[i] > num2[i]) {
                return 1;
            } else if (num1[i] < num2[i]) {
                return -1;
            }
        }
        return 0;  
    }
}

// 实现大数减法
void jianBN(char *num1, char *num2, char *result) {
    int cmp = compareBN(num1, num2);

    if (cmp == 0) {
        // 两个数相等，结果为0
        strcpy(result, "0");
    } else if (cmp > 0) {
        // num1 > num2
        int len1 = strlen(num1);
        int len2 = strlen(num2);
        int maxLen ;
        if (len1 > len2) {
        maxLen = len1;
    } else {
        maxLen = len2;
    }

        // 初始化结果数组
        memset(result, '0', maxLen );
        result[maxLen + 1] = '\0';  // 字符串结束符

        int borrow = 0;//借位 
        int i, j, k;

        // 从最低位开始逐位相减
        for (i = len1 - 1, j = len2 - 1, k = maxLen ; k >= 0; i--, j--, k--) {
            int digit1 = 0;
            int digit2 = 0;
			if (i >= 0) {
                digit1 = num1[i] - '0';
            }
            if (j >= 0) {
                digit2 = num2[j] - '0';
            }
            int jian = digit1 - digit2 - borrow;

            if (jian < 0) {
                jian += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result[k] = jian + '0';
        }
        // 去掉前导零
        int len = strlen(result);
        int start = 0;
        while (result[start] == '0' && start < len - 1) {
            start++;
        }
        memmove(result, result + start, len - start + 1);
        
    } else {
        // num1 < num2
        jianBN(num2, num1, result);
        int len = strlen(result);
        memmove(result + 1, result, len + 1);
        result[0] = '-';
    }
} 
// 实现大数加法
void addBN(char *num1, char *num2, char *result) {
    int a = 0;
    int b = 0;

    // 判断 num1 是否为负数
    if (num1[0] == '-') {
        a = 1;
        num1++; // 指向后面的部分以丢掉负号 
    }

    // 判断 num2 是否为负数
    if (num2[0] == '-') {
        b = 1;
        num2++; // 指向后面的部分以丢掉负号
    }

    if ( a == 1 && b == 1 ) {
        // 两个负数相加
        char tResult[MAX];
        addBN(num1, num2, tResult);
        int len = strlen(tResult);
        strcpy(result + 1, tResult);
        result[0] = '-';
        result[len + 1] = '\0';
    } else if ( a == 1 ) {
        // 第一个数是负数，第二个数是正数
        jianBN(num2, num1, result);
    } else if ( b == 1) {
        // 第一个数是正数，第二个数是负数
        jianBN(num1, num2, result);
    } else {
        // 两个正数相加
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

        int carry = 0;
        int i, j, k;

        // 从最低位开始逐位相加
        for (i = len1 - 1, j = len2 - 1, k = maxLen; k >= 0; i--, j--, k--) {
            int digit1 = 0;
            int digit2 = 0;
            if (i >= 0) {
                digit1 = num1[i] - '0';
            }
            if (j >= 0) {
                digit2 = num2[j] - '0';
            }
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result[k] = (sum % 10) + '0';
        }

        // 如果最高位有进位，需要处理
        if (carry > 0) {
            result[0] = carry + '0';
        } else {
            // 如果没有进位，结果数组的第一位是'0'，需要去掉
            memmove(result, result + 1, maxLen + 1);
        }
    }
}


int main() {
    char num1[MAX + 1];
    char num2[MAX + 1];
    char result[MAX + 2];  // +2 因为可能会有进位

    // 输入两个大数
    printf("输入第一个number: ");
    scanf("%s", num1);
    printf("输入第二个number: ");
    scanf("%s", num2);

    // 调用函数进行加法运算
    addBN(num1, num2, result);

    // 输出结果
    printf("两数之和为: %s\n", result);

    return 0;
}






