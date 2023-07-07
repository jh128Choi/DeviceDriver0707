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

class ApplicationFixture : public testing::Test
{
public:
	ApplicationFixture()
	{
		driver = new DeviceDriver(&flashMock);
		app = new Application(driver);
	}
	FlashMemoryDeviceMock flashMock;
	DeviceDriver* driver;
	Application* app;
};

TEST_F(ApplicationFixture, WriteAll) {
	for (int i = 0; i < 5; ++i)
	{
		EXPECT_CALL(flashMock, write(i, 'C'))
			.Times(1);
	}

	app->WriteAll('C');
}

TEST_F(ApplicationFixture, ReadAndPrint) {
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

	app->ReadAndPrint(0, 4);
}
