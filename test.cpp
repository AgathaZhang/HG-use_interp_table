// #include <stdio.h>
// #include <stdlib.h>
// #include <iostream>
// #include <cmath>
// #include <string>
// #include <stack>
// #include <typeinfo>

// 老方法读文本--------------------------------------------
// int read_table()
// {                                                                            
//    std::ifstream file("output.txt");  // 检查文件是否成功打开
//     if (!file.is_open()) {
//         std::cerr << "Error: Unable to open file!" << std::endl;
//         return 1;
//     }

//     // std::vector<DataPoint> dataPoints;
//     std::string line;

//     while (std::getline(file, line)) {
                                            
//         std::istringstream iss(line);   // 使用字符串流来解析每行内容                                       
//         DataPoint dp;                   // 创建一个临时的 DataPoint 结构体

//         char delim;                     // 解析每个键值对
//         iss >> delim >> dp.posi_ID_x >> delim >> delim >> dp.posi_ID_y 
//             >> delim >> delim >> dp.mean_x >> delim >> delim >> dp.mean_y
//             >> delim >> delim >> dp.weight_x >> delim >> delim >> dp.weight_y;

//         dataPoints.push_back(dp);       // 将解析后的结构体添加到数组中
//         }

//         // for (const auto& dp : dataPoints) {
//         // std::cout << "posi_ID_x: " << dp.posi_ID_x << ", posi_ID_y: " << dp.posi_ID_y
//         //           << ", mean_x: " << dp.mean_x << ", mean_y: " << dp.mean_y
//         //           << ", weight_x: " << dp.weight_x << ", weight_y: " << dp.weight_y << std::endl;
//     // }
//     file.close();
//     return 0;
// }

// 老方法读文本--------------------------------------------


// int fun(void)
// {
//     static int i = 0;
//     i++;
//     printf("num%d\n", i);
//     return 0;
// } 

// int main()
// {
//     for (size_t i = 0; i < 5; i++)
//     {
//         fun();
//         printf("num%d\n", i);
//     }
    
//     fun();
//     printf("end coding zhang");
//     return 0;
// }


// #include <iostream>
// #include <sstream>
// #include <string>

// int main() {
//     std::string line = "posi_ID_x: 0, posi_ID_y: 7, mean_x: -0.098, mean_y: 2.79915, weight_x: 1.0, weight_y: 1.0005";

//     // 创建一个字符串流对象，并将字符串 line 初始化为输入流
//     std::istringstream iss(line);

//     // 定义变量来存储从字符串中提取的数据
//     int posi_ID_x, posi_ID_y;
//     double mean_x, mean_y, weight_x, weight_y;
//     char delim;

//     // 从字符串流中提取数据
//     iss >> delim >> posi_ID_x >> delim >> delim >> posi_ID_y 
//         >> delim >> delim >> mean_x >> delim >> delim >> mean_y
//         >> delim >> delim >> weight_x >> delim >> delim >> weight_y;

//     // 打印提取的数据
//     std::cout << "posi_ID_x: " << posi_ID_x << ", posi_ID_y: " << posi_ID_y
//               << ", mean_x: " << mean_x << ", mean_y: " << mean_y
//               << ", weight_x: " << weight_x << ", weight_y: " << weight_y << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <sstream>
// #include <string>

// // 定义结构体
// struct Position {
//     int posi_ID_x;
//     int posi_ID_y;
//     double mean_x;
//     double mean_y;
//     double weight_x;
//     double weight_y;
// };

// int main() {
//     // 给定的字符串
//     std::string line = "posi_ID_x: 0, posi_ID_y: 7, mean_x: -0.098, mean_y: 2.79915, weight_x: 1.0, weight_y: 1.0005";

//     // 创建一个 stringstream 对象，并将字符串传入其中
//     std::stringstream ss(line);

//     // 创建一个 Position 结构体对象
//     Position pos;

//     // 使用 stringstream 分解字符串，并将每个字段赋值给结构体的成员变量
//     char colon;
//     ss >> colon >> pos.posi_ID_x >> colon >> pos.posi_ID_y >> colon >> pos.mean_x >> colon >> pos.mean_y >> colon >> pos.weight_x >> colon >> pos.weight_y;

