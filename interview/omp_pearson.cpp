#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>  // OpenMP for multi-threading
#include <stdexcept>

// Structure to hold local statistics for each thread
struct LocalStats {
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_x2 = 0.0;
    double sum_y2 = 0.0;
    size_t count = 0;
};

double parallel_correlation(const std::vector<double>& x, const std::vector<double>& y, int num_threads = 0) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("x and y must have the same length");
    }
    size_t n = x.size();
    if (n < 2) {
        return NAN;  // Insufficient data
    }

    // Set number of threads; default to max available
    if (num_threads <= 0) {
        num_threads = omp_get_max_threads();
    }
    omp_set_num_threads(num_threads);

    double total_sum_x = 0.0;
    double total_sum_y = 0.0;
    double total_sum_xy = 0.0;
    double total_sum_x2 = 0.0;
    double total_sum_y2 = 0.0;
    size_t total_count = 0;

    // Parallel computation using OpenMP reduction
    #pragma omp parallel for reduction(+:total_sum_x, total_sum_y, total_sum_xy, total_sum_x2, total_sum_y2, total_count)
    for (size_t i = 0; i < n; ++i) {
        total_sum_x += x[i];
        total_sum_y += y[i];
        total_sum_xy += x[i] * y[i];
        total_sum_x2 += x[i] * x[i];
        total_sum_y2 += y[i] * y[i];
        total_count += 1;
    }

    if (total_count != n) {
        throw std::runtime_error("Count mismatch in parallel computation");
    }

    double mean_x = total_sum_x / n;
    double mean_y = total_sum_y / n;

    // Sample covariance and variances (divide by n-1)
    double cov = (total_sum_xy - total_sum_x * total_sum_y / n) / (n - 1);
    double var_x = (total_sum_x2 - total_sum_x * total_sum_x / n) / (n - 1);
    double var_y = (total_sum_y2 - total_sum_y * total_sum_y / n) / (n - 1);

    if (var_x == 0.0 || var_y == 0.0) {
        return 0.0;  // Avoid division by zero
    }

    double corr = cov / std::sqrt(var_x * var_y);
    return corr;
}

int main() {
    // Example usage
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 4.0, 6.0, 8.0, 10.0};

    try {
        double corr = parallel_correlation(x, y);
        std::cout << "Correlation: " << corr << std::endl;  // Output: 1
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}