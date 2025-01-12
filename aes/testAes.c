#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� aes.h �а�����������غ���������
#include "aes.h"

// ���Ժ���
int main() {
    // �����ܵ�����
    //const char *original_plaintext = "Hello, AES!";

    // �洢�û����������
    char original_plaintext[1024];
    printf("������Ҫ���ܵ�����: ");
    if (fgets(original_plaintext, sizeof(original_plaintext), stdin) == NULL) {
        printf("��ȡ����ʧ��\n");
        return 1;
    }
    // �Ƴ����з�
    size_t original_len = strlen(original_plaintext);
    if (original_plaintext[original_len - 1] == '\n') {
        original_plaintext[original_len - 1] = '\0';
    }


    // ��������ĳ���
    size_t plaintext_len = original_len;
    while (plaintext_len % 16!= 0) {
        plaintext_len++;
    }

    // �����ڴ����ڴ洢���������
    unsigned char *plaintext = (unsigned char*)malloc(plaintext_len);
    if (plaintext == NULL) {
        printf("�ڴ����ʧ��\n");
        return 1;
    }

    // ����ԭʼ���ĵ��·�����ڴ�
    memcpy(plaintext, original_plaintext, original_len);
    // ��� 0
    for (size_t i = original_len; i < plaintext_len; i++) {
        plaintext[i] = 0;
    }

    // ��Կ�����ȱ���Ϊ 16
    unsigned char key[] = "This is a 16 key";

    // ��̬�����ڴ����ڴ洢���ܺ������
    unsigned char *ciphertext = (unsigned char*)malloc(plaintext_len);
    if (ciphertext == NULL) {
        printf("�ڴ����ʧ��\n");
        free(plaintext);
        return 1;
    }
    memcpy(ciphertext, plaintext, plaintext_len);

    // ���� aes �������м���
    aes(ciphertext, plaintext_len, key);

    // ������ܺ������
    printf("���ܺ������: ");
    for (size_t i = 0; i < plaintext_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // ��̬�����ڴ����ڴ洢���ܺ������
    unsigned char *decrypted_text = (unsigned char*)malloc(plaintext_len);
    if (decrypted_text == NULL) {
        printf("�ڴ����ʧ��\n");
        free(ciphertext);
        free(plaintext);
        return 1;
    }
    memcpy(decrypted_text, ciphertext, plaintext_len);

    // ���� deAes �������н���
    deAes(decrypted_text, plaintext_len, key);

    // ������ܺ������
    printf("���ܺ������: ");
    for (size_t i = 0; i < plaintext_len; i++) {
        if (decrypted_text[i]!= 0) {
            printf("%c", decrypted_text[i]);
        }
    }
    printf("\n");

    // �ͷŶ�̬������ڴ�
    free(plaintext);
    free(ciphertext);
    free(decrypted_text);

    return 0;
}