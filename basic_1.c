//
// Created by 1708cjy on 2020/11/25.
//

#include "basic_1.h"

char *studentInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\StudentInformation.txt";
char *teacherInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\TeacherInformation.txt";
char *courseInformation_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\CourseInformation.txt";
char *account_PATH = "D:\\Learn\\CProgrammingLanguage\\programming\\CLion experiment\\Information\\Administrator.bat";
extern Student *Head;
extern Course *CourseList;
extern Teacher *TeacherList;
extern Teacher *pNowTea;
extern Student *pNowStu;
//�ж��Ƿ�������
int weatherStuInformation(){
    FILE *fp = fopen(studentInformation_PATH,"ab");

    fseek(fp,0,SEEK_SET);
    Student text = {.ID = 0};
    fread(&text,sizeof(Student),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    if (text.ID == 0) return -1;
    else return 0;
}

int weatherCourseInformation(){
    FILE *fp = fopen(courseInformation_PATH,"ab");

    fseek(fp,0,SEEK_SET);
    Course text = {.Course_ID = 0};
    fread(&text,sizeof(Course),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    if (text.Course_ID == 0) return -2;
    else return 0;
}

int weatherTeacherInformation(){
    FILE *fp = fopen(teacherInformation_PATH,"ab");

    fseek(fp,0,SEEK_SET);
    Teacher text = {.Teacher_ID = 0};
    fread(&text,sizeof(Teacher),1,fp);
    fseek(fp,0,SEEK_SET);
    fclose(fp);
    if (text.Teacher_ID == 0) return -4;
    else return 0;
}
//�жϴ������
void MisjudgmentCase(int result){
    printf("�����У����Ժ�");
    if(!result) {
        printf("�������������سɹ���");
        Head = readInformation();
        TeacherList = readTeacherInformation();
        CourseList = readCourseInformation();
    }
    else if (result == -1){
        printf("��ѧ�����ݣ�\n");
        TeacherList = readTeacherInformation();
        CourseList = readCourseInformation();
    }
    else if (result == -2){
        printf("�޿γ����ݣ�\n");
        Head = readInformation();
        TeacherList = readTeacherInformation();
    }
    else if (result == -4){
        printf("�޽�ʦ���ݣ�\n");
        Head = readInformation();
        CourseList = readCourseInformation();
    }
    else if (result == -3){
        printf("��ѧ���Ϳγ����ݣ�\n");
        TeacherList = readTeacherInformation();
    }
    else if (result == -5){
        printf("��ѧ���ͽ�ʦ���ݣ�\n");
        CourseList = readCourseInformation();
    }
    else if (result == -6){
        printf("�޿γ̺ͽ�ʦ���ݣ�\n");
        Head = readInformation();
    }
    else if (result == -7) printf("��ѧ�����γ̺ͽ�ʦ���ݣ�\n");
}
//���ļ��ж���ѧ����Ϣ
Student *readInformation(){
    Student *head = NULL;
    Student *p = NULL;
    Student *q = NULL;
    FILE *fp = fopen(studentInformation_PATH,"rb");

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
    FILE *fp = fopen(courseInformation_PATH,"rb");

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
//���ļ��ж�����ʦ��Ϣ
Teacher *readTeacherInformation(){
    Teacher *pTemp = NULL;
    Teacher temp;
    int index = 1;
    FILE *fp = fopen(teacherInformation_PATH,"rb");

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
//��ȡ����Ա��Ϣ,����Ϣ���˺����벻��ȷ����0����ȷ����1
int weatherAdministrator(char *account,char *password){
    Account wayForPoint;
    Account *p = &wayForPoint;
    FILE *fp = fopen(account_PATH,"rb");

    if (fp == NULL){
        printf("�˺�������󣬳������\n");
        sleep(3);
        return 0;
    }else{
        while(1){
            fread(p,sizeof(Account),1,fp);
            if(strcmp(p->name,account) == 0 && strcmp(p->password,password) == 0){
                printf("��ǰ����Ա�ѵ�¼\n");
                fclose(fp);
                return 1;
            }
            if(p == NULL)
                break;
        }
        fclose(fp);
        printf("�˺�������󣬳������\n");
        sleep(3);
        return 0;
    }
}

//��¼��Ϣ,�ɹ��ͷ����˺ţ�ʧ�ܷ���0������Ա����1��
int loginIn(){
    int ID;
    char account[20] = {};
    char tryPassword[16] = {};

    printf("�������˺Ż�������");
    fflush(stdin);
    scanf("%s",account);
    printf("���������룺");
    fflush(stdin);
    scanf("%s",tryPassword);
    if(isdigit(account[0]) && isdigit(account[6])){
        ID = atoi(account);
        if (ID <= 20000000 && (pNowTea = searchTeacher(ID)) != NULL){
            printf("��ӭ%s��ʦ��¼",pNowTea->name);
            return ID;
        }
        else if (ID > 20000000 && ID < 21000000 && (pNowStu = searchStudent(ID)) != NULL){
            printf("��ӭ%sͬѧ��¼",pNowStu->name);
            return ID;
        }
        printf("�˺�������󣬳�����3������\n");
        sleep(3);
        return 0;
    }else{
        return weatherAdministrator(account,tryPassword);
    }
}

//��ѧ��ID������������
Student *searchStudent(int ID){
    Student *p = Head;
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
//�Խ�ʦID������ʦ����
Teacher *searchTeacher(int ID){
    for(int i = 0;TeacherList[i].Teacher_ID != 0;i++){
        if(TeacherList[i].Teacher_ID == ID){
            return &TeacherList[i];
        }
    }
    return NULL;
}
//�Կγ�ID�����γ�����
Course *searchCourse(unsigned int ID){
    for (int i = 0; (CourseList + i)->Course_ID != 0; i++) {
        if ((CourseList + i)->Course_ID == ID){
            return (CourseList + i);
        }
    }
    return NULL;
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