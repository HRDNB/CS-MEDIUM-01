#include <stdio.h>
#include <string.h>

#define MAX 40  // �������λ��Ϊ40

// ʵ�ִ����ӷ�
void addBN(char *num1, char *num2, char *result) {
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

    int c = 0;
    int i, j, k;

    // �����λ��ʼ��λ���
    for (i = len1 - 1, j = len2 - 1, k = maxLen; k >= 0; i--, j--, k--) {
        int digit1 = 0;
        int digit2 = 0;
        //���ַ������ 
        if (i >= 0) {
            digit1 = num1[i] - '0';
        }

        if (j >= 0) {
            digit2 = num2[j] - '0';
        }

        int sum = digit1 + digit2 + c;  // ��ǰλ�ĺ�

        c = sum / 10;  // �����λ
        result[k] = (sum % 10) + '0';  // ��ǰλ�Ľ��
    }

    // ������λ�н�λ����Ҫ����
    if (c > 0) {
        result[0] = c + '0';  // ���λ����Ϊ��λֵ
    } else {
        // ���û�н�λ���������ĵ�һλ��'0'����Ҫȥ��
        memmove(result, result + 1, maxLen + 1);
    }
}

int main() {
    char num1[MAX + 1];
    char num2[MAX + 1];
    char result[MAX + 2];  // +2 ��Ϊ���ܻ��н�λ

    // ������������
    printf("�����һ������: ");
    scanf("%s", num1);
    printf("����ڶ�������: ");
    scanf("%s", num2);

    // ���ú������мӷ�����
    addBN(num1, num2, result);

    // ������
    printf("Sum: %s\n", result);

    return 0;
}


