//Yunshi Lu
// yxl161630
// CS3377.501
#include <iostream>
#include <stdint.h>

using namespace std;

// header function
class BinaryFileHeader
{
	public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;
};
