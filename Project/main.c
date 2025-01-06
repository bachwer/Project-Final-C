#include "include/datatype.h"
#include "include/function.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int menu, menu1;
    //counter variable for Student
    int nS;
    //counter variable for Teacher
    int nT;
    //counter variable for Class
    int nC;

//login admin
    setPadmin();
    adminlogin();
//--

    system("clear"); //macos dung clear
    menu0:
    system("clear");//macos dung clear
    //menu Start
    menuStart(&menu);
    switch (menu) {
        //Student
        case 1:
            system("clear");//macos dung clear
                menustudent:
                menuStudent(&menu);
                switch (menu) {
                    //add Student
                    case 1:
                        system("clear");//macos dung clear
                        dataLoadS(&student, &nS);
                        dataLoadC(&class, &nC);
                        addStudent(&student, &nS, &class, &nC);
                    goto menu1;
                    //Show Student
                    case 2:
                        dataLoadS(&student, &nS);
                    showStudent(&student, &nS);
                    goto menu1;
                    //Search Student
                    case 3:
                        system("clear");//macos dung clear
                        dataLoadS(&student, &nS);
                    searchStudent(&student, &nS);
                    goto menu1;
                    //Edit Student
                    case 4:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        dataLoadS(&student, &nS);
                    editStudent(&student, &nS, &class, &nC);
                    dataSaveS(&student, &nS);
                    goto menu1;
                    //Delete Student
                    case 5:
                        system("clear");//macos dung clear
                        dataLoadS(&student, &nS);
                    deleteStudent(&student, &nS);
                    dataSaveS(&student, &nS);
                    goto menu1;
                    // Sort Student
                    case 6:
                        system("clear");//macos dung clear
                        dataLoadS(&student, &nS);
                    sortStudentBN(&student, &nS);
                    dataSaveS(&student, &nS);
                    goto menu1;

                    //Back to Menu Start
                    case 7:
                        dataLoadS(&student, &nS);
                        chooseSubject(&student, &nS);
                        dataSaveS(&student, &nS);
                        goto menu1;;

                    case 8:
                    system("clear");//macos dung clear
                    goto menu0;

                    //Admin Delete
                    case 9:
                        adminlogin();
                    do {
                        printf("\033[31m1.Delete\033[0m\n");
                        printf("\033[32m2.No!!\033[0m\n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 1) {
                        clearFileS();
                        goto menu1;
                    }else {
                        goto menu1;
                    }

                    default:
                        printf("Exited !!!");
                    return 1;
                    menu1:
                    do {
                        printf("1.Go Back \n");
                        printf("2.Exit \n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 1) {
                        goto menustudent;
                    }else {
                        return 1;
                    }
                }
        //Teacher
        case 2:
            menusteacher:
            system("clear");
                menuTeacher(&menu);
                switch (menu) {
                    //Add teacher
                    case 1:
                        system("clear");//macos dung clear
                        dataLoadT(&teachers, &nT);
                        dataLoadC(&class, &nC);
                        addTeacher(&teachers, &nT, &class, &nC);
                    goto menu2;

                    //Show teacher
                    case 2:
                        system("clear");//macos dung clear
                        dataLoadT(&teachers, &nT);
                    showTeacher(&teachers, &nT);
                    goto menu2;
                    // Search Teacher
                    case 3:
                        system("clear");//macos dung clear
                        dataLoadT(&teachers, &nT);
                    searchTeacher(&teachers, &nT);
                    goto menu2;

                    //Edit teacher
                    case 4:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        dataLoadT(&teachers, &nT);
                        editTeacher(&teachers, &nT,&class, &nC);
                        dataSaveT(&teachers, &nT);
                        dataSaveC(&class, &nC);
                    goto menu2;
                    //Delete Teacehr
                    case 5:
                        system("clear");//macos dung clear
                        dataLoadT(&teachers, &nT);
                        deleteTeacher(&teachers, &nT);
                    dataSaveT(&teachers, &nT);
                    goto menu2;
                    //Back to Menu Start
                    case 6:
                        system("clear");//macos dung clear
                        goto menu0;

                    case 7:
                        adminlogin();
                    do {
                        printf("\033[31m1.Delete\033[0m\n");
                        printf("\033[32m2.No!!\033[0m\n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 1) {
                        clearFileT();
                        goto menu2;
                    }else {
                        goto menu2;
                    }

                    default:
                        printf("Exited !!!");
                    return 1;
                    menu2:
                    do {
                        printf("1.Go Back \n");
                        printf("2.Exit \n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 1) {
                        goto menusteacher;
                    }else {
                        return 1;
                    }

        }
        //Class
        case 3:
            system("clear");//macos dung clear
            menuclass:
            system("clear");
                menuClass(&menu);
                switch (menu) {
                    //Add Class
                    case 1:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        addClass(&class, &nC);
                    goto menu3;
                    //Show all Class
                    case 2:
                        system("clear");
                        dataLoadC(&class, &nC);
                    showClass(&class, &nC);
                    goto menu3;
                    //Edit Class
                    case 3:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        editClass(&class, &nC);
                    dataSaveC(&class, &nC);
                    goto menu3;
                    //Delete Class
                    case 4:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        deleteClass(&class, &nC);
                    dataSaveC(&class, &nC);
                    goto menu3;
                    //Show Details Classs
                    case 5:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        dataLoadS(&student, &nS);
                        dataLoadT(&teachers, &nT);
                        detailslass(&class, &nC, &student, &nS, &teachers, &nT);
                    goto menu3;
                    //remove students from class[6]
                    case 6:
                        system("clear");//macos dung clear
                        dataLoadC(&class, &nC);
                        dataLoadS(&student, &nS);
                        deleteStudentandAddForclass(&class, &nC, &student, &nS);
                        dataSaveC(&class, &nC);
                        dataSaveS(&student, &nS);
                    goto menu3;

                    case 7:
                        system("clear");//macos dung clear
                    dataLoadC(&class, &nC);
                    dataLoadT(&teachers, &nT);
                    deleteTeacherandAddForclass(&class, &nC, &teachers, &nT);
                    dataSaveC(&class, &nC);
                    dataSaveT(&teachers, &nT);
                    goto menu3;


                    case 8:
                        dataLoadC(&class, &nC);
                        dataLoadS(&student, &nS);
                        addStudentForClass(&class, &nC,  &student, &nS);
                        dataSaveS(&student, &nS);
                        goto menu3;

                    case 9:
                        dataLoadC(&class, &nC);
                        dataLoadT(&teachers, &nT);
                        addTeacherForClass(&class, &nC, &teachers, &nT);
                        dataSaveT(&teachers, &nT);
                        goto menu3;


                    case 10:
                        goto menu0;

                    case 11:
                        adminlogin();
                    do {
                        printf("\033[31m1.Delete\033[0m\n");
                        printf("\033[32m2.No!!\033[0m\n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 1) {
                        clearFileC();
                        goto menu3;
                    }else {
                        goto menu3;
                    }


                    default:
                        printf("Exited !!!");
                    return 1;
                    menu3:
                    do {
                        printf("1.Go Back \n");
                        printf("2.Exit \n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 1) {
                        goto menuclass;
                    }else {
                        return 1;
                    }
                }

        default:
            printf("Exited !!!");
            return 0;
    }
}
