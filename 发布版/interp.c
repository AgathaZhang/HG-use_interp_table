/**
  ******************************************************************************
  * @file    UWB/interp.c
  * @author  Zhang weizhi
  * @version V1.0.0
  * @date    9-April-2024
  * @brief   The truth value of UWB in image space is calculated by calibration table interpolation
  ******************************************************************************

 * Function simpleAtof 不依赖库函数转换浮点为double
 * Function read_calibration_table 读取存在table.c中的字符串数组 table.c用于存校准表
 * Function distance_interp 用于测算新得到的x， y（称为目标点）遍历标定点的最短距离
 * Function surround_by 计算新得到的x， y（称为目标点）离哪一个校准点的mean_x，mean_y距离最近 
 * Function find_grid_ID 返回最近标定点ID
 * Function interp_1 第一次插值
 * Function interp_2 第二次插值
 * Function find_corners 找到四个角点
 * Function Interp_coords 对main函数的对外接口总函数

 */


#include "interp.h"

void test_printf(void)
{
    printf("----------test calibration----------");
}

int charToInt(char c)
{
    return c - '0';
}

double simpleAtof(const char *str) {
    double result = 0.0;
    double fraction = 1.0;
    int decimalFound = 0; // 标记是否找到小数点

    while (*str != '\0') {
        if (*str == '.') {
            decimalFound = 1;
        } else if (*str >= '0' && *str <= '9') {
            if (decimalFound) {
                fraction *= 0.1;
                result += (*str - '0') * fraction;
            } else {
                result = result * 10.0 + (*str - '0');
            }
        }
        str++;
    }

    return result;
}

DataPoint* read_calibration_table(const char** interp_table, int* count) {

    int dataSize = 0, capacity = GRID_NUM; // 初始容量为10，根据需要增加

    // DataPoint* dataPoints = (DataPoint*)malloc(capacity * sizeof(DataPoint));    // 用malloc开辟数组指针单片机是将空间动态分配在堆上的 可能导致地址不连续 大小不够 这里用下面直接开辟数组将空间分配在栈上保证安全
    extern DataPoint dataPoints[GRID_NUM];
    for (dataSize; dataSize < capacity; dataSize++){
        int flag_single_read = 0;   // 在读状态指示 1在读
        int is_neg = 0;             // 是否为负 1为负
        int cont = 0;               // 用于区段计数
        char temp_num[10] = {'\0'};
        DataPoint dp = {0};
        const char* line = interp_table[dataSize];
        for (int i = 0; line[i] != '\0'; ++i)     // 遍历一行的每个字符
        {   // printf("%c",line[i]);
            if (line[i] == ':')
            {
                cont++;
                flag_single_read = 1;
                continue;
            }
            if (cont == 1 && flag_single_read == 1)
            {
              dp.posi_ID_x = charToInt(line[i]);
                // printf("%d",dp.posi_ID_x);
                flag_single_read = 0;
            }
            if (cont == 2 && flag_single_read == 1)
            {
                dp.posi_ID_y = charToInt(line[i]);
                // printf("%d",dp.posi_ID_y);
                flag_single_read = 0;
            }

            if (cont == 3 && flag_single_read == 1)
            {
                if (line[i] == '-')
                {
                    is_neg = 1;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (int j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num[j] = line[i + j];}
                        else break;
                    }   
                    flag_single_read = 0;
                    if (is_neg == 1)
                    {
                        dp.mean_x = (-1) * atof(temp_num);
                    }
                    else
                        {dp.mean_x = atof(temp_num);}
                }
                is_neg = 0;
                memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
            }

            if (cont == 4 && flag_single_read == 1)
            {
                if (line[i] == '-')
                {
                    is_neg = 1;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (int j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num[j] = line[i + j];}
                        else break;
                    }   
                    flag_single_read = 0;
                    if (is_neg == 1)
                    {
                        dp.mean_y = (-1) * atof(temp_num);
                    }
                    else
                        {dp.mean_y = atof(temp_num);}
                }
                is_neg = 0;
                memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
            }

            if (cont == 5 && flag_single_read == 1)
            {
                if (line[i] == '-')
                {
                    is_neg = 1;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (int j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num[j] = line[i + j];}
                        else break;
                    }
                    flag_single_read = 0;
                    if (is_neg == 1)
                    {
                        dp.weight_x = (-1) * atof(temp_num);
                    }
                    else
                        {dp.weight_x = atof(temp_num);}
                    
                }
                is_neg = 0;
                memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
            }

            if (cont == 6 && flag_single_read == 1)
            {
                if (line[i] == '-')
                {
                    is_neg = 1;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (int j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num[j] = line[i + j];}
                        else break;
                    }                                                       // TODO 验证这里的问题
                    flag_single_read = 0;
                    if (is_neg == 1)
                    {
                        dp.weight_y = (-1) * atof(temp_num);
                    }
                    else
                        {dp.weight_y = atof(temp_num);}
                }
                is_neg = 0;
                memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
                break;
            }
        }
        dataPoints[dataSize] = dp;
        // printf("%d ",dp.posi_ID_y);
        // printf("%d\n",dataPoints[dataSize].posi_ID_y);
    }
    *count = dataSize;
    printf("----------read interp table finished----------\n");
    return dataPoints;
}

static double distance_interp(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));}

int surround_by(double x, double y, DataPoint this_point, const DataPoint* dataPoints, int dataSize, DataPoint* four_point) {
    /** 计算新得到的x， y（称为目标点）离哪一个校准点的mean_x，mean_y距离最近 返回目标点ID
     * vector_x vector_y 代表目标点在最近校准点的那个方向 1 1 表示在左上角方向
     */
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
        if (four_point[j].posi_ID_x == minX && four_point[j].posi_ID_y == minY) *right_down = four_point[j];
        else if (four_point[j].posi_ID_x == maxX && four_point[j].posi_ID_y == minY) *left_down = four_point[j];
        else if (four_point[j].posi_ID_x == minX && four_point[j].posi_ID_y == maxY) *right_up = four_point[j];
        else if (four_point[j].posi_ID_x == maxX && four_point[j].posi_ID_y == maxY) *left_up = four_point[j];
    }
}

void Interp_coords(const DataPoint* dataPoints, int count, double x, double y, double* p) {

    DataPoint this_grid = find_grid_ID(x, y, dataPoints, count);
    DataPoint four_point[4];
    int four_count = surround_by(x, y, this_grid, dataPoints, count, four_point);

    // 确保找到了四个点
    if (four_count != 4) {
        printf("Unable to find all four surrounding points\n");
        return;
    }
    // 找到四个角点
    DataPoint left_up, right_up, left_down, right_down;
    find_corners(four_point, &left_up, &right_up, &left_down, &right_down);

    double r1[4], r2[4];    // 其中1 2位存新xy权重 3 4位存线上交点坐标
    interp_1(left_up, right_up, x, y, r1);
    interp_1(left_down, right_down, x, y, r2);
    // 执行最终的插值计算
    interp_2(r1, r2, x, y, p);
    return; // 用于存储 Interp_coords 函数的输出
}
