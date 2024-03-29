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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define CLEAR() system("clear")

static inline void ShowLine(void);  // 显示分界线
void Menu(void);                    // 显示主界面
void AddInfo(void);                 // 手动添加成绩
void ReadFileInfo(void);            // 文件导入
void InquireScore(void);            // 查询个人成绩
void ResetScore(void);              // 修改个人成绩
void DeleteScore(void);             // 删除学生成绩
void ShowRanking(void);             // 查看成绩排名
void WriteFileInfo(void);           // 文件导出
void TurnOff(void);                 // 退出程序

StuList stu;
void (*Func[])(void) = {Menu, AddInfo, ReadFileInfo, InquireScore, ResetScore, DeleteScore, ShowRanking, WriteFileInfo, TurnOff};

int main() {
    stu = StuSysInit();
    Menu();
    return 0;
}

// 显示分界线
static inline void ShowLine(void) {
    printf("\t\t");
    for (int i = 0; i < 66; ++i) {
        printf("*");
    }
    printf("\n");
}

// 输入操作
static inline void InputNum(void) {
    int select;
    char tmp[10];
    printf("\t\t请输入序号: ");
    scanf("%s", tmp);
    select = atoi(tmp);
    while (select < 1 || select > 8) {
        printf("\t\t输入错误，请重新输入序号: ");
        scanf("%s", tmp);
        select = atoi(tmp);
    }
    Func[select]();
}

//返回主菜单
static inline void BackMenu(void) {
    char tmp[10];
    printf("\t\t输入q返回主菜单: ");
    getchar();
    scanf("%s", tmp);
    while (strlen(tmp) > 1 || (tmp[0] != 'q' && tmp[0] != 'Q')) {
        printf("\t\t输入错误，请重新输入: ");
        scanf("%s", tmp);
    }
    Func[0]();
}

// 主界面
void Menu(void) {
    CLEAR();
    ShowLine();
    printf("\t\t%s %47s %24s\n", "*", "学生成绩管理系统", "*");
    ShowLine();
    printf("\t\t%-25s %-30s %15s\n", "*", "1:手动添加成绩", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "2:文件导入成绩", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "3:查询学生成绩", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "4:修改学生成绩", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "5:删除学生成绩", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "6:查看成绩排名", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "7:导出学生成绩", "*");
    printf("\t\t%-25s %-30s %15s\n", "*", "8:退出成绩系统", "*");
    ShowLine();
    InputNum();
}

// 手动添加成绩
void AddInfo(void) {
    char name[NAME_SIZE];
    int id, ch, ma, en;
    printf("\t\t请分别输入姓名，学号，语文，数学，英语成绩(以空格隔开): ");
    scanf("%s%d%d%d%d", name, &id, &ch, &ma, &en);
    StuInsert(&stu, name, id, ch, ma, en);
    printf("\t\t添加成功！\n");
    InputNum();
}

// 文件导入
void ReadFileInfo(void) {
    StuReadFile(&stu, "test_small.txt");
    StuBubbleSort(&stu, 0);
    InputNum();
}

// 文件导出
void WriteFileInfo(void) {
    StuBubbleSort(&stu, 0);
    StuWriteFile(stu, "data.txt");
    InputNum();
}

// 查询个人成绩
void InquireScore(void) {
    int id;
    printf("\t\t请输入待查询学生的学号: ");
    scanf("%d", &id);
    CLEAR();
    ShowLine();
    StuSearch(stu, id);
    ShowLine();
    BackMenu();
}

// 修改个人成绩
void ResetScore(void) {
    int id;
    printf("\t\t请输入待查询学生的学号: ");
    scanf("%d", &id);
    StuReset(&stu, id);
    StuBubbleSort(&stu, 0);
    InputNum();
}

// 删除学生成绩
void DeleteScore(void) {
    int id;
    printf("\t\t请输入待删除学生的学号(输入0表示删除全部学生成绩): ");
    scanf("%d", &id);
    if (id == 0) {
        StuDeleteAll(&stu);
        printf("\t\t已清空全部成绩!\n");
    } else {
        StuDelete(&stu, id);
    }
    StuBubbleSort(&stu, 0);
    InputNum();
}

// 查看成绩排名
void ShowRanking(void) {
    CLEAR();
    ShowLine();
    printf("\t\t%s %40s %27s\n", "*", "语文排名", "*");
    ShowLine();
    StuBubbleSort(&stu, 1);
    StuOutput(stu);
    ShowLine();
    printf("\t\t%s %40s %27s\n", "*", "数学排名", "*");
    ShowLine();
    StuBubbleSort(&stu, 2);
    StuOutput(stu);
    ShowLine();
    printf("\t\t%s %40s %27s\n", "*", "英语排名", "*");
    ShowLine();
    StuBubbleSort(&stu, 3);
    StuOutput(stu);
    ShowLine();
    printf("\t\t%s %40s %27s\n", "*", "总分排名", "*");
    ShowLine();
    StuBubbleSort(&stu, 0);
    StuOutput(stu);
    ShowLine();
    BackMenu();
}

// 退出程序
void TurnOff(void) {
    printf("\t\tBYE!\n");
    return;
}
