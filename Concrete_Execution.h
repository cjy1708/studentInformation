//
// Created by 1708cjy on 2020/11/29.
//

#ifndef STUDENTINFORMATION_CONCRETE_EXECUTION_H
#define STUDENTINFORMATION_CONCRETE_EXECUTION_H

#include <stdio.h>
#include "basic_1.h"


//通用
//判断输入的是数字还是字符串，字符串不变 返回值为0，数字返回整型
int dealID(char *ID);
//学生看得见的
void student();
//教师看见的
void teacher();
//管理员看见的
void administrator();

//学生端界面
int stuView();
//教师端界面
int teaView_1();
int teaView_2();
//判断是否为自己所教班级，是则返回1，否则返回0
int teaView_3();
int teaView_4();
//管理员界面
int adminView_main();
int adminView_object();
//query为查询之意
void adminView_query(Student *pStu,Teacher *pTea,Course *pCour);
//管理员修改的界面
int adminViewStuOptions();

//显示学生信息
void showStuInformation(int num);
//学生选课
void chooseCourse();
//修改学生课程信息
void studentCourse(int *count);
//用名字或ID检测有无课程信息，有则返回课程ID
int weatherCour(char *name);

//查询教师个人信息
void showTeaInformation();
//查询相同课程的学生,有则pNowStu为刚开始相同的学生
void sameQueryCourse();
//判断班级
void judgeClass();

//对教师的第二层菜单判断并开始相应函数
void changeClassmate(int choice_2);
//教师端删除班级学生链表
void deleteStudentInformation();
//教师端增加学生信息
void addStuInformation();
//改变链表，未把班级名单排序，能把链表还链起来,function为零 删除，为1 增加
void changeStuLink(Student *pTemp,int function);
//改变学生链表的信息
void changeTargetStuInformation();

//找到可插入的位置
Student *searchPlace(char *ID);

#endif //STUDENTINFORMATION_CONCRETE_EXECUTION_H
