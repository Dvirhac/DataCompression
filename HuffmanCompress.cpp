/* 
 * Compression application using static Huffman coding
 * 
 * Usage: HuffmanCompress InputFile OutputFile
 * Then use the corresponding "HuffmanDecompress" application to recreate the original input file.
 * Note that the application uses an alphabet of 257 symbols - 256 symbols for the byte values
 * and 1 symbol for the EOF marker. The compressed file format starts with a list of 257
 * code lengths, treated as a canonical code, and then followed by the Huffman-coded data.
 * 
 * Copyright (c) Project Nayuki
 * 
 * https://www.nayuki.io/page/reference-huffman-coding
 * https://github.com/nayuki/Reference-Huffman-coding
 */

#define NUM_OF_STRINGS 64

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "BitIoStream.hpp"
#include "CanonicalCode.hpp"
#include "FrequencyTable.hpp"
#include "HuffmanCoder.hpp"
#include "math.h"
#include "TrieTree.hpp"
#include "map"




using std::uint32_t;

std :: vector<uint32_t> breakNum(int counter){
    std :: vector<uint32_t> nums;
    while(counter != 0){
        unsigned int num = log2(counter);
        counter = counter - pow(2, num);
        nums.push_back(num);
    }
    return nums;
}


int main(int argc, char *argv[]) {
    // Handle command line arguments

    /*  if (argc != 3) {
          std::cerr << "Usage: " << argv[0] << " InputFile OutputFile" << std::endl;
          return EXIT_FAILURE;
      }
      const char *inputFile  = argv[1];
      const char *outputFile = argv[2];*/
    const char *inputFile  = "/home/dvir/CLionProjects/dvir-pro/Files/BST.out";
    const char *outputFile = "/home/dvir/CLionProjects/dvir-pro/Files/BSTCompress";

    // Read input file once to compute symbol frequencies.
    // The resulting generated code is optimal for static Huffman coding and also canonical.
    std::ifstream in(inputFile, std::ios::binary);
    FrequencyTable freqs(std::vector<uint32_t>(322+NUM_OF_STRINGS, 0)); // add 2^32 0 00 0000 00000000 ..
    uint32_t null_counter  = 0;

    //////////////////////// THIS CODE GENERATED THE strings.txt file/////////////////////////////

    /*std :: vector<Trie> topStrings = getTopString();
    std :: ofstream topString("strings.txt",ios::out);
    for (Trie const &trie : topStrings){
        topString << trie.code_word << endl;
        int sum = 0;
        for (int file: trie.files){
           sum+= file;
        }
        sum/=5;
        topString << sum << std :: endl;
    }

    topString.close();*/

    //////////////////////creation of the vector of vectors ///////////////////////////////////

    ifstream strings("/home/dvir/CLionProjects/dvir-pro/strings.txt", ios:: in|ios::binary);
    string line;
    std::vector<std::vector<uint32_t >> words_to_int;
    std :: vector<int> words_freqs;
    while (std :: getline(strings,line))
    {
        string code_word = line;
        std :: getline(strings, line);
        std :: stringstream num(line);
        int freq = 0;
        num >> freq;
        std :: vector<uint32_t> chars_as_int;
        for (const char &character : code_word){
            chars_as_int.push_back((int)character);
        }
        words_to_int.push_back(chars_as_int);
        words_freqs.push_back(freq);
    }

    /////////////////////increamanting the freqs table////////////////////////////////////////
    for (int i = 0 ; i < 64; i ++)
    {
        int freq = words_freqs[i];
        for (int j = 0 ; j < freq ; j ++){
            freqs.increment(322 + i);
        }
    }




    while (true) {
        int b = in.get();
        if (b == EOF)
            break;
        if (b < 0 || b > 255)
            throw std::logic_error("Assertion error");
        if (b == 0)
        {
            null_counter++;
        }
        else {
            if (null_counter == 0)
                freqs.increment(static_cast<uint32_t>(b));
            else if(null_counter == 1)
            {
                freqs.increment(static_cast<uint32_t>(0));
                freqs.increment(static_cast<uint32_t>(b)); //add breaking char
                null_counter = 0;
            }
            else
            {
                freqs.increment(static_cast<uint32_t>(b)); //add breaking char
                std::vector<uint32_t> log_of_num = breakNum(null_counter);
                for(const auto &i : log_of_num){
                    if(i == 0)
                        freqs.increment(static_cast<uint32_t>(0));
                    else
                        freqs.increment(static_cast<uint32_t>(256 + i));   //add null
                }
                null_counter = 0;
            }
        }
    }

    freqs.increment(256);  // EOF symbol gets a frequency of 1
    CodeTree code = freqs.buildCodeTree();
    const CanonicalCode canonCode(code, freqs.getSymbolLimit());
    // Replace code tree with canonical one. For each symbol,
    // the code value may change but the code length stays the same.
    code = canonCode.toCodeTree();

    // Read input file again, compress with Huffman coding, and write output file
    in.clear();
    in.seekg(0);
    std::ofstream out(outputFile, std::ios::binary);
    BitOutputStream bout(out);
    try {
        // Write code length table
        for (uint32_t i = 0; i < canonCode.getSymbolLimit(); i++) {
            uint32_t val = canonCode.getCodeLength(i);
            // For this file format, we only support codes up to 255 bits long
            if (val >= 256)
                throw std::domain_error("The code for a symbol is too long");
            // Write value as 8 bits in big endian
            for (int j = 7; j >= 0; j--){
                bout.write((val >> j) & 1);
                 std::cout << ((val >> j) & 1) << " ";
            }
            // std::cout << std::endl;
        }
        HuffmanEncoder enc(bout);
        enc.codeTree = &code;
        int zero_counter = 0;
        while (true) {
            // Read and encode one byte
            int symbol = in.get();
            int tmp = symbol;
            auto saved_location = in.tellg();
            if (symbol == EOF)
                break;
            if (symbol < 0 || symbol > 255)
                throw std::logic_error("Assertion error");
            if (symbol == 0)
            {
                while (symbol == 0)
                {
                    zero_counter ++;
                    saved_location = in.tellg();
                    symbol = in.get();

                }
                // reached non-zero symbol
                if(zero_counter == 1){
                    enc.write(static_cast<uint32_t >(0));
                    in.seekg(saved_location);
                   // int tmp = in.get();
                  //  cout << tmp << " ";
                }
                else
                {
                    std::vector<uint32_t> log_of_num = breakNum(zero_counter);
                    for (const auto &i : log_of_num) {
                        if(i == 0)
                            enc.write(static_cast<uint32_t >(0));
                        else
                            enc.write(static_cast<uint32_t>(256 + i));
                    }
                }
                zero_counter = 0;
                if (symbol != EOF){
                    in.seekg(saved_location);
                    //int tmp = in.get();
                   // cout << tmp << " ";
                }
                 //   enc.write(static_cast<uint32_t>(symbol));
                else if(symbol == EOF)
                    break;
            }
            else
            {
                bool find_word = false;
                std :: map<int,std :: vector<uint32_t>> index_to_vec;
                for (int i = 0 ; i < NUM_OF_STRINGS; i ++)
                {
                    index_to_vec[i] = words_to_int[i];
                }
              //  index_to_vec[0] = words_to_int[42];
                auto it = index_to_vec.begin();
                const auto end_it = index_to_vec.end();
                while (!index_to_vec.empty())
                {
                    it = index_to_vec.begin();
                    while (it != index_to_vec.end())
                    {
                        if (it->second[0] == symbol)
                        {
                            if (it->second.size() == 1){
                                // we find it
                                std :: vector<uint32_t> vect = words_to_int[it->first];
                                for (int i = 0; i < vect.size() ; i ++){
                                    std :: cout << vect[i] << " ";
                                }
                                std :: cout << "\n";
                                find_word = true;
                                break;
                            }
                            it->second.erase(it->second.begin(), it->second.begin() + 1);
                            ++it;
                        }
                        else{
                            it = index_to_vec.erase(it); // C++11: returns the next iterator

                        }
                    }
                    if (find_word)
                        break;

                    symbol = in.get();
                }

                if (index_to_vec.empty())
                {
                    enc.write(static_cast<uint32_t>(tmp));
                    in.seekg(saved_location);
                }
                else
                {
                    enc.write(static_cast<uint32_t>(322 + it->first));
                }

            }
        }


        enc.write(256);  // EOF
        bout.finish();
        return EXIT_SUCCESS;

    } catch (const char *msg) {
        std::cerr << msg << std::endl;
        return EXIT_FAILURE;
    }

    std:: cout << "here";
}