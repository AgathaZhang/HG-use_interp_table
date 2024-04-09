#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <limits.h>

#define MAX_SIZE 1024 // 假设数据点的最大数量
#define MAX_SURROUND_POINTS 4
#define MAX_LINE_LENGTH 1024

typedef struct {
    int posi_ID_x;
    int posi_ID_y;
    double mean_x;
    double mean_y;
    double weight_x;
    double weight_y;
} DataPoint;

// DataPoint dataPoints[MAX_SIZE];

static double distance_interp(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));}

int surround_by(double x, double y, DataPoint this_point, const DataPoint* dataPoints, int dataSize, DataPoint* four_point) {
    int count = 0; // 用于跟踪找到的点数
    int vector_x = -1, vector_y = -1;
    if (x - this_point.mean_x > 0) { vector_x = 1; }
    if (y - this_point.mean_y > 0) { vector_y = 1; }
    int i;
    for (i = 0; i < dataSize; ++i) {
        const DataPoint gridPoint = dataPoints[i];
        if (gridPoint.posi_ID_x == this_point.posi_ID_x && gridPoint.posi_ID_y == this_point.posi_ID_y) {
                four_point[count++] = gridPoint;
        }
        if (gridPoint.posi_ID_x == (this_point.posi_ID_x + vector_x) && gridPoint.posi_ID_y == this_point.posi_ID_y) {
                four_point[count++] = gridPoint;
        }
        if (gridPoint.posi_ID_x == (this_point.posi_ID_x) && gridPoint.posi_ID_y == (this_point.posi_ID_y + vector_y)) {
                four_point[count++] = gridPoint;
        }
        if (gridPoint.posi_ID_x == (this_point.posi_ID_x + vector_x) &&
            gridPoint.posi_ID_y == (this_point.posi_ID_y + vector_y)) {
                four_point[count++] = gridPoint;
        }
    }

    if (count != MAX_SURROUND_POINTS) {
        // 根据实际情况处理错误或边界条件
        // printf("Matching error or boundary condition not handled.\n");
        return 0; // 返回0表示函数没有按预期工作
    }
    return count; // 返回找到的点的数量
}

// void* my_open_file(const char* filename, const char* mode) {
// return fopen(filename, mode);}
//     // const char* fname = filename;
//     // void* file = my_open_file(fname, "r");


// 动态分配数组来存储读取的数据点
DataPoint* read_table(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");


    char line[MAX_LINE_LENGTH];
    DataPoint* dataPoints = NULL;
    int dataSize = 0, capacity = 64; // 初始容量为10，根据需要增加

    if (!file) {
        // fprintf(stderr, "Error opening file: %s\n", filename);
        // printf(stderr, "Error opening file: %s\n", filename);
        // *count = 0;
        return NULL;
    }

    dataPoints = (DataPoint*)malloc(capacity * sizeof(DataPoint));  // 该方法为什么不行？
    // DataPoint dataPoints[capacity] = {0};

    while (fgets(line, sizeof(line), (FILE*)file)) {
        // if (dataSize >= capacity) {
        //     // 需要更多空间
        //     capacity *= 2;
        //     dataPoints = (DataPoint*)realloc(dataPoints, capacity * sizeof(DataPoint));
        // }

        DataPoint point = {0};
        char* token;
        char* rest = line;

        while ((token = strtok_r(rest, ",", &rest))) {
            char key[20];
            if (sscanf(token, "posi_ID_x: %d", &point.posi_ID_x) == 1 ||
                sscanf(token, " posi_ID_y: %d", &point.posi_ID_y) == 1 ||
                sscanf(token, " mean_x: %lf", &point.mean_x) == 1 ||
                sscanf(token, " mean_y: %lf", &point.mean_y) == 1 ||
                sscanf(token, " weight_x: %lf", &point.weight_x) == 1 ||
                sscanf(token, " weight_y: %lf", &point.weight_y) == 1) {
            }
        }

        dataPoints[dataSize++] = point;
        // *(dataPoints + dataSize) = point;
        // dataSize = dataSize + 1;
        // printf("MyStruct: x=%d, y=%d", *(dataPoints[dataSize]).posi_ID_x, dataPoints[dataSize]->posi_ID_y);
    }
        auto& watch = dataPoints[2];
    fclose((FILE*)file);
    *count = dataSize;
    return dataPoints;
}

// 注意：这个版本假设dataPoints是一个数组，且count是数组中元素的数量
DataPoint find_grid_ID(double x, double y, const DataPoint* dataPoints, int count) {
    double minDistance = DBL_MAX;
    DataPoint nearestGridPoint = {0}; // 使用一个空的初始化器来避免未初始化警告
    int i;
    for (i = 0; i < count; i++) {
        double dist = distance_interp(x, y, dataPoints[i].mean_x, dataPoints[i].mean_y);
        if (dist < minDistance) {
            minDistance = dist;
            nearestGridPoint = dataPoints[i];
        }
    }
    return nearestGridPoint;
}


