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

TEST(ApplicationTest, WriteAll) {
	FlashMemoryDeviceMock flashMock;
	DeviceDriver* driver = new DeviceDriver(&flashMock);
	Application app(driver);

	for (int i = 0; i < 5; ++i)
	{
		EXPECT_CALL(flashMock, write(i, 'C'))
			.Times(1);
	}

	app.WriteAll('C');
}

TEST(ApplicationTest, ReadAndPrint) {
	FlashMemoryDeviceMock flashMock;
	DeviceDriver* driver = new DeviceDriver(&flashMock);
	Application app(driver);

	EXPECT_CALL(flashMock, read(0))
		.Times(5)
		.WillRepeatedly(Return('H'));
	EXPECT_CALL(flashMock, read(1))
		.Times(5)
		.WillRepeatedly(Return('E'));
	EXPECT_CALL(flashMock, read(2))
		.Times(5)
		.WillRepeatedly(Return('L'));
	EXPECT_CALL(flashMock, read(3))
		.Times(5)
		.WillRepeatedly(Return('L'));
	EXPECT_CALL(flashMock, read(4))
		.Times(5)
		.WillRepeatedly(Return('O'));

	app.ReadAndPrint(0, 4);
}
