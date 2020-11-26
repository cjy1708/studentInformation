//
// Created by 1708cjy on 2020/11/25.
//

#ifndef STUDENTINFORMATION_BASIC_1_H
#define STUDENTINFORMATION_BASIC_1_H

#include <stdlib.h>
//初始化结构体信息
typedef struct Tea{
    int Teacher_ID;
    char name[20];
    int taughtSubjectsID;
    int teachTime;
    char title[20];
    int teachClass[10];
} Teacher;

//课程结构体
typedef struct Cour{
    int Course_ID;
    char name[20];
} Course;
//学生结构体
typedef struct Stu{
    int ID;
    char name[20];
    int age;
    char sex;
    int class;
    int course[15];
} Student;

extern char *studentInformation_PATH;
//判断是否有内容
int weatherInformation();
//从文件中读出学生信息
void readInformation();

#endif //STUDENTINFORMATION_BASIC_1_H
