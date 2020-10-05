cmake_minimum_required(VERSION 3.16)
project(dvir_pro)

set(CMAKE_CXX_STANDARD 14)

#add_executable(dvir_pro TrieTree.cpp)

## FOR RUNNING THE Huffman COMPRESS##
#add_executable(dvir_pro BitIoStream.hpp BitIoStream.cpp CanonicalCode.cpp CanonicalCode.hpp
 #       CodeTree.cpp CodeTree.hpp FrequencyTable.hpp FrequencyTable.cpp HuffmanCoder.cpp HuffmanCoder.hpp
  #    HuffmanCompress.cpp TrieTree.hpp TrieTree.cpp)

## FOR RUNNING THE Huffman DECOMPRESS##
add_executable(dvir_pro BitIoStream.hpp BitIoStream.cpp CanonicalCode.cpp CanonicalCode.hpp
       CodeTree.cpp CodeTree.hpp FrequencyTable.hpp FrequencyTable.cpp HuffmanCoder.cpp HuffmanCoder.hpp
 HuffmanDecompress.cpp)