//     // 输出解析后的结构体成员变量值
//     std::cout << "posi_ID_x: " << pos.posi_ID_x << std::endl;
//     std::cout << "posi_ID_y: " << pos.posi_ID_y << std::endl;
//     std::cout << "mean_x: " << pos.mean_x << std::endl;
//     std::cout << "mean_y: " << pos.mean_y << std::endl;
//     std::cout << "weight_x: " << pos.weight_x << std::endl;
//     std::cout << "weight_y: " << pos.weight_y << std::endl;

//     return 0;
// }


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// 定义结构体
// struct Position {
//     int posi_ID_x;
//     int posi_ID_y;
//     long double mean_x;
//     long double mean_y;
//     long double weight_x;
//     long double weight_y;
// };

// // 分割字符串函数
// std::vector<std::string> split(const std::string& str, char delimiter) {
//     std::vector<std::string> tokens;
//     std::string token;
//     std::istringstream tokenStream(str);
//     while (std::getline(tokenStream, token, delimiter)) {
//         tokens.push_back(token);
//     }
//     return tokens;
// }

// int main() {
//     // 给定的字符串
//     std::string line = "posi_ID_x: 0, posi_ID_y: 7, mean_x: -0.098, mean_y: 2.79915, weight_x: 1.0, weight_y: 1.0005";

//     // 分割字符串为字段
//     std::vector<std::string> tokens = split(line, ',');

//     // 创建一个 Position 结构体对象
//     Position pos;

//     // 逐个字段赋值给结构体的成员变量
//     for (const auto& token : tokens) {
//         std::istringstream tokenStream(token);
//         std::string key;
//         char colon;
//         tokenStream >> key >> colon;
//         if (key == "posi_ID_x:") {
//             tokenStream >> pos.posi_ID_x;
//         } else if (key == "posi_ID_y:") {
//             tokenStream >> pos.posi_ID_y;
//         } else if (key == "mean_x:") {
//             tokenStream >> pos.mean_x;
//         } else if (key == "mean_y:") {
//             tokenStream >> pos.mean_y;
//         } else if (key == "weight_x:") {
//             tokenStream >> pos.weight_x;
//         } else if (key == "weight_y:") {
//             tokenStream >> pos.weight_y;
//         }
//     }

//     // 输出解析后的结构体成员变量值
//     std::cout << "posi_ID_x: " << pos.posi_ID_x << std::endl;
//     std::cout << "posi_ID_y: " << pos.posi_ID_y << std::endl;
//     std::cout << "mean_x: " << pos.mean_x << std::endl;
//     std::cout << "mean_y: " << pos.mean_y << std::endl;
//     std::cout << "weight_x: " << pos.weight_x << std::endl;
//     std::cout << "weight_y: " << pos.weight_y << std::endl;

//     return 0;
// }


// #include <iostream>
// #include <string>

// // 定义结构体
// struct Position {
//     int posi_ID_x;
//     int posi_ID_y;
//     double mean_x;
//     double mean_y;
//     double weight_x;
//     double weight_y;
// };

// // 函数：判断字符是否是数字
// bool isDigit(char c) {
//     return (c >= '0' && c <= '9');
// }

// int main() {
//     // 给定的字符串
//     std::string line = "posi_ID_x: 0, posi_ID_y: 7, mean_x: -0.098, mean_y: 2.79915, weight_x: 1.0, weight_y: 1.0005";

//     // 创建一个 Position 结构体对象
//     Position pos;

//     // 遍历字符串中的每个字符
//     int fieldIndex = 0;
//     bool isNegative = false;
//     bool readingNumber = false;
//     std::string currentNumber;
//     for (char c : line) {
//         // 如果是分隔符或者空格，则切换到下一个字段
//         if (c == ':' || c == ',' || c == ' ') {
//             fieldIndex++;
//             readingNumber = false;
//             currentNumber.clear();
//             continue;
//         }

//         // 如果是负号，记录下来
//         if (c == '-') {
//             isNegative = true;
//             continue;
//         }

//         // 如果是数字，则累积数字字符
//         if (isDigit(c) || c == '.') {
//             readingNumber = true;
//             currentNumber += c;
//         }

//         // 如果累积到了数字，将其转换为 double 类型并放入相应的结构体成员变量中
//         if (readingNumber && (c == ',' || c == ' ')) {
//             double number = std::stod(currentNumber);
//             if (isNegative) {
//                 number *= -1; // 如果之前遇到了负号，则将数字部分乘以 -1
//                 isNegative = false;
//             }
            
