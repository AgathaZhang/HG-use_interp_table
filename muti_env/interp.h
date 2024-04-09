#ifndef __USE_INTERP__
#define __USE_INTERP__

#define INT_MAX 0x7fffffff
#define INT_MIN (-INT_MAX - 1)
#define DBL_MAX ((double)1.79769313486231570814527423731704357e+308L)
#define GRID_NUM 64

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <float.h>
// #include <limits.h>

#define MAX_SIZE 1024               // 假设标定数据点的最大数量
#define MAX_SURROUND_POINTS 4       // 插值包围点数量
#define MAX_LINE_LENGTH 1024        // 设置读取标定文件的最大行数

  // struct _iobuf {
  //   char *_ptr;
  //   int _cnt;
  //   char *_base;
  //   int _flag;
  //   int _file;
  //   int _charbuf;
  //   int _bufsiz;
  //   char *_tmpfname;
  // };
  // typedef struct _iobuf FILE;
  
typedef struct {
    int posi_ID_x;
    int posi_ID_y;
    double mean_x;
    double mean_y;
    double weight_x;
    double weight_y;
} DataPoint;                            // 标定点的结构体

extern const char* interp_table[];      // 存离线标定数据table
extern DataPoint* read_calibration_table(const char** /*interp table*/, int* /*count*/);     // 读标定表
extern void Interp_coords(const DataPoint* dataPoints, int count, double x, double y, double* P);

extern void test_printf(void);
// extern double* use_interp(DataPoint*, double, double, int);
// extern int read_table(void);
#endif
