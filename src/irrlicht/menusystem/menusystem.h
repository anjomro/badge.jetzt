#include "../../base/display.h"
#include "../../base/button.h"

namespace menusystem {
    // Struktur eines Menü-Eintrags
    struct MenuEntry {
        const char* title;
        void (*action)();
    };
    
    void launch();
    void handleMenuInput();
    void drawMenu();
}