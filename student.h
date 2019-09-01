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

#ifndef STUDENT_H_
#define STUDENT_H_

#define NAME_SIZE 15
typedef struct StuNode {
    char name[NAME_SIZE];  // 姓名
    int ID;                // 学号
    int chinese_score;     // 语文成绩
    int math_score;        // 数学成绩
    int english_score;     // 英语成绩
    int total_score;       // 总分
    int ranking;           // 排名
    struct StuNode *next;
} StuNode, *StuList;

StuList StuSysInit(void);                                                 // 初始化
void StuInsert(StuList *head, char *na, int id, int ch, int ma, int en);  // 在链表头部添加一个新的结点
void StuDelete(StuList *head, int id);                                    // 删除一个结点(按学号查询删除的结点)
void StuDeleteAll(StuList *head);                                         // 删除整个链表
void StuReset(StuList *head, int id);                                     // 修改一个结点上的内容(按学号查询结点)
void StuSearch(StuList head, int id);                                     // 查询单个结点
void StuOutput(StuList head);                                             // 遍历打印整个链表内容
void StuBubbleSort(StuList *head, int sort_type);                         // 按要求降序冒泡排序(0:总分，1:语文，2:数学，3:英语)
void StuReadFile(StuList *head, char *file_name);                         // 从文件中添加新的结点
void StuWriteFile(StuList head, char *file_name);                         // 将结点信息导出至文件

#endif
