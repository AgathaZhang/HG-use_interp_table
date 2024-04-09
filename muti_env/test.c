
// #include <stdio.h>

// int main() {
//     // 创建并初始化字符串数组
//     const char *strings[] = {
//         "这是第一个字符串",
//         "这是第二个字符串",
//         "这是第三个字符串",
//         "这是第四个字符串",
//         "这是第五个字符串"
//     };
    
//     // 计算字符串数组的元素数量
//     int num_strings = sizeof(strings) / sizeof(strings[0]);
    
//     // 使用循环依次输出字符串数组的每个元素
//     for(int i = 0; i < num_strings; ++i) {
//         printf("%s\n", strings[i]);
//     }
    
//     return 0;
// }

// #include <stdio.h>

// int main() {
//     char* interp_table[] = {
//         "posi_ID_x: 0, posi_ID_y: 0, mean_x: -0.08035, mean_y: -0.10474, weight_x: 1.0, weight_y: 1.0",
//         "posi_ID_x: 0, posi_ID_y: 1, mean_x: -0.29683, mean_y: -0.03684, weight_x: 1.0, weight_y: -10.85776",
//     };
    
//     // 计算 interp_table 的长度
//     int tableSize = sizeof(interp_table) / sizeof(interp_table[0]);
    
//     // 逐一遍历数组，并将每个元素赋值给 line
//     for(int i = 0; i < tableSize; ++i) {
//         char* line = interp_table[i];
//         printf("Line %d: %s\n", i, line);
//     }
    
//     return 0;
// }