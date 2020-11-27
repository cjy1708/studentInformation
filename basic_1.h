//
// Created by 1708cjy on 2020/11/25.
//

#ifndef STUDENTINFORMATION_BASIC_1_H
#define STUDENTINFORMATION_BASIC_1_H

#include <stdlib.h>
#include <stdio.h>


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
    struct Stu *pNext;
} Student;


//判断是否有内容
int weatherStuInformation();
int weatherCourseInformation();
int weatherTeacherInformation();
//判断错误情况
int MisjudgmentCase(int result);
//从文件中读出学生信息
Student *readInformation();


//安全释放学生数据
void safeFreeStu(Student *head);
//安全释放课程数据
void safeFreeCour(Course *courseList);
//安全释放教师数据
void safeFreeTea(Teacher *teacherList);
//安全释放数据
void safeFreeAll(Course *courseList,Teacher *teacherList,Student *head);

#endif //STUDENTINFORMATION_BASIC_1_H
