// Liczby pierwsze
// Napisać program który: 
// - na wejściu dostaje N liczb (czytane z pliku)  (liczby są nie większe niż  9223372036854775807
// - implementuje 3 algorytmy sprawdzanie czy liczba jest pierwsza
// - sprawdza N liczb każdym algorytmem i podaje na wyjściu czas wykonania dla każdego algorytmy (std::chrono)
// - Program ma używać wielu wątków do sprawdzania, ale nie więcej niż ilość rdzeni na używanej maszynie (jeżeli N == 4 to odpalamy 4 wątki, jeżeli N == 100, to odpalamy nproc i dzielimy zbiór liczba na odpowiednie podzbiory)
//   a) Przykładowo: nproc =2 && N = 17. Mamy tylko dwa wątki, tak więc dzielimy zbiór na dwa podzbiory - jeden o wielkości 
// - algorytmy to:
//   a) Trial division (https://en.wikipedia.org/wiki/Primality_test#Simple_methods)
//   b) Miller–Rabin
//   c) mpz_probab_prime_p (https://gmplib.org/manual/Prime-Testing-Algorithm.html)

#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <array>
#include <algorithm>

bool trialDivision(unsigned long long n)
{
    if(n<=1) return false;
    if(n==2) return true;
    for(unsigned int i=2; i<=sqrt(n); ++i)
    {
        if(n%i == 0) return false;
    }
    return true;
}

bool millerRabin(unsigned long long n)
{
    
}

void thread(unsigned int algorithm, unsigned int begin, unsigned int end, std::vector<std::chrono::duration<double>>& ret)
{
    std::cout << "\tI'm a new thread id = " << std::this_thread::get_id() << " Range: " << begin << " : " << end << std::endl;

    std::ifstream file("prime_numbers.txt");
    file.clear();
    file.seekg(0, std::ios::beg);
    unsigned int i=0;
    bool clock_started=false;
    auto clock_start=std::chrono::system_clock::now();
    auto clock_end=std::chrono::system_clock::now();
    std::string s;
    while(std::getline(file, s))
    {
        ++i;
        if(i>=begin && i<=end)
        {
            if(clock_started==false)
            {
                clock_start = std::chrono::system_clock::now();
                clock_started=true;
            }
            switch(algorithm)
            {
                case 0: trialDivision(std::stoll(s)); break;
                case 1: millerRabin(std::stoll(s)); break;
            }
            if(i==end)
            {
                clock_end = std::chrono::system_clock::now();
            }
        }
    }
    std::chrono::duration<double> elapsed_seconds = clock_end-clock_start;
    ret.push_back(elapsed_seconds);
 
    std::cout << "\tThread id = " << std::this_thread::get_id() << " elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

    file.close();
}

int main()
{
    unsigned int nproc=std::thread::hardware_concurrency(); // const size_t
    unsigned int job_div=0;

    std::cout << "Processors: " << nproc << std::endl;

    std::ifstream file("prime_numbers.txt");
    if(!file.is_open())
    {
        std::cout << "Can't open file!" << std::endl;
        return 1;
    }
    // std::cout << "--- BEGIN ---" << std::endl;
    // std::cout << file.rdbuf();
    // std::cout << "--- END ---" << std::endl;
    file.clear();
    file.seekg(0, std::ios::beg);

    unsigned int num_lines=0;
    std::string s;
    while(std::getline(file, s))
    {
        ++num_lines;
    }
    std::cout << "Lines: " << num_lines << std::endl;
    file.close();

    if(nproc>1)
    {
        job_div=num_lines/nproc;
    }
    std::cout << "Job div: " << job_div << std::endl;

    std::array<std::chrono::duration<double>, 3> algorithm;

    for(unsigned int alg=0; alg<3; alg++)
    {
        std::cout << "Testing algorithm: " << alg << std::endl;
        std::vector<std::thread> threads(nproc);
        unsigned int begin=0;
        unsigned int end=0;
        std::vector<std::chrono::duration<double>> threads_time;
        for(unsigned int i=0; i<nproc; i++)
        {
            begin=i*job_div;
            if(begin>0) begin++;
            end=(i+1)*job_div;
            if((i+1)==nproc) end=num_lines;

            threads[i] = std::thread(thread, alg, begin, end, std::ref(threads_time));
        }
        std::for_each(threads.begin(),threads.end(),[](std::thread& x){x.join();});

        std::chrono::duration<double> sum;
        for(unsigned int i=0; i<nproc; i++)
        {
            sum+=threads_time[i];
        }
        algorithm[alg] = sum;
        std::cout << "\t Sum a time: " << sum.count() << std::endl;
    }
    for(unsigned int i=0; i<3; i++)
    {
        std::cout << "Algorithm " << i << " have a time: " << algorithm[i].count() << std::endl;
    }
    

    // std::thread first (thread,5,10);
    // std::cout << first.get_id() << std::endl;
    // first.join();

    return 0;
}