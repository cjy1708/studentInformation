//
// Created by 1708cjy on 2020/11/25.
//

#include "basic_1.h"

char *studentInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\StudentInformation.txt";
char *teacherInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\TeacherInformation.txt";
char *courseInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\CourseInformation.txt";
char *account_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\Account.txt";
extern Student *Head;
extern Course *CourseList;
extern Teacher *TeacherList;
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
    printf("�����У����Ժ�");
    if(!result) {
        printf("�������������سɹ���");
        Head = readInformation();
        teacherList = readTeacherInformation();
        courseList = readCourseInformation();
        return 0;
    }
    else if (result == -1){
        printf("��ѧ�����ݣ�\n");
        teacherList = readTeacherInformation();
        courseList = readCourseInformation();
    }
    else if (result == -2){
        printf("�޿γ����ݣ�\n");
        Head = readInformation();
        teacherList = readTeacherInformation();
    }
    else if (result == -4){
        printf("�޽�ʦ���ݣ�\n");
        Head = readInformation();
        courseList = readCourseInformation();
    }
    else if (result == -3){
        printf("��ѧ���Ϳγ����ݣ�\n");
        teacherList = readTeacherInformation();
    }
    else if (result == -5){
        printf("��ѧ���ͽ�ʦ���ݣ�\n");
        courseList = readCourseInformation();
    }
    else if (result == -6){
        printf("�޿γ̺ͽ�ʦ���ݣ�\n");
        Head = readInformation();
    }
    else if (result == -7) printf("��ѧ�����γ̺ͽ�ʦ���ݣ�\n");

    return 1;
}
//���ļ��ж���ѧ����Ϣ
Student *readInformation(){
    Student *head = NULL;
    Student *p = NULL;
    Student *q = NULL;
    FILE *fp = fopen(studentInformation_PATH,"r");

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
            safeFreeStu(head);
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
    Course temp;
    int index = 1;
    FILE *fp = fopen(courseInformation_PATH,"r");

    courseList = (Course *)malloc(sizeof(Course));
    if (courseList == NULL){
        exit(EXIT_FAILURE);
    }
    fread(courseList,sizeof(Course),1,fp);
    do{
        pTemp = (Course *)realloc(courseList,(index + 1) * sizeof(Course));
        if (pTemp == NULL){
            safeFreeCour(courseList);
            exit(EXIT_FAILURE);
        }
        courseList = pTemp;
        if (fread(&temp,sizeof(Course),1,fp) != 0){
            courseList[index] = temp;
        }else{
            courseList[index].Course_ID = 0;
            break;
        }
    }while (index++);
    fclose(fp);

    return courseList;
}
//���ļ��ж����γ���Ϣ
Teacher *readTeacherInformation(){
    Teacher *TeacherList = NULL;
    Teacher *pTemp = NULL;
    Teacher temp;
    int index = 1;
    FILE *fp = fopen(teacherInformation_PATH,"r");

    TeacherList = (Teacher *)malloc(sizeof(Course));
    if (TeacherList == NULL){
        exit(EXIT_FAILURE);
    }
    fread(TeacherList,sizeof(Course),1,fp);
    do{
        pTemp = (Teacher *)realloc(TeacherList,(index + 1) * sizeof(Teacher));

        if (pTemp == NULL){
            safeFreeTea(TeacherList);
            exit(EXIT_FAILURE);
        }
        TeacherList = pTemp;
        if (fread(&temp,sizeof(Course),1,fp) != 0){
            TeacherList[index] = temp;
        }else{
            TeacherList[index].Teacher_ID = 0;
            break;
        }
    }while (index++);
    fclose(fp);

    return TeacherList;
}

//��¼��Ϣ,�ɹ��ͷ����˺ţ�ʧ�ܷ���0��
int loginIn(){
    int ID = 0;
    char account[20] = {};
    char tryPassword[16] = {};

    printf("�������˺Ż�������");
    scanf("%s",account);
    printf("���������룺");
    scanf("%s",tryPassword);
    if(isdigit(account[0]) && isdigit(account[6])){
        ID = atoi(account);
        if (ID <= 20000000 && searchTeacher(ID) != NULL)
            return ID;
        else if (ID > 20000000 && ID < 21000000 && searchStudent(ID) != NULL){
            return ID;
        }
    }else{

    }

    return 0;
}

//��ID������������
Student *searchStudent(int ID){
    Student *p = head;
    Student *q = NULL;

    while(p != NULL){
        if(p->ID == ID){
            return p;
        }
        q = p->pNext;
        p = q;
    }
    return NULL;
}
//��ID������ʦ����
Course *searchTeacher(int ID){

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