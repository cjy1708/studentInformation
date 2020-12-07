//
// Created by 1708cjy on 2020/11/25.
//

#ifndef STUDENTINFORMATION_BASIC_1_H
#define STUDENTINFORMATION_BASIC_1_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>



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
    int course[16];
    int teacher[16];
    struct Stu *pNext;
} Student;
//管理员结构体
typedef struct Adm {
    char name[20];
    char password[16];
}Account;

//判断是否有内容
int weatherStuInformation();
int weatherCourseInformation();
int weatherTeacherInformation();
//判断错误情况
void MisjudgmentCase(int result);

//从文件中读出学生信息
Student *readInformation();
//从文件中读出课程信息
Course *readCourseInformation();
//从文件中读出教师信息
Teacher *readTeacherInformation();
//读取管理员信息,无信息、账号密码不正确返回0，正确返回1
int weatherAdministrator(char *account,char *password);

//登录信息,成功就返回账号，失败返回0；管理员返回1；
int loginIn();

//以学生ID搜索学生链表内容
Student *searchStudent(int ID);
//以教师ID搜索教师
Teacher *searchTeacher(int ID);
//以课程ID搜索课程名称
Course *searchCourse(unsigned int ID);
//以学生姓名搜索学生链表内容
Student *searchStuByName(char *name);
//以课程ID搜索教师
Teacher *searchTeaByCourseID(int ID);


//输入学生ID信息
void inputStuInformation_ID(Student *pAddStudent);
//输入、修改学生信息
void inputStuInformation(Student *pAddStudent);
void inputStuInformationLevelUp(Student *pAddStudent);
//完善学生信息
void improveStuInformation(Student *pTarget);


//安全释放学生数据
void safeFreeStu(Student *head);
//安全释放课程数据
void safeFreeCour(Course *courseList);
//安全释放教师数据
void safeFreeTea(Teacher *teacherList);
//安全释放数据
void safeFreeAll(Course *courseList,Teacher *teacherList,Student *head);

#endif //STUDENTINFORMATION_BASIC_1_H
