#include "../include/function.h"
#include "../include/datatype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // read;  write lseek; for file
#include <termios.h> // for echo mode
#include <stdbool.h>

//Kham khao, de nhap "*" cho mat khau (macos)
//(disable echo mode)The character you enter will not be displayed on the screen
void disable_echo_mode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);  // Lấy cấu hình hiện tại của terminal
    t.c_lflag &= ~(ECHO | ICANON); // Tắt chế độ echo và chế độ nhập dòng
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Áp dụng thay đổi ngay lập tức
}
//opposite of above..
void enable_echo_mode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);  // Lấy cấu hình hiện tại của terminal
    t.c_lflag &= ~(ECHO | ICANON); // Tắt chế độ echo và chế độ nhập dòng
    tcsetattr(STDIN_FILENO, TCSANOW, &t);// Áp dụng thay đổi
}


//show menu Start
void menuStart(int *menu) {
    do {
        printf("\n");
        printf(" *** Student Management System Using C *** \n");
        printf("\n");
        printf("\t\tCHOOSE YOUR ROLE\n");
        printf("\t=========================\n");
        printf("\t[1] Student Management.\n");
        printf("\t[2] Teacher Management.\n");
        printf("\t[3] Class management. \n");
        printf("\t[0] Exit the Program.\n");
        printf("\t=========================\n");
        printf("Enter your choice: ");
        if(scanf("%d", menu) != 1) {
            printf("Invalid\n");
            }
        getchar();
    }while (*menu > 3|| *menu < 0);
}

// set password for admin
void setPadmin() {
    struct admin account;
    strcpy(account.email, "admin@gmail.com");
    strcpy(account.password, "admin");

    FILE *file = fopen("admin.dat", "wb");
    if (file == NULL) {
        perror("Erorr open file!!!");
        return;
    }
    fwrite(&account, sizeof(struct admin), 1, file);
    fclose(file);
}

//login admin
void adminlogin() {
    struct admin adminAccount;
    FILE *f = fopen("admin.dat", "rb");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }
    size_t const numR = fread(&adminAccount, sizeof(struct admin), 1, f);
    fclose(f);

    if (numR != 1) {
        printf("Failed to read file.\n");
        return;
    }
    char email[100];
    char password[50];
    int i = 0;
    admin:
    printf("\t\t\t  LOGIN\n");
    printf("\t=========================\n");
    printf("Email: ");
    scanf("%s", email);
    fflush(stdin);

    printf("Enter Password: ");
    disable_echo_mode();

    while (1) {
        char ch = getchar();
        if (ch == '\n') {
            password[i] = '\0';
            break;
        } else if (ch == 127) { //delete ASClII 127
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }

    enable_echo_mode();
    printf("\n");

    printf("||");
    for (int j = 0; j < 30; j++) {
        if (j % 2 == 0) {
            printf("\033[33m=\033[0m");
        } else {
            printf("\033[32m=\033[0m");
        }
        fflush(stdout);
        usleep(50000);
    }
    printf("||\n");

    if (strcmp(email, adminAccount.email) == 0 && strcmp(password, adminAccount.password) == 0) {
        printf("\t\t\033[32mLogin Successful.\033[0m\n");
        usleep(50000);
    } else {
        printf("\t\t\033[31mLogin Failed. Try Again.\033[0m\n");
        fflush(stdin);
        goto admin;
    }
}

//-----------------------------------MENU STUDENT--------------------------------------//
void menuStudent(int *menu) {
    do {
        printf(" *** Student Management System Using C *** \n");
        printf("\n");
        printf("\t\t\t\tMENU\n");
        printf("\t=========================\n");
        printf("\t[1] Add A New Student.\n");
        printf("\t[2] Show All Student.\n");
        printf("\t[3] Search A Student.\n");
        printf("\t[4] Edit A Student.\n");
        printf("\t[5] Delete A Student.\n");
        printf("\t[6] Sort Students By Name.\n");
        printf("\t[7] Choose Subjects\n");
        printf("\t[8] Back\n");
        printf("\t\033[31m[9] Clear ALL FILE\033[0m\n");
        printf("\t[0] Exit Program.\n");
        printf("\t=========================\n");
        printf("Enter your choice: ");
        scanf("%d", menu);
        getchar();
    }while (*menu > 9|| *menu < 0);
}
//--------------------------------FUNCTION IN MENU STUDENT-----------------------------//
//Function add Student[1]
void addStudent(struct information *student[], int *n, struct Classroom *class[], int *r) {
    //gender
    char gender;

    char *endptr;
    int indext;
    int test1;
    do{
        test1 = 0;
        char input[10];

        printf("Enter quanity Student: ");
        fgets(input, sizeof(input), stdin);
        fflush(stdin);
        int const index = strtol(input, &endptr, 10);

        if (*endptr != '\0' && *endptr != '\n') {
            printf("Invalid !!!\n");
            test1 = 1;
        }
        if(index < 1) {
            printf("Invalid !!!\n");
            test1 = 1;
        }
        indext = *n;
        *n += index;
    } while (test1 != 0);



    *student = (struct information*) realloc(*student, *n * sizeof(struct information));
    if (*student == NULL) {
        printf("erorr \n");
        return;
    }
    int count = 0;
    for(int i = indext; i < *n; i++) {
        count++;
            add:
        while(1) {
            printf("-------Student %d-------\n", count);
            printf("Enter Student ID: ");
            fgets((*student)[i].StudenId, sizeof(*student)[i].StudenId, stdin);
            (*student)[i].StudenId[strlen((*student)[i].StudenId) - 1] = '\0';
            fflush(stdin);
            strcpy((*student)[i].subjects.StudenId, (*student)[i].StudenId);
            (*student)[i].subjects.C = false;
            (*student)[i].subjects.S = false;
            (*student)[i].subjects.E = false;
            //condition
            //
            for(int j = 0; j < i; j++) {
                if(strcmp((*student)[j].StudenId, (*student)[i].StudenId) == 0) {
                    printf("\033[31mInvalid ID ID.\033[0m\n");
                    goto add;
                }
            }

            if (strlen((*student)[i].StudenId) < 1) {
                printf("\033[31mInvalid Student ID.\033[0m\n");
                goto add;
            }
            if(strlen((*student)[i].StudenId) >= 8){
                printf("\033[31mInvalid Student ID.\033[0m\n");
                goto add;
            }
            //done
            printf("Enter Name: ");
            fgets((*student)[i].name, sizeof(*student)[i].name, stdin);
            (*student)[i].name[strlen((*student)[i].name) - 1] = '\0';
            //condition
            if (strlen((*student)[i].name) <= 8) {
                printf("\033[31mInvalid Student Name\033[0m\n");
                goto add;
            }
            char *str = (char *)malloc(strlen((*student)[i].name) + 1);
            strcpy(str,(*student)[i].name);
            const char *pos = strchr(str, ' ');
            if(pos == NULL) {
                printf("\033[31mInvalid Student Name\033[0m\n");
                goto add;
            }
            free(str);
            strcpy((*student)[i].subjects.name, (*student)[i].name);
            //call funcstion Show Class;
            showClass(class, r);
            int menu1;
            if((*class)[0].classroomId[0] == '\0') {
                do {
                    printf("There are no classes.\n");
                    printf("1.Continue\n");
                    printf("2.Back & don't save\n");
                    scanf("%d", &menu1);
                }while(menu1 != 1 && menu1 != 2);
                if(menu1 == 2) {
                   return;
                }else {
                    strcpy((*student)[i].classroomId, "NULL");
                }
            }
            printf("|========================================|\n");
            printf("|             Press S to skip            |\n");
            printf("|========================================|\n");
                printf("Enter ");
                printf("\033[31mID\033[0m ");
                printf("Class room: ");
                fgets((*student)[i].classroomId, sizeof(*student)[i].classroomId, stdin);
                (*student)[i].classroomId[strlen((*student)[i].classroomId) - 1] = '\0';

                //condition
                int isValid = 0;
                for (int z = 0; z < *r; z++) {
                    if (strcmp((*class)[z].classroomId, (*student)[i].classroomId) == 0) {
                        isValid = 1;
                    }
                }
                if(strcmp((*student)[i].classroomId, "s") == 0 || strcmp((*student)[i].classroomId, "S") == 0) {
                    strcpy((*student)[i].classroomId, "NULL");
                    isValid = 1;
                }

                if (!isValid) {
                    printf("\033[31mInvalid ID CLass ID111.\033[0m\n");
                    goto add;
                }

            //done

            //date
            int test;
            do{
                test = 1;
                printf("Month (1-12): ");
                scanf("%d", &(*student)[i].dateOfbirth.month);
                if ((*student)[i].dateOfbirth.month < 1 || (*student)[i].dateOfbirth.month > 12) {
                    printf("\033[31mInvalid month.\033[0m\n");
                    test = 0;
                    fflush(stdin);
                    continue;
                }

                printf("Day (1-31): ");
                scanf("%d", &(*student)[i].dateOfbirth.day);
                if ((*student)[i].dateOfbirth.day < 1 || (*student)[i].dateOfbirth.day > 31) {
                    printf("\033[31mInvalid day.\033[0m\n");
                    test = 0;
                    fflush(stdin);
                    continue;
                }

                printf("Year (1950-2023): ");
                scanf("%d", &(*student)[i].dateOfbirth.year);
                if ((*student)[i].dateOfbirth.year < 1950 || (*student)[i].dateOfbirth.year > 2023) {
                    printf("\033[31mInvalid year.\033[0m\n");
                    fflush(stdin);
                    test = 0;
                }

            } while (test != 1);

            fflush(stdin);
            while (1) {
                printf("Boy Or Girl: ('b' or 'g'): ");
                scanf("%c", &gender);
                getchar();
                if(gender == 'b'|| gender == 'B') {
                    strcpy((*student)[i].gender, "Man");
                    break;
                }else if(gender == 'g'|| gender == 'G'){
                    strcpy((*student)[i].gender, "wonman");
                    break;
                }
            }

            printf("Enter Email : ");
            fgets((*student)[i].email, sizeof(*student)[i].email, stdin);
            (*student)[i].email[strlen((*student)[i].email) - 1] = '\0';
            //condition
            for(int j = 0; j < i; j++) {
                if(strcmp((*student)[j].email, (*student)[i].email) == 0) {
                    printf("\033[31mInvalid Email ID111.\033[0m\n");
                    goto add;
                }
            }
            const char gmail[] = "@gmail.com";

            if (strlen((*student)[i].email) < strlen(gmail)) {
                printf("\033[31mInvalid Teacher email.\033[0m\n");
                goto add;
            } else {
                int const strPig = strlen((*student)[i].email);
                int const strS = strlen(gmail);

                int is_valid = 1;
                for (int j = 0; j < strS; j++) {
                    if ((*student)[i].email[strPig - strS + j] != gmail[j]) {
                        is_valid = 0;
                        break;
                    }
                }

                if (!is_valid) {
                    printf("\033[31mInvalid Student email\033[0m\n");
                    goto add;
                }
            }

            printf("Enter Phone: ");
            fgets((*student)[i].phone, sizeof(*student)[i].phone, stdin);
            (*student)[i].phone[strlen((*student)[i].phone) - 1] = '\0';
            //condition
            for(int j = 0; j < i; j++) {
                if(strcmp((*student)[j].phone, (*student)[i].phone) == 0) {
                    printf("\033[31mInvalid Phone ID111.\033[0m\n");
                    goto add;
                }
            }
            if (strlen((*student)[i].phone) < 9) {
                printf("\033[31mInvalid Student Phone.\033[0m\n");
                goto add;
            }
                printf("\033[32mAdd Student Success.\033[0m\n");
                dataSaveS(student, n);
                break;
            }
        }
        //password
    }
