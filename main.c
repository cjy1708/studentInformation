#include "basic_1.h"


int main() {
    int result = 0;//�ж�����ṹ�����Ƿ���ԭʼ����

    result = weatherCourseInformation() + weatherStuInformation() + weatherTeacherInformation();
    result = MisjudgmentCase(result);


    return 0;
}

