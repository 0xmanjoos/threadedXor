#include <bits/stdc++.h>
#include <unistd.h> // for sleep

// compile: g++ xor.cpp -pthread
// ld dumdum linker

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::thread;
using std::vector;

char key[] = {'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F'};

void xorEncrypt(string input) {
    string temp = input;
    for (int i = 0; i < input.size(); i++)
        temp[i] = input[i] ^ key[i % (sizeof(key) / sizeof(key[0]))];
    cout<< temp<<"\n";
    // flushing takes too long
}

void threadXor(const char* arr[], int th) {
    vector<thread> t;
    for (int a=1; a<th ; a++) {
        t.push_back(thread(xorEncrypt, arr[a]));
    }
    for (auto &th : t) {
        th.join();
    }
}

void normalXor(const char* arr[], int iter) {
    for(int e=1; e<iter; e++) {
        xorEncrypt(arr[e]);
    }
}
int main(int argc, const char * argv[]) {
    if(argc<=1) {
        cout<<"Usage: " << argv[0] << " <string> <string> <etc..>";
    } else {
        // timer for threaded
        cout<<"Threaded XOR: \n";
        auto start=std::chrono::high_resolution_clock::now();

        threadXor(argv, argc);

        // get the speed of the binary
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<<"Milliseconds: "<<duration.count()<<endl; // flush
        sleep(1);

        // timer for normal
        cout<<"Normal XOR: \n";
        auto start2=std::chrono::high_resolution_clock::now();

        normalXor(argv, argc);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto duration2=std::chrono::duration_cast<std::chrono::microseconds>(stop2-start2);
        cout<<"Milliseconds: "<<duration2.count()<<endl;
    }
    return 0;
}
