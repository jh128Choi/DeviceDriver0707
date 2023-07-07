#include "DeviceDriver.h"

#include <exception>

using namespace std;

class ReadFailException : public exception
{

};

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	// TODO: implement this method properly
	int value1 = (int)(m_hardware->read(address));
	int value2 = (int)(m_hardware->read(address));
	int value3 = (int)(m_hardware->read(address));
	int value4 = (int)(m_hardware->read(address));
	int value5 = (int)(m_hardware->read(address));
	if (value1 == value2 && value2 && value3 && value3 && value4 && value4 && value5)
	{
		return 0;
	}
	throw ReadFailException();
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}