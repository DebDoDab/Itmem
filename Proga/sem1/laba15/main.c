#include "settings.h"
#include "arch.h"

int main(int argc, char **argv)
{
    Settings *settings = setSettings(argc, argv);

    if (settings->create) {
        create(settings);
    } else if (settings->extract) {
        extract(settings);
    } else if (settings->list) {
        list(settings);
    }
}