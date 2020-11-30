//
// Created by 1708cjy on 2020/11/29.
//

#ifndef STUDENTINFORMATION_CONCRETE_EXECUTION_H
#define STUDENTINFORMATION_CONCRETE_EXECUTION_H

#include <stdio.h>
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
int teaView_3();
int teaView_4();
//管理员界面
void adminView();

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


#endif //STUDENTINFORMATION_CONCRETE_EXECUTION_H
