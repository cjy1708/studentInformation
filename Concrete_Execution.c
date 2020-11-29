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
    for(;choice_1 != 3;){
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
            chooseCourse();
        }else if(choice_1 == 3){
            break;
        }else{
            printf("输入错误，请重新输入！\n");
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
        printf("学号      姓名       年龄   性别   班级\n");
        printf("%d  %-20s %d  %c  %d\n", pNowStu->ID, pNowStu->name, pNowStu->age, pNowStu->sex, pNowStu->class);
        count++;
        if(num > 1){
            q = p->pNext;
            p = q;
            if(p->ID - (pNowStu->ID)/100*100 <100){
                printf("%d  %-20s %d  %c  %d\n", p->ID, p->name, p->age, p->sex, p->class);
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
    char choose;
    printf("当前已选：\n");
    for(count = 0;pNowStu->course[count] != 0;count++){
        for(int j = 0;(CourseList+j)->Course_ID != 0;j++){
            if(pNowStu->course[count] == (CourseList+j)->Course_ID){
                printf("%-8d%20s\t",(CourseList+j)->Course_ID,(CourseList+j)->name);
                printf("%s\n",searchTeacher(pNowStu->teacher[count])->name);
                break;
            }
        }
    }
    printf("\n还可选的课程列表：\n");
    for(totalCourse = 0;(CourseList+totalCourse)->Course_ID != 0;totalCourse++){
        int judge = 0;
        for(int i = 0;i < count;i++){
            if ((CourseList+totalCourse)->Course_ID == pNowStu->course[i]){
                judge++;
                break;
            }
        }
        if(judge == 0){
            printf("%-8d%s\n",(CourseList+totalCourse)->Course_ID,(CourseList+totalCourse)->name);
        }
    }
    if(count < 15){
        if (totalCourse > 15) {
            printf("当前已选%d门课,还可选%d门课\n", count, totalCourse - count);
            printf("为了您的生命着想，最多还可选%d门课\n", 15 - count);
        } else {
            printf("当前已选%d门课,还可选%d门课\n", count, totalCourse - count);
        }
        while(1) {
            printf("是否选课（y/n）：");
            fflush(stdin);
            choose = getchar();
            if (choose == 'Y' || choose == 'y') {
                //修改学生课程数据
                studentCourse(&count);
            } else if (choose == 'N' || choose == 'n') {
                break;
            } else {
                printf("输入错误，请重新选择！\n");
            }
        }
    }else if(count == 15){
        printf("选课已达最大上限，无法选课\n");
    }
    getchar();
    getchar();
}
//修改学生课程信息
void studentCourse(int *count){
    int result = 0;
    char name[20] = {};

    printf("请输入课程ID或名称：");
    fflush(stdin);
    scanf("%s",name);
    result = weatherCour(name);
    if(result != 0){
        pNowStu->course[(*count)++] = result;
    }else{
        printf("输入无效\n");
    }
    getchar();
    getchar();
}
//检测有无课程信息,有则返回课程ID
int weatherCour(char *name){
    int both_1;
    int both_2;
    int ID;

    if(isdigit(name[0]) && isdigit(name[5])){
        ID = atoi(name);
        for(int i = 0;(CourseList + i)->Course_ID != 0;i++){
            if((CourseList + i)->Course_ID == ID){
                both_1 = ID;
                break;
            }else{
                both_1 = 0;
            }
        }
        for(int i = 0;pNowStu->course[i] != 0;i++){
            if(pNowStu->course[i] == ID){
                both_2 = 0;
                break;
            }else{
                both_2 = 1;
            }
        }
    }else{
        for(int i = 0;(CourseList + i)->Course_ID != 0;i++){
            if(strcmp((CourseList + i)->name,name) != 0){
                both_1 = 0;
            }else{
                ID = (CourseList + i)->Course_ID;
                both_1 = ID;
                break;
            }
        }
        for(int i =0;pNowStu->course[i] != 0;i++){
            if(ID == pNowStu->course[i]){
                both_2 = 0;
                break;
            }else{
                both_2 = 1;
            }
        }
    }
    return both_2 * both_1;
}
