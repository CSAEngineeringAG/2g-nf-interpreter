//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------
#include "NETIF.h"
#include "NETIF_NETIF_MacAddress.h"

#include <nanoHAL.h>
#include <nanoHAL_v2.h>
#include <Target_BlockStorage_STM32FlashDriver.h>

using namespace NETIF;

bool MacAddress::NativeUpdate( CLR_RT_TypedArray_UINT8 param0, HRESULT &hr )
{
	
	(void)hr;
	
	uint8_t* targetMac = param0.GetBuffer();
	
	HAL_Configuration_NetworkInterface* networkConfig = (HAL_Configuration_NetworkInterface*)platform_malloc(sizeof(HAL_Configuration_NetworkInterface));
	bool success = false;

	success = ConfigurationManager_GetConfigurationBlock(networkConfig, DeviceConfigurationOption_Network, 0);
	
	if(!success)
	{
		return false;
	}
	
	networkConfig->MacAddress[0] = *(targetMac+0);
    networkConfig->MacAddress[1] = *(targetMac+1);
    networkConfig->MacAddress[2] = *(targetMac+2);
    networkConfig->MacAddress[3] = *(targetMac+3);
    networkConfig->MacAddress[4] = *(targetMac+4);
    networkConfig->MacAddress[5] = *(targetMac+5);
	
	success = ConfigurationManager_UpdateConfigurationBlock(networkConfig, DeviceConfigurationOption_Network, 0);

    return success;
}

