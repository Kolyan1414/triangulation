#include <iostream>
#include "Graphics.h"
#include "Point/point.cpp"


int main(int argc, char** argv){

    std::vector<Point> point_vector;
    point_vector.reserve(5);
    std::vector<Point*> point_pointer_vector;
    point_pointer_vector.reserve(5);

    for(int i = 0; i < 5; i++)
    {
        std::cin >> point_vector[i];
        point_pointer_vector[i] = &point_vector[i];

        point_pointer_vector[i]->show();
    }

    InitializationGLUT(&argc, argv, LFK, FULL_SCREEN, &point_pointer_vector);

    return(0);
}
