//
// Created by 1708cjy on 2020/11/25.
//

#include "basic_1.h"

char *studentInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\StudentInformation.txt";
char *teacherInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\TeacherInformation.txt";
char *courseInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\CourseInformation.txt";
char *account_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\Account.txt";

//判断是否有内容
int weatherStuInformation(){
    FILE *fp = fopen(studentInformation_PATH,"a+");

    fseek(fp,0,SEEK_SET);
    Student text = {.ID = 0};
    fread(&text,sizeof(Student),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    if (text.ID == 0) return -1;
    else return 0;
}

int weatherCourseInformation(){
    FILE *fp = fopen(courseInformation_PATH,"a+");

    fseek(fp,0,SEEK_SET);
    Course text = {.Course_ID = 0};
    fread(&text,sizeof(Course),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    if (text.Course_ID == 0) return -2;
    else return 0;
}

int weatherTeacherInformation(){
    FILE *fp = fopen(teacherInformation_PATH,"a+");

    fseek(fp,0,SEEK_SET);
    Teacher text = {.Teacher_ID = 0};
    fread(&text,sizeof(Teacher),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    if (text.Teacher_ID == 0) return -4;
    else return 0;
}
//判断错误情况
int MisjudgmentCase(int result){
    if(!result) {
        printf("数据完整，加载成功！");
        return 0;
    }
    else if (result == -1) printf("无学生数据！\n");
    else if (result == -2) printf("无课程数据！\n");
    else if (result == -4) printf("无教师数据！\n");
    else if (result == -3) printf("无学生和课程数据！\n");
    else if (result == -5) printf("无学生和教师数据！\n");
    else if (result == -6) printf("无课程和教师数据！\n");
    else if (result == -7) printf("无学生、课程和教师数据！\n");

    return 1;
}
//从文件中读出学生信息
Student *readInformation(){
    Student *head = NULL;
    Student *p = NULL;
    Student *q = NULL;
    FILE *fp = fopen(studentInformation_PATH,"r");

//    fseek(fp,0,SEEK_SET);
    q = (Student *)malloc(sizeof(Student));
    if (q == NULL){
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fread(q,sizeof(Student),1,fp);
    head = q;
    do{
        p = (Student *)malloc(sizeof(Student));
        if (p == NULL){
            safeFree(head);
            exit(EXIT_FAILURE);
        }
        fread(p,sizeof(Student),1,fp);
        q = q->pNext = p;
    }while (q->pNext != NULL);
    fclose(fp);

    return head;
}
//从文件中读出课程信息
Course *readCourseInformation(){
    Course *courseList = NULL;
    Course *pTemp = NULL;
    int index = 2;
    FILE *fp = fopen(courseInformation_PATH,"r");

    courseList = (Course *)malloc(sizeof(Course));
    if (courseList == NULL){
        exit(EXIT_FAILURE);
    }
    fread(courseList,sizeof(Course),1,fp);
    do{
        pTemp = (Course *)realloc(courseList,index * sizeof(Course));
        if (pTemp == NULL){
            safeFreeCour(courseList);
            exit(EXIT_FAILURE);
        }
        if (fread(pTemp,sizeof(Course),1,fp) != 0){
            courseList[index++ - 1] = *pTemp;
        }
    }while (pTemp != NULL);

    return courseList;
}
//安全释放学生链表
void safeFreeStu(Student *head){
    Student *p,*q;
    p = head;

    while(p != NULL){
        q = p->pNext;
        free(p);
        p = q;
    }
}
//安全释放课程数据
void safeFreeCour(Course *courseList){
    free(courseList);
}
//安全释放教师数据
void safeFreeTea(Teacher *teacherList){
    free(teacherList);
}
//安全释放数据
void safeFreeAll(Course *courseList,Teacher *teacherList,Student *head){
    safeFreeCour(courseList);
    safeFreeTea(teacherList);
    safeFreeStu(head);
}