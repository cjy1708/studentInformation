//
// Created by 1708cjy on 2020/11/29.
//
//学生看得见的
#include "Concrete_Execution.h"

extern Student *Head;
extern Course *CourseList;
extern Teacher *TeacherList;
extern Teacher *pNowTea;
extern Student *pNowStu;
extern Student *pPastStu;

//判断输入的是数字还是字符串，字符串不变 返回值为0，数字返回整型
int dealID(char *ID){
    int digitalID;

    if (isdigit(ID[0]) == 1 && isdigit(ID[4]) == 1) {
        digitalID = atoi(ID);
        return digitalID;
    } else {
        return 0;
    }
}
//学生看见的
void student(){
    int choice = 0;

    while((choice = stuView()) != 3) {

        if (choice == 1) {
            showStuInformation(1);
            getchar();
            getchar();
        } else if (choice == 2) {
            chooseCourse();
            getchar();
            getchar();
        }else {
            printf("输入错误，请重新输入！\n");
        }
    }
}
//教师看见的
void teacher(){
    int choice_1 = 0;
    int choice_2 = 0;

    while ((choice_1 = teaView_1()) != 3){
        if (choice_1 == 1){
            while ((choice_2 = teaView_2()) != 3){
                if(choice_2 == 1){
                    showTeaInformation();
                    getchar();
                    getchar();
                }else if(choice_2 == 2){
                    printf("当前已教班级名单：\n");
                    pNowStu = Head;
                    while(pNowStu != NULL){
                        sameQueryCourse(); //使得pNowStu为刚开始的同一课程的学生
                        judgeClass();
                        showStuInformation(99);
                        getchar();
                        getchar();
                    }
                }else{
                    printf("输入错误，请重新输入");
                }
            }
        }else if (choice_1 == 2) {
            while(1) {
                if (teaView_3() == 1) {
                    printf("班级成员名单为：\n");
                    showStuInformation(99);
                    changeClassmate(teaView_4());
                } else {
                    printf("输入回车键返回上一层菜单\n");
                    getchar();
                    getchar();
                    break;
                }
            }
        }else{
            printf("输入错误，请重新输入\n");
        }
    }
}
//管理员
void administrator(){
    int choice_1;
    int choice_2;
    int digitalID;
    char ID[20];

    if ((choice_1 = adminView_main()) == 1){
        switch (adminView_object()){
            case 1:
                printf("请输入要查询的学生信息：\n"
                       "(例如：20170801 或ChenGuanYu)\n");
                do {
                    fflush(stdin);
                    scanf("%s", ID);
                    digitalID = dealID(ID);
                    if (digitalID != 0) {
                        pNowStu = searchStudent(digitalID);
                    } else {
                        pNowStu = searchStuByName(ID);
                    }
                    if (pNowStu == NULL) {
                        printf("学生信息不存在！\n");
                        break;
                    } else {
                        adminView_query(Head + 1, NULL, NULL);
                    }
                }while (pNowStu != NULL);
                break;
            case 2:
                adminView_query(Head,NULL,NULL);
                break;
            case 3:
                printf("请输入要查询的教师ID：");
                do {
                    fflush(stdin);
                    scanf("%d", &digitalID);
                    pNowTea = searchTeacher(digitalID);
                    if (pNowTea != NULL) {
                        adminView_query(NULL, TeacherList + 1, NULL);
                    } else {
                        printf("无当前教师信息！\n");
                    }
                }while (pNowTea != NULL);
                break;
            case 4:
                adminView_query(NULL,TeacherList,NULL);
                break;
            case 5:
                adminView_query(NULL,NULL,CourseList);
                break;
            case 6:
                break;
            default :
                printf("输入错误，将返回上一层菜单！\n");
        }
    }else if (choice_1 == 2){
        if((choice_2 = adminView_object()) == 1){
            switch (adminViewStuOptions()) {
                case 1://修改学生信息
                    printf("请输入要修改的学生信息：\n"
                           "(例如：20170801 或ChenGuanYu)\n");
                    do {
                        fflush(stdin);
                        scanf("%s", ID);
                        digitalID = dealID(ID);
                        if (digitalID != 0) {
                            pNowStu = searchStudent(digitalID);
                        } else {
                            pNowStu = searchStuByName(ID);
                        }
                        if (pNowStu == NULL){
                            printf("当前学生信息不存在，将返回上一层菜单\n");
                            break;
                        }else {
                            inputStuInformationLevelUp(pNowStu);
                        }
                    } while (pNowStu != NULL);
                    break;
                case 2://增加
                    addStuInformation();
                    break;
                case 3://删除
                    deleteStudentInformation();
                    break;
                case 4://修改课程
                    break;
                case 5://增加课程
                    chooseCourse();
                    break;
                case 6://删除课程
                    break;
                case 7://返回上一级菜单
                    break;
                default://输入错误
                    printf("输入错误，请重新输入！\n");
            }
        }
    }
}

