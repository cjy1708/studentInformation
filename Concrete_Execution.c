//
// Created by 1708cjy on 2020/11/29.
//
//ѧ�����ü���
#include "Concrete_Execution.h"

extern Student *Head;
extern Course *CourseList;
extern Teacher *TeacherList;
extern Teacher *pNowTea;
extern Student *pNowStu;
extern Student *pPastStu;

//�ж�����������ֻ����ַ������ַ������� ����ֵΪ0�����ַ�������
int dealID(char *ID){
    int digitalID;

    if (isdigit(ID[0]) == 1 && isdigit(ID[4]) == 1) {
        digitalID = atoi(ID);
        return digitalID;
    } else {
        return 0;
    }
}
//ѧ��������
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
            printf("����������������룡\n");
        }
    }
}
//��ʦ������
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
                    printf("��ǰ�ѽ̰༶������\n");
                    pNowStu = Head;
                    while(pNowStu != NULL){
                        sameQueryCourse(); //ʹ��pNowStuΪ�տ�ʼ��ͬһ�γ̵�ѧ��
                        judgeClass();
                        showStuInformation(99);
                        getchar();
                        getchar();
                    }
                }else{
                    printf("�����������������");
                }
            }
        }else if (choice_1 == 2) {
            while(1) {
                if (teaView_3() == 1) {
                    printf("�༶��Ա����Ϊ��\n");
                    showStuInformation(99);
                    changeClassmate(teaView_4());
                } else {
                    printf("����س���������һ��˵�\n");
                    getchar();
                    getchar();
                    break;
                }
            }
        }else{
            printf("�����������������\n");
        }
    }
}
//����Ա
void administrator(){
    int choice_1;
    int choice_2;
    int digitalID;
    char ID[20];

    if ((choice_1 = adminView_main()) == 1){
        switch (adminView_object()){
            case 1:
                printf("������Ҫ��ѯ��ѧ����Ϣ��\n"
                       "(���磺20170801 ��ChenGuanYu)\n");
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
                        printf("ѧ����Ϣ�����ڣ�\n");
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
                printf("������Ҫ��ѯ�Ľ�ʦID��");
                do {
                    fflush(stdin);
                    scanf("%d", &digitalID);
                    pNowTea = searchTeacher(digitalID);
                    if (pNowTea != NULL) {
                        adminView_query(NULL, TeacherList + 1, NULL);
                    } else {
                        printf("�޵�ǰ��ʦ��Ϣ��\n");
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
                printf("������󣬽�������һ��˵���\n");
        }
    }else if (choice_1 == 2){
        if((choice_2 = adminView_object()) == 1){
            switch (adminViewStuOptions()) {
                case 1://�޸�ѧ����Ϣ
                    printf("������Ҫ�޸ĵ�ѧ����Ϣ��\n"
                           "(���磺20170801 ��ChenGuanYu)\n");
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
                            printf("��ǰѧ����Ϣ�����ڣ���������һ��˵�\n");
                            break;
                        }else {
                            inputStuInformationLevelUp(pNowStu);
                        }
                    } while (pNowStu != NULL);
                    break;
                case 2://����
                    addStuInformation();
                    break;
                case 3://ɾ��
                    deleteStudentInformation();
                    break;
                case 4://�޸Ŀγ�
                    break;
                case 5://���ӿγ�
                    chooseCourse();
                    break;
                case 6://ɾ���γ�
                    break;
                case 7://������һ���˵�
                    break;
                default://�������
                    printf("����������������룡\n");
            }
        }
    }
}

