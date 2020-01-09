//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoHAL.h>
#include <nanoHAL_v2.h>
#include <nanoWeak.h>
#include <Target_BlockStorage_STM32FlashDriver.h>

#include <ch.h>
#include <hal.h>
#include <string.h>
#include <targetPAL.h>
#include <win_dev_i2c_native_target.h>

bool checkMac(uint8_t* buf);

// Default initialisation for Network interface config blocks
// strong implementation replacing ChibiOS 'weak' one
bool InitialiseNetworkDefaultConfig(HAL_Configuration_NetworkInterface * pconfig, uint32_t configurationIndex)
{
    (void)configurationIndex;

    // make sure the config block marker is set
    memcpy(pconfig->Marker, c_MARKER_CONFIGURATION_NETWORK_V1, sizeof(c_MARKER_CONFIGURATION_NETWORK_V1));
    
	// select DHCP mode for startup
    pconfig->InterfaceType = NetworkInterfaceType_Ethernet;
    pconfig->StartupAddressMode = AddressMode_DHCP;
    pconfig->AutomaticDNS = 1;
    pconfig->SpecificConfigId = 0;

	// read the devices MAC address from the EEPROM via I2C
	// only applicable for M4MCUv3 boards
#ifdef USE_M4MCU_V3

	// ------- init i2c first --------
	
	NF_PAL_I2C* palI2c = NULL;
	
	if(I2C1_PAL.Driver == NULL)
	{
		ConfigPins_I2C1();

		I2C1_PAL.Driver = &I2CD1;
		palI2c = &I2C1_PAL;
	}
	I2CConfig* conf = new I2CConfig;
	conf->op_mode = OPMODE_I2C;
	conf->clock_speed = 100000U;
	conf->duty_cycle = STD_DUTY_CYCLE;
	palI2c->Configuration = *conf;
	palI2c->ByteTime = 0.1;
	
	// --------------------------------

	msg_t transactionResult = MSG_OK;

	uint8_t writeBuffer = 0xfa; // address of Microchip-EEPROM where the MAC address is stored (0xFA)
	uint8_t readBuffer[6] = {0x0};
	uint8_t writeSize = 1;
	uint8_t readSize = 6;

	palI2c->WriteSize = writeSize;
	palI2c->ReadSize = readSize;
	palI2c->WriteBuffer = &writeBuffer;
	palI2c->ReadBuffer = readBuffer;

	palI2c->Address = 0x50; // slave address is 80 (0x50)
	palI2c->Driver->addr = palI2c->Address;

	// because the bus access is shared, acquire the appropriate bus
	i2cAcquireBus(palI2c->Driver);
	i2cStart(palI2c->Driver, &palI2c->Configuration);

	// this is a Write/Read transaction
	transactionResult = i2cMasterTransmitTimeout(palI2c->Driver, palI2c->Address, palI2c->WriteBuffer, palI2c->WriteSize, palI2c->ReadBuffer, palI2c->ReadSize, TIME_MS2I(20));

	i2cReleaseBus(palI2c->Driver);
	i2cStop(palI2c->Driver);

	// check if the read buffer contains a valid MAC address
	if (!checkMac(palI2c->ReadBuffer))
	{
		// MAC address invalid, so we have to use the Atmel-EEPROM instead of the Microchip EEPROM and restart the read process
		writeBuffer = 0x9A; // address of Atmel-EEPROM where the MAC address is stored (0x9A)
		i2cAcquireBus(palI2c->Driver);
		i2cStart(palI2c->Driver, &palI2c->Configuration);

		// this is a Write/Read transaction
		transactionResult = i2cMasterTransmitTimeout(palI2c->Driver, palI2c->Address, palI2c->WriteBuffer, palI2c->WriteSize, palI2c->ReadBuffer, palI2c->ReadSize, TIME_MS2I(20));

		i2cReleaseBus(palI2c->Driver);
		i2cStop(palI2c->Driver);

		// check if the read buffer now contains a valid MAC address
		if (!checkMac(palI2c->ReadBuffer))
		{
			// something went wrong... use default MAC
			pconfig->MacAddress[0] = 0x00;
			pconfig->MacAddress[1] = 0x80;
			pconfig->MacAddress[2] = 0xE1;
			pconfig->MacAddress[3] = 0x01;
			pconfig->MacAddress[4] = 0x35;
			pconfig->MacAddress[5] = 0xD1;
		}

		return true;
		
	}
	
	(void)transactionResult;

	// set the MAC address obtained from the EEPROM
	pconfig->MacAddress[0] = readBuffer[0];
    pconfig->MacAddress[1] = readBuffer[1];
    pconfig->MacAddress[2] = readBuffer[2];
    pconfig->MacAddress[3] = readBuffer[3];
    pconfig->MacAddress[4] = readBuffer[4];
    pconfig->MacAddress[5] = readBuffer[5];

#else

    // set MAC address with ST provided MAC for development boards
    // 00:80:E1:01:35:D1
    pconfig->MacAddress[0] = 0x00;
    pconfig->MacAddress[1] = 0x80;
    pconfig->MacAddress[2] = 0xE1;
    pconfig->MacAddress[3] = 0x01;
    pconfig->MacAddress[4] = 0x35;
    pconfig->MacAddress[5] = 0xD1;

#endif

    return true;
}


bool checkMac(uint8_t* buf)
{
	uint8_t mac[6];
	for (int i = 0; i < 6; i++)
	{
		mac[i] = *(buf + i);
	}
	// check if the 3 first bytes are equal
	for (int i = 1; i < 4; i++)
	{
		if (mac[i] == mac[i - 1]) return false;
	}
	return true;
}
