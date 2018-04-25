#include <iostream>
#include <stdint.h>

using namespace std;

class BinaryFileHeader
{
	public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;
};
