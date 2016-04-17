/*
* The MIT License(MIT)
* Copyright(c) 2016 Lorenzo Delana, https://searchathing.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

//===========================================================================
// EXAMPLE	: ex03-arp.ino
//===========================================================================
// Setup()
//   - Resolve name.
//---------------------------------------------------------------------------
// Suggested defines for this example
//---------------------------------------------------------------------------
// SEARCHATHING_DISABLE;DPRINT_SERIAL;SERIAL_SPEED=9600;DEBUG;DEBUG_ASSERT
//

// SearchAThing.Arduino debug macro definitions
#include <SearchAThing.Arduino.Utils\DebugMacros.h>

//---------------------------------------------------------------------------
// Libraries
//---------------------------------------------------------------------------
#include <SearchAThing.Arduino.Utils\Util.h>
using namespace SearchAThing::Arduino;

//#include <SearchAThing.Arduino.Net\Protocol.h>
#include <SearchAThing.Arduino.Net\Checksum.h>
using namespace SearchAThing::Arduino::Net;

//---------------------------------------------------------------------------
// Setup
//---------------------------------------------------------------------------
void setup()
{
	byte buf[] =
	{
		0x45, 0x00, 0x00, 0x28, 0x2e, 0x27, 0x40, 0x00, 0x80, 0x06,
		0x00, 0x00, 0xc0, 0xa8, 0x00, 0x64, 0x6c, 0xa8, 0x97, 0x06
	};

	uint16_t expectedResult = 0x07ee;

	auto checksumOneCall = CheckSum(buf, sizeof(buf));

	uint16_t checksumMultiCall;
	{
		uint32_t pchksum = 0;
		pchksum = CheckSumPartial(pchksum, buf, 10);
		pchksum = CheckSumPartial(pchksum, buf + 10, 10);
		checksumMultiCall = CheckSumFinalize(pchksum);
	}

	if (checksumOneCall != expectedResult ||
		checksumOneCall != checksumMultiCall)
		DPrintln(F("* checksum failed"));
	else
		DPrintln(F("Checksum matches"));
}

//---------------------------------------------------------------------------
// Loop
//---------------------------------------------------------------------------
void loop()
{

}
