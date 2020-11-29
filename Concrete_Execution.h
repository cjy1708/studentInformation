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
void stuView();
//教师端界面
void teaView();
//管理员界面
void adminView();

//显示学生信息
void showStuInformation(int num);
//学生选课
void chooseCourse();

#endif //STUDENTINFORMATION_CONCRETE_EXECUTION_H
