#include "basic_1.h"


Student *Head = NULL;
Course *CourseList = NULL;
Teacher *TeacherList = NULL;

int main() {
    int result = 0;//�ж�����ṹ�����Ƿ���ԭʼ����

    result = weatherCourseInformation() + weatherStuInformation() + weatherTeacherInformation();
    result = MisjudgmentCase(result);//���سɹ�����0��ʧ�ܷ���1

    return 0;
}

