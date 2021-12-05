#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <complex>
#include <numbers>

void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}

void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}
int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                            std::move(accumulate_promise));

    // future::get() will wait until the future has a valid result and retrieves it.
    // Calling wait() before get() is not needed
    //accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion

    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
    std::cout << "Някакъв текст !" << std::endl;
    std::cout << "Kofti rabota : ne se pishe na kirilica ..." << std::endl;
    std::vector<std::string> myStringVector {"Branimir"};
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    std::cout << "Hello, World !" << std::endl;
    std::cout << "Some tests !" << std::endl;
    std::cout << "I tuk malko printowe .. " << std::endl;

    using namespace std::complex_literals;
    std::cout << std::fixed << std::setprecision(1);

    std::complex<double> z1 = 1i * 1i;     // imaginary unit squared
    std::cout << "i * i = " << z1 << '\n';

    std::complex<double> z2 = std::pow(1i, 2); // imaginary unit squared
    std::cout << "pow(i, 2) = " << z2 << '\n';

    const double PI = std::numbers::pi; //std::acos(-1); // or std::numbers::pi in C++20
    std::complex<double> z3 = std::exp(1i * PI); // Euler's formula
    std::cout << "exp(i * pi) = " << z3 << '\n';

    std::complex<double> z4 = 1. + 2i, z5 = 1. - 2i; // conjugates
    std::cout << "(1+2i)*(1-2i) = " << z4*z5 << '\n';

    double pi=std::numbers::pi;

    std::cout << pi << std::endl;
    std::cout << "И със Cygwin се пише на кирилица ! 😍" << std::endl;

}