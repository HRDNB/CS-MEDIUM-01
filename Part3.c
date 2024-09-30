#include <stdio.h>
#include <string.h>
#include <ctype.h>

// ��������
void tiqu(char *expression, char *num1, char *num2, char *operator);

int main() {
    char expression[666];
    char num1[66];
    char num2[66];
    char operator;

    // ������ʽ
    printf("��������ʽ:");
    scanf("%[^\n]", expression);  // ʹ�� scanf ��ȡ��������

    // ��ȡ�������Ͳ�����
    tiqu(expression, num1, num2, &operator);

    // ������
    printf("������1:%s\n", num1);
    printf("������2:%s\n", num2);
    printf("������:%c\n", operator);

    return 0;
}

// ��ȡ�������Ͳ������ĺ���
void tiqu(char *expression, char *num1, char *num2, char *operator) {
    int i = 0;
    int j = 0;
    int len = strlen(expression);
    // ��ȡ��һ��������
    while ((i < len && isdigit(expression[i])) ) {
        num1[j++] = expression[i++];
    }
    num1[j] = '\0';

    // �����ո�
    while (i < len && isspace(expression[i])) {
        i++;
    }
    // ��ȡ������
    if (i < len) {
        *operator = expression[i++];
    }
    // �����ո�
    while (i < len && isspace(expression[i])) {
        i++;
    }
    // ���������ڵĸ���
    j=0;
    if (i < len && expression[i] == '('){
        i++;  // ����������
        if (expression[i] == '-') {
            num2[j++] = '-';  // ������
            i++;
        }
    }

    // ��ȡ�ڶ���������
    while (i < len && isdigit(expression[i]) ) {
        num2[j++] = expression[i++];
    }
    num2[j] = '\0';


}
