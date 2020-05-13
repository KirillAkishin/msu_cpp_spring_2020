#include <chrono>
#include <iostream>
#include <random>
#include <limits>
#include <fstream>
#include <thread>
#include <mutex>
#include <functional>
#include <string>
#include <queue>
#include <iterator>
#include <cstdio>

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {}

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};


class Uint64_order
{
private:
    size_t cnt_block = 393216;            
    std::queue<std::string> queue_parts;  

    int nom_part = 1;                     
    size_t sz = sizeof(uint64_t);

    std::mutex guard_nom_part;            
    std::mutex guard_queue_parts;         
    std::mutex guard_input;               

private:
    void sort_uint64(std::ifstream& for_sort);
    void merge_parts(std::string& p1fn, std::string& p2fn, std::string& outfn);
    void merge_array_with_part(std::unique_ptr<uint64_t[]>& dat, size_t cnt, std::string& pfn, std::string& outfn);
public:
    Uint64_order(size_t block_size = 393216) : cnt_block(block_size) {}
    ~Uint64_order() {}
    void init(size_t block_size = 393216)
    {
        cnt_block = block_size;
        nom_part = 1;
        while ( !queue_parts.empty() )
            queue_parts.pop();
    }
    std::string operator()(std::string file_for_sort = "for_sort.dat")
    {
        std::ifstream for_sort;
        for_sort.open(file_for_sort, std::ios::binary);
        if ( !for_sort ) {
            return std::string("");
        }

        std::string file_sorted = "sorted.dat";
        {
            Timer ttt;
            auto fun = [this](std::ifstream& for_sort) { this->sort_uint64(for_sort); };
            std::thread t1(std::bind(fun,std::ref(for_sort)));
            std::thread t2(std::bind(fun, std::ref(for_sort)));
            t1.join();
            t2.join();
        }

        for_sort.close();
        remove(file_sorted.c_str());
        int rc = rename(queue_parts.front().c_str(), file_sorted.c_str());
        return file_sorted;
    }

};