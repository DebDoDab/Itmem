#ifndef LAB8_SMALL_CUBE_H
#define LAB8_SMALL_CUBE_H

#include <iostream>
#include <vector>
#include <GL/glut.h>

//Маленькие кубики.
class small_cube {
public:
    unsigned char _rgb[3]; //Для того, чтобы покрасить кубики в с помощью функций "gl".
    unsigned int _color[6]; //Цвета для метода "set", который мы вызываем в других файлах.(верх, низ, впереди, сзади, лево, право)
    double size; //Размер кубика.

    small_cube();

    //Меням цвета кубиков при повороте в разных осях.
    void XOY();

    void XOZ();

    void YOZ();


    //Записываем цвета в массив с помощью сдвига(8(char) и 32(int)).
    unsigned char *RGB_(unsigned int a);

    //Рисование маленьких кубиков со смещением.
    void draw(double x, double y, double z);

    //Рисуем.
    void draw();

    //Меняем цвета.
    void set(int ind, unsigned int color);
};

#endif
