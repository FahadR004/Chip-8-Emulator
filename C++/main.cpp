#include <cstdint>
#include <fstream>

const unsigned int START_ADDRESS = 0x200;

class Chip8 {
    Chip8();
    public: 
        uint8_t registers[16]{};
        uint8_t memory[4096]{};
        uint16_t index{};
        uint16_t pc{};
        uint16_t stack[16];
        uint8_t sp{};
        uint8_t delayTimer{};
        uint8_t soundTimer{};
        uint8_t keypad[16]{};
        uint32_t video[64*32];
        uint16_t opcode;
    
        void Chip8::LoadROM(char const* filename); 
};

Chip8::Chip8() {
    pc = START_ADDRESS;
}

void Chip8::LoadROM(char const* filename) {
    // Open the file as a stream of binary and move the file pointer to the end
    // file is a variable/object with type/class as std::ifstream and the () is the constructor of the class
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    // std::ios::binary means read the file as raw bytes
    // std::ios::ate = 'at the end' => Move the read position to the end immediately which will help us tell how big the file is 
    // '|' is the bitwise OR operator combining two open-mode flags. Each flag has certain bits set and with the OR operator, you combine them to say that you want to open the file in binary and place the read position at the end of the file

    if (file.is_open()) {
        // .tellg() returns current read position, essentially the telling the file size in bytes
        std::streampos size = file.tellg(); 
        char * buffer = new char[size]; // temp storage; remember char is 1 byte

        file.seekg(0, std::ios::beg); // move read position back to the beginning of file
        file.read(buffer,size); // read size bytes from the file into buffer meaning you have the read this much data (in bytes) from the file
        file.close(); // Not necessary as ifstream destructor will close it

        // The loop writes data starting from 0x200 or 512 address from the buffer into the memory
        for (long i = 0; i < size; ++i) {
            memory[START_ADDRESS + i] = buffer[i];
        }

        // Free temporary heap buffer
        delete[] buffer;
    }
}


