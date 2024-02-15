#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point topLeft;
    Point bottomRight;
} Rectangle;

struct Example {
    // char a;
    int b[10];
};

int main() {
    Rectangle rectangle = { { 0, 0 }, { 100, 200 } };

    printf("TopLeft point: (%d, %d)\n", rectangle.topLeft.x, rectangle.topLeft.y);
    printf("BottomRight point: (%d, %d)\n", rectangle.bottomRight.x, rectangle.bottomRight.y);

    printf("Size of rectangle: %zu bytes\n", sizeof(Rectangle));

    printf("Size of struct Example: %zu bytes\n", sizeof(struct Example));

    return 0;
}
