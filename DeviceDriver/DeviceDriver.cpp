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
	int value = (int)(m_hardware->read(address));
	throw ReadFailException();
	return 0;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}