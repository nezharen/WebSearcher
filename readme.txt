The WebSearcher Program
Author: Zhang Kai, School of Software, Tsinghua University

This program was written in Ubuntu 12.04 LTS but can be compiled and excuted in all systems with C++ compiler and linker.
This text introduces you how to compile and excute this WebSearcher program.


For Linux/Mac:

1.Compile
Open the terminal and enter the following shells:
# cd /src
# g++ -o WebSearcher main.cpp CharString.h CharString.cpp Stack.h LinkedList.h WordDic.h WordDic.cpp WebSearcher.h WebSearcher.cpp
If your system has not installed g++ then please excute:
# sudo apt-get update
# sudo apt-get install g++

2.Excute
Copy the dictionary "UTF-8.dic" and "ANSI.dic" to the "src" directory. Then open the terminal and enter the following shells:
# cd /src
# ./WebSearcher
Enter the full filename of the HTML file. The program will analyze this file and save the results to "WebSearcher.txt".


For Windows:
1.Compile
Open the terminal and enter the following shells:
# cd /src
# g++ -o WebSearcher.exe main.cpp CharString.h CharString.cpp Stack.h LinkedList.h WordDic.h WordDic.cpp WebSearcher.h WebSearcher.cpp
If your system has not installed g++ you can download and use MinGW.

2.Excute
Copy the dictionary "UTF-8.dic" and "ANSI.dic" to the "src" directory. Then open the terminal and enter the following shells:
# cd /src
# WebSearcher.exe
Enter the full filename of the HTML file. The program will analyze this file and save the results to "WebSearcher.txt".


For IDE
You can use IDE to compile and run this program. For example, you can use Visual Studio to create a new project, and copy the codes in the "src" directory to the project directory, then add them to your project. So you can compile this program in your VS. Then you can copy the dictionary file to the project directory and follow the front steps to excute this program.
