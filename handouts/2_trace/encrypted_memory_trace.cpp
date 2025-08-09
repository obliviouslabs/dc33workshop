#include <bits/stdc++.h>
using namespace std;

char FLAG[128];

struct alignas(16) State {
  uint8_t flag[128];
  uint64_t zero;

  void reset() {
    memset(flag, 0, sizeof(flag));
    memcpy(flag, FLAG, 128);
    zero = 0;
  }

  void go() {
    // The initial flag:
    // std::cout << "Initial flag: " << (char*) this->flag << std::endl;
    //

    // Instead of dumping encrypted memory, we just provide the instruction
    // pointer at each step. This is similar to the information one can get from
    // sgx-step.
    int i, j, k;
    for (k = 2; k <= 128; k = 2 * k) {
      for (j = k >> 1; j > 0; j = j >> 1) {
        for (i = 0; i < 128; i++) {
          cout << k << " " << j << " " << i << ": ";
          int ij = i ^ j;
          if ((ij) > i) {
            if ((i & k) == 0 && flag[i] > flag[ij]) {
              swap(flag[i], flag[ij]);
              cout << "0 ";
            }
            if ((i & k) != 0 && flag[i] < flag[ij]) {
              swap(flag[i], flag[ij]);
              cout << "1 ";
            }
          }
          cout << endl;
        }
      }
    }
    
    for (i = 0; i < 128; i++) if (flag[i] != 0) break;
    std::cout << "Post-processed flag: " << (char*)(this->flag + i) << std::endl;
  }
};

State state;

void init() {
  // reads the flag from flag_interactive.txt
  std::ifstream flag_file("flag_trace.txt");
  if (!flag_file.is_open()) {
    std::cerr << "Error opening flag file." << std::endl;
    exit(1);
  }
  flag_file.getline(FLAG, 128);
  flag_file.close();

  state.reset();
}

int main() {
  init();

  state.go();
}