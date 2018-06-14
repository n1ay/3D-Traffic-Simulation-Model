#include <ctime>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <fstream>

int main() {

	float a = 1.0;
	std::ofstream file("colors.bin", std::ios::out | std::ios::binary);

    for (int id=0; id<10000; id++) {
		srand(id);
		float r = rand()%256*1.0/255;
		srand(id+10);
		float g = rand()%256*1.0/255;
		srand(id+20);
		float b = rand()%256*1.0/255;
		
		file.write((char*)&r, sizeof(float));
		file.write((char*)&g, sizeof(float));
		file.write((char*)&b, sizeof(float));
		file.write((char*)&a, sizeof(float));
    }

    return 0;
}
