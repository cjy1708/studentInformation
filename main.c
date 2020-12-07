#include "basic_1.h"
#include "Concrete_Execution.h"


Student *Head = NULL;
Course *CourseList = NULL;
Teacher *TeacherList = NULL;
Teacher *pNowTea;
Student *pNowStu;
Student *pPastStu = NULL;

int main() {
    int result = 0;//判断输出结构，即是否有原始数据
    int ID = 0;

    result = weatherCourseInformation() + weatherStuInformation() + weatherTeacherInformation();
    MisjudgmentCase(result);//加载成功返回0，失败返回1

    ID = loginIn();
    if (ID == 0){
        exit(EXIT_FAILURE);
    }else if(ID == 1){
        //管理员端口

    }else if(ID <= 20000000){
        //教师端口
        
    }else if(ID < 21000000){
        //学生端口
        stuView();
    }

    safeFreeAll(CourseList,TeacherList,Head);
    return 0;
}

