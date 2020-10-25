<p>Final Project in Computer Science &amp; Mathematics Bc.S.</p>
<p><strong>Thesis:</strong> Today most compression algorithms that are being used to compress files have a generic algorithm that works on all types of files without addressing the unique characteristics and properties of the file type. Our research question is whether a better compression algorithm can be achieved for a specific type of file, in our case an EXE. file.</p>
<p><strong>Idea:</strong> Find patterns in EXE. files which can then be used to manipulate&nbsp;existing compressing algorithms on the files in order to achieve better compression.</p>
<p><strong>Implementation:&nbsp;</strong>Currently, the compression algorithm we used is the most popular compression algorithm - Huffman.</p>
<p><strong>Work Method:</strong></p>
<ul>
<li>Find common strings for the files and repeating strings in each file.</li>
<li>Exe. files have a high volume of null sequences (= Zeros) and thus we can use this knowledge to manipulate the compressing algorithm by reducing the representation of the sequences.</li>
<li>Modify the algorithms alphabet and add our common strings and the null sequences to the alphabet.</li>
<li>Compress/Decompress the file using the Huffman algorithm with the new alphabet.</li>
</ul>
<p><strong>Code:</strong></p>
<ul>
<li>&nbsp;<a title="TrieTree.hpp/cpp" href="FrequencyTable.cpp"><strong>TrieTree.hpp/cpp</strong> </a>- This part is in charge of the scanning of the files to find common patterns.</li>
<li><strong><a href="HuffmanCompress.cpp">HuffmanCompress.cpp</a>&nbsp;</strong>- This part is in charge of the new modified compression.</li>
<li><strong><a title="HuffmanDecompress.cpp" href="HuffmanDecompress.cpp">HuffmanDecompress.cpp</a>&nbsp;</strong>-&nbsp;This part is in charge of the new modified decompression.</li>
</ul>
<p><strong>How to use:</strong></p>
<p><strong>Results:&nbsp;</strong>Our results show an improvement of 10% on average per file, which means that knowing the type of file before using the compression algorithm can be used to manipulate the algorithm to achieve a better compression due to the use of the file type characteristics for expending and modifying the alphabet.</p>
<p>&nbsp;</p>
