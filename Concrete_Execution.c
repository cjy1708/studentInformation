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

//
void student(){
    int choice = 0;

    while((choice = stuView()) != 3) {

        if (choice == 1) {
            showStuInformation(1);
            getchar();
            getchar();
        } else if (choice == 2) {
            chooseCourse();
            getchar();
            getchar();
        }else {
            printf("输入错误，请重新输入！\n");
        }
    }
}
//教师看见的
void teacher(){
    int choice_1 = 0;
    int choice_2 = 0;

    while ((choice_1 = teaView_1()) != 3){
        if (choice_1 == 1){
            while ((choice_2 = teaView_2()) != 3){
                if(choice_2 == 1){
                    showTeaInformation();
                    getchar();
                    getchar();
                }else if(choice_2 == 2){
                    printf("当前已教班级名单：\n");
                    pNowStu = Head;
                    while(pNowStu != NULL){
                        sameQueryCourse(); //使得pNowStu为刚开始的同一课程
                        judgeClass();
                        showStuInformation(99);
                        getchar();
                        getchar();
                    }
                }else{
                    printf("输入错误，请重新输入");
                }
            }
        }else if (choice_1 == 2){

        }else{
            printf("输入错误，请重新输入");
        }
    }
}
//管理员看见的
void administrator(){

}

//学生端界面
int stuView(){
    int choice_1 = 0;
    printf("1.查询\n"
           "2.选课\n"
           "3.退出\n"
           "请输入你的选择：");
    fflush(stdin);
    scanf("%d", &choice_1);

    return choice_1;
}
//教师端界面
int teaView_1(){
    int choice = 0;

    printf("1.查询\n"
           "2.修改所教班级成员\n"
           "3.退出\n"
           "请输入你的选择：");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
int teaView_2(){
    int choice = 0;

    printf("1.查询个人信息\n"
           "2.查询所教班级名单\n"
           "3.返回主菜单\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
int teaView_3(){
    int targetClass = 0;

    printf("请输入要修改的班级：");
    fflush(stdin);
    scanf("%d",&targetClass);
    targetClass = targetClass * 100 +1;
    pNowStu = searchStudent(targetClass);
    if(pNowStu == NULL){
        printf
    }
}
int teaView_4(){

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
                pNowStu = p;
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
//用名字或ID检测有无课程信息,有则返回课程ID
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
                ID = (int )(CourseList + i)->Course_ID;
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

//查询教师个人信息
void showTeaInformation(){
    printf("教师工号     姓名     所教学科\n");
    printf("%-9d%-20s%-20s\n",pNowTea->Teacher_ID,pNowTea->name,searchCourse(pNowTea->taughtSubjectsID)->name);
    printf("职称      教龄");
    printf("%-20s%3d\n",pNowTea->rank,pNowTea->teachTime);
}
//查询相同课程的学生,有则pNowStu为刚开始相同的学生
void sameQueryCourse(){
    int courID = pNowTea->taughtSubjectsID;
    Student *p = pNowStu;
    Student *q;

    while(p != NULL){
        for(int i = 0;i < 16;i++) {
            if (p->course[i] == courID) {
                pNowStu = p;
                break;
            }
        }
        if(pNowStu == p){
            break;
        }
        q = p->pNext;
        p = q;
    }
    if(p == NULL){
        pNowStu = p;
    }
}
//判断班级
void judgeClass(){
    int integer;
    int remainder;

    //获取原始数据
    integer = pNowStu->ID / 100;
    remainder = integer % 100;

    printf("\n当前班级为%3d班,成员名单如下：\n",remainder);
}