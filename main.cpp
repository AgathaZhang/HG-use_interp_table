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
#include <limits>
// #include <json/json.h>

// #include <E:/Project_C/json_lib/json/include/nlohmann/json.hpp>

typedef struct DataPoint
{
    int posi_ID_x = 0;
    int posi_ID_y = 0;
    double mean_x = 0.0;
    double mean_y = 0.0;
    double weight_x = 0.0;
    double weight_y = 0.0;
} DataPoint;

extern std::vector<DataPoint> dataPoints;

std::vector<DataPoint> dataPoints;

int charToInt(char c)
{
    return c - '0';
}

double charToDouble(char c)
{
    return static_cast<double>(c - '0');
}

double stringToDouble(const std::string &str)
{
    return std::stod(str);
}

double distance(double x1, double y1, double x2, double y2) {
return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));}

std::vector<DataPoint> surround_by(double x, double y, DataPoint this_point, const std::vector<DataPoint>& dataPoints)
{   
    std::vector<DataPoint> four_point;
    int vector_x = -1, vector_y = -1;
    if (x - this_point.mean_x > 0){vector_x = 1;}
    if (y - this_point.mean_y > 0){vector_y = 1;}
    for (const auto& gridPoint : dataPoints)
    {
        if (gridPoint.posi_ID_x == this_point.posi_ID_x && gridPoint.posi_ID_y == this_point.posi_ID_y)
        {
            four_point.push_back(gridPoint);
        }
        if (gridPoint.posi_ID_x == (this_point.posi_ID_x + vector_x) && gridPoint.posi_ID_y == this_point.posi_ID_y)
        {
            four_point.push_back(gridPoint);
        }
        if (gridPoint.posi_ID_x == (this_point.posi_ID_x) && gridPoint.posi_ID_y == (this_point.posi_ID_y + vector_y))
        {
            four_point.push_back(gridPoint);
        }
        if (gridPoint.posi_ID_x == (this_point.posi_ID_x + vector_x) && gridPoint.posi_ID_y == (this_point.posi_ID_y + vector_y))
        {
            four_point.push_back(gridPoint);
        }
        
    }
    if (four_point.max_size() == 4)     // TODO 这里要加入边界可能选点出错的情况处理
    return four_point;
    else printf("Matching error");

}

int read_table()
{
    std::ifstream file("interp_table.txt"); // 检查文件是否成功打开
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file!" << std::endl;
    }

    extern std::vector<DataPoint> dataPoints;
    std::string line;

    while (std::getline(file, line))
    {
        bool flag_single_read = false;
        bool is_neg = false;
        std::string temp_num;
        DataPoint dp;
        int cont = 0; // 用于计数
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == ':')
            {
                cont++;
                flag_single_read = true;
                continue;
            }
            if (cont == 1 && flag_single_read == true)
            {
                dp.posi_ID_x = charToInt(line[i]);
                flag_single_read = false;
            }
            if (cont == 2 && flag_single_read == true)
            {
                dp.posi_ID_y = charToInt(line[i]);
                flag_single_read = false;
            }

            if (cont == 3 && flag_single_read == true)
            {
                if (line[i] == '-')
                {
                    is_neg = true;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (size_t j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num += line[i + j];}
                        else break;
                    }   
                    flag_single_read = false;
                    if (is_neg == true)
                    {
                        dp.mean_x = (-1) * stringToDouble(temp_num);
                    }
                    else
                        {dp.mean_x = stringToDouble(temp_num);}
                }
                is_neg = false;
                temp_num.clear();
            }

            if (cont == 4 && flag_single_read == true)
            {
                if (line[i] == '-')
                {
                    is_neg = true;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (size_t j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num += line[i + j];}
                        else break;
                    }   
                    flag_single_read = false;
                    if (is_neg == true)
                    {
                        dp.mean_y = (-1) * stringToDouble(temp_num);
                    }
                    else
                        {dp.mean_y = stringToDouble(temp_num);}
                }
                is_neg = false;
                temp_num.clear();
            }

            if (cont == 5 && flag_single_read == true)
            {
                if (line[i] == '-')
                {
                    is_neg = true;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (size_t j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num += line[i + j];}
                        else break;
                    }
                    flag_single_read = false;
                    if (is_neg == true)
                    {
                        dp.weight_x = (-1) * stringToDouble(temp_num);
                    }
                    else
                        {dp.weight_x = stringToDouble(temp_num);}
                    
                }
                is_neg = false;
                temp_num.clear();
            }

            if (cont == 6 && flag_single_read == true)
            {
                if (line[i] == '-')
                {
                    is_neg = true;
                    continue;
                }
                if (line[i] >= '0' && line[i] <= '9')
                {
                    for (size_t j = 0; j < 10; j++)
                    {   if (line[i+j] >= '0' && line[i+j] <= '9'|| line[i+j] =='.')
                        {temp_num += line[i + j];}
                        else break;
                    }                                                           // TODO 验证这里的问题
                    flag_single_read = false;
                    if (is_neg == true)
                    {
                        dp.weight_y = (-1) * stringToDouble(temp_num);
                    }
                    else
                        {dp.weight_y = stringToDouble(temp_num);}
                }
                is_neg = false;
                temp_num.clear();
                break;
            }
        }
        dataPoints.push_back(dp);
    }

    file.close();
    return 0;
}

