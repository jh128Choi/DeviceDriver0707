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



TEST(DeviceDriver, ReadFailException) {
	FlashMemoryDeviceMock flashMock;
	long address = 0x1000;

	EXPECT_CALL(flashMock, read(address))
		.WillOnce(Return('B'))
		.WillRepeatedly(Return('A'));

	DeviceDriver driver(&flashMock);

	EXPECT_THROW(driver.read(address), ReadFailException);
}
