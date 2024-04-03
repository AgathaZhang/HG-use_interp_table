// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <string.h>
// #include <float.h>
// #include <limits.h>

// #define MAX_SIZE 1024 // 假设数据点的最大数量
// #define MAX_SURROUND_POINTS 4
// #define MAX_LINE_LENGTH 1024

// typedef struct DataPoint {
//     int posi_ID_x;
//     int posi_ID_y;
//     double mean_x;
//     double mean_y;
//     double weight_x;
//     double weight_y;
// } DataPoint;
// #define MAX_POINTS 1000     // 设置容器深度

// DataPoint dataPoints[MAX_POINTS];

// int main()
// {
//     DataPoint P;
//     double A = P.mean_x;
//     printf("%f",A);


// }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <limits.h>
// 定义一个结构体
typedef struct {
    int x;
    int y;
    double z;
} MyStruct;

int main() {
    // 创建一个指向结构体的指针，并分配内存
    MyStruct *myStructPtr = malloc(sizeof(MyStruct));
    if (myStructPtr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // 使用箭头运算符给结构体成员赋值
    myStructPtr->x = 1;
    myStructPtr->y = 2;
    myStructPtr->z = 3.0;

    // 使用箭头运算符访问结构体成员并打印
    printf("x: %d\n", myStructPtr->x);
    printf("y: %d\n", myStructPtr->y);
    printf("z: %f\n", myStructPtr->z);

    // 释放动态分配的内存
    free(myStructPtr);

    return 0;
}