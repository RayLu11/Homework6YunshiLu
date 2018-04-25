// Yunshi Lu
// yxl161630
// CS3377.501
const int maxRecordStringLength = 25;
#include <stdint.h>

class BinaryFileRecord
{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];

};
