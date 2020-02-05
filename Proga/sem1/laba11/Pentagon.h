//
// Created by vadim on 4.11.19.
//

#ifndef PENTAGON_H
#define PENTAGON_H


struct Pentagon {
    double R;
};

double perimeter(struct Pentagon x);
void init(struct Pentagon* x, double R);


#endif //PENTAGON_H