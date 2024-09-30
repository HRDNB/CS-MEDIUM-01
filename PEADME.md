# 微光招新第四题

## Part 1 理解大数运算

### 1.为什么要使用字符数组来表示大数？

在处理非常大的整数（大数）时，传统的整型数据类型（如 `int`, `long`, `long long` 等）可能会变得不够用。因为这些数据类型通常有固定的存储大小和范围。此外，使用字符数组表示大数更易读，简化了大数运算，通过实现基本的算术算法（如小学里的竖式计算），可以方便地进行复杂的大数运算。

### 2.如何处理大数运算中的进位和借位问题？

可以使用一个额外的变量（如 `carry`）来记录进位值。初始时，将该变量设置为0。在逐位相加或者相减的过程中，如果和大于或等于10，则将 `carry` 设置为1（或相应的进位值），并从和中减去10（或相应的基数）。在处理下一位时，将 `carry` 加到该位的和上。

### 3.如何处理负数

将字符串第一个位置设置为‘-’，表示为负数。在计算中，我通常会先将'-'去掉，面对一负一正或者一正一负或者两正或者两负的情况，用if-else语句进行分类讨论，一正减一负将其转化为加法，再入一负减一正先变为加法，再给结果加上负号，诸如此类。



***考虑到文本长度，以下代码运行截图均已放入一个单独的文件夹，方便查阅***

## Part 2 初步实现大数运算

### Step 1 尝试存储大数

```c
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
```

### Step 2 实现大数加法

```c
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
```

### Step 3 实现大数加法（处理负数）

```c
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
```

## Part 3 从表达式中提取操作数和操作符

```c
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
```

## Part 4 封装大数四则运算

```c
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
    printf("please printf");
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

    printf("sum=%s",result);

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
```

**==小感想：哇，这一节绝对是我打过的代码最长的一节，学习路程也是比较坎坷，但无论怎样还是攻克下来了，我觉得出题人也很厉害，做到了循序渐进，看到Part4时有一种恍然大悟的感觉，这不就是前几部分的结合起来，也同时让我更加熟练掌握大数运算这门知识，非常感谢（鞠躬），此外还要感谢up主麦克老师讲算法，真的讲得好，最后也祝自己越来越好==**
