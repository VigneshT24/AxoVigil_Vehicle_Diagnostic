#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::cout << "================================================= AxoVigil Vehical Diagnostic =================================================" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    double speed = 0;
    // in celsius (standard metric)
    double temperature = 0;

    // currently either "NORMAL" or "ABNORMAL"
    std::string status = "";

    int test_duration = 0;

    std::cout << "Enter the duration of the vehicle diagnostic test (in seconds): ";
    std::cin >> test_duration;

    std::string min_or_mins = (int(test_duration / 60) <= 1) ? " minute " : " minutes ";
    std::string sec_or_secs = (int(test_duration % 60) <= 1) ? " second " : " seconds ";

    std::cout << "The test duration: " << (test_duration / 60) << min_or_mins << "and " << (test_duration % 60) << sec_or_secs << std::endl;

    return 0;
}