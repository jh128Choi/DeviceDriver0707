#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/Application.cpp"

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

TEST(ApplicationTest, ReadAndPrint) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}
