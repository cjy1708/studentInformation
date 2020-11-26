#include "basic_1.h"


int main() {
    int result = 0;//判断输出结构，即是否有原始数据

    result = weatherCourseInformation() + weatherStuInformation() + weatherTeacherInformation();
    result = MisjudgmentCase(result);


    return 0;
}