//             // 将数字放入对应的结构体成员变量中
//             switch (fieldIndex) {
//                 case 1: pos.posi_ID_x = number; break;
//                 case 2: pos.posi_ID_y = number; break;
//                 case 3: pos.mean_x = number; break;
//                 case 4: pos.mean_y = number; break;
//                 case 5: pos.weight_x = number; break;
//                 case 6: pos.weight_y = number; break;
//                 default: break;
//             }

//             currentNumber.clear();
//             readingNumber = false;
//         }
//     }

//     // 输出结构体成员变量的值
//     std::cout << "posi_ID_x: " << pos.posi_ID_x << std::endl;
//     std::cout << "posi_ID_y: " << pos.posi_ID_y << std::endl;
//     std::cout << "mean_x: " << pos.mean_x << std::endl;
//     std::cout << "mean_y: " << pos.mean_y << std::endl;
//     std::cout << "weight_x: " << pos.weight_x << std::endl;
//     std::cout << "weight_y: " << pos.weight_y << std::endl;

//     return 0;
// }

// 定义结构体
struct Position {
    int posi_ID_x;
    int posi_ID_y;
    double mean_x;
    double mean_y;
    double weight_x;
    double weight_y;
};

// 函数：判断字符是否是数字
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int main() {
    // 给定的字符串
    std::string line = "posi_ID_x: 0, posi_ID_y: 7, mean_x: -0.098, mean_y: 2.79915, weight_x: 1.0, weight_y: 1.0005";

    // 创建一个 Position 结构体对象
    Position pos;

    // 遍历字符串中的每个字符
    int fieldIndex = 0;
    bool isNegative = false;
    bool readingNumber = false;
    std::string currentNumber;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        // 如果是分隔符或者空格，则切换到下一个字段
        if (c == ':' || c == ',' || c == ' ') {
            fieldIndex++;
            readingNumber = false;
            currentNumber.clear();
            continue;
        }

        // 如果是负号，记录下来
        if (c == '-') {
            isNegative = true;
            continue;
        }

        // 如果是数字，则累积数字字符
        if (isDigit(c)) {
            readingNumber = true;
            currentNumber += c;
        }

        // 如果累积到了数字，将其转换为 double 类型并放入相应的结构体成员变量中
        if (readingNumber) {
            // 如果下一位是小数点，读取后续的5位数字
            if (i < line.size() - 1 && line[i + 1] == '.') {
                std::string floatPart;
                for (size_t j = i + 1; j < i + 6 && j < line.size(); ++j) {
                    if (isDigit(line[j])) {
                        floatPart += line[j];
                    }
                }
                double number = std::stod(currentNumber + "." + floatPart);
                if (isNegative) {
                    number *= -1; // 如果之前遇到了负号，则将数字部分乘以 -1
                    isNegative = false;
                }

                // 将数字放入对应的结构体成员变量中
                switch (fieldIndex) {
                    case 1: pos.posi_ID_x = number; break;
                    case 2: pos.posi_ID_y = number; break;
                    case 3: pos.mean_x = number; break;
                    case 4: pos.mean_y = number; break;
                    case 5: pos.weight_x = number; break;
                    case 6: pos.weight_y = number; break;
                    default: break;
                }

                currentNumber.clear();
                readingNumber = false;
                i += 5; // 跳过小数点及其后的5位数字
            } else if (i == line.size() - 1 || !isDigit(line[i + 1])) {
                double number = std::stod(currentNumber);
                if (isNegative) {
                    number *= -1; // 如果之前遇到了负号，则将数字部分乘以 -1
                    isNegative = false;
                }

                // 将数字放入对应的结构体成员变量中
                switch (fieldIndex) {
                    case 1: pos.posi_ID_x = number; break;
                    case 2: pos.posi_ID_y = number; break;
                    case 3: pos.mean_x = number; break;
                    case 4: pos.mean_y = number; break;
                    case 5: pos.weight_x = number; break;
                    case 6: pos.weight_y = number; break;
                    default: break;
                }

                currentNumber.clear();
                readingNumber = false;
            }
        }
    }

    // 输出结构体成员变量的值
    std::cout << "posi_ID_x: " << pos.posi_ID_x << std::endl;
    std::cout << "posi_ID_y: " << pos.posi_ID_y << std::endl;
    std::cout << "mean_x: " << pos.mean_x << std::endl;
    std::cout << "mean_y: " << pos.mean_y << std::endl;
    std::cout << "weight_x: " << pos.weight_x << std::endl;
    std::cout << "weight_y: " << pos.weight_y << std::endl;

    return 0;
}