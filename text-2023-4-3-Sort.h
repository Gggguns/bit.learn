#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Size 10

//��������
void InsertSort(int* str, int size);

//ϣ������
void ShellSort(int* str, int size);

//ѡ������
void SelectSort(int* str, int size);

//������
void HeapSort(int* str, int n);

//ð������
void BubbleSort(int* str, int size);

//��������
void QuickSort(int* str, int left, int right);

//�鲢����

//������������
void Swap(int* p1, int* p2);

//��ѵ����µ���
void AdjustDown(int* str, int end,int parent);

//��������ıȽϲ���
void TextOP();

//��ӡ����
void PrintfArray(int* str, int size);