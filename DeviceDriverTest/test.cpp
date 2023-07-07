#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace std;
using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverFixture : public testing::Test
{
public:
	DeviceDriverFixture()
	{
		driver = new DeviceDriver(&flashMock);
	}
	FlashMemoryDeviceMock flashMock;
	long address = 0x1000;
	DeviceDriver* driver;
};

TEST_F(DeviceDriverFixture, ReadFailException) {
	EXPECT_CALL(flashMock, read(address))
		.WillOnce(Return('B'))
		.WillRepeatedly(Return('A'));

	EXPECT_THROW(driver->read(address), ReadFailException);
}

TEST_F(DeviceDriverFixture, ReadSuccess) {
	EXPECT_CALL(flashMock, read(address))
		.WillRepeatedly(Return('A'));

	EXPECT_THAT(driver->read(address), Eq('A'));
}

TEST_F(DeviceDriverFixture, WriteSuccess) {
	unsigned char data = 'B';
	EXPECT_CALL(flashMock, read(address))
		.WillOnce(Return(0xFF));
	EXPECT_CALL(flashMock, write(address, data))
		.Times(1);

	driver->write(address, data);
}

TEST_F(DeviceDriverFixture, WriteFailException) {
	unsigned char data = 'B';
	EXPECT_CALL(flashMock, read(address))
		.WillOnce(Return('A'));
	EXPECT_CALL(flashMock, write(address, data))
		.Times(0);

	EXPECT_THROW(driver->write(address, data), WriteFailException);
}
