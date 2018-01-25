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
#include <chrono>
#include <thread>
#include <vector>
#include <array>
#include <algorithm>

#include <gmp.h>

#include "prime_numbers.hpp"
#include "trial_division.hpp"
#include "miller_rabin.hpp"

int main(int argc, char **argv)
{
    if(argc<2)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t" << argv[0] << " input_file_name repetitions" << std::endl;
        return 1;
    }

    std::string file_name=argv[1];
    std::ifstream file(file_name);
    if(!file.is_open())
    {
        std::cout << "Can't open input file!" << std::endl;
        return 1;
    }
    unsigned int nproc=std::thread::hardware_concurrency();
    std::cout << "Processors: " << nproc << std::endl;

    unsigned int num_lines=countLines(file);
    std::cout << "Lines: " << num_lines << std::endl;
    file.close();

    unsigned int job_div=jobDiv(nproc, num_lines);
    std::cout << "Job div: " << job_div << std::endl;

    std::array<std::chrono::duration<double>, 3> algorithm;

    for(unsigned int alg=0; alg<3; alg++)
    {
        std::cout << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Testing algorithm: " << alg+1 << std::endl;
        std::cout << "--------------------------------------" << std::endl;
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

            threads[i] = std::thread(thread, file_name, alg, begin, end, std::ref(threads_time));
        }
        std::for_each(threads.begin(), threads.end(), [](std::thread& x) { x.join(); } );

        std::cout << "Execution time: " << std::endl;
        std::chrono::duration<double> sum;
        for(unsigned int i=0; i<nproc; i++)
        {
            std::cout << "\tThread " << i+1 << ": " << threads_time[i].count() << std::endl;
            sum += threads_time[i];
        }
        algorithm[alg] += sum;
        std::cout << "\tSum: " << sum.count() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Result " << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    for(unsigned int i=0; i<3; i++)
    {
        std::cout << "Algorithm " << i+1 << " have a time: " << algorithm[i].count() << std::endl;
    }

    return 0;
}

unsigned int countLines(std::ifstream &file)
{
    file.clear();
    file.seekg(0, std::ios::beg);

    unsigned int num_lines=0;
    std::string s;
    while(std::getline(file, s))
    {
        ++num_lines;
    }
    return num_lines;
}

unsigned int jobDiv(const int &nproc, const int &num_lines)
{
    unsigned int job_div=0;
    if(nproc>1)
    {
        job_div=num_lines/nproc;
    }
    return job_div;
}

void thread(const std::string &file_name, const unsigned int &algorithm, const unsigned int &begin, const unsigned int &end, std::vector<std::chrono::duration<double>>& ret)
{
    std::cout << "Create new thread id = " << std::this_thread::get_id() << " Range: " << begin << " : " << end << std::endl;

    std::ifstream file(file_name);
    file.clear();
    file.seekg(0, std::ios::beg);
    unsigned int i=0;
    bool clock_started=false;
    auto clock_start=std::chrono::system_clock::now();
    auto clock_end=std::chrono::system_clock::now();

    mpz_t n;
    mpz_init(n);

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
            int status;
            switch(algorithm)
            {
                case 0:
                    status=trialDivision(std::stoll(s));
                    if(status)
                    {
                        std::cout << "\ttrialDivision: " << std::stoll(s) << " is " << status << std::endl;
                    }
                    break;

                case 1:
                    status=Miller(std::stoll(s), 50);
                    if(status)
                    {
                        std::cout << "\tMiller: " << std::stoll(s) << " is " << status << std::endl;
                    }
                    break;

                case 2:
                    // 2 - n is definitely prime
                    // 1 - n is probably prime (without being certain)
                    // 0 - n is definitly composite. There should be it.
                    mpz_set_ui(n,std::stol(s)); // only long :(
                    status=mpz_probab_prime_p(n, 50);
                    if(status)
                    {
                        std::cout << "\tmpz_probab_prime_p: " << std::stoll(s) << " is " << status << std::endl;
                    }
                    break;
            }
            if(i==end)
            {
                clock_end = std::chrono::system_clock::now();
            }
        }
    }
    std::chrono::duration<double> elapsed_seconds = clock_end-clock_start;
    ret.push_back(elapsed_seconds); 
    mpz_clear(n);
    file.close();
}