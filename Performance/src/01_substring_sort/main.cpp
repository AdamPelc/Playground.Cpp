// Substring sort
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::cout;
using std::endl;
using std::minstd_rand;
using std::unique_ptr;
using std::vector;

bool compare(const char* s1, const char* s2, unsigned int l);

int main() {
    //constexpr unsigned int L = 1 << 24, N = 1 << 20; // Use with options A, B
    constexpr unsigned int L = 1 << 18, N = 1 << 14;  // Use with option C
    //constexpr unsigned int L = 1 << 22, N = 1 << 18;  // Use with option C, takes longer
    //constexpr unsigned int L = 1 << 8, N = 1 << 3;

    //system_clock::time_point t0 = system_clock::now();
    unique_ptr<char[]> s(new char[L]);
    vector<const char*> vs(N);
    {
        minstd_rand rgen;
        using rand_t = minstd_rand::result_type;
        if(0) for (char* p = s.get(), *end = p + L; p != end; p += sizeof(rand_t)) {    // Option A
                const rand_t x = rgen();
                ::memcpy(p, &x, sizeof(x));
            }
        else if(0) for (unsigned int i = 0; i < L; ++i) {       // Option B
                s[i] = 'a' + (rgen() % ('z' - 'a' + 1));
            }
        else {    // Option C
            ::memset(s.get(), 'a', L*sizeof(char));
            for (unsigned int i = 0; i < L/1024; ++i) {
                s[rgen() % (L - 1)] = 'a' + (rgen() % ('z' - 'a' + 1));
            }
        }
        s[L-1] = 0;
        for (unsigned int i = 0; i < N; ++i) {
            vs[i] = &s[rgen() % (L - 1)];
        }
        //cout << "s=" << s.get() << endl;
        //for (unsigned int i = 0; i < N; ++i) cout << "vs[" << i << "]=" << vs[i] << endl;
    }
    system_clock::time_point t1 = system_clock::now();
    //cout << "Prep time(L=" << L << ", N=" << N << "): " << duration_cast<milliseconds>(t1 - t0).count() << "ms" << endl;


    size_t count = 0;
    std::sort(vs.begin(), vs.end(), [&](const char* a, const char* b) { ++count; return compare(a, b, L); });
    //for (unsigned int i = 0; i < N; ++i) cout << "vs[" << i << "]=" << vs[i] << endl;
    system_clock::time_point t2 = system_clock::now();
    cout << "Sort time: " << duration_cast<milliseconds>(t2 - t1).count() << "ms (" << count << " comparisons)" << endl;
}
