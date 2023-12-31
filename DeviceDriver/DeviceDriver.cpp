#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	int value1 = (int)(m_hardware->read(address));
	int value2 = (int)(m_hardware->read(address));
	int value3 = (int)(m_hardware->read(address));
	int value4 = (int)(m_hardware->read(address));
	int value5 = (int)(m_hardware->read(address));
	if (value1 == value2 && value2 == value3 && value3 == value4 && value4 == value5)
	{
		return value1;
	}
	throw ReadFailException();
}

void DeviceDriver::write(long address, int data)
{
	int value = (int)(m_hardware->read(address));
	if (value == EMPTY)
	{
		m_hardware->write(address, (unsigned char)data);
		return;
	}
	throw WriteFailException();
}