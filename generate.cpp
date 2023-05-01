#include <iostream>
#include <fstream>
#include <random>

int main()
{
    const int num_points = 20; // number of points to generate
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 30.0); // range of x,y coordinates

    std::ofstream output_file("input.txt");
    output_file << num_points << std::endl;
    output_file << 2 << std::endl;
    for (int i = 0; i < num_points; ++i) {
        output_file << dis(gen) << " " << dis(gen) << std::endl;
    }
    output_file.close();

    // std::cout << "Generated " << num_points << " points in file \"points.txt\"" << std::endl;
    return 0;
}
