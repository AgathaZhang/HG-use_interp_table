#include "interp.h"

void test_printf(void)
{
    printf("----------test calibration----------");
}
// const char *interp_table;

// DataPoint* read_calibration_table(const char* filename, int* count)
// {
//             test_printf();
// }

// void verifyNullTermination(const char* str) {
//     size_t len = strlen(str); // 获取字符串的长度，不包括 '\0'
//     // len = len - 5;
//     if (str[len] == '\0') { // 检查位于长度索引处的字符
//         printf("The string is null-terminated.\n");
//     } else {
//         printf("The string is NOT null-terminated.\n");
//     }
// }


// void parseDataPoint(const char* str, DataPoint* dp) {
//     sscanf(str, "posi_ID_x: %d, posi_ID_y: %d, mean_x: %lf, mean_y: %lf, weight_x: %lf, weight_y: %lf",
//            &dp->posi_ID_x, &dp->posi_ID_y, &dp->mean_x, &dp->mean_y, &dp->weight_x, &dp->weight_y);
// }

// DataPoint* read_calibration_table(const char** interp_table, int* count) {

//     // char line[MAX_LINE_LENGTH];
//     DataPoint* dataPoints;      //TODO 这里不进行初始化可能会有些问题
//     int dataSize = 0, capacity = 64; // 初始容量为10，根据需要增加
//     // capacity = sizeof(interp_table) / sizeof(interp_table[0]);

//     dataPoints = (DataPoint*)malloc(capacity * sizeof(DataPoint));
//     double tt;
//     for (int i = 0; i < capacity; i++){
//         // char* line = (char*)malloc(1024);
//         // line[0] = 't';
//         // printf("init %d, %s\n", i, line);
//         // printf("str %d, %s\n", i, interp_table[i]);
//         // strcpy(line, interp_table[i]);
//         // printf("line: %s\n", line);
//         // dataPoints[i] = {0};
//         // verifyNullTermination(interp_table[i]);
//             // 获取第一行
//         const char* firstLine = interp_table[i];

//         // 遍历第一行的每个字符
//         for (int i = 0; firstLine[i] != '\0'; ++i) {
//             printf("%c", firstLine[i]);
//         }
//         printf("\n");
//         parseDataPoint(interp_table[i], &dataPoints[i]);
//         tt = dataPoints[i].weight_y;
//         printf("%f",dataPoints[i].weight_y);

//         // char* line = const_cast<char*>(interp_table[i]);
//         // DataPoint point = {0};
//         // char* token;
//         // // char* rest = line;
//         // while ((token = strtok_r(const_cast<char*>(interp_table[i]), ",", &line))) {
//         //         // line = &saveptr;

//         // if (sscanf(token, "posi_ID_x: %d", &point.posi_ID_x) == 1 ||
//         //     sscanf(token, " posi_ID_y: %d", &point.posi_ID_y) == 1 ||
//         //     sscanf(token, " mean_x: %lf", &point.mean_x) == 1 ||
//         //     sscanf(token, " mean_y: %lf", &point.mean_y) == 1 ||
//         //     sscanf(token, " weight_x: %lf", &point.weight_x) == 1 ||
//         //     sscanf(token, " weight_y: %lf", &point.weight_y) == 1) {
//         //     }
//         // }

//         // free(line);
//         // dataPoints[dataSize++] = point;

//     }
//     *count = dataSize;
//     printf("----------read interp table finished----------");
//     return dataPoints;
// }

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

// DataPoint* read_calibration_table(const char** interp_table, int* count) {

//     // char line[MAX_LINE_LENGTH];
//     DataPoint* dataPoints;      //TODO 这里不进行初始化可能会有些问题
//     int dataSize = 0, capacity = 64; // 初始容量为10，根据需要增加
//     // capacity = sizeof(interp_table) / sizeof(interp_table[0]);

//     dataPoints = (DataPoint*)malloc(capacity * sizeof(DataPoint));
//     for (int k = 0; k < capacity; k++){
//         int flag_single_read = 0;   // 在读状态指示 1在读
//         int is_neg = 0;             // 是否为负 1为负
//         int cont = 0;               // 用于区段计数
//         char temp_num[10] = {'\0'};
//         // const char* temp_num[10] = {""};
//         DataPoint dp = {0};
//         const char* line = interp_table[k];       // TODO 用动态开辟空间line
//         for (int i = 0; line[i] != '\0'; ++i)     // 遍历第一行的每个字符
//         {
//             if (line[i] == ':')
//             {
//                 cont++;
//                 flag_single_read = 1;
//                 continue;
//             }
//             if (cont == 1 && flag_single_read == 1)
//             {
//                 dp.posi_ID_x = charToInt(line[i]);
//                 flag_single_read = 0;
//             }
//             if (cont == 2 && flag_single_read == 1)
//             {
//                 dp.posi_ID_y = charToInt(line[i]);
//                 flag_single_read = 0;
//             }

//             if (cont == 3 && flag_single_read == 1)
//             {
//                 if (line[i] == '-')
//                 {
//                     is_neg = 1;
//                     continue;
//                 }
//                 if (line[i] >= '0' && line[i] <= '9')
//                 {
//                     for (int j = 0; j < 10; j++)
//                     {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
//                         {temp_num[j] = line[i + j];}
//                         else break;
//                     }   
//                     flag_single_read = 0;
//                     if (is_neg == 1)
//                     {
//                         dp.mean_x = (-1) * simpleAtof(temp_num);
//                     }
//                     else
//                         {dp.mean_x = simpleAtof(temp_num);}
//                 }
//                 is_neg = 0;
//                 // memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
//             }

