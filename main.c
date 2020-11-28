#include "basic_1.h"


Student *Head = NULL;
Course *CourseList = NULL;
Teacher *TeacherList = NULL;

int main() {
    int result = 0;//判断输出结构，即是否有原始数据

    result = weatherCourseInformation() + weatherStuInformation() + weatherTeacherInformation();
    result = MisjudgmentCase(result);//加载成功返回0，失败返回1

    return 0;
}

