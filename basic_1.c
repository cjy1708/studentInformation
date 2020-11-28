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
    printf("加载中，请稍后");
    if(!result) {
        printf("数据完整，加载成功！");
        Head = readInformation();
        teacherList = readTeacherInformation();
        courseList = readCourseInformation();
        return 0;
    }
    else if (result == -1){
        printf("无学生数据！\n");
        teacherList = readTeacherInformation();
        courseList = readCourseInformation();
    }
    else if (result == -2){
        printf("无课程数据！\n");
        Head = readInformation();
        teacherList = readTeacherInformation();
    }
    else if (result == -4){
        printf("无教师数据！\n");
        Head = readInformation();
        courseList = readCourseInformation();
    }
    else if (result == -3){
        printf("无学生和课程数据！\n");
        teacherList = readTeacherInformation();
    }
    else if (result == -5){
        printf("无学生和教师数据！\n");
        courseList = readCourseInformation();
    }
    else if (result == -6){
        printf("无课程和教师数据！\n");
        Head = readInformation();
    }
    else if (result == -7) printf("无学生、课程和教师数据！\n");

    return 1;
}
//从文件中读出学生信息
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
//从文件中读出课程信息
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
//从文件中读出课程信息
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

//登录信息,成功就返回账号，失败返回0；
int loginIn(){
    int ID = 0;
    char account[20] = {};
    char tryPassword[16] = {};

    printf("请输入账号或姓名：");
    scanf("%s",account);
    printf("请输入密码：");
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

//以ID搜索链表内容
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
//以ID搜索教师工号
Course *searchTeacher(int ID){

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