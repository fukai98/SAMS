# 学生成绩管理系统

> 本项目用于2019年赛博智能车实验室大一学生C语言考核

#### Clone this project :

```
git clone https://github.com/fukai98/SAMS.git
```

### 代码框架

- 本代码已在macOS平台上编译通过

- 如需在Windows上编译，需要更改main.c中的清屏函数

- ```C
  // 注释掉不是自己电脑系统的那一部分代码
  #define CLEAR() system("clear") 	// Unix or Linux
  #define CLEAR() system("cls")		// windows
  ```

- 代码中采用链表存储每个学生的数据，具体见studemt.c和student.h

- test_small.txt为导入文件样例，可直接使用

- data.txt为导出文件

- SAMS.exe为Windows平台下的执行文件

- SAMS.out为Mac平台上的二进制可执行文件，执行代码如下

  ```ssh
  ./SAMS.out
  ```

- 代码的导入测试样例可通过在Excel上建立之后复制到txt文件当中

  

### 考核任务要求

- 必须含有三个独立代码文件：main.c，student.c，student.h

- student.c和student.h中不允许定义任何的全局变量

- 管理系统具有以下几个功能：

  1. 允许手动添加成绩
  2. 允许文件导入成绩
  3. 查询学生成绩
  4. 修改学生成绩
  5. 删除学生成绩
  6. 查看成绩排名
  7. 导出学生成绩
  8. 退出成绩系统

- 导入文件为.txt文件，具体格式如下：

  1. 从左到右依次为姓名、学号、语文成绩、数学成绩、英语成绩
  2. 每一行每个元素之间用一个制表符（TAB）隔开
  3. 需学生人数是不确定的，考核时的测试导入样例可能很大

  ```
  A1	1	100	1	1
  A2	2	99	2	2
  A3	3	98	3	3
  A4	4	97	4	4
  A5	5	96	5	5
  A6	6	95	6	6
  A7	7	94	7	7
  A8	8	93	8	8
  A9	9	92	9	9
  A10	10	91	10	10
  ```

- 导出文件为.txt文件，具体要求如下：

  1. 从左到右依次为姓名、学号、语文成绩、数学成绩、英语成绩、总分、排名
  2. 以总分降序排名后导出
  3. 每一行的每个元素之间向右对齐10个单元格

  ```
  NAME       ID         CH         MA         EN         TOTAL      RANKING   
  A100       100        1          100        100        201        1         
  A99        99         2          99         99         200        2         
  A98        98         3          98         98         199        3         
  A97        97         4          97         97         198        4         
  A96        96         5          96         96         197        5         
  A95        95         6          95         95         196        6         
  A94        94         7          94         94         195        7         
  A93        93         8          93         93         194        8         
  A92        92         9          92         92         193        9         
  A91        91         10         91         91         192        10    
  ```