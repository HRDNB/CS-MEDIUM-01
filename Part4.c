#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 66
// 比较两个大数的大小
int compare(char *num1, char *num2);
//两个大数相加
void add(char *num1, char *num2, char *result);
// 两个大数相减
void jian(char *num1, char *num2, char *result);
// 两个大数相除
void chu(char *num1, char *num2, char *result);
//两个大数相乘
void cheng(char *num1, char *num2, char *result);

int main(){
    char num1[MAX];
    char num2[MAX];
    char expression[666];
    char caozuofu;
    char result[MAX];
// 输入表达式
    scanf("%[^\n]", expression);  // 使用 scanf 读取整行输入
    // 提取操作数和操作符
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
        caozuofu = expression[i++];
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

    if(caozuofu == '+'){
        add(num1,num2,result);
    } 
    if(caozuofu == '-'){
        jian(num1,num2,result);
    } 
    if(caozuofu == '*'){
        cheng(num1,num2,result);
    }
    if(caozuofu == '/'){
        chu(num1,num2,result);
    }
    //输出结果

    printf("%s",result);

    return 0;
}
//比较
int compare(char *num1, char *num2) {
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
void jian(char *num1, char *num2, char *result) {
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
    if(a == 1 && b != 1){
        add(num1,num2,result);
        int len = strlen(result);
        memmove(result + 1, result, len + 1);
        result[0] = '-';
    }else if(b == 1 && a != 1){
        add(num1,num2,result);
    }else if(a == 1 && b == 1){
        jian(num1,num2,result);
    }else if(a != 1 && b != 1){
    int cmp = compare(num1, num2);

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
        jian(num2, num1, result);
        int len = strlen(result);
        memmove(result + 1, result, len + 1);
        result[0] = '-';
    }
  }
} 
// 实现大数加法
void add(char *num1, char *num2, char *result) {
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
        add(num1, num2, tResult);
        int len = strlen(tResult);
        strcpy(result + 1, tResult);
        result[0] = '-';
        result[len + 1] = '\0';
    } else if ( a == 1 ) {
        // 第一个数是负数，第二个数是正数
        jian(num2, num1, result);
    } else if ( b == 1) {
        // 第一个数是正数，第二个数是负数
        jian(num1, num2, result);
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
//乘法
void cheng(char *num1, char *num2, char *result){
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
	int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 + len2;
    memset(result, '0', maxLen);
    result[maxLen] = '\0';
    
    int i,j;
    for (i = len1 - 1; i >= 0; i--) {
        int c = 0;
        for (j = len2 - 1; j >= 0; j--) {
            int p = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + c;
            c = p / 10;
            result[i + j + 1] = (p % 10) + '0';
        }
        result[i] += c;
    }
    int len = strlen(result);
    i = 0;
    while (i < len && result[i] == '0') {
        i++;
    }
    if (i == len) {
        result[0] = '0';
        result[1] = '\0';
    } else {
        memmove(result, result + i, len - i + 1);
    }
    if((a == 1 && b != 1) || (a != 1 && b == 1)){
        int len = strlen(result);
        memmove(result + 1, result, len + 1);
        result[0] = '-';
    }
}
//除法
void chu(char* num1, char* num2, char* result) {
    int a = 0;
    int b = 0;
    // 判断 num1 是否为负数
    if (num1[0] == '-') {
        a = 1;
        num1++;
    }
    // 判断 num2 是否为负数
    if (num2[0] == '-') {
        b = 1;
        num2++;
    }
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxlen = len1 - len2 + 1;
    memset(result, '0', maxlen);
    result[maxlen] = '\0';
    char remainder[MAX];
    strcpy(remainder, num1);
    int k;
    while (compare(remainder, num2) >= 0) {
        char tresult[MAX];
        jian(remainder, num2, tresult);
        strcpy(remainder, tresult);
        k++;
    }  
	sprintf(result, "%d", k); 
	if(a == 1 || b == 1){
		int len = strlen(result);
        memmove(result + 1, result, len + 1);
        result[0] = '-';
	}
}
