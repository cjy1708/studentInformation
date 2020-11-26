//
// Created by 1708cjy on 2020/11/25.
//

#include "basic_1.h"
#include <stdio.h>

//判断是否有内容
int weatherInformation(){
    FILE *fp = fopen(studentInformation_PATH,"a+");

    fseek(fp,0,SEEK_SET);
    Student text = {.ID = 0};
    fread(&text,sizeof(Student),1,fp);
    fclose(fp);
    if (text.ID == 0) return 0;
    else return 1;
}
//从文件中读出学生信息
void readInformation(){
    FILE *fp = fopen(studentInformation_PATH,"a+");

    fseek(fp,0,SEEK_SET);

}