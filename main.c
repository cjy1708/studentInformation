#include "basic_1.h"
#include "Concrete_Execution.h"


Student *Head = NULL;
Course *CourseList = NULL;
Teacher *TeacherList = NULL;
Teacher *pNowTea;
Student *pNowStu;
Student *pPastStu = NULL;

int main() {
    int result = 0;//�ж�����ṹ�����Ƿ���ԭʼ����
    int ID = 0;

    result = weatherCourseInformation() + weatherStuInformation() + weatherTeacherInformation();
    MisjudgmentCase(result);//���سɹ�����0��ʧ�ܷ���1

    ID = loginIn();
    if (ID == 0){
        exit(EXIT_FAILURE);
    }else if(ID == 1){
        //����Ա�˿�

    }else if(ID <= 20000000){
        //��ʦ�˿�
        
    }else if(ID < 21000000){
        //ѧ���˿�
        stuView();
    }

    safeFreeAll(CourseList,TeacherList,Head);
    return 0;
}

