#include <iostream>

#include "DeviceDriver.h"

using namespace std;

class Application
{
public:
	explicit Application(DeviceDriver* driver)
		: driver(driver)
	{
	}

	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long i = startAddr; i <= endAddr; ++i)
		{
			cout << driver->read(i) << endl;
		}
	}

	void WriteAll(unsigned char value)
	{
		for (long i = 0; i <= 4; ++i)
		{
			driver->write(i, value);
		}
	}
private:
	DeviceDriver* driver;
};