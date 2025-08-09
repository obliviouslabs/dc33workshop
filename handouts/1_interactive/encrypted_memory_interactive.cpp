#include <bits/stdc++.h>
#include <openssl/aes.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

uint8_t key[16];
AES_KEY aes_key;

char FLAG[33];

void dump_buffer(uint8_t *thing, size_t length) {
  uint8_t nonce = 0;
  for (auto i=0; i<length/16; i++) {
    uint8_t output[64];
    uint8_t buffer[64];
    memcpy(buffer, thing + i*16, 16);
    for (int j = 0; j < 16; j++) {
      buffer[j] ^= nonce;
    }
    nonce++;
    
    AES_encrypt(buffer, output, &aes_key);
    // prints output in base16:
    for (int j = 0; j < 16; j++) {
      cout << std::hex << std::setw(2) << std::setfill('0') << (int)output[j];
    }
  }
  cout << std::endl;
}

struct alignas(16) State {
  uint8_t flag[32];
  bool failed;
  uint8_t input[32];

  void reset() {
    memcpy(flag, FLAG, 32);
    memset(input, 0, sizeof(input));
    failed = false;
  }

  void dump() {
    dump_buffer((uint8_t*) this, sizeof(State));
  }
  
  bool check() {
    this->dump();
    for (int i = 0; i < 32; i++) {
      if (input[i] != flag[i]) {
        this->failed = true;
      }
      this->dump();
    }
    return !this->failed;
  }
};

State state;

void init() {
  // reads the flag from flag_interactive.txt
  std::ifstream flag_file("flag_interactive.txt");
  if (!flag_file.is_open()) {
    std::cerr << "Error opening flag file." << std::endl;
    exit(1);
  }
  flag_file.getline(FLAG, sizeof(FLAG));
  flag_file.close();

  // Initialize the key with random values
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0 || read(fd, key, sizeof(key)) != sizeof(key)) {
    std::cerr << "Error reading from /dev/urandom." << std::endl;
    exit(1);
  }
  close(fd);

  AES_set_encrypt_key(key, 128, &aes_key);
  state.reset();
}

int main() {
  init();

  for (uint64_t i=0; i<9002; i++) {
    // Simulate some processing
    state.reset();
    std::cout << "input: " << std::endl;
    std::flush(std::cout);
    std::string input;
    std::cin >> input;
    for (auto i=0; i < std::min(32, static_cast<int>(input.size())); i++) {
      state.input[i] = input[i];
    }
    for (auto i=std::min(32, static_cast<int>(input.size())); i<32; i++) {
      state.input[i] = 0;
    }

    if (state.check()) {
      std::cout << "Success!" << std::endl;
      std::cout << "Flag: " << state.flag << std::endl;
      std::cout << "Input: " << state.input << std::endl;
      std::flush(std::cout);
      return 0;
      break;
    } else {
      std::cout << "Failed!" << std::endl;
      std::flush(std::cout);
    }
  }
  return 42;
}