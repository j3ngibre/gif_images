#ifndef CCOLOR_H_INCLUDED
#define CCOLOR_H_INCLUDED
#include <cmath>

#include <string>

using namespace std;

struct Color {
     string name;
    int r;
    int g;
    int b;
    int valor;

};

// Define colors

Color BLACK = {"Negro", 0, 0, 0,0};
Color DARK_BLUE = {"Azul oscuro", 0, 0, 128,1};
Color DARK_GREEN = {"Verde oscuro", 0, 128, 0,2};
Color DARK_CYAN = {"Cyan oscuro", 0, 128, 128,3};
Color DARK_RED = {"Rojo oscuro", 128, 0, 0,4};
Color DARK_MAGENTA = {"Magenta oscuro", 128, 0, 128,5};
Color BROWN = {"Marrón oscuro", 139, 69, 19,6};
Color LIGHT_GRAY = {"Gris claro", 192, 192, 192,7};
Color MEDIUM_GRAY = {"Gris medio", 128, 128, 128,8};
Color LIGHT_BLUE = {"Azul claro", 173, 216, 230,9};
Color LIGHT_GREEN = {"Verde claro", 144, 238, 144,10};
Color LIGHT_CYAN = {"Cyan claro", 224, 255, 255,11};
Color LIGHT_RED = {"Rojo claro", 255, 0, 0,12};
Color LIGHT_MAGENTA = {"Magenta claro", 255, 0, 255,13};
Color YELLOW = {"Amarillo", 255, 255, 0,14};
Color WHITE = {"Blanco", 255, 255, 255,15};



int classify_color(int r, int g, int b) {
    double min_distance = 100000000000;
    int closest_color_index = 15;


    Color colors[] = {BLACK, DARK_BLUE, LIGHT_BLUE, DARK_GREEN, LIGHT_GREEN, DARK_CYAN, LIGHT_CYAN,
                      DARK_RED,LIGHT_RED, DARK_MAGENTA, LIGHT_MAGENTA, BROWN, YELLOW, LIGHT_GRAY, MEDIUM_GRAY, WHITE };
    for (int i = 0; i < 16; i++) {
        double distance = sqrt(pow(r - colors[i].r, 2) + pow(g - colors[i].g, 2) + pow(b - colors[i].b, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest_color_index = i;
        }
    }


    return colors[closest_color_index].valor;
}


#endif // CCOLOR_H_INCLUDED
