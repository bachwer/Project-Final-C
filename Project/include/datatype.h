#ifndef DATATYPE_H#define DATATYPE_H#include <stdbool.h>struct Date {    int month, day, year;};//Subjectstruct subject {    char StudenId[10];    char name[20];    // Programing C    bool C;    // scratch    bool S;    // Eglish    bool E;};//Stdentstruct information{    char StudenId[10];    char classroomId[10];    char name[20];    struct Date dateOfbirth;    char gender[8];    char email[30];    char phone[20];    struct subject subjects;    //char password[20];};//Teacherstruct teacher {    char teacherId[10];    char classroomId[10];    char name[20];    struct Date dateOfbirth;    char gender[8];    char email[30];    char phone[20];};//Classstruct Classroom {    char classroomId[10];    char teacherId[10];    char teacherName[20];    char classroomName[10];};//adminstruct admin {    char email[50];    char password[50];};//declare structstruct admin adminAccount;struct Classroom *class;struct information *student;struct teacher *teachers;#endif