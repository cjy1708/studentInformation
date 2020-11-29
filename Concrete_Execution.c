//
// Created by 1708cjy on 2020/11/29.
//
//学生看得见的
#include "Concrete_Execution.h"
#include "basic_1.h"
extern Student *Head;
extern Course *CourseList;
extern Teacher *TeacherList;
extern Teacher *pNowTea;
extern Student *pNowStu;

void student(){

}
//教师看见的
void teacher(){

}
//管理员看见的
void administrator(){

}

//学生端界面
void stuView(){
    int choice_1 = 0;
    for(;choice_1 != 3;) {
        printf("1.查询\n"
               "2.选课\n"
               "3.退出\n"
               "请输入你的选择：");
        fflush(stdin);
        scanf("%d", &choice_1);
        if (choice_1 == 1){
            showStuInformation(1);
            getchar();
            getchar();
        }else if(choice_1 == 2){

        }
    }
}
//教师端界面
void teaView(){

}
//管理员界面
void adminView(){

}

//显示学生信息
void showStuInformation(int num){
    int count = 0;
    Student *p = pNowStu;
    Student *q = NULL;

    for(int i = 0;i < num;i++){
        printf("学号      姓名       性别   班级\n");
        printf("%d  %-20s    %c  %d\n", pNowStu->ID, pNowStu->name, pNowStu->sex, pNowStu->class);
        count++;
        if(num > 1){
            q = p->pNext;
            p = q;
            if(p->ID - (pNowStu->ID)/100*100 <100){
                printf("%d  %-20s    %c  %d\n", p->ID, p->name, p->sex, p->class);
                count++;
            }else{
                printf("共有%d条记录\n",count);
            }
        }
    }
}

//学生选课
void chooseCourse(){
    int count;
    int totalCourse;
    printf("当前已选：\n");
    for(count = 0;pNowStu->course[count] != 0;count++){
        for(int j = 0;(CourseList+j)->Course_ID != 0;j++){
            if(pNowStu->course[count] == (CourseList+j)->Course_ID){
                printf("%-8d%s\n",(CourseList+j)->Course_ID,(CourseList+j)->name);
                break;
            }
        }
    }
    for(totalCourse = 0;(CourseList+totalCourse)->Course_ID != 0;totalCourse++){
        int judge = 0;
        printf("\n还可选的课程列表：\n");
        for(int i = 0;i < count;i++){

        }
    }
    printf("当前已选%d门课,最多还可选%d门课\n",count,totalCourse - count);
}