#include "GUIHelper.h"
#include "SearchEngine.h"
#include <cstdlib>

int main() {
    system("title Mini-Google Engine");
    showIntro();
    
    SearchEngine system;
    system.handleMenu();
    return 0;
}