void interp_1(DataPoint p1, DataPoint p2, double x, double y, double* result) {
    // 确保调用此函数的人已经分配了足够的内存来存储结果
    double weigh_p1[2], weigh_p2[2]; // 临时存储权重
    double y_new;

    weigh_p1[0] = p1.weight_x;
    weigh_p1[1] = p1.weight_y;
    weigh_p2[0] = p2.weight_x;
    weigh_p2[1] = p2.weight_y;

    // 计算加权平均值
    double denom = fabs(p1.mean_x - p2.mean_x); // 分母，确保不为0
    if (denom == 0) denom = 0.1; // 防止除以0

    result[0] = fabs((x - p1.mean_x)) / denom * weigh_p2[0] + fabs((x - p2.mean_x)) / denom * weigh_p1[0];
    result[1] = fabs((x - p1.mean_x)) / denom * weigh_p2[1] + fabs((x - p2.mean_x)) / denom * weigh_p1[1];

    // 计算新的y值
    y_new = (x - p2.mean_x) / (p1.mean_x - p2.mean_x) * (p1.mean_y - p2.mean_y) + p2.mean_y;
    result[2] = x;
    result[3] = y_new;
}

void interp_2(const double p1[4], const double p2[4], double x, double y, double result[2]) {
    // 解构输入数组以便于访问
    double p1_weigh_x = p1[0];
    double p1_weigh_y = p1[1];
    double p1_set_x = p1[2];
    double p1_set_y = p1[3];

    double p2_weigh_x = p2[0];
    double p2_weigh_y = p2[1];
    double p2_set_x = p2[2];
    double p2_set_y = p2[3];

    // 计算欧氏距离以用于权重计算
    double total, left, right;
    total = sqrt(pow(p2_set_x - p1_set_x, 2) + pow(p2_set_y - p1_set_y, 2));
    left = sqrt(pow(x - p2_set_x, 2) + pow(y - p2_set_y, 2));
    right = sqrt(pow(x - p1_set_x, 2) + pow(y - p1_set_y, 2));

    // 计算并设置结果
    result[0] = left / total * p1_weigh_x + right / total * p2_weigh_x;
    result[1] = left / total * p1_weigh_y + right / total * p2_weigh_y;
}

void find_corners(const DataPoint four_point[4], DataPoint* left_up, DataPoint* right_up, DataPoint* left_down, DataPoint* right_down) {
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;

    // 首先找到最小和最大的posi_ID_x和posi_ID_y
    int i;
    for ( i = 0; i < 4; i++) {
        if (four_point[i].posi_ID_x < minX) minX = four_point[i].posi_ID_x;
        if (four_point[i].posi_ID_x > maxX) maxX = four_point[i].posi_ID_x;
        if (four_point[i].posi_ID_y < minY) minY = four_point[i].posi_ID_y;
        if (four_point[i].posi_ID_y > maxY) maxY = four_point[i].posi_ID_y;
    }

    // 然后根据最小和最大值识别每个角点
    int j;
    for (j = 0; j < 4; j++) {
        // if (four_point[j].posi_ID_x == minX && four_point[j].posi_ID_y == minY) *left_up = four_point[j];
        // else if (four_point[j].posi_ID_x == maxX && four_point[j].posi_ID_y == minY) *right_up = four_point[j];
        // else if (four_point[j].posi_ID_x == minX && four_point[j].posi_ID_y == maxY) *left_down = four_point[j];
        // else if (four_point[j].posi_ID_x == maxX && four_point[j].posi_ID_y == maxY) *right_down = four_point[j];
        if (four_point[j].posi_ID_x == minX && four_point[j].posi_ID_y == minY) *right_down = four_point[j];
        else if (four_point[j].posi_ID_x == maxX && four_point[j].posi_ID_y == minY) *left_down = four_point[j];
        else if (four_point[j].posi_ID_x == minX && four_point[j].posi_ID_y == maxY) *right_up = four_point[j];
        else if (four_point[j].posi_ID_x == maxX && four_point[j].posi_ID_y == maxY) *left_up = four_point[j];
    }
}

void Interp_coords(const DataPoint* dataPoints, int count, double x, double y, double* P) {
    DataPoint this_grid = find_grid_ID(x, y, dataPoints, count);
    DataPoint four_point[4];
    int four_count = surround_by(x, y, this_grid, dataPoints, count, four_point);

    // 确保找到了四个点
    if (four_count != 4) {
        printf("无法找到四个周围的点。\n");
        return;
    }
    // 找到四个角点
    DataPoint left_up, right_up, left_down, right_down;
    find_corners(four_point, &left_up, &right_up, &left_down, &right_down);

    double r1[4], r2[4];    // 其中1 2位存新xy权重 3 4位存线上交点坐标
    interp_1(left_up, right_up, x, y, r1);
    interp_1(left_down, right_down, x, y, r2);
    // 执行最终的插值计算
    interp_2(r1, r2, x, y, P);
}

int main() {
    double x = 0.94, y = 2.11;
    // double x = 1.38, y = 1.68;
    int count;      // 计数data处理到第几个
    DataPoint* data_vector = read_table("cali_table.c", &count);
    if (data_vector == NULL) {
        printf("Failed to read data points.\n");
        return 1; // 错误退出
    }

    // //TODO 写入一个.C文件
    // FILE *file = fopen("calibration_table.c", "w");
    // for (int i = 0; i < count; i++) {
    //     fprintf(file, "%s", data_vector[i]);
    // }

    // // 关闭文件
    // fclose(file);





    double weigh_out[2]; // 用于存储 Interp_coords 函数的输出
    Interp_coords(data_vector, count, x, y, weigh_out);

    double x_out = x * weigh_out[0];
    double y_out = y * weigh_out[1];
    printf("result x:%f y:%f\n", x_out, y_out);

    // free(data_vector); // 释放由 readDataPoints 分配的内存
    return 0;
}