//ѧ���˽���
int stuView(){
    int choice_1 = 0;
    printf("1.��ѯ\n"
           "2.ѡ��\n"
           "3.�˳�\n"
           "���������ѡ��");
    fflush(stdin);
    scanf("%d", &choice_1);

    return choice_1;
}
//��ʦ�˽���
int teaView_1(){
    int choice = 0;

    printf("1.��ѯ\n"
           "2.�޸����̰༶��Ա\n"
           "3.�˳�\n"
           "���������ѡ��");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
int teaView_2(){
    int choice = 0;

    printf("1.��ѯ������Ϣ\n"
           "2.��ѯ���̰༶����\n"
           "3.�������˵�\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
//�ж��Ƿ�Ϊ�Լ����̰༶�����򷵻�1�����򷵻�0
int teaView_3(){
    int targetClass = 0;

    printf("������Ҫ�޸ĵİ༶��(�꼶�༶  201708��\n");
    fflush(stdin);
    scanf("%d",&targetClass);
    targetClass = targetClass * 100 + 1;
    pNowStu = searchStudent(targetClass);
    if(pNowStu == NULL){
        printf("�޵�ǰ�༶���ݣ�\n");
        return 0;
    }else{
        for(int i = 0;pNowStu->teacher[i] != 0;i++){
            if (pNowStu->teacher[i] == pNowTea->Teacher_ID){
                printf("���ݺϷ����ɼ�������\n");
                return 1;
            }
        }
        printf("�������̰༶���޷����в�����\n");
        return 0;
    }
}
int teaView_4(){
    int choice;

    printf("1.�޸�\n"
           "2.ɾ��\n"
           "3.����\n"
           "4.������һ��\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
//�Խ�ʦ�ĵڶ���˵��жϲ���ʼ��Ӧ����
void changeClassmate(int choice_2){
    if (choice_2 == 1){
        changeTargetStuInformation();
    }else if (choice_2 == 2){
        deleteStudentInformation();
    }else if (choice_2 == 3){
        addStuInformation();
    }else if (choice_2 == 4){
        printf("�༶Ԥ������\n");
    }else {
        printf("�������"
               "���������룡\n");
        changeClassmate(teaView_4());
    }
}

//����Ա����
int adminView_main() {
    int choice;

    printf("1.��ѯ\n"
           "2.�޸�\n"
           "3.ǿ����Ϣ����\n"
           "4.�˳�\n");
    fflush(stdin);
    scanf("%d",&choice);

    return choice;
}
int adminView_object() {
    int object;

    printf("1.ѧ��\n"
           "2.�༶\n"
           "3.��ʦ\n"
           "4.��ʦ����\n"
           "5.�γ�\n"
           "6.������һ��˵�\n");
    fflush(stdin);
    scanf("%d",&object);

    return object;
}
//queryΪ��ѯ֮��
void adminView_query(Student *pStu,Teacher *pTea,Course *pCour) {

    //objectΪѧ��
    if (pStu != NULL && pStu != Head) {
        showStuInformation(1);
        for(int i = 0;pNowStu->course[i] != 0;i++) {
            pCour = searchCourse(pNowStu->course[i]);
            if (pCour == NULL){
                printf("��ѯѧ���γ���Ϣʧ�ܣ�");
            }else{
                printf("%-8d%20s\t",pCour->Course_ID,pCour->name);
            }
            if (pNowStu->teacher[i] != -1){
                pTea = searchTeacher(pNowStu->teacher[i]);
                if (pTea == NULL){
                    printf("�޴˿γ̽�ʦ��Ϣ\n");
                    pNowStu->teacher[i] = -1;
                }else{
                    printf("%s\n",pTea->name);
                }
            }else{
                printf("�޴˿γ̽�ʦ��Ϣ\n");
            }
        }
        //��ѯѧ������������Ҫ�İ༶���
    }else if (pStu != NULL && pStu == Head){
        int target;
        char choice;

        do {
            printf("������Ҫ��ѯ�İ༶��\n"
                   "(2017��8��  201708)\n");
            fflush(stdin);
            scanf("%d", &target);
            target = target * 100 + 1;
            pNowStu = searchStudent(target);
            if (pNowStu == NULL){
                printf("�޵�ǰ�༶��Ϣ�����������룡\n");
            }else{
                judgeClass();
                showStuInformation(99);
            }
            printf("�Ƿ������(y/n)");
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
        printf("��%d����¼\n",count);
    }
}
//����Ա�޸ĵĽ���
int adminViewStuOptions(){
    int choice;

    printf("1.�޸Ļ�����Ϣ\n"
           "2.���ӻ�����Ϣ\n"
           "3.ɾ��ѧ����Ϣ\n"
           "4.�޸�ѧ��ѡ����Ϣ\n"
           "5.����ѧ��ѡ����Ϣ\n"
           "6.ɾ��ѧ��ѡ����Ϣ\n"
           "7.������һ��\n");
    scanf("%d",&choice);

    return choice;
}
//��ʾѧ����Ϣ
void showStuInformation(int num){
    int count = 0;
    Student *p = pNowStu;
    Student *q = NULL;

    for(int i = 0;i < num;i++){
        printf("ѧ��      ����       ����   �Ա�   �༶\n");
        printf("%d  %-20s %d  %c  %d\n", pNowStu->ID, pNowStu->name, pNowStu->age, pNowStu->sex, pNowStu->class);
        count++;
        if(num > 1){
            q = p->pNext;
            p = q;
            if(p->ID - (pNowStu->ID)/100*100 <100){
                printf("%d  %-20s %d  %c  %d\n", p->ID, p->name, p->age, p->sex, p->class);
                count++;
            }else{
                printf("����%d����¼\n",count);
                pNowStu = p;
            }
        }
    }
}

//ѧ��ѡ��
void chooseCourse(){
    int count;
    int totalCourse;
    char choose;

    printf("��ǰ��ѡ��\n");
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
    printf("\n����ѡ�Ŀγ��б�\n");
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
            printf("��ǰ��ѡ%d�ſ�,����ѡ%d�ſ�\n", count, totalCourse - count);
            printf("Ϊ��ѧ�����˵��������룬��໹��ѡ%d�ſ�\n", 15 - count);
        } else {
            printf("��ǰ��ѡ%d�ſ�,����ѡ%d�ſ�\n", count, totalCourse - count);
        }
        while(1) {
            printf("�Ƿ�ѡ�Σ�y/n����");
            fflush(stdin);
            scanf("%c",&choose);
            if (choose == 'Y' || choose == 'y') {
                //�޸�ѧ���γ�����
                studentCourse(&count);
            } else if (choose == 'N' || choose == 'n') {
                break;
            } else {
                printf("�������������ѡ��\n");
            }
        }
        improveStuInformation(pNowStu);
    }else if(count == 15){
        printf("ѡ���Ѵ�������ޣ��޷�ѡ��\n");
    }
}
//�޸�ѧ���γ���Ϣ
void studentCourse(int *count){
    int result;
    char name[20] = {};

    printf("������γ�ID�����ƣ�");
    fflush(stdin);
    scanf("%s",name);
    result = weatherCour(name);
    if(result != 0){
        pNowStu->course[(*count)++] = result;
    }else{
        printf("������Ч\n");
    }
    getchar();
    getchar();
}
//�����ֻ�ID������޿γ���Ϣ,���򷵻ؿγ�ID
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

//��ѯ��ʦ������Ϣ
void showTeaInformation(){
    printf("��ʦ����     ����     ����ѧ��\n");
    printf("%-9d%-20s%-20s\n",pNowTea->Teacher_ID,pNowTea->name,searchCourse(pNowTea->taughtSubjectsID)->name);
    printf("ְ��      ����\n");
    printf("%-20s%3d\n",pNowTea->rank,pNowTea->teachTime);
}
//��ѯ��ͬ�γ̵�ѧ��,����pNowStuΪ�տ�ʼ��ͬ��ѧ��
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
//�жϰ༶
void judgeClass(){
    int integer;
    int remainder;

    //��ȡԭʼ����
    integer = pNowStu->ID / 100;
    remainder = integer % 100;

    printf("\n��ǰ�༶Ϊ%3d��,��Ա�������£�\n",remainder);
}
//��ʦ��ɾ���༶ѧ������
void deleteStudentInformation() {
    char ID[20] = {};
    char weatherContinue;
    Student *pTemp = NULL;

    printf("������Ҫɾ����ѧ����Ϣ��\n"
           "(���磺20170801 ��ChenGuanYu)\n");
    do {
        scanf("%s", ID);
        //ִ����֮��pTempһ��ָ��ǰID��ѧ��
        if (isdigit(ID[0]) == 1 && isdigit(ID[6]) == 1) {
            pTemp = searchStudent(atoi(ID));
        } else {
            pTemp = searchStuByName(ID);
        }
        changeStuLink(pTemp, 0);
        printf("%s��ɾ��\n", ID);
        printf("�Ƿ������y/n����");
        fflush(stdin);
        scanf("%c", &weatherContinue);
    }while ((weatherContinue == 'y' || weatherContinue == 'Y') && (weatherContinue != 'n' && weatherContinue != 'N'));
}

//��ʦ������ѧ����Ϣ
void addStuInformation(){
    char ID[20] = {};
    char weatherContinue;
    Student *pTest = NULL;
    Student *pTemp = NULL;

    printf("������Ҫ���ӵ�ѧ����Ϣ��\n"
           "(���磺20170801 ��ChenGuanYu)\n");
    do {
        scanf("%s", ID);
        //�ж�ѧ����Ϣ�Ƿ����
        if (isdigit(ID[0]) == 1 && isdigit(ID[6]) == 1) {
            pTest = searchStudent(atoi(ID));
        } else {
            pTest = searchStuByName(ID);
        }
        if (pTest != NULL){
            printf("������Ч��ѧ����Ϣ�Ѵ���\n");
        }else{
            pTemp = searchPlace(ID);
            changeStuLink(pTemp, 1);
            printf("������%s\n", ID);
        }
        printf("�Ƿ������y/n����");
        fflush(stdin);
        scanf("%c", &weatherContinue);
    }while ((weatherContinue == 'y' || weatherContinue == 'Y') && (weatherContinue != 'n' && weatherContinue != 'N'));
}

//�ı�����δ�Ѱ༶���������ܰ�����������,functionΪ�� ɾ����Ϊ1 ����
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
        //����ѧ����Ϣ
        inputStuInformation_ID(pAddStu);
        inputStuInformation(pAddStu);
        improveStuInformation(pAddStu);
        pPastStu->pNext = pAddStu;
        pAddStu->pNext = pTemp;
    }
}
//�ı�Ŀ��ѧ������Ϣ
void changeTargetStuInformation() {
    int ID;
    char inputID[20] = {};
    Student *pTemp = NULL;

    printf("������Ҫ�޸ĵ�ѧ��ID��������\n"
           "(20170801 �� ChenGuanYu)\n");
    scanf("%s", inputID);
    ID = dealID(inputID);
    if (ID == 0) {
        pTemp = searchStuByName(inputID);
        if (pTemp == NULL) {
            printf("�޷�ʶ��ǰ������ѧ����Ϣ\n");
        } else {
            if ((pTemp->ID - pNowStu->ID) > 99) {
                printf("�������̰༶��ѧ�����޷��޸�ѧ����Ϣ��\n");
            } else {
                inputStuInformation(pTemp);
                improveStuInformation(pTemp);
            }
        }
    } else {
        pTemp = searchStudent(ID);
        if (pTemp == NULL) {
            printf("�޷���ѯ����ǰID��ѧ����Ϣ\n");
        } else {
            if ((pTemp->ID - pNowStu->ID) > 99) {
                printf("�������̰༶��ѧ�����޷��޸�ѧ����Ϣ��\n");
            } else {
                inputStuInformation(pTemp);
                improveStuInformation(pTemp);
            }
        }
    }
}

//�ҵ��ɲ����λ��,������һ��λ�ã�pPastStuΪ��һ��,������NULL����pPastStuΪ����ĩβ
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

//����Ա���޸ġ�ɾ��������ѧ���γ���Ϣ,function�ֱ��Ӧ0 -1 1
void AdminChangeStuCourInformation(Student *pStu,int function){
    int count;
    int result;
    char name[20] = {};

    if (function == -1){
        printf("��ǰ��ѡ��\n");
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
        printf("��ǰ����%d�ڿ�",count);
        printf("������Ҫɾ���Ŀγ�ID��γ�����\n");
        do {
            Course *searchResult;

            fflush(stdin);
            scanf("%s", name);
            result = dealID(name);
            if (result == 0){
                for (int i = 0;i < 16;i++){
                    //Ϊ�˼����������
                    searchResult = searchCourse(pStu->course[i]);
                    if (strcmp(searchResult->name,name) == 0){
                        result = searchResult->Course_ID;

                        printf("�γ���ɾ��");
                        break;
                    }
                }
            }else{
                for (int i = 0;i < 16;i++){
                    if (pStu->course[i] == result){
                        printf("�γ���ɾ��");
                        break;
                    }
                }
            }
        }while ()
    }
}

//ɾ��,���ӣ��޸�ѧ���Ŀγ���Ϣ�����������������ʦ��ϢҲͬ�����£�function��ֵ-1 1 0
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