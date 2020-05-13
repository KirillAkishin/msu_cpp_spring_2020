#include "sort.h"

int main()
{
    std::string file_for_sort = "for_sort.dat";
    std::string sorted_file;

    size_t sz = sizeof(uint64_t);
    size_t cnt_block = 393216;
    bool create_data = true;
    if ( create_data ) {
        Timer tm; 
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint64_t> dis(0, std::numeric_limits<uint64_t>::max() / 4);
        size_t sz_sorting_data = cnt_block * 10;
        std::ofstream for_sort;
        int czap = 0;
        for_sort.open(file_for_sort, std::ios::binary); 
        for ( size_t i = 0; i < sz_sorting_data; ++i ) {
            uint64_t rnd = dis(gen);
            for_sort.write(reinterpret_cast<char*>( &rnd ), sz);
            ++czap;
        }
        for_sort.close();
    }

    {
        Uint64_order order(cnt_block);
        sorted_file = order(file_for_sort);
    }

    std::ifstream check_sort;
    check_sort.open(sorted_file, std::ios::binary);
    uint64_t uprev;
    uint64_t unext;
    bool is_correct_sorting = true;

    bool stop_read = !check_sort.read(reinterpret_cast<char*>( &uprev ), sz);

    size_t count_of_numbers = 1;
    while ( !stop_read ) {
        stop_read = !check_sort.read(reinterpret_cast<char*>( &unext ), sz);
        if ( !stop_read ) {
            ++count_of_numbers;
            if ( uprev > unext ) {
                std::cout << "EROR SORTING Pos= " << count_of_numbers << "\n";
                is_correct_sorting = false;
            }
            unext = uprev;
        }
    }
    std::cout << "Sorting is " << ( is_correct_sorting ? "correct" : "uncorrect" ) << std::endl;
}