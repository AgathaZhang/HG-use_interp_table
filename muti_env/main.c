#include "interp.h"

DataPoint dataPoints[64] = {0};

int main()

{   DataPoint* data_vector;
    // double x = 1.123 , y = 1.777; 
    double x = 0.84 , y = 2.61; // 3 6 点
    int count = 0;
    data_vector = read_calibration_table(interp_table, &count);
    data_vector[1];
    double weigh_out[2]; // 用于存储 Interp_coords 函数的输出
    Interp_coords(data_vector, count, x, y, weigh_out);
    double x_out = x * weigh_out[0];
    double y_out = y * weigh_out[1];
    printf("result x:%f y:%f\n", x_out, y_out);

    test_printf();
    return 0;
}
