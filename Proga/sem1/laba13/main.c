#include "Settings.h"
#include "mp3.h"


int main(int argc, char **argv)
{
    Settings *settings = setSettings(argc, argv);
    if (settings->show) {
        show(settings);
    } else if (settings->get) {
        get(settings);
    } else if (settings->set) {
        set(settings);
    }

    return 0;
}