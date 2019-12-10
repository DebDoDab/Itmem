#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 2) { // Первый элемент в аргументах – путь самого exe, далее уже идет нужная
        //нам строка с именем файла, откуда мы будем считывать
        printf("Something went wrong :(\n"); // Нам ничего не передали
        return 0;
    }
    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL) {  // Такого файла не существует
        printf("I think such file does not exist :(\n");
        return 0;
    }

    int it = 0;
    while ((read = getline(&line, &len, fp)) != -1) { //Читаем новую строку из файла, пока
        //они есть
        if (it & 1) printf("line = %s", line); //Если это четная строка, то выводим
        it++;
    }
}
