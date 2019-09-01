/*
Copyright (c) 2019 fukai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化
// 建立一个头结点
StuList StuSysInit(void) {
    StuList head;
    head = (StuList)malloc(sizeof(StuNode));
    head->next = NULL;
    return head;
}

// 在链表头部添加一个新的结点
// 因为这样添加结点不用遍历到链表尾部
void StuInsert(StuList *head, char *na, int id, int ch, int ma, int en) {
    StuNode *s;
    s = (StuNode *)malloc(sizeof(StuNode));
    strcpy(s->name, na);
    s->ID = id;
    s->chinese_score = ch;
    s->math_score = ma;
    s->english_score = en;
    s->total_score = ch + ma + en;
    s->ranking = 0;
    s->next = (*head)->next;
    (*head)->next = s;
}

// 删除一个结点(按学号查询删除的结点)
void StuDelete(StuList *head, int id) {
    StuNode *tmp, *de;
    tmp = *head;
    while (tmp->next != NULL) {
        if (tmp->next->ID == id) {
            de = tmp->next;
            tmp->next = tmp->next->next;
            free(de);
            printf("\t\tDelete OK!\n");
            return;
        }
        tmp = tmp->next;
        if (tmp == NULL) break;
    }
    printf("\t\tNULL\n");
}

// 删除整个链表
void StuDeleteAll(StuList *head) {
    StuNode *tmp;
    while ((*head)->next != NULL) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

// 修改一个结点上的内容(按学号查询结点)
void StuReset(StuList *head, int id) {
    StuNode *tmp;
    int score;
    for (tmp = (*head)->next; tmp != NULL; tmp = tmp->next) {
        if (tmp->ID == id) {
            printf("\t\tPlease input new info:\n");
            printf("\t\tChinese: ");
            scanf("%d", &score);
            tmp->chinese_score = score;
            printf("\t\tMath: ");
            scanf("%d", &score);
            tmp->math_score = score;
            printf("\t\tEnglish: ");
            scanf("%d", &score);
            tmp->english_score = score;
            tmp->total_score = tmp->chinese_score + tmp->math_score + tmp->english_score;
            printf("\t\tReset OK!\n");
            return;
        }
    }
    printf("\t\tNULL\n");
}

// 查询单个结点
void StuSearch(StuList head, int id) {
    StuNode *tmp;
    printf("\t\t%-5s %-15s %-10s %-5s %-5s %-5s %-5s %-5s %3s\n", "*", "name", "ID", "CH", "MA", "EN", "SUM", "RA", "*");
    for (tmp = head->next; tmp != NULL; tmp = tmp->next) {
        if (tmp->ID == id) {
            printf("\t\t%-5s %-15s %-10d %-5d %-5d %-5d %-5d %-5d %3s\n", "*", tmp->name, tmp->ID, tmp->chinese_score, tmp->math_score, tmp->english_score, tmp->total_score, tmp->ranking, "*");
            return;
        }
    }
    printf("\t\t%-5s %-15s %-10s %-5s %-5s %-5s %-5s %-5s %3s\n", "*", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "*");
}

// 遍历打印整个链表内容
void StuOutput(StuList head) {
    StuNode *tmp;
    printf("\t\t%-5s %-15s %-10s %-5s %-5s %-5s %-5s %-5s %3s\n", "*", "name", "ID", "CH", "MA", "EN", "SUM", "RA", "*");
    if (head->next == NULL) {
        printf("\t\t%-5s %-15s %-10s %-5s %-5s %-5s %-5s %-5s %3s\n", "*", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "*");
        return;
    }
    for (tmp = head->next; tmp != NULL; tmp = tmp->next) {
        printf("\t\t%-5s %-15s %-10d %-5d %-5d %-5d %-5d %-5d %3s\n", "*", tmp->name, tmp->ID, tmp->chinese_score, tmp->math_score, tmp->english_score, tmp->total_score, tmp->ranking, "*");
    }
}

// 按要求降序冒泡排序
// 0: 按总分排序
// 1: 按语文排序
// 2: 按数学排序
// 3: 按英语排序
static inline void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
static inline void StuSwap(StuNode *a, StuNode *b) {
    char tmp[NAME_SIZE];
    int ch_tmp, ma_tmp, en_tmp, total_tmp;
    strcpy(tmp, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tmp);
    swap(&a->ID, &b->ID);
    swap(&a->chinese_score, &b->chinese_score);
    swap(&a->math_score, &b->math_score);
    swap(&a->english_score, &b->english_score);
    swap(&a->total_score, &b->total_score);
}
void StuBubbleSort(StuList *head, int sort_type) {
    StuNode *i, *j;
    int ranking = 1;
    for (i = (*head)->next; i != NULL; i = i->next, ++ranking) {
        for (j = i->next; j != NULL; j = j->next) {
            switch (sort_type) {
                case 0:
                    if (i->total_score < j->total_score) StuSwap(i, j);
                    break;
                case 1:
                    if (i->chinese_score < j->chinese_score) StuSwap(i, j);
                    break;
                case 2:
                    if (i->math_score < j->math_score) StuSwap(i, j);
                    break;
                case 3:
                    if (i->english_score < j->english_score) StuSwap(i, j);
                    break;
            }
        }
        i->ranking = ranking;
    }
}

// 从文件中添加新的结点
#define MAX_LINE 1024
void StuReadFile(StuList *head, char *file_name) {
    char buf[MAX_LINE];
    int cnt = 0, n = 0;
    FILE *fp;
    char tmp[5][30];
    char name[20];
    int id, ch, ma, en;
    if ((fp = fopen(file_name, "r")) == NULL) {
        printf("\t\t文件打开错误!\n");
        exit(1);
    } else {
        while (fgets(buf, MAX_LINE, fp) != NULL) {
            int len = strlen(buf);
            if (buf[len - 1] == '\n') buf[len - 1] = '\0';
            len = strlen(buf);
            for (int i = 0; i <= len; ++i) {
                tmp[n][cnt++] = buf[i];
                if (buf[i] == ' ' || buf[i] == '\0' || buf[i] == '\t') {
                    tmp[n][cnt - 1] = '\0';
                    cnt = 0;
                    ++n;
                }
            }
            n = 0;
            strcpy(name, tmp[0]);
            id = atoi(tmp[1]);
            ch = atoi(tmp[2]);
            ma = atoi(tmp[3]);
            en = atoi(tmp[4]);
            StuInsert(head, name, id, ch, ma, en);
        }
        printf("\t\t文件导入完成!\n");
    }
}

// 将结点信息导出至文件
void StuWriteFile(StuList head, char *file_name) {
    char buf[MAX_LINE];
    FILE *fp;
    StuNode *tmp;
    int cnt = 0;
    if ((fp = fopen(file_name, "w")) == NULL) {
        printf("\t\t文件打开错误!\n");
        exit(1);
    } else {
        fprintf(fp, "%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "NAME", "ID", "CH", "MA", "EN", "TOTAL", "RANKING");
        for (tmp = head->next; tmp != NULL; tmp = tmp->next) {
            fprintf(fp, "%-10s %-10d %-10d %-10d %-10d %-10d %-10d\n", tmp->name, tmp->ID, tmp->chinese_score, tmp->math_score, tmp->english_score, tmp->total_score, tmp->ranking);
        }
        fclose(fp);
        printf("\t\t文件导出完成!\n");
    }
}
