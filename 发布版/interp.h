#ifndef __USE_INTERP__
#define __USE_INTERP__

#define INT_MAX 0x7fffffff          // 定义比较大小时要用到的一些值
#define INT_MIN (-INT_MAX - 1)
#define DBL_MAX ((double)1.79769313486231570814527423731704357e+308L)
#define GRID_NUM 64                 // 定义标定格点

#include <stdio.h>                  // 算法要用大的头文件是在keil microLib中的 需要注意函数调用差异
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <float.h>
// #include <limits.h>

#define MAX_SIZE 1024               // 假设标定数据点的最大数量
#define MAX_SURROUND_POINTS 4       // 插值包围点数量
#define MAX_LINE_LENGTH 1024        // 设置读取标定文件的最大行数

typedef struct {
    int posi_ID_x;                  // 格点的ID
    int posi_ID_y;
    double mean_x;                  // 放在格点位置时UWB实际计算得出的值 这个值和格点真实坐标有偏差
    double mean_y;
    double weight_x;                // 重新计算出的权重
    double weight_y;
} DataPoint;                        // 标定点的结构体

extern const char* interp_table[];      // 存离线标定数据table
extern DataPoint* read_calibration_table(const char** /*interp table*/, int* /*count*/);     // 读标定表
extern void Interp_coords(const DataPoint* dataPoints, int count, double x, double y, double* p);       // 计算插值 返回double*二维向量 得出的第一个值为x 第二个值为y 

extern void test_printf(void);
#endif
