/*
 *Yunshi Lu
 * yxl161630
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <bits/stdc++.h>
#include "BinaryFileHeader.cc"
#include <stdint.h>
#include "BinaryFileRecord.cc"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3","C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
   BinaryFileHeader *myRecord = new BinaryFileHeader();
   ifstream file("/scratch/perkins/cs3377.bin",ios::in | ios::binary);
   file.read((char*)myRecord, sizeof(BinaryFileHeader));
   char buffer[100];
    // magic number
   sprintf(buffer, "Magic: Ox%.8X", myRecord->magicNumber);
   setCDKMatrixCell(myMatrix, 1, 1, buffer);

   // for version
   sprintf(buffer, "Version: %u", myRecord->versionNumber);
   
   setCDKMatrixCell(myMatrix,1,2,buffer);
   //Num records
    sprintf(buffer, "NumRecords: %lu" , myRecord->numRecords);
    setCDKMatrixCell(myMatrix, 1, 3, buffer);
    // for records
    BinaryFileRecord *Record = new BinaryFileRecord();
    for(int i = 0; i < (int) myRecord->numRecords; i++)
	{
		file.read((char* ) Record, sizeof(BinaryFileRecord));
 		sprintf(buffer, "strlen: %u", Record->strLength);
		setCDKMatrixCell(myMatrix, i+2, 1, buffer);
		setCDKMatrixCell(myMatrix, i+2, 2, Record->stringBuffer);
	}

     
  drawCDKMatrix(myMatrix, true);    /* required  */
  file.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