//             if (cont == 4 && flag_single_read == 1)
//             {
//                 if (line[i] == '-')
//                 {
//                     is_neg = 1;
//                     continue;
//                 }
//                 if (line[i] >= '0' && line[i] <= '9')
//                 {
//                     for (int j = 0; j < 10; j++)
//                     {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
//                         {temp_num[j] = line[i + j];}
//                         else break;
//                     }   
//                     flag_single_read = 0;
//                     if (is_neg == 1)
//                     {
//                         dp.mean_y = (-1) * simpleAtof(temp_num);
//                     }
//                     else
//                         {dp.mean_y = simpleAtof(temp_num);}
//                 }
//                 is_neg = 0;
//                 // memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
//             }

//             if (cont == 5 && flag_single_read == 1)
//             {
//                 if (line[i] == '-')
//                 {
//                     is_neg = 1;
//                     continue;
//                 }
//                 if (line[i] >= '0' && line[i] <= '9')
//                 {
//                     for (int j = 0; j < 10; j++)
//                     {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
//                         {temp_num[j] = line[i + j];}
//                         else break;
//                     }
//                     flag_single_read = 0;
//                     if (is_neg == 1)
//                     {
//                         dp.weight_x = (-1) * simpleAtof(temp_num);
//                     }
//                     else
//                         {dp.weight_x = simpleAtof(temp_num);}
                    
//                 }
//                 is_neg = 0;
//                 // memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
//             }

//             if (cont == 6 && flag_single_read == 1)
//             {
//                 if (line[i] == '-')
//                 {
//                     is_neg = 1;
//                     continue;
//                 }
//                 if (line[i] >= '0' && line[i] <= '9')
//                 {
//                     for (int j = 0; j < 10; j++)
//                     {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
//                         {temp_num[j] = line[i + j];}
//                         else break;
//                     }                                                       // TODO 验证这里的问题
//                     flag_single_read = 0;
//                     if (is_neg == 1)
//                     {
//                         dp.weight_y = (-1) * simpleAtof(temp_num);
//                     }
//                     else
//                         {dp.weight_y = simpleAtof(temp_num);}
//                 }
//                 is_neg = 0;
//                 // memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
//                 break;
//             }
//         }
//         dataPoints[k] = dp;
//         printf("%d\n",dp.weight_y);
//         // printf("%d\n",dataPoints[k].posi_ID_y);
//         // printf("%s\n", line);
//         // printf("\nget line over");
//     }
//     *count = dataSize;
//     printf("----------read interp table finished----------");
//     return dataPoints;
// }

DataPoint* read_calibration_table(const char** interp_table, int* count) {

    // char line[MAX_LINE_LENGTH];
    // DataPoint* dataPoints = NULL;      //TODO 这里不进行初始化可能会有些问题
    int dataSize = 0, capacity = GRID_NUM; // 初始容量为10，根据需要增加
    // capacity = sizeof(interp_table) / sizeof(interp_table[0]);

    // DataPoint* dataPoints = (DataPoint*)malloc(capacity * sizeof(DataPoint));
    extern DataPoint dataPoints[GRID_NUM];
    // DataPoint* ptr = dataPoints;
    for (dataSize; dataSize < capacity; dataSize++){
        int flag_single_read = 0;   // 在读状态指示 1在读
        int is_neg = 0;             // 是否为负 1为负
        int cont = 0;               // 用于区段计数
        char temp_num[10] = {'\0'};
        // const char* temp_num[10] = {""};
        DataPoint dp = {0};
        const char* line = interp_table[dataSize];       // TODO 用动态开辟空间line
        for (int i = 0; line[i] != '\0'; ++i)     // 遍历第一行的每个字符
        {   // printf("%c",line[i]);
            if (line[i] == ':')
            {
                cont++;
                flag_single_read = 1;
                continue;
            }
            if (cont == 1 && flag_single_read == 1)
            { // printf("%c",line[i]);  这里正确
              dp.posi_ID_x = charToInt(line[i]);
                // printf("%d",dp.posi_ID_x);
                flag_single_read = 0;
            }
            if (cont == 2 && flag_single_read == 1)
            {
                dp.posi_ID_y = charToInt(line[i]);
                // printf("%d",dp.posi_ID_y);
                // printf("\n");
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
                // printf("%f\n",dp.weight_y);
                is_neg = 0;
                memset(temp_num, 0, sizeof(temp_num));      // temp_num = {'\0'};
                break;
            }
        }

        // ptr->mean_x = dp.mean_x;
        // ptr->mean_y = dp.mean_y;
        // ptr->posi_ID_x = dp.posi_ID_x;
        // ptr->posi_ID_y = dp.posi_ID_y;
        // ptr->weight_x = dp.weight_x;
        // ptr->weight_y = dp.weight_y;
        // ptr++;
        dataPoints[dataSize] = dp;
        printf("%d ",dp.posi_ID_y);
        printf("%d\n",dataPoints[dataSize].posi_ID_y);
        // printf("%s\n", line);
        // printf("\nget line over");
    }
        //     for (int i = 0; i < 64; i++)
        // {
        //     int a = dataPoints[i].posi_ID_y;
        //     double b = dataPoints[i].weight_y;
        //     printf("%d and %f\n", a, b);
        // }
    *count = dataSize;
    printf("----------read interp table finished----------\n");
    return dataPoints;
}

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
