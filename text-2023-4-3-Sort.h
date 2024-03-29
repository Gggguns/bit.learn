#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define Size 20

//插入排序
void InsertSort(int* str, int size);

//希尔排序
void ShellSort(int* str, int size);

//选择排序
void SelectSort(int* str, int size);

//堆排序
void HeapSort(int* str, int n);

//冒泡排序
void BubbleSort(int* str, int size);

//快速排序
void QuickSort(int* str, int left, int right);

//归并排序
void MergeSort(int* str, int n);

//交换两个数据
void Swap(int* p1, int* p2);

//大堆的向下调整
void AdjustDown(int* str, int end,int parent);

//各个排序的比较测试
void TextOP();

//打印数组
void PrintfArray(int* str, int size);

//取中间值
int GetMidNumi(int* str, int left, int right);

//挖坑法的快排
void QuickSort2(int* str, int left, int right);

//前后是指针
void QuickSort3(int* str, int left, int right);

//归并排序非递归
void MergeSort2(int* str, int n);

//快速排序非递归
void QuickSort4(int* str, int n);

//计数排序
void CountSort(int* str, int n);