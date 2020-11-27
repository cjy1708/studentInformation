//
// Created by 1708cjy on 2020/11/25.
//

#include "basic_1.h"

char *studentInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\StudentInformation.txt";
char *teacherInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\TeacherInformation.txt";
char *courseInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\CourseInformation.txt";
char *account_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\Account.txt";

//�ж��Ƿ�������
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
//�жϴ������
int MisjudgmentCase(int result){
    if(!result) {
        printf("�������������سɹ���");
        return 0;
    }
    else if (result == -1) printf("��ѧ�����ݣ�\n");
    else if (result == -2) printf("�޿γ����ݣ�\n");
    else if (result == -4) printf("�޽�ʦ���ݣ�\n");
    else if (result == -3) printf("��ѧ���Ϳγ����ݣ�\n");
    else if (result == -5) printf("��ѧ���ͽ�ʦ���ݣ�\n");
    else if (result == -6) printf("�޿γ̺ͽ�ʦ���ݣ�\n");
    else if (result == -7) printf("��ѧ�����γ̺ͽ�ʦ���ݣ�\n");

    return 1;
}
//���ļ��ж���ѧ����Ϣ
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
//���ļ��ж����γ���Ϣ
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
//��ȫ�ͷ�ѧ������
void safeFreeStu(Student *head){
    Student *p,*q;
    p = head;

    while(p != NULL){
        q = p->pNext;
        free(p);
        p = q;
    }
}
//��ȫ�ͷſγ�����
void safeFreeCour(Course *courseList){
    free(courseList);
}
//��ȫ�ͷŽ�ʦ����
void safeFreeTea(Teacher *teacherList){
    free(teacherList);
}
//��ȫ�ͷ�����
void safeFreeAll(Course *courseList,Teacher *teacherList,Student *head){
    safeFreeCour(courseList);
    safeFreeTea(teacherList);
    safeFreeStu(head);
}