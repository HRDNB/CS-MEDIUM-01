#include <stdio.h>
#include <string.h>
#define MAX 40  // �������λ��Ϊ40
// �Ƚ����������Ĵ�С
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

// ʵ�ִ�������
void jianBN(char *num1, char *num2, char *result) {
    int cmp = compareBN(num1, num2);

    if (cmp == 0) {
        // ��������ȣ����Ϊ0
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

        // ��ʼ���������
        memset(result, '0', maxLen );
        result[maxLen + 1] = '\0';  // �ַ���������

        int borrow = 0;//��λ 
        int i, j, k;

        // �����λ��ʼ��λ���
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
        // ȥ��ǰ����
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
// ʵ�ִ����ӷ�
void addBN(char *num1, char *num2, char *result) {
    int a = 0;
    int b = 0;

    // �ж� num1 �Ƿ�Ϊ����
    if (num1[0] == '-') {
        a = 1;
        num1++; // ָ�����Ĳ����Զ������� 
    }

    // �ж� num2 �Ƿ�Ϊ����
    if (num2[0] == '-') {
        b = 1;
        num2++; // ָ�����Ĳ����Զ�������
    }

    if ( a == 1 && b == 1 ) {
        // �����������
        char tResult[MAX];
        addBN(num1, num2, tResult);
        int len = strlen(tResult);
        strcpy(result + 1, tResult);
        result[0] = '-';
        result[len + 1] = '\0';
    } else if ( a == 1 ) {
        // ��һ�����Ǹ������ڶ�����������
        jianBN(num2, num1, result);
    } else if ( b == 1) {
        // ��һ�������������ڶ������Ǹ���
        jianBN(num1, num2, result);
    } else {
        // �����������
        int len1 = strlen(num1);
        int len2 = strlen(num2);
        int maxLen;
    if (len1 > len2) {
        maxLen = len1;
    } else {
        maxLen = len2;
    }

        // ��ʼ���������
        memset(result, '0', maxLen + 1);
        result[maxLen + 1] = '\0';  // �ַ���������

        int carry = 0;
        int i, j, k;

        // �����λ��ʼ��λ���
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

        // ������λ�н�λ����Ҫ����
        if (carry > 0) {
            result[0] = carry + '0';
        } else {
            // ���û�н�λ���������ĵ�һλ��'0'����Ҫȥ��
            memmove(result, result + 1, maxLen + 1);
        }
    }
}


int main() {
    char num1[MAX + 1];
    char num2[MAX + 1];
    char result[MAX + 2];  // +2 ��Ϊ���ܻ��н�λ

    // ������������
    printf("�����һ��number: ");
    scanf("%s", num1);
    printf("����ڶ���number: ");
    scanf("%s", num2);

    // ���ú������мӷ�����
    addBN(num1, num2, result);

    // ������
    printf("����֮��Ϊ: %s\n", result);

    return 0;
}