//Function Show Student [2]
void showStudent(struct information *student[], int const *n) {
    printf("\t\t\t**** All Student ****\n");
    printf("\n");
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    printf("|\t ID\t\t |\t\t\tName\t\t\t |\t\t\t\tEmail\t\t\t\t |\t\tPhone\t\t |\t\tGender\t |\tClass room\t | Date of birht |\n");
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    for(int i = 0; i < *n; i++) {
            printf("| %-10s | %-25s | %-33s | %-17s | %-13s | %-14s|   %-2d/%-2d/%-6d|\n",(*student)[i].StudenId,(*student)[i].name,(*student)[i].email, (*student)[i].phone, (*student)[i].gender, (*student)[i].classroomId, (*student)[i].dateOfbirth.day , (*student)[i].dateOfbirth.month, (*student)[i].dateOfbirth.year);
    }
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
}
//Function search Student [3]
void searchStudent(struct information *student[], int const *n) {
    char search[20];
    printf("Enter name student to search: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    int check = 0;
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    printf("|\t ID\t\t |\t\t\tName\t\t\t |\t\t\t\tEmail\t\t\t\t |\t\tPhone\t\t |\t\tGender\t |\tClass room\t | Date of birht |\n");
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    for(int i = 0; i < *n; i ++) {
        if(strstr((*student)[i].name, search) != NULL) {
            printf("| %-10s | %-25s | %-33s | %-17s | %-13s | %-14s|   %d/%d/%-6d |\n",(*student)[i].StudenId, (*student)[i].name,(*student)[i].email, (*student)[i].phone, (*student)[i].gender, (*student)[i].classroomId, (*student)[i].dateOfbirth.month , (*student)[i].dateOfbirth.day, (*student)[i].dateOfbirth.year);
            printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
            check = 1;
        }
    }

    if(!check) {
        printf("\033[31mStudent information'Does not' found!!.\033[0m\n");
    }else {
        printf("\033[32mStudent information found!!.\033[0m\n");
    }

}
//Function Edit Student[4]
void editStudent(struct information *student[], int const *n,struct Classroom *class[], int *r) {
    char gender;
    char search[20];
    printf("Enter student ID  to edit: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    fflush(stdin);
    int check = 0;
    for(int i = 0; i < *n; i ++) {
            if(strcmp((*student)[i].StudenId, search) == 0) {
                add:
                while (1) {
                printf("--ID Stdent : %s --\n", (*student)[i].StudenId);
                printf("Enter information to change: \n");
                    printf("Enter Name: ");
                    fgets((*student)[i].name, sizeof(*student)[i].name, stdin);
                    (*student)[i].name[strlen((*student)[i].name) - 1] = '\0';
                    //condition
                    if (strlen((*student)[i].name) <= 8) {
                        printf("\033[31mInvalid Student Name\033[0m\n");
                        goto add;
                    }
                    char *str = (char *)malloc(strlen((*student)[i].name) + 1);
                    strcpy(str,(*student)[i].name);
                    const char *pos = strchr(str, ' ');
                    if(pos == NULL) {
                        printf("\033[31mInvalid Student Name\033[0m\n");
                        goto add;
                    }
                    free(str);
                    //done
                    for (int j = 0; j < *n; j++) {
                        if(strcmp((*student)[i].subjects.StudenId, search ) == 0){
                            strcpy((*student)[i].subjects.name,(*student)[i].name);
                        }
                    }
                   showClass(class, r);
                    int menu1;
                    if((*class)[0].classroomId[0] == '\0') {
                        do {
                            printf("There are no classes.\n");
                            printf("1.Continue\n");
                            printf("2.Back & don't save\n");
                            scanf("%d", &menu1);
                        }while(menu1 != 1 && menu1 != 2);
                        if(menu1 == 2) {
                            return;
                        }else {
                            strcpy((*student)[i].classroomId, "NULL");
                        }
                    }
                    printf("|========================================|\n");
                    printf("|             Press S to skip            |\n");
                    printf("|========================================|\n");
                    printf("Enter ");
                    printf("\033[31mID\033[0m ");
                    printf("Class room: ");
                fgets((*student)[i].classroomId, sizeof(*student)[i].classroomId, stdin);
                (*student)[i].classroomId[strlen((*student)[i].classroomId) - 1] = '\0';

                //condition
                    int isValid = 0;
                    for (int z = 0; z < *r; z++) {
                        if (strcmp((*class)[z].classroomId, (*student)[i].classroomId) == 0) {
                            isValid = 1;
                            break;
                        }
                    }
                    if(strcmp((*student)[i].classroomId, "s") == 0 || strcmp((*student)[i].classroomId, "S") == 0) {
                        strcpy((*student)[i].classroomId, "NULL");
                        isValid = 1;
                    }
                    if (!isValid) {
                        printf("\033[31mInvalid Class ID111.\033[0m\n");
                        goto add;
                    }

                //done

                int test;
            do{
                test = 1;
                printf("Month (1-12): ");
                scanf("%d", &(*student)[i].dateOfbirth.month);
                if ((*student)[i].dateOfbirth.month < 1 || (*student)[i].dateOfbirth.month > 12) {
                    printf("\033[31mInvalid month.\033[0m\n");
                    fflush(stdin);
                    goto add;
                }

                printf("Day (1-31): ");
                scanf("%d", &(*student)[i].dateOfbirth.day);
                if ((*student)[i].dateOfbirth.day < 1 || (*student)[i].dateOfbirth.day > 31) {
                    fflush(stdin);
                    printf("\033[31mInvalid day.\033[0m\n");
                    goto add;
                }

                printf("Year (1950-2023): ");
                scanf("%d", &(*student)[i].dateOfbirth.year);
                if ((*student)[i].dateOfbirth.year < 1950 || (*student)[i].dateOfbirth.year > 2023) {
                    fflush(stdin);
                    printf("\033[31mInvalid year.\033[0m\n");
                    test = 0;
                }

            } while (test != 1);

            fflush(stdin);
            while (1) {
                printf("Boy Or Girl: ('b' or 'g'): ");
                scanf("%c", &gender);
                getchar();
                if(gender == 'b'|| gender == 'B') {
                    strcpy((*student)[i].gender, "Man");
                    break;
                }else if(gender == 'g'|| gender == 'G'){
                    strcpy((*student)[i].gender, "wonman");
                    break;
                }
            }

            printf("Enter Email : ");
            fgets((*student)[i].email, sizeof(*student)[i].email, stdin);
            (*student)[i].email[strlen((*student)[i].email) - 1] = '\0';
            //condition
             for(int j = 0; j < i; j++) {
                 if(j == i) {
                     continue;
                 }
                if(strcmp((*student)[j].email, (*student)[i].email) == 0) {
                    printf("\033[31mInvalid Email ID111.\033[0m\n");
                    goto add;
                }
            }
                    const char gmail[] = "@gmail.com";

                    if (strlen((*student)[i].email) < strlen(gmail)) {
                        printf("\033[31mInvalid Teacher email.\033[0m\n");
                        goto add;
                    } else {
                        int const strPig = strlen((*student)[i].email);
                        int const strS = strlen(gmail);

                        int is_valid = 1;
                        for (int j = 0; j < strS; j++) {
                            if ((*student)[i].email[strPig - strS + j] != gmail[j]) {
                                is_valid = 0;
                                break;
                            }
                        }

                        if (!is_valid) {
                            printf("\033[31mInvalid Student email\033[0m\n");
                            goto add;
                        }
                    }

            printf("Enter Phone: ");
            fgets((*student)[i].phone, sizeof(*student)[i].phone, stdin);
            (*student)[i].phone[strlen((*student)[i].phone) - 1] = '\0';
            //condition
            if (strlen((*student)[i].phone) < 8) {
                printf("\033[31mInvalid Student Phone.\033[0m\n");
                goto add;
            }
                    for(int j = 0; j < *n; j++) {
                        if(j == i) {
                            continue;
                        }
                        if(strcmp((*student)[j].phone, (*student)[i].phone) == 0) {
                            printf("\033[31mInvalid phone ID111.\033[0m\n");
                            goto add;
                        }
                    }
            //done
                check = 1;
                break;

            }
        }
    }
    if(!check) {
        printf("\033[31mStudent infromation 'Does not' found\033[0m\n");
    }else {
        printf("\033[32mEdit Student Success.\033[0m\n");
    }
}
//Function Delete Student[5]
void deleteStudent(struct information *student[], int *n) {
    char search[20];
    printf("Enter student ID  to delete: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    int menu1;
    menu1:
        do {
            printf("\033[31m1.Delete\033[0m\n");
            printf("\033[32m2.No!!\033[0m\n");
            scanf("%d", &menu1);
        }while(menu1 != 1 && menu1 != 2);
        if(menu1 == 2) {
            return;
        }
    int check = 0;
    for(int i = 0; i < *n; i ++) {
        if(strcmp((*student)[i].StudenId, search) == 0) {
            for(int j = i; j < *n - 1; j++) {
                strcpy((*student)[j].StudenId, (*student)[j + 1].StudenId );
                strcpy((*student)[j].classroomId, (*student)[j + 1].classroomId );
                strcpy((*student)[j].name, (*student)[j + 1].name );
                strcpy((*student)[j].email, (*student)[j + 1].email );
                strcpy((*student)[j].gender, (*student)[j + 1].gender );
                strcpy((*student)[j].phone, (*student)[j + 1].phone );
                //date
                (*student)[j].dateOfbirth.day = (*student)[j + 1].dateOfbirth.day;
                (*student)[j].dateOfbirth.month = (*student)[j + 1].dateOfbirth.month;
                (*student)[j].dateOfbirth.year = (*student)[j + 1].dateOfbirth.year;
                //subject
                strcpy((*student)[j].subjects.name, (*student)[j + 1].subjects.name);
                strcpy((*student)[j].subjects.StudenId, (*student)[j + 1].subjects.StudenId);
                (*student)[j].subjects.C = (*student)[j + 1].subjects.C;
                (*student)[j].subjects.S = (*student)[j + 1].subjects.S;
                (*student)[j].subjects.E = (*student)[j + 1].subjects.E;
            }
            (*n)--;
            check = 1;
            printf("\033[32mDelted studen ID: %s is Success\033[0m\n",search);
            break;
        }else {
            continue;
        }
    }
    if(!check) {
        printf("\033[31mStudent infromation 'Does not' found\033[0m\n");
    }
}
//Sort Students by name[6]
void sortStudentBN(struct information *student[],int const *n) {
    int menu;
    int check;
    do {
        printf("1.Decrease\n");
        printf("2.Increase\n");
        printf("Enter your number:" );
        scanf("%d", &menu);
        getchar();
    }while(menu != 1 && menu != 2);
    if(menu == 1) {
        check = 1;
    }else {
        check = 0;
    }

    for(int i = 1; i < *n; i++) {
        for(int j = 0; j < *n; j++) {
            if(check? strcmp((*student)[i].name, (*student)[j].name)  > 0 : strcmp((*student)[i].name, (*student)[j].name)  < 0) {
                char tempchar[50];
                //ID
                strcpy(tempchar, (*student)[i].StudenId);
                strcpy((*student)[i].StudenId, (*student)[j].StudenId);
                strcpy((*student)[j].StudenId, tempchar);
                //ID Class
                strcpy(tempchar, (*student)[i].classroomId);
                strcpy((*student)[i].classroomId, (*student)[j].classroomId);
                strcpy((*student)[j].classroomId, tempchar);
                //Name
                strcpy(tempchar, (*student)[i].name);
                strcpy((*student)[i].name, (*student)[j].name);
                strcpy((*student)[j].name, tempchar);

                //date
                int const day = (*student)[i].dateOfbirth.day;
                (*student)[i].dateOfbirth.day = (*student)[j].dateOfbirth.day;
                (*student)[j].dateOfbirth.day = day;

                int const month = (*student)[i].dateOfbirth.month;
                (*student)[i].dateOfbirth.month = (*student)[j].dateOfbirth.month;
                (*student)[j].dateOfbirth.month = month;

                int const year = (*student)[i].dateOfbirth.year;
                (*student)[i].dateOfbirth.year = (*student)[j].dateOfbirth.year;
                (*student)[j].dateOfbirth.year = year;
                //Email
                strcpy(tempchar, (*student)[i].email);
                strcpy((*student)[i].email, (*student)[j].email);
                strcpy((*student)[j].email, tempchar);
                //Phone
                strcpy(tempchar, (*student)[i].phone);
                strcpy((*student)[i].phone, (*student)[j].phone);
                strcpy((*student)[j].phone, tempchar);
                //Subject
                strcpy(tempchar, (*student)[i].subjects.name);
                strcpy((*student)[i].subjects.name, (*student)[j].subjects.name);
                strcpy((*student)[j].subjects.name, tempchar);

                strcpy(tempchar, (*student)[i].subjects.StudenId);
                strcpy((*student)[i].subjects.StudenId, (*student)[j].subjects.StudenId);
                strcpy((*student)[j].subjects.StudenId, tempchar);

                bool temp =(*student)[i].subjects.C;
                (*student)[i].subjects.C = (*student)[j].subjects.C;
                (*student)[j].subjects.C = temp;

                temp = (*student)[i].subjects.S;
                (*student)[i].subjects.S = (*student)[j].subjects.S;
                (*student)[j].subjects.S = temp;

                temp = (*student)[i].subjects.E;
                (*student)[i].subjects.E = (*student)[j].subjects.E;
                (*student)[j].subjects.E = temp;
            }

        }
    }
    printf("\033[32mArrange success\033[0m\n");
}
//choose Subjects [7]
void chooseSubject(struct information *student[],int const *n) {
    char search[20];
    printf("Enter student ID  to Choose subject: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    fflush(stdin);
    int check = 0;
    add:
    printf("\n");
    printf("|============|===========================|==================|====================|================|\n");
    printf("|\t ID\t\t |\t\t\tName\t\t\t |\t\033[31mS01\033[0m Scratch\t\t|\t\033[31mC02\033[0m Programing C |\t\033[31mE03\033[0m English\t  |\n");
    printf("|============|===========================|==================|====================|================|\n");
    for(int i = 0; i < *n; i ++) {
        if(strcmp((*student)[i].subjects.StudenId, search) == 0) {
            char C[10];
            char S[10];
            char E[10];
            char colorS[5];
            char colorC[5];
            char colorE[5];
            if((*student)[i].subjects.S == false) {
                strcpy(S,"NULL");
                strcpy(colorS,"31m");
            }else if((*student)[i].subjects.S == true){
                strcpy(S,"TRUE");
                strcpy(colorS,"32m");

            }
            if((*student)[i].subjects.E == false) {
                strcpy(E,"NULL");
                strcpy(colorE,"31m");
            }else if((*student)[i].subjects.E == true){
                strcpy(E,"TRUE");
                strcpy(colorE,"32m");
            }
            if((*student)[i].subjects.C == false) {
                strcpy(C,"NULL");
                strcpy(colorC,"31m");
            }else if ((*student)[i].subjects.C == true){
                strcpy(C,"TRUE");
                strcpy(colorC,"32m");
            }
            printf("| %-10s | %-25s |\t\t\033[%s%-11s\033[0m |\t\033[%s%-12s\033[0m \t |\t\t\033[%s%-9s\033[0m |\n",(*student)[i].subjects.StudenId,(*student)[i].subjects.name, colorS,S,colorC,C,colorE,E);
            printf("|============|===========================|==================|====================|================|\n");
            printf("|                                  Press  S to skip                                               |\n");
            printf("|============|===========================|==================|====================|================|\n");
            check = 1;
            char Idsubject[10];
            printf("Enter the \033[31mID\033[0m Subject: ");
            scanf("%s", Idsubject);
            if(strlen(Idsubject) > 9) {
                goto add;
            }
            if (strcmp(Idsubject, "S01") == 0) {
                (*student)[i].subjects.S = true;
                printf("\033[32mAdd Success S01!!\033[0m\n");
            }else if(strcmp(Idsubject, "C02") == 0) {
                (*student)[i].subjects.C = true;
                printf("\033[32mAdd Success C02!!\033[0m\n");
            }else if (strcmp(Idsubject, "E03") == 0) {
                (*student)[i].subjects.E = true;
                printf("\033[32mAdd Success E03!!\033[0m\n");
            }else if(strcmp(Idsubject, "s") == 0 || strcmp(Idsubject, "S") == 0 ){

            }else {
                printf("\033[31mInvalid!!!\033[0m\n");
                goto add;
            }
        }
    }
    if(!check) {
        printf("\033[31mStudent information'Does not' found!!.\033[0m\n");
    }
}
//--------------------------------END MENU Student--------------------------------------//


//--------------------------------***MENU Teacher***-----------------------------------//
void menuTeacher(int *menu) {
    do {
        printf("\n");
        printf(" *** Teacher Management System Using C *** \n");
        printf("\n");
        printf("\t\t\t\tMENU\n");
        printf("\t=========================\n");
        printf("\t[1] Add A New Teacher.\n");
        printf("\t[2] Show All Teacher.\n");
        printf("\t[3] Search A Teacher.\n");
        printf("\t[4] Edit A Teacher.\n");
        printf("\t[5] Delete A Teacher.\n");
        printf("\t[6] Back\n");
        printf("\t\033[31m[7] Clear ALL FILE\033[0m\n");
        printf("\t[0] Exit Program.\n");
        printf("\t=========================\n");
        printf("Enter your choice: ");
        if(scanf("%d", menu) != 1) {
            printf("Invalid\n");
        }
        getchar();
    }while (*menu > 7|| *menu < 0);
}
//--------------------------------FUNCTION IN MENU Teacher-----------------------------//
//Function add Teacher[1]
void addTeacher(struct teacher *teachers[], int *n, struct Classroom *class[], int *r){
    //gender
    char gender;
    //change mode for file

    char *endptr;
    int test1;
    int indext;
    do{
        test1 = 0;
        char input[10];

        printf("Enter quanity Teacher: ");
        fgets(input, sizeof(input), stdin);
        fflush(stdin);
        int const index = strtol(input, &endptr, 10);

        if (*endptr != '\0' && *endptr != '\n') {
            printf("Invalid !!!\n");
            test1 = 1;
        }
        if(index < 1) {
            printf("Invalid !!!\n");
            test1 = 1;
        }
        indext = *n;
        *n += index;
    } while (test1 != 0);

    *teachers = (struct teacher*) realloc(*teachers, *n * sizeof(struct teacher));
    if (*teachers == NULL) {
        printf("erorr \n");
        return;
    }
    int count = 0;
    for(int i = indext; i < *n; i++) {
        count++;
            add:
        while(1) {
            printf("-------Teacher %d-------\n", count);
            printf("Enter Teacher ID: ");
            fgets((*teachers)[i].teacherId, sizeof(*teachers)[i].teacherId, stdin);
            (*teachers)[i].teacherId[strlen((*teachers)[i].teacherId) - 1] = '\0';
            fflush(stdin);
            //condition

            for(int j = 0; j < i; j++) {
                if(strcmp((*teachers)[j].teacherId, (*teachers)[i].teacherId) == 0) {
                    printf("\033[31mInvalid Class ID111.\033[0m\n");
                    goto add;
                }
            }
            if (strlen((*teachers)[i].teacherId) < 1) {
                printf("\033[31mInvalid Teacher ID.\033[0m\n");
                goto add;
            }
            if(strlen((*teachers)[i].teacherId) >= 8){
                printf("\033[31mInvalid Teacher ID.\033[0m\n");
                goto add;
            }
            //done
            printf("Enter Name: ");
            fgets((*teachers)[i].name, sizeof(*teachers)[i].name, stdin);
            (*teachers)[i].name[strlen((*teachers)[i].name) - 1] = '\0';
            //condition
            if (strlen((*teachers)[i].name) <= 8) {
                printf("\033[31mInvalid Teacher Name\033[0m\n");
                goto add;
            }
            char *str = (char *)malloc(strlen((*teachers)[i].name) + 1);
            strcpy(str,(*teachers)[i].name);
            const char *pos = strchr(str, ' ');
            if(pos == NULL) {
                printf("\033[31mInvalid Teacher Name\033[0m\n");
                goto add;
            }
            free(str);
            //done
            //call funcstion Show Class;
            showClass(class, r);
            int menu1;
            if((*class)[0].classroomId[0] == '\0') {
                do {
                    printf("There are no classes.\n");
                    printf("1.Continue\n");
                    printf("2.Back & don't save\n");
                    scanf("%d", &menu1);
                }while(menu1 != 1 && menu1 != 2);
                if(menu1 == 2) {
                    return;
                }else {
                    strcpy((*teachers)[i].classroomId, "NULL");
                }
            }
            printf("|========================================|\n");
            printf("|             Press S to skip            |\n");
            printf("|========================================|\n");
            printf("Enter ");
            printf("\033[31mID\033[0m ");
            printf("Class room: ");
            fgets((*teachers)[i].classroomId, sizeof(*teachers)[i].classroomId, stdin);
            (*teachers)[i].classroomId[strlen((*teachers)[i].classroomId) - 1] = '\0';
            //condition
            int isValid = 0;
            for (int z = 0; z < *r; z++) {
                if (strcmp((*class)[z].classroomId, (*teachers)[i].classroomId) == 0) {
                    //strcpy((*class)[z].teacherId, (*teachers)[i].teacherId);
                    //strcpy((*class)[z].teacherName, (*teachers)[i].name);
                    isValid = 1;
                    break;
                }
            }
            if(strcmp((*teachers)[i].classroomId, "s") == 0 || strcmp((*teachers)[i].classroomId, "S") == 0) {
                strcpy((*teachers)[i].classroomId, "NULL");
                isValid = 1;
            }

            if (!isValid) {
                printf("\033[31mInvalid Class ID111.\033[0m\n");
                goto add;
            }

            //done

            //date
            int test;
            do{
                test = 1;
                printf("Month (1-12): ");
                scanf("%d", &(*teachers)[i].dateOfbirth.month);
                if ((*teachers)[i].dateOfbirth.month < 1 || (*teachers)[i].dateOfbirth.month > 12) {
                    printf("\033[31mInvalid month.\033[0m\n");
                    test = 0;
                    fflush(stdin);
                    continue;
                }

                printf("Day (1-31): ");
                scanf("%d", &(*teachers)[i].dateOfbirth.day);
                if ((*teachers)[i].dateOfbirth.day < 1 || (*teachers)[i].dateOfbirth.day > 31) {
                    printf("\033[31mInvalid day.\033[0m\n");
                    test = 0;
                    fflush(stdin);
                    continue;
                }

                printf("Year (1950-2023): ");
                scanf("%d", &(*teachers)[i].dateOfbirth.year);
                if ((*teachers)[i].dateOfbirth.year < 1950 || (*teachers)[i].dateOfbirth.year > 2023) {
                    printf("\033[31mInvalid year.\033[0m\n");
                    fflush(stdin);
                    test = 0;
                }

            } while (test != 1);

            fflush(stdin);
            while (1) {
                printf("Boy Or Girl: ('b' or 'g'): ");
                scanf("%c", &gender);
                getchar();
                if(gender == 'b'|| gender == 'B') {
                    strcpy((*teachers)[i].gender, "Man");
                    break;
                }else if(gender == 'g'|| gender == 'G'){
                    strcpy((*teachers)[i].gender, "wonman");
                    break;
                }
            }

            printf("Enter Email : ");
            fgets((*teachers)[i].email, sizeof(*teachers)[i].email, stdin);
            (*teachers)[i].email[strlen((*teachers)[i].email) - 1] = '\0';
            //condition
            for(int j = 0; j < i; j++) {
                if(strcmp((*teachers)[j].email, (*teachers)[i].email) == 0) {
                    printf("\033[31mInvalid Class ID111.\033[0m\n");
                    goto add;
                }
            }
            const char gmail[] = "@gmail.com";

            if (strlen((*teachers)[i].email) < strlen(gmail)) {
                printf("\033[31mInvalid Teacher email.\033[0m\n");
                goto add;
            } else {
                int const strPig = strlen((*teachers)[i].email);
                int const strS = strlen(gmail);

                int is_valid = 1;
                for (int j = 0; j < strS; j++) {
                    if ((*teachers)[i].email[strPig - strS + j] != gmail[j]) {
                        is_valid = 0;
                        break;
                    }
                }

                if (!is_valid) {
                    printf("\033[31mInvalid Teacher email\033[0m\n");
                    goto add;
                }
            }

            printf("Enter Phone: ");
            fgets((*teachers)[i].phone, sizeof(*teachers)[i].phone, stdin);
            (*teachers)[i].phone[strlen((*teachers)[i].phone) - 1] = '\0';
            //condition
            for(int j = 0; j < i; j++) {
                if(strcmp((*teachers)[j].phone, (*teachers)[i].phone) == 0) {
                    printf("\033[31mInvalid Class ID111.\033[0m\n");
                    goto add;
                }
            }
            if (strlen((*teachers)[i].email) < 10) {
                printf("\033[31mInvalid Teacher Phone.\033[0m\n");
                goto add;
            }
            //done
                printf("\033[32mAdd Teacher Success.\033[0m\n");
            dataSaveT(teachers, n);
            dataSaveC(class, r);
                break;
            }
        }

}
//Function Show Teacher [2]
void showTeacher(struct teacher *teachers[], int const *n) {
    printf("\t\t\t**** All Student ****\n");
    printf("\n");
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    printf("|\t ID\t\t |\t\t\tName\t\t\t |\t\t\t\tEmail\t\t\t\t |\t\tPhone\t\t |\t\tGender\t |\tClass room\t | Date of birht |\n");
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    for(int i = 0; i < *n; i++) {
        printf("| %-10s | %-25s | %-33s | %-17s | %-13s | %-14s|   %-2d/%-2d/%-6d|\n",(*teachers)[i].teacherId, (*teachers)[i].name,(*teachers)[i].email, (*teachers)[i].phone, (*teachers)[i].gender, (*teachers)[i].classroomId, (*teachers)[i].dateOfbirth.month , (*teachers)[i].dateOfbirth.day, (*teachers)[i].dateOfbirth.year);
    }
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
}
//Function search Teacher [3]
void searchTeacher(struct teacher *teachers[], int const *n){
    char search[20];
    printf("Enter name Teacher to search: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    int check = 0;
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    printf("|\t ID\t\t |\t\t\tName\t\t\t |\t\t\t\tEmail\t\t\t\t |\t\tPhone\t\t |\t\tGender\t |\tClass room\t | Date of birht |\n");
    printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
    for(int i = 0; i < *n; i ++) {
        if(strstr((*teachers)[i].name, search) != NULL) {
            printf("| %-10s | %-25s | %-33s | %-17s | %-13s | %-14s|   %d/%d/%-6d |\n",(*teachers)[i].teacherId, (*teachers)[i].name,(*teachers)[i].email, (*teachers)[i].phone, (*teachers)[i].gender, (*teachers)[i].classroomId, (*teachers)[i].dateOfbirth.month , (*teachers)[i].dateOfbirth.day, (*teachers)[i].dateOfbirth.year);
            printf("|============|===========================|===================================|===================|===============|===============|===============|\n");
            check = 1;
        }
    }
    if(!check) {
        printf("\033[31mTeacher information'Does not' found!!.\033[0m\n");
    }else {
        printf("\033[32mTeacher information found!!.\033[0m\n");
    }
}
//Function Edit Teacher[4]
void editTeacher(struct teacher *teachers[], int const *n, struct Classroom *class[], int *r) {
    char gender;
    char search[20];
    printf("Enter Teacher ID  to edit: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    fflush(stdin);
    int check = 0;
    for(int i = 0; i < *n; i ++) {
        if(strcmp((*teachers)[i].teacherId, search) == 0) {
            while (1) {
                add:
                printf("--ID Teacher : %s --\n", (*teachers)[i].teacherId);
                printf("Enter information to change: \n");

                printf("Enter Name: ");
                fgets((*teachers)[i].name, sizeof(*teachers)[i].name, stdin);
                (*teachers)[i].name[strlen((*teachers)[i].name) - 1] = '\0';
                //condition
                if (strlen((*teachers)[i].name) <= 8) {
                    printf("\033[31mInvalid Teacher Name\033[0m\n");
                    goto add;
                }
                char *str = (char *)malloc(strlen((*teachers)[i].name) + 1);
                strcpy(str,(*teachers)[i].name);
                const char *pos = strchr(str, ' ');
                if(pos == NULL) {
                    printf("\033[31mInvalid Teacher Name\033[0m\n");
                    goto add;
                }
                free(str);
                //done
                showClass(class, r);
                int menu1;
                if((*class)[0].classroomId[0] == '\0') {
                    do {
                        printf("There are no classes.\n");
                        printf("1.Continue\n");
                        printf("2.Back & don't save\n");
                        scanf("%d", &menu1);
                    }while(menu1 != 1 && menu1 != 2);
                    if(menu1 == 2) {
                        return;
                    }else {
                        strcpy((*teachers)[i].classroomId, "NULL");
                    }
                }
                printf("|========================================|\n");
                printf("|             Press S to skip            |\n");
                printf("|========================================|\n");
                printf("Enter ");
                printf("\033[31mID\033[0m ");
                printf("Class room: ");
                fgets((*teachers)[i].classroomId, sizeof(*teachers)[i].classroomId, stdin);
                (*teachers)[i].classroomId[strlen((*teachers)[i].classroomId) - 1] = '\0';

                //condition

                int isValid = 0;
                for (int z = 0; z < *r; z++) {
                    if (strcmp((*class)[z].classroomId, (*teachers)[i].classroomId) == 0) {
                        //strcpy((*class)[z].teacherId, (*teachers)[i].teacherId);
                       // strcpy((*class)[z].teacherName, (*teachers)[i].name);
                        isValid = 1;
                        break;
                    }
                }
                if(strcmp((*teachers)[i].classroomId, "s") == 0 || strcmp((*teachers)[i].classroomId, "S") == 0) {
                    strcpy((*teachers)[i].classroomId, "NULL");
                    isValid = 1;
                }

                if (!isValid) {
                    printf("\033[31mInvalid Class ID111.\033[0m\n");
                    goto add;
                }

                //done


                int test;
                do{
                    test = 1;
                    printf("Month (1-12): ");
                    scanf("%d", &(*teachers)[i].dateOfbirth.month);
                    if ((*teachers)[i].dateOfbirth.month < 1 || (*teachers)[i].dateOfbirth.month > 12) {
                        printf("\033[31mInvalid month.\033[0m\n");
                        fflush(stdin);
                        goto add;
                    }

                    printf("Day (1-31): ");
                    scanf("%d", &(*teachers)[i].dateOfbirth.day);
                    if ((*teachers)[i].dateOfbirth.day < 1 || (*teachers)[i].dateOfbirth.day > 31) {
                        printf("\033[31mInvalid day.\033[0m\n");
                        fflush(stdin);
                        goto add;
                    }

                    printf("Year (1950-2023): ");
                    scanf("%d", &(*teachers)[i].dateOfbirth.year);
                    if ((*teachers)[i].dateOfbirth.year < 1950 || (*teachers)[i].dateOfbirth.year > 2023) {
                        printf("\033[31mInvalid year.\033[0m\n");
                        fflush(stdin);
                        test = 0;
                    }

                } while (test != 1);

                fflush(stdin);
                while (1) {
                    printf("Boy Or Girl: ('b' or 'g'): ");
                    scanf("%c", &gender);
                    getchar();
                    if(gender == 'b'|| gender == 'B') {
                        strcpy((*teachers)[i].gender, "Man");
                        break;
                    }else if(gender == 'g'|| gender == 'G'){
                        strcpy((*teachers)[i].gender, "wonman");
                        break;
                    }
                }

                printf("Enter Email : ");
                fgets((*teachers)[i].email, sizeof(*teachers)[i].email, stdin);
                (*teachers)[i].email[strlen((*teachers)[i].email) - 1] = '\0';
                //condition

                for(int j = 0; j < *n; j++) {
                    if(j == i) {
                        continue;
                    }
                    if(strcmp((*teachers)[j].email, (*teachers)[i].email) == 0) {
                        printf("\033[31mInvalid Class ID111.\033[0m\n");
                        goto add;
                    }
                }


                const char gmail[] = "@gmail.com";
                if (strlen((*teachers)[i].email) < strlen(gmail)) {
                    printf("\033[31mInvalid Teacher email.\033[0m\n");
                    goto add;
                }else {
                    for (int j = 0; j < strlen(gmail); j++) {
                        if ((*teachers)[j].email[strlen((*teachers)[j].email - strlen(gmail) + j)]!= gmail[j]) {
                            continue;
                        }
                    }
                }

                printf("Enter Phone: ");
                fgets((*teachers)[i].phone, sizeof(*teachers)[i].phone, stdin);
                (*teachers)[i].phone[strlen((*teachers)[i].phone) - 1] = '\0';
                //condition
                for(int j = 0; j < *n; j++) {
                    if(j == i) {
                        continue;
                    }
                    if(strcmp((*teachers)[j].phone, (*teachers)[i].phone) == 0) {
                        printf("\033[31mInvalid Class ID111.\033[0m\n");
                        goto add;
                    }
                }
                if (strlen((*teachers)[i].phone) < 9) {
                    printf("\033[31mInvalid Teacher Phone.\033[0m\n");
                    goto add;
                }
                check = 1;
                break;
            }

        }else if (check == 1){
            break;
        }else {
            check = 0;
        }
    }
    if(check == 0) {
        printf("\033[31mTeacher infromation 'Does not' found\033[0m\n");
    }else {
        printf("\033[32mAdd Student Success.\033[0m\n");
    }
}
//Function Delete Teacher[5]
void deleteTeacher(struct teacher *teachers[], int *n) {
    char search[20];
    printf("Enter Teacher ID  to delete: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    int menu1;
    int check = 0;
    menu1:
    for(int i = 0; i < *n; i ++) {
        if(strcmp((*teachers)[i].teacherId, search) == 0) {
            do {
                printf("\033[31m1.Delete\033[0m\n");
                printf("\033[32m2.No!!\033[0m\n");
                scanf("%d", &menu1);
            }while(menu1 != 1 && menu1 != 2);
            if(menu1 == 2) {
                return;
            }
            for(int j = i; j < *n - 1; j++) {
                strcpy((*teachers)[j].teacherId, (*teachers)[j + 1].teacherId );
                strcpy((*teachers)[j].classroomId, (*teachers)[j + 1].classroomId );
                strcpy((*teachers)[j].name, (*teachers)[j + 1].name );
                strcpy((*teachers)[j].email, (*teachers)[j + 1].email );
                strcpy((*teachers)[j].gender, (*teachers)[j + 1].gender );
                strcpy((*teachers)[j].phone, (*teachers)[j + 1].phone );
                //date
                (*teachers)[j].dateOfbirth.day = (*teachers)[j + 1].dateOfbirth.day;
                (*teachers)[j].dateOfbirth.month = (*teachers)[j + 1].dateOfbirth.month;
                (*teachers)[j].dateOfbirth.year = (*teachers)[j + 1].dateOfbirth.year;
            }
            (*n)--;
            check = 1;
            printf("\033[32mDelted Teacher ID: %s is Success\033[0m\n",search);
            break;
        }
    }
    if(!check) {
        printf("\033[31mTeacher infromation 'Does not' found\033[0m\n");
    }
}
//------------------------------END MENU Teacher---------------------------------------//


//--------------------------------- MENU Class---------------------------------------//
void menuClass(int *menu) {
    do {
        printf("\n");
        printf(" *** Class Management System Using C *** \n");
        printf("\n");
        printf("\t\t\t\tMENU\n");
        printf("\t=========================\n");
        printf("\t[1] Add A New Class.\n");
        printf("\t[2] Show All Class\n");
        printf("\t[3] Edit A Class.\n");
        printf("\t[4] Delete A Class.\n");
        printf("\t[5] Details Class.\n");
        printf("\t[6] Delete or Change the student for class.\n");
        printf("\t[7] Delete or Change the Teacher for class.\n");
        printf("\t[8] Add student for Class\n");
        printf("\t[9] Add Teacher for Class\n");
        printf("\t[10] Back\n");
        printf("\t\033[31m[11] Clear ALL FILE\033[0m\n");
        printf("\t[0] Exit Program.\n");
        printf("\t=========================\n");
        printf("Enter your choice: ");
        if(scanf("%d", menu) != 1) {
            printf("Invalid\n");
        }
        getchar();
    }while (*menu > 11|| *menu < 0);

}
//--------------------------------***MENU Class***-----------------------------------//
//Function add class[1]
void addClass(struct Classroom *class[], int *n) {
    //change mode for file

    char *endptr;
    int test1;
    int indext;
    do{
        test1 = 0;
        char input[10];

        printf("Enter quanity Class: ");
        fgets(input, sizeof(input), stdin);
        fflush(stdin);
        int const index = strtol(input, &endptr, 10);

        if (*endptr != '\0' && *endptr != '\n') {
            printf("Invalid !!!\n");
            test1 = 1;
        }
        if(index < 1) {
            printf("Invalid !!!\n");
            test1 = 1;
        }
        indext = *n;
        *n += index;
    } while (test1 != 0);
    *class = (struct Classroom*) realloc(*class, *n * sizeof(struct Classroom));
    if (*class == NULL) {
        printf("erorr \n");
        return;
    }
    int count = 0;
    for(int i = indext; i < *n ; i++) {
        count++;
        add:
        while (1) {
            printf("-------Class %d-------\n", count);
            printf("Enter Class ID: ");
            fgets((*class)[i].classroomId, sizeof(*class)[i].classroomId, stdin);
            (*class)[i].classroomId[strlen((*class)[i].classroomId) - 1] = '\0';
            fflush(stdin);
            //condition
            for(int j = 0; j < i; j++) {
                if(strcmp((*class)[j].classroomId, (*class)[i].classroomId) == 0) {
                    printf("\033[31mInvalid Class ID111.\033[0m\n");
                    goto add;
                    }
                }

            if (strlen((*class)[i].classroomId) < 1) {
                printf("\033[31mInvalid Class ID.\033[0m\n");
                goto add;
            }
            if(strlen((*class)[i].classroomId) >= 8){
                printf("\033[31mInvalid Class ID.\033[0m\n");
                goto add;
            }

            printf("Enter Name Class Room: ");
            fgets((*class)[i].classroomName, sizeof(*class)[i].classroomName, stdin);
            (*class)[i].classroomName[strlen((*class)[i].classroomName) - 1] = '\0';

            //condition
            if (strlen((*class)[i].classroomName) < 3) {
                printf("\033[31mInvalid Teacher Class Room..\033[0m\n");
                goto add;
            }

            if (strlen((*class)[i].classroomName) >= 9) {
                printf("\033[31mInvalid Class name ID\033[0m\n");
                goto add;
            }
            for(int j = 0; j < i; j++) {
                if(strcmp((*class)[j].classroomName, (*class)[i].classroomName) == 0) {
                    printf("\033[31mInvalid Class name ID.\033[0m\n");
                    goto add;
                }
            }
            //done
            break;
        }
    }
    printf("\033[32mSuccess!!.\033[0m\n");
    dataSaveC(class, n);
}
//Function show class[2]
void showClass(struct Classroom *class[], int const *n) {
    printf("\t\t\t**** All Class ****\n");
    printf("\n");
    printf("|============|===========================|\n");
    printf("|\t ID\t\t |\t\t\tClass Name\t\t |\n");
    printf("|============|===========================|\n");
    for(int i = 0; i < *n; i++) {
        printf("| %-10s | %-25s |\n",(*class)[i].classroomId, (*class)[i].classroomName);
    }
    printf("|============|===========================|\n");
}
//Function edit class[3]
void editClass(struct Classroom *class[], int const *n) {
    char search[20];
    printf("Enter class ID  to edit: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    for(int i = 0; i < *n; i++) {
        if(strcmp((*class)[i].classroomId, search) == 0) {
            while(1) {
                add:
                printf("--ID Class : %s --\n", (*class)[i].classroomId);
                printf("--Enter information to change--\n");

                printf("Enter Name Class Room: ");
                fgets((*class)[i].classroomName, sizeof(*class)[i].classroomName, stdin);
                (*class)[i].classroomName[strlen((*class)[i].classroomName) - 1] = '\0';
                //condition

                for(int j = 0; j < *n; j++) {
                    if(i == j) {
                        continue;
                    }
                    if(strcmp((*class)[j].classroomName, (*class)[i].classroomName) == 0) {
                        printf("\033[31mInvalid Class name ID.\033[0m\n");
                        goto add;
                    }
                }

                if (strlen((*class)[i].classroomName) < 3) {
                    printf("\033[31mInvalid Class Class Room..\033[0m\n");
                    continue;
                }

                if (strlen((*class)[i].classroomName) >= 9) {
                    printf("\033[31mInvalid Class Class Room\033[0m\n");
                    continue;
                }

                printf("\033[32mSuccess!!!\033[0m\n");
                return;
            }
        }
    }
    printf("\033[31mClass infromation 'Does not' found\033[0m\n");
}
//Function delete class[4]
void deleteClass(struct Classroom *class[], int  *n) {
    char search[20];
    int check = 0;
    printf("Enter Class ID  to delete: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    int menu1;
    menu1:

    for(int i = 0; i < *n; i ++) {
        if(strcmp((*class)[i].classroomId, search) == 0) {
            do {
                printf("\033[31m1.Delete\033[0m\n");
                printf("\033[32m2.No!!\033[0m\n");
                scanf("%d", &menu1);
            }while(menu1 != 1 && menu1 != 2);
            if(menu1 == 2) {
                return;
            }
            for(int j = i; j < *n - 1; j++) {
                strcpy((*class)[j].teacherId, (*class)[j + 1].teacherId );
                strcpy((*class)[j].classroomId, (*class)[j + 1].classroomId );
                strcpy((*class)[j].classroomName, (*class)[j + 1].classroomName );
                //strcpy((*student)[i].password, (*student)[i + 1].password );
            }
            (*n)--;
            check = 1;
            printf("\033[32mSuccess!!!\033[0m\n");
            break;
        }
    }
    if(!check) {
        printf("\033[31mClass infromation 'Does not' found\033[0m\n");
    }
}
//Function show details class[5]
void detailslass(struct Classroom *class[], int const *n,struct information *student[], int const *r, struct teacher *teachers[], int const *k) {
    char search[20];
    printf("Enter class ID for details: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    for(int i = 0; i < *n; i++) {
        if(strcmp((*class)[i].classroomId, search) == 0){
            printf("\t\t\t\t\t\t\t\t\t**** Class %s ****\n",(*class)[i].classroomName );
            printf("\n");
        printf("|============|===========================|=======================|==================================|\n");
        printf("|\t ID\t\t |\t\t\tClass Name\t\t |\t\t\tACADEMY\t\t |\t\t\t\tSubject\t\t\t\t|\n");
        printf("|============|===========================|=======================|==================================|\n");
        printf("| %-10s | %-25s | %-22s|  Scracth | Programing C| English |\n",(*class)[i].classroomId, (*class)[i].classroomName, "RIKKEI");
        printf("|========================================STUDENT====================================================|\n");
        for(int j = 0; j < *r; j++) {//\033[%s%-12s\033[0m
            if(strcmp((*student)[j].classroomId, (*class)[i].classroomId) == 0) {
                char C[10];
                char S[10];
                char E[10];
                char colorS[5];
                char colorC[5];
                char colorE[5];
                if((*student)[j].subjects.S == false) {
                    strcpy(S,"NULL");
                    strcpy(colorS,"31m");
                }else {
                    strcpy(S,"TRUE");
                    strcpy(colorS,"32m");
                }
                if((*student)[j].subjects.E == false) {
                    strcpy(E,"NULL");
                    strcpy(colorE,"31m");
                }else {
                    strcpy(E,"TRUE");
                    strcpy(colorE,"32m");
                }
                if((*student)[j].subjects.C == false) {
                    strcpy(C,"NULL");
                    strcpy(colorC,"31m");
                }else {
                    strcpy(C,"TRUE");
                    strcpy(colorC,"32m");
                }
                printf("| %-10s |\t\t\t %-25s \t\t\t\t |  \033[%s%-8s\033[0m| \033[%s%-12s\033[0m| \033[%s%-8s\033[0m|\n",(*student)[j].StudenId, (*student)[j].name, colorS,S,colorC,C,colorE,E);
            }
        }
        printf("|===================================================================================================|\n");
        printf("\n");

            printf("|===========|==================TEACHER===========================|\n");
                if(strcmp((*class)[i].classroomId, search) == 0) {

                    for(int j = 0; j < *k ; j++){
                        if(strcmp((*teachers)[j].classroomId,search) == 0) {
                            printf("| %-10s|\t\t\t %-25s \t\t\t\t |\n",(*teachers)[j].teacherId, (*teachers)[j].name);
                            strcpy((*class)[i].classroomName, (*teachers)[j].name);
                        }
                    }

                }
            printf("|===========|====================================================|\n");

    }
}
}
//Function remove or add students from class[6]
void deleteStudentandAddForclass(struct Classroom *class[], int const *n,struct information *student[], int const *r) {
    char search[20];
    printf("Enter the student ID  to delete for class: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    fflush(stdin);
    int check = 0;
    int menu1;
    for(int i = 0; i < *r; i ++) {
        if(strcmp((*student)[i].StudenId, search) == 0) {
            check = 1;
            do {
                printf("1.Delete \n");
                printf("2.Change Class \n");
                scanf("%d", &menu1);
            }while(menu1 != 1 && menu1 != 2);
            getchar();
            if(menu1 == 1) {
                strcpy((*student)[i].classroomId, "NULL");
                break;
            }else if( menu1 == 2){
                showClass(class, n);
                if((*class)[0].classroomId[0] == '\0') {
                    printf("There are no classes.\n");
                    return;
                }
                //done
                add:
                printf("Enter ");
                printf("\033[31mID\033[0m ");
                printf("Class room: ");
                fgets((*student)[i].classroomId, sizeof(*student)[i].classroomId, stdin);
                (*student)[i].classroomId[strlen((*student)[i].classroomId) - 1] = '\0';

                //condition
                int isValid = 0;
                for (int z = 0; z < *n; z++) {
                    if (strcmp((*class)[z].classroomId, (*student)[i].classroomId) == 0) {
                        isValid = 1;
                        break;
                    }
                }

                if (!isValid) {
                    printf("\033[31mInvalid Class ID111.\033[0m\n");
                    goto add;
                }
                if (strlen((*student)[i].classroomId) < 3) {
                    printf("\033[31mInvalid Student Class Room..\033[0m\n");
                    goto add;
                }

                if (strlen((*student)[i].classroomId) >= 9) {
                    printf("\033[31mInvalid Student Class Room\033[0m\n");
                    goto add;
                }
            }
        }
    }
    if(!check) {
        printf("\033[31mStudent information'Does not' found!!.\033[0m\n");
    }
}
//Function remove or add Teacher from class[7]
void deleteTeacherandAddForclass(struct Classroom *class[], int const *n, struct teacher *teachers[], int const *r) {

    char search[20];
    printf("Enter ID Old Class: ");
    fgets(search, 20, stdin);
    search[strlen(search) - 1] = '\0';
    fflush(stdin);
    int check = 0;
    int menu1 =0;
    int v = 0;
    for(int i = 0; i < *n; i ++) {
        if(strcmp((*class)[i].classroomId, search) == 0) {
            if((*class)[i].teacherName == '\0') {
                printf("No teacher\n");
                return;
            }
            int check2 = 0;
            printf("|============|===========================|=======================|\n");
            printf("|\t ID\t\t |\t\t\tClass Name\t\t |\t\t\tGVCN\t\t |\n");
            printf("|============|===========================|=======================|\n");
            for(int j = 0; j < *r; j++) {
                if(strcmp((*teachers)[j].classroomId, search) == 0){
                    printf("| %-10s | %-25s | %-22s|\n",(*teachers)[j].teacherId, (*class)[i].classroomName, (*teachers)[j].name);
                    check2 = 1;
                }
            }
            printf("|================================================================|\n");
            char ID[10];
            if(!check2) {
                printf("No Teacher \n");
                return;
            }
                add:

            printf("Enter ID teacher: ");
            scanf("%s", ID);
            if(strlen(ID) > 9) {
                printf("\033[31mInvalid!!!\033[0m\n");
                goto add;
            }
            for(int j = 0; j < *r; j++) {
                if(strcmp((*teachers)[j].teacherId, ID) == 0) {
                    v = j;
                    do {
                        printf("1.Delete\n");
                        printf("2.Change Class\n");
                        scanf("%d", &menu1);
                    }while (menu1 != 1 && menu1 != 2);
                    char search1[10];
                    if(menu1 == 1) {
                                strcpy((*teachers)[v].classroomId, "NULL");
                                check = 1;
                                printf(".");
                                break;
                    }else {
                        showClass(class, n);
                        printf("Enter The ID Class: ");
                        scanf("%s", &search1);
                        for(int l = 0; l < *n; l++) {
                            if(strcmp((*class)[l].classroomId, search1) == 0) {
                                strcpy((*teachers)[v].classroomId, search1);
                                strcpy((*class)[l].teacherName,(*class)[i].teacherName );
                                strcpy((*class)[l].teacherId, (*class)[i].teacherId);
                                check = 1;
                                printf("Success!!\n");
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if(!check) {
        printf("\033[31mTeacher information'Does not' found!!.\033[0m\n");
    }
}
//Add Student For Class[8], Show only students whose class ID == NULL;
void addStudentForClass(struct Classroom *class[], int const *n, struct information *student[], int const *r) {
    int check2 = 0;
    printf("\033[33mShow only Student Whose class ID == NULL\033[0m\n");
    printf("|===========|==================STUDENT===========================|\n");
    for(int i = 0; i< *r; i++) {
        if(strcmp((*student)[i].classroomId, "NULL") == 0) {
            printf("| %-10s|\t\t\t %-25s \t\t\t\t |\n",(*student)[i].StudenId, (*student)[i].name);
            check2 = 1;
        }
    }
    printf("|===========|====================================================|\n");
    if(!check2) {
        printf("No Student\n");
        return;
    }
    char search[10];
    char search1[10];
    int check = 0;
    int check1 = 0;
    printf("Enter the ID student: ");
    scanf("%s", &search);
    for(int i = 0; i < *r; i++) {
        if(strcmp((*student)[i].StudenId, search) == 0) {
            check = 1;
            add:
            showClass(class, n);
            printf("Enter The ID Class: ");
            scanf("%s", &search1);
            for(int j = 0; j < *n; j++) {
                if(strcmp((*class)[j].classroomId, search1) == 0) {
                    strcpy((*student)[i].classroomId, search1);
                    printf("Success!!\n");
                    check1 = 1;
                }
            }
        }
    }
    if(!check1) {
        printf("\033[31mInvalid !!!\033[0m\n");
        goto add;
    }
    if(!check) {
        printf("\033[31mStudent information'Does not' found!!.\033[0m\n");
    }
}
//Add Teacher For Class[9]. Show only students whose class ID == NULL;
void addTeacherForClass(struct Classroom *class[], int const *n, struct teacher *teachers[], int const *r) {
    add:
    printf("\033[33mShow only Teacher Whose class ID == NULL\033[0m\n");
    printf("|===========|==================TEACHER===========================|\n");
    int check2 = 0;
    for(int i = 0; i< *r; i++) {
        if(strcmp((*teachers)[i].classroomId, "NULL") == 0) {
            printf("| %-10s|\t\t\t %-25s \t\t\t\t |\n",(*teachers)[i].teacherId, (*teachers)[i].name);
            check2 = 1;
        }
    }
    printf("|===========|====================================================|\n");
    if(!check2) {
        printf("No Teacher\n");
        return;
    }
    char search[10];
    char search1[10];
    int check = 0;
    int check1 = 0;
    printf("Enter the ID Teacher: ");
    scanf("%s", &search);
    for(int i = 0; i < *r; i++) {
        if(strcmp((*teachers)[i].teacherId, search) == 0) {
            check = 1;
            showClass(class, n);
            printf("Enter The ID Class: ");
            scanf("%s", &search1);
            for(int j = 0; j < *n; j++) {
                if(strcmp((*class)[j].classroomId, search1) == 0) {
                        strcpy((*teachers)[i].classroomId, search1);
                        strcpy((*class)[i].teacherName, (*teachers)[i].name);
                        strcpy((*class)[i].teacherId, (*teachers)[i].teacherId);
                        printf("Success!!\n");
                        check1 = 1;
                }
            }
        }
    }
    if(!check1) {
        printf("\033[31mInvalid !!!\033[0m\n");
        goto add;
    }
    if(!check) {
        printf("\033[31mTeacher information'Does not' found!!.\033[0m\n");
    }

}
//------------------------------END MENU Class---------------------------------------//


//-----------------------------------FILE DATA STUDENT---------------------------------//
//function save DATA to file .dat
void dataSaveS(struct information *student[], int const *n) {
    FILE *f = fopen("DataStudent1.dat", "wb");
    if(f == NULL) {
        printf("Erorr open file!!!");
        return;
    }
    size_t const numW = fwrite(*student, sizeof(struct information), *n, f);
    if(numW !=*n) {
        printf("Erorr. Just wirte %zu element", numW);
    }
    fclose(f);
}
//Funcion load file in program !
void dataLoadS(struct information *student[], int *n){
    FILE *f = fopen("DataStudent1.dat", "rb");
    if (f == NULL) {
        printf("Erorr open file");
        return;
    }
    fseek(f, 0, SEEK_END);
    int const size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int const structSize = sizeof(struct information);
    int const count = size / structSize;

    *student = (struct information*) realloc(*student, count * sizeof(struct information));
    if (*student == NULL) {
        printf("Erorr\n");
        fclose(f);
        return;
    }
    fread(*student, sizeof(struct information), count, f);
    fclose(f);
    *n = count;
}
//Funcion clear all file DataStuden.dat
void clearFileS() {
    FILE *f = fopen("DataStudent1.dat", "w");
    if(f == NULL) {
        printf("Erorr open file!!!\n");
        return;
    }
    fclose(f);
}
//--------------------------------END FILE-------------------------------------------//


//-----------------------------------FILE DATA TEACHER---------------------------------//
//function save DATA to file .dat
void dataSaveT(struct teacher *teachers[], int const *n) {
    FILE *f = fopen("DataTeacher.dat", "wb");
    if(f == NULL) {
        printf("Erorr open file!!!");
        return;
    }
    size_t const numW = fwrite(*teachers, sizeof(struct teacher), *n, f);
    if(numW !=*n) {
        printf("Erorr. Just wirte %zu element", numW);
    }
    fclose(f);
}
//Funcion load file in program !
void dataLoadT(struct teacher *teachers[], int *n){
    FILE *f = fopen("DataTeacher.dat", "rb");
    if (f == NULL) {
        printf("Erorr open file");
        return;
    }
    fseek(f, 0, SEEK_END);
    int const size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int const structSize = sizeof(struct teacher);
    int const count = size / structSize;

    *teachers = (struct teacher*) realloc(*teachers, count * sizeof(struct teacher));
    if (*teachers == NULL) {
        printf("Erorr\n");
        fclose(f);
        return;
    }
    fread(*teachers, sizeof(struct information), count, f);
    fclose(f);
    *n = count;
}
//Funcsion clear all file DataTeacher.dat
void clearFileT() {
    FILE *f = fopen("DataTeacher.dat", "w");
    if(f == NULL) {
        printf("Erorr open file!!!\n");
        return;
    }
    fclose(f);
}
//--------------------------------END FILE-------------------------------------------//


//-----------------------------------FILE DATA CLASS---------------------------------//
//function save DATA to file .dat
void dataSaveC(struct Classroom *class[], int const *n) {
    FILE *f = fopen("DataClass1.dat", "wb");
    if(f == NULL) {
        printf("Erorr open file!!!\n");
        return;
    }
    size_t const numW = fwrite(*class, sizeof(struct Classroom), *n, f);
    if(numW !=*n) {
        printf("Erorr. Just wirte %zu element", numW);
    }
    fclose(f);
}
//Funcion load file in program !
void dataLoadC(struct Classroom *class[], int *n) {
    FILE *f = fopen("DataClass1.dat", "rb");
    if (f == NULL) {
        printf("Erorr open file\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    int const size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int const structSize = sizeof(struct Classroom);
    int const count = size / structSize;

    *class = (struct Classroom*) realloc(*class, count * sizeof(struct Classroom));
    if (*class == NULL) {
        printf("Erorr\n");
        fclose(f);
        return;
    }
    fread(*class, sizeof(struct Classroom), count, f);
    fclose(f);
    *n = count;
}
//Funcion clear all file Class.dat
void clearFileC() {
    FILE *f = fopen("DataClass1.dat", "w");
    if(f == NULL) {
        printf("Erorr open file!!!\n");
        return;
    }
    fclose(f);
}
//--------------------------------END FILE-------------------------------------------//



//Admin to Delete all file
void adminDelete();
