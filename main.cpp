#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <vector>

typedef struct DataPoint {
    int posi_ID_x;
    int posi_ID_y;
    double mean_x;
    double mean_y;
    double weight_x;
    double weight_y;
}DataPoint;

std::vector<DataPoint> dataPoints;
int read_table()
{                                                                            
   std::ifstream file("output.txt");  // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1;
    }

    // std::vector<DataPoint> dataPoints;
    std::string line;

    while (std::getline(file, line)) {
                                            
        std::istringstream iss(line);   // 使用字符串流来解析每行内容                                       
        DataPoint dp;                   // 创建一个临时的 DataPoint 结构体

        char delim;                     // 解析每个键值对
        iss >> delim >> dp.posi_ID_x >> delim >> delim >> dp.posi_ID_y 
            >> delim >> delim >> dp.mean_x >> delim >> delim >> dp.mean_y
            >> delim >> delim >> dp.weight_x >> delim >> delim >> dp.weight_y;

        dataPoints.push_back(dp);       // 将解析后的结构体添加到数组中
        }

        // for (const auto& dp : dataPoints) {
        // std::cout << "posi_ID_x: " << dp.posi_ID_x << ", posi_ID_y: " << dp.posi_ID_y
        //           << ", mean_x: " << dp.mean_x << ", mean_y: " << dp.mean_y
        //           << ", weight_x: " << dp.weight_x << ", weight_y: " << dp.weight_y << std::endl;
    // }
    file.close();
    return 0;
}

int Interp_coords(const std::vector<DataPoint>& dataPoints)
{
    for (const auto& dp : dataPoints) {             // 处理每个 DataPoint 元素
        // std::cout << "posi_ID_x: " << dp.posi_ID_x << ", posi_ID_y: " << dp.posi_ID_y
        //           << ", mean_x: " << dp.mean_x << ", mean_y: " << dp.mean_y
        //           << ", weight_x: " << dp.weight_x << ", weight_y: " << dp.weight_y << std::endl;
        // int A;
        auto&A = dp.posi_ID_x;
        auto&B = dp.posi_ID_y;
    }
    printf("!!!!!!!!!!!!!!!!!!!!zhang");
    return 0;
} 



int main()
{    
    read_table();
    Interp_coords(dataPoints);
    printf("end coding zhang");
    return 0;
}
