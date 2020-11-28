//
// Created by 1708cjy on 2020/11/25.
//

#ifndef STUDENTINFORMATION_BASIC_1_H
#define STUDENTINFORMATION_BASIC_1_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


//初始化结构体信息
typedef struct Tea{
    int Teacher_ID;
    char name[20];
    unsigned int taughtSubjectsID;
    int teachTime;
    char rank[20];
    int teachClass[10];
} Teacher;

//课程结构体
typedef struct Cour{
    unsigned int Course_ID;
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
//从文件中读出课程信息
Course *readCourseInformation();
//从文件中读出教师信息
Teacher *readTeacherInformation();

//登录信息
int loginIn();

//以ID搜索链表内容
Student *searchStudent(int ID);
//以ID搜索教师工号
Course *searchTeacher(int ID);

//安全释放学生数据
void safeFreeStu(Student *head);
//安全释放课程数据
void safeFreeCour(Course *courseList);
//安全释放教师数据
void safeFreeTea(Teacher *teacherList);
//安全释放数据
void safeFreeAll(Course *courseList,Teacher *teacherList,Student *head);

#endif //STUDENTINFORMATION_BASIC_1_H
