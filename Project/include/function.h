#ifndef FUNCTION_H#define FUNCTION_Hvoid menuStart(int *menu);//-------FOR MENU STUDENT----------////studentvoid menuStudent();//1void addStudent();//2void showStudent();//3void searchStudent();//4void editStudent();//5void deleteStudent();//6void sortStudentBN();//-------END MENU STUDENT----------////-------FOR MENU Teacher----------//void menuTeacher();//1void addTeacher();//2void showTeacher();//3void searchTeacher();//4void editTeacher();//5void deleteTeacher();//6void addClassforTeacher();//7void chooseSubject();//-------END MENU Teacher----------////-------FOR MENU Class----------//void menuClass();//1void addClass();//2void showClass();//3void editClass();//4void deleteClass();//5void detailslass();//6void deleteStudentandAddForclass();//7void deleteTeacherandAddForclass();//8void addStudentForClass();//9void addTeacherForClass();//-------END MENU Class----------////-----FILE Student-----////file Datavoid dataSaveS();void dataLoadS();void clearFileS();//-----FILE Teacher-----//void dataSaveT();void dataLoadT();void clearFileT();//----FILE CLASS-------//void dataSaveC();void dataLoadC();void clearFileC();//----Login admin-----//void adminlogin();void setPadmin();//--------------////----mode for charter---//void disable_echo_mode();void enable_echo_mode();//--------end--------////testvoid delete0();#endif