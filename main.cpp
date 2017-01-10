#include "application.h"

int main() {
    Application *app = new Application();
    app->loop();
    delete app;
}