DataPoint find_grid_ID(double x, double y, const std::vector<DataPoint>& dataPoints)
{

    double minDistance = std::numeric_limits<double>::max();
    DataPoint nearestGridPoint;

    for (const auto& gridPoint : dataPoints) {
        double dist = distance(x, y, gridPoint.mean_x, gridPoint.mean_y);
        if (dist < minDistance) {
            minDistance = dist;
            nearestGridPoint = gridPoint;
        }
    }
    return nearestGridPoint;

}

std::vector<double> interp_1(DataPoint p1, DataPoint p2, double x, double y)
{   std::vector<double> weigh_p1(2), weigh_p2(2), weigh_ans(2);
    weigh_p1[0] = p1.weight_x;
    weigh_p1[1] = p1.weight_y;
    weigh_p2[0] = p2.weight_x;
    weigh_p2[1] = p2.weight_y;
    // weigh_ans[0] = abs((x - p1.mean_x))/abs((p1.mean_x - p2.mean_x));
    weigh_ans[0] = abs((x - p1.mean_x))/abs((p1.mean_x - p2.mean_x))*weigh_p2[0] + abs((x - p2.mean_x))/abs((p1.mean_x - p2.mean_x))*weigh_p1[0];
    weigh_ans[1] = abs((x - p1.mean_x))/abs((p1.mean_x - p2.mean_x))*weigh_p2[1] + abs((x - p2.mean_x))/abs((p1.mean_x - p2.mean_x))*weigh_p1[1];

    return weigh_ans;
}

std::vector<double> interp_2(std::vector<double> p1, std::vector<double> p2, double x, double y)
{
    std::vector<double> weigh_ans(2)
    
}


int Interp_coords(const std::vector<DataPoint> &dataPoints, double x, double y)
{

    DataPoint this_grid = find_grid_ID(x, y, dataPoints);     // 找到最近的格点 // 返回基于格点的方位向量 // 根据方位向量确定包围
    std::vector<DataPoint> four_point = surround_by(x, y, this_grid, dataPoints);

    // 判断四点的构型
    DataPoint right_down_point;     // 找到序号最小点
    int min_cooder = four_point[1].posi_ID_x + four_point[0].posi_ID_y;
    for (size_t i = 0; i < 4; i++)
    {if (four_point[i].posi_ID_x + four_point[i].posi_ID_y <= min_cooder)
            right_down_point = four_point[i];}
            
    DataPoint left_up_point, left_down_point, right_up_point;     // 左上点 右上点 左下点依次找到
    for (size_t i = 0; i < 4; i++)
    {if (four_point[i].posi_ID_x == right_down_point.posi_ID_x + 1 && four_point[i].posi_ID_y == right_down_point.posi_ID_y)
        left_down_point = four_point[i];
    if (four_point[i].posi_ID_x == right_down_point.posi_ID_x && four_point[i].posi_ID_y == right_down_point.posi_ID_y + 1)
        right_up_point = four_point[i];
    if (four_point[i].posi_ID_x == right_down_point.posi_ID_x + 1 && four_point[i].posi_ID_y == right_down_point.posi_ID_y + 1)
        left_up_point = four_point[i];}
    
    // 开始插值
    std::vector<double> r1(2), r2(2), P(2);
    r1 = interp(left_up_point, right_up_point, x, y);
    r2 = interp(left_down_point, right_down_point, x, y);
    // P = interp(left_up_point, right_up_point, x, y);        // 这里要区分插值方向，第三次是插y值



    
    

    printf("!w!!!!!!!!!!!!!!!!!!!zhang");
    return 0;
}

int main()
{   

    double x = 1.13, y = 0.91;
    extern std::vector<DataPoint> dataPoints;
    read_table();
    Interp_coords(dataPoints, x, y);
    printf("end coding zhang");
    return 0;
}
