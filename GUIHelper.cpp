#include "GUIHelper.h"
#include <iostream>
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawHeader(string title) {
    system("cls");
    setColor(11); // Cyan
    cout << "==============================================================" << endl;
    cout << "                    " << title << "                    " << endl;
    cout << "==============================================================" << endl;
    setColor(7); // Reset
}

void drawLine() {
    setColor(8); 
    cout << "--------------------------------------------------------------" << endl;
    setColor(7);
}

void showIntro() {
    system("cls");
    setColor(14); 
    cout << "\n==============================================================" << endl;
    setColor(11); 
    cout << "          DATA STRUCTURES AND ALGORITHMS LAB PROJECT          " << endl;
    setColor(14);
    cout << "==============================================================" << endl;
    
    setColor(7); 
    cout << "\nCourse: "; setColor(10); cout << "Data Structures and Algorithms LAB" << endl;
    setColor(7);

    cout << "\nStudents Name & Registration Numbers:" << endl;
    drawLine();
    
    cout << " 1. "; setColor(11); cout << "ROMAISA MAJEED";       setColor(7); cout << "       (24-CS-36)" << endl;
    cout << " 2. "; setColor(11); cout << "AYESHA KHURRAM";       setColor(7); cout << "       (24-CS-68)" << endl;
    cout << " 3. "; setColor(11); cout << "HASSAAN SAFDAR";       setColor(7); cout << "       (24-CS-71)" << endl;
    cout << " 4. "; setColor(11); cout << "MUHAMMAD BURHAN NIAZ"; setColor(7); cout << " (24-CS-1)" << endl;

    cout << "\n\n";
    setColor(14); 
    cout << ">>> PRESS ENTER TO LAUNCH MINI-GOOGLE <<<";
    setColor(7);
    cin.get(); 
}