//学生端界面
int stuView(){
    int choice_1 = 0;
    printf("1.查询\n"
           "2.选课\n"
           "3.退出\n"
           "请输入你的选择：");
    fflush(stdin);
    scanf("%d", &choice_1);

    return choice_1;
}
//教师端界面
int teaView_1(){
    int choice = 0;

    printf("1.查询\n"
           "2.修改所教班级成员\n"
           "3.退出\n"
           "请输入你的选择：");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
int teaView_2(){
    int choice = 0;

    printf("1.查询个人信息\n"
           "2.查询所教班级名单\n"
           "3.返回主菜单\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
//判断是否为自己所教班级，是则返回1，否则返回0
int teaView_3(){
    int targetClass = 0;

    printf("请输入要修改的班级：(年级班级  201708）\n");
    fflush(stdin);
    scanf("%d",&targetClass);
    targetClass = targetClass * 100 + 1;
    pNowStu = searchStudent(targetClass);
    if(pNowStu == NULL){
        printf("无当前班级数据！\n");
        return 0;
    }else{
        for(int i = 0;pNowStu->teacher[i] != 0;i++){
            if (pNowStu->teacher[i] == pNowTea->Teacher_ID){
                printf("数据合法，可继续操作\n");
                return 1;
            }
        }
        printf("不是所教班级，无法进行操作！\n");
        return 0;
    }
}
int teaView_4(){
    int choice;

    printf("1.修改\n"
           "2.删除\n"
           "3.增添\n"
           "4.返回上一层\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
//对教师的第二层菜单判断并开始相应函数
void changeClassmate(int choice_2){
    if (choice_2 == 1){
        changeTargetStuInformation();
    }else if (choice_2 == 2){
        deleteStudentInformation();
    }else if (choice_2 == 3){
        addStuInformation();
    }else if (choice_2 == 4){
        printf("班级预览结束\n");
    }else {
        printf("输入错误，"
               "请重新输入！\n");
        changeClassmate(teaView_4());
    }
}

//管理员界面
int adminView_main() {
    int choice;

    printf("1.查询\n"
           "2.修改\n"
           "3.强制信息完善\n"
           "4.退出\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
int adminView_object() {
    int object;

    printf("1.学生\n"
           "2.班级\n"
           "3.教师\n"
           "4.教师集体\n"
           "5.课程\n"
           "6.返回上一层菜单\n");
    fflush(stdin);
    scanf("%d",&object);

    return object;
}
//query为查询之意
void adminView_query(Student *pStu,Teacher *pTea,Course *pCour) {

    //object为学生
    if (pStu != NULL && pStu != Head) {
        showStuInformation(1);
        for(int i = 0;pNowStu->course[i] != 0;i++) {
            pCour = searchCourse(pNowStu->course[i]);
            if (pCour == NULL){
                printf("查询学生课程信息失败！");
            }else{
                printf("%-8d%20s\t",pCour->Course_ID,pCour->name);
            }
            if (pNowStu->teacher[i] != -1){
                pTea = searchTeacher(pNowStu->teacher[i]);
                if (pTea == NULL){
                    printf("无此课程教师信息\n");
                    pNowStu->teacher[i] = -1;
                }else{
                    printf("%s\n",pTea->name);
                }
            }else{
                printf("无此课程教师信息\n");
            }
        }
        //查询学生链表，并以需要的班级输出
    }else if (pStu != NULL && pStu == Head){
        int target;
        char choice;

        do {
            printf("请输入要查询的班级：\n"
                   "(2017级8班  201708)\n");
            fflush(stdin);
            scanf("%d", &target);
            target = target * 100 + 1;
            pNowStu = searchStudent(target);
            if (pNowStu == NULL){
                printf("无当前班级信息，请重新输入！\n");
            }else{
                judgeClass();
                showStuInformation(99);
            }
            printf("是否继续：(y/n)");
            fflush(stdin);
            scanf("%c",&choice);
        }while ((choice == 'y' || choice == 'Y') && (choice != 'N' && choice != 'n'));
    }else if (pTea != NULL && pTea != TeacherList){
        showTeaInformation();
    }else if (pTea != NULL && pTea == TeacherList){
        for (int i = 0;(TeacherList + i)->Teacher_ID != 0;i++){
            pNowTea = (TeacherList + i);
            showTeaInformation();
        }
    }else if (pCour != NULL){
        int count;
        for (count = 0;(CourseList + count) != 0;count++){
            printf("%-8d%20s\n",(CourseList + count)->Course_ID,(CourseList + count)->name);
        }
        printf("共%d条记录\n",count);
    }
}
//管理员修改的界面
int adminViewStuOptions(){
    int choice;

    printf("1.修改基本信息\n"
           "2.增加基本信息\n"
           "3.删除学生信息\n"
           "4.修改学生选课信息\n"
           "5.增加学生选课信息\n"
           "6.删除学生选课信息\n"
           "7.返回上一级\n");
    scanf("%d",&choice);

    return choice;
}
//显示学生信息
void showStuInformation(int num){
    int count = 0;
    Student *p = pNowStu;
    Student *q = NULL;

    for(int i = 0;i < num;i++){
        printf("学号      姓名       年龄   性别   班级\n");
        printf("%d  %-20s %d  %c  %d\n", pNowStu->ID, pNowStu->name, pNowStu->age, pNowStu->sex, pNowStu->class);
        count++;
        if(num > 1){
            q = p->pNext;
            p = q;
            if(p->ID - (pNowStu->ID)/100*100 <100){
                printf("%d  %-20s %d  %c  %d\n", p->ID, p->name, p->age, p->sex, p->class);
                count++;
            }else{
                printf("共有%d条记录\n",count);
                pNowStu = p;
            }
        }
    }
}

//学生选课
void chooseCourse(){
    int count;
    int totalCourse;
    char choose;

    printf("当前已选：\n");
    for(count = 0;pNowStu->course[count] != 0;count++){
        for(int j = 0;(CourseList+j)->Course_ID != 0;j++){
            if(pNowStu->course[count] == (CourseList+j)->Course_ID){
                printf("%-8d%20s\t",(CourseList+j)->Course_ID,(CourseList+j)->name);
                if (pNowStu->teacher[count] == -1){
                    printf("NULL\n");
                }else{
                    printf("%s\n",searchTeacher(pNowStu->teacher[count])->name);
                }
                break;
            }
        }
    }
    printf("\n还可选的课程列表：\n");
    for(totalCourse = 0;(CourseList+totalCourse)->Course_ID != 0;totalCourse++){
        int judge = 0;
        for(int i = 0;i < count;i++){
            if ((CourseList+totalCourse)->Course_ID == pNowStu->course[i]){
                judge++;
                break;
            }
        }
        if(judge == 0){
            printf("%-8d%s\n",(CourseList+totalCourse)->Course_ID,(CourseList+totalCourse)->name);
        }
    }
    if(count < 15){
        if (totalCourse > 15) {
            printf("当前已选%d门课,还可选%d门课\n", count, totalCourse - count);
            printf("为了学生本人的生命着想，最多还可选%d门课\n", 15 - count);
        } else {
            printf("当前已选%d门课,还可选%d门课\n", count, totalCourse - count);
        }
        while(1) {
            printf("是否选课（y/n）：");
            fflush(stdin);
            scanf("%c",&choose);
            if (choose == 'Y' || choose == 'y') {
                //修改学生课程数据
                studentCourse(&count);
            } else if (choose == 'N' || choose == 'n') {
                break;
            } else {
                printf("输入错误，请重新选择！\n");
            }
        }
        improveStuInformation(pNowStu);
    }else if(count == 15){
        printf("选课已达最大上限，无法选课\n");
    }
}
//修改学生课程信息
void studentCourse(int *count){
    int result;
    char name[20] = {};

    printf("请输入课程ID或名称：");
    fflush(stdin);
    scanf("%s",name);
    result = weatherCour(name);
    if(result != 0){
        pNowStu->course[(*count)++] = result;
    }else{
        printf("输入无效\n");
    }
    getchar();
    getchar();
}
//用名字或ID检测有无课程信息,有则返回课程ID
int weatherCour(char *name){
    int both_1;
    int both_2;
    int ID;

    if(isdigit(name[0]) && isdigit(name[5])){
        ID = atoi(name);
        for(int i = 0;(CourseList + i)->Course_ID != 0;i++){
            if((CourseList + i)->Course_ID == ID){
                both_1 = ID;
                break;
            }else{
                both_1 = 0;
            }
        }
        for(int i = 0;pNowStu->course[i] != 0;i++){
            if(pNowStu->course[i] == ID){
                both_2 = 0;
                break;
            }else{
                both_2 = 1;
            }
        }
    }else{
        for(int i = 0;(CourseList + i)->Course_ID != 0;i++){
            if(strcmp((CourseList + i)->name,name) != 0){
                both_1 = 0;
            }else{
                ID = (int )(CourseList + i)->Course_ID;
                both_1 = ID;
                break;
            }
        }
        for(int i =0;pNowStu->course[i] != 0;i++){
            if(ID == pNowStu->course[i]){
                both_2 = 0;
                break;
            }else{
                both_2 = 1;
            }
        }
    }
    return both_2 * both_1;
}

//查询教师个人信息
void showTeaInformation(){
    printf("教师工号     姓名     所教学科\n");
    printf("%-9d%-20s%-20s\n",pNowTea->Teacher_ID,pNowTea->name,searchCourse(pNowTea->taughtSubjectsID)->name);
    printf("职称      教龄\n");
    printf("%-20s%3d\n",pNowTea->rank,pNowTea->teachTime);
}
//查询相同课程的学生,有则pNowStu为刚开始相同的学生
void sameQueryCourse(){
    int courID = pNowTea->taughtSubjectsID;
    Student *p = pNowStu;
    Student *q;

    while(p != NULL){
        for(int i = 0;i < 16;i++) {
            if (p->course[i] == courID) {
                pNowStu = p;
                break;
            }
        }
        if(pNowStu == p){
            break;
        }
        q = p->pNext;
        p = q;
    }
    if(p == NULL){
        pNowStu = p;
    }
}
//判断班级
void judgeClass(){
    int integer;
    int remainder;

    //获取原始数据
    integer = pNowStu->ID / 100;
    remainder = integer % 100;

    printf("\n当前班级为%3d班,成员名单如下：\n",remainder);
}
//教师端删除班级学生链表
void deleteStudentInformation() {
    char ID[20] = {};
    char weatherContinue;
    Student *pTemp = NULL;

    printf("请输入要删除的学生信息：\n"
           "(例如：20170801 或ChenGuanYu)\n");
    do {
        scanf("%s", ID);
        //执行完之后，pTemp一定指向当前ID的学生
        if (isdigit(ID[0]) == 1 && isdigit(ID[6]) == 1) {
            pTemp = searchStudent(atoi(ID));
        } else {
            pTemp = searchStuByName(ID);
        }
        changeStuLink(pTemp, 0);
        printf("%s已删除\n", ID);
        printf("是否继续（y/n）：");
        fflush(stdin);
        scanf("%c", &weatherContinue);
    }while ((weatherContinue == 'y' || weatherContinue == 'Y') && (weatherContinue != 'n' && weatherContinue != 'N'));
}

//教师端增加学生信息
void addStuInformation(){
    char ID[20] = {};
    char weatherContinue;
    Student *pTest = NULL;
    Student *pTemp = NULL;

    printf("请输入要增加的学生信息：\n"
           "(例如：20170801 或ChenGuanYu)\n");
    do {
        scanf("%s", ID);
        //判断学生信息是否存在
        if (isdigit(ID[0]) == 1 && isdigit(ID[6]) == 1) {
            pTest = searchStudent(atoi(ID));
        } else {
            pTest = searchStuByName(ID);
        }
        if (pTest != NULL){
            printf("输入无效，学生信息已存在\n");
        }else{
            pTemp = searchPlace(ID);
            changeStuLink(pTemp, 1);
            printf("已新增%s\n", ID);
        }
        printf("是否继续（y/n）：");
        fflush(stdin);
        scanf("%c", &weatherContinue);
    }while ((weatherContinue == 'y' || weatherContinue == 'Y') && (weatherContinue != 'n' && weatherContinue != 'N'));
}

//改变链表，未把班级名单排序，能把链表还链起来,function为零 删除，为1 增加
void changeStuLink(Student *pTemp,int function){
    if (function == 0) {
            pPastStu->pNext = pTemp->pNext;
            free(pTemp);
    } else if (function == 1) {
        Student *pAddStu = (Student *) malloc(sizeof(Student));
        if (pAddStu == NULL) {
            safeFreeAll(CourseList, TeacherList, Head);
            exit(EXIT_FAILURE);
        }
        //输入学生信息
        inputStuInformation_ID(pAddStu);
        inputStuInformation(pAddStu);
        improveStuInformation(pAddStu);
        pPastStu->pNext = pAddStu;
        pAddStu->pNext = pTemp;
    }
}
//改变目标学生的信息
void changeTargetStuInformation() {
    int ID;
    char inputID[20] = {};
    Student *pTemp = NULL;

    printf("请输入要修改的学生ID或姓名：\n"
           "(20170801 或 ChenGuanYu)\n");
    scanf("%s", inputID);
    ID = dealID(inputID);
    if (ID == 0) {
        pTemp = searchStuByName(inputID);
        if (pTemp == NULL) {
            printf("无法识别当前姓名的学生信息\n");
        } else {
            if ((pTemp->ID - pNowStu->ID) > 99) {
                printf("不是所教班级的学生，无法修改学生信息！\n");
            } else {
                inputStuInformation(pTemp);
                improveStuInformation(pTemp);
            }
        }
    } else {
        pTemp = searchStudent(ID);
        if (pTemp == NULL) {
            printf("无法查询到当前ID的学生信息\n");
        } else {
            if ((pTemp->ID - pNowStu->ID) > 99) {
                printf("不是所教班级的学生，无法修改学生信息！\n");
            } else {
                inputStuInformation(pTemp);
                improveStuInformation(pTemp);
            }
        }
    }
}

//找到可插入的位置,返回下一个位置，pPastStu为上一个,若返回NULL则以pPastStu为链表末尾
Student *searchPlace(char *ID){
    int digitalID;
    Student *p = pNowStu;
    Student *q;

    if (isdigit(ID[0]) == 1 && isdigit(ID[6]) == 1) {
        digitalID = atoi(ID);
        while (p != NULL && (p->ID - pNowStu->ID) < 101){
            if (p->ID > digitalID){
                return p;
            }
            q = p->pNext;
            pPastStu = p;
            p = q;
        }
    } else {
        while (p != NULL && (p->ID - pNowStu->ID) < 100){
            q = p->pNext;
            pPastStu = p;
            p = q;
        }
        return p;
    }

    return NULL;
}

//管理员层修改、删除、增加学生课程信息,function分别对应0 -1 1
void AdminChangeStuCourInformation(Student *pStu,int function){
    int count;
    int result;
    char name[20] = {};

    if (function == -1){
        printf("当前已选：\n");
        for(count = 0;pStu->course[count] != 0;count++){
            for(int j = 0;(CourseList+j)->Course_ID != 0;j++){
                if(pStu->course[count] == (CourseList+j)->Course_ID){
                    printf("%-8d%20s\t",(CourseList+j)->Course_ID,(CourseList+j)->name);
                    if (pStu->teacher[count] == -1){
                        printf("NULL\n");
                    }else{
                        printf("%s\n",searchTeacher(pStu->teacher[count])->name);
                    }
                    break;
                }
            }
        }
        printf("当前已有%d节课",count);
        printf("请输入要删除的课程ID或课程名称\n");
        do {
            Course *searchResult;

            fflush(stdin);
            scanf("%s", name);
            result = dealID(name);
            if (result == 0){
                for (int i = 0;i < 16;i++){
                    //为了减少运算次数
                    searchResult = searchCourse(pStu->course[i]);
                    if (strcmp(searchResult->name,name) == 0){
                        result = searchResult->Course_ID;

                        printf("课程已删除");
                        break;
                    }
                }
            }else{
                for (int i = 0;i < 16;i++){
                    if (pStu->course[i] == result){
                        printf("课程已删除");
                        break;
                    }
                }
            }
        }while ()
    }
}

//删除,增加，修改学生的课程信息并保持序号连续，教师信息也同步更新，function的值-1 1 0
void changeStuCourOrder(Student *pStu,int function,int courseID){
    if (function == -1){
        for (int i = 0,j = i;i < 16;i++,j++){
            if (pStu->course[j] == courseID){
                pStu->course[i] = pStu->course[++j];
                break;
            }else{
                pStu->course[i] = pStu->course[j];
            }

        }
    }
}