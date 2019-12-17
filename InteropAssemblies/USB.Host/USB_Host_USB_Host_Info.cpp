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
#include "USB_Host.h"
#include "USB_Host_USB_Host_Info.h"
#include "usbh/dev/msd.h"
#include <target_windows_storage_config.h>

using namespace USB::Host;

USBH_DEFINE_BUFFER(char str[64]);
USBHDriver * usbh = &USB_MSD_DRIVER;

bool Info::NativeIsDevicePresent( HRESULT &hr )
{
	(void)hr;
	
	if(usbh->status == USBH_STATUS_STARTED)
	{
		usbh_device_t * device = &usbh->rootport.device;
		if(device->status == USBH_DEVSTATUS_CONFIGURED){
			return true;
		}
		return false;
	}
	return false;
}

unsigned short Info::NativeGetVID( HRESULT &hr )
{
    (void)hr;
	
	if(usbh->status == USBH_STATUS_STARTED)
	{
		usbh_device_t * device = &usbh->rootport.device;
		if(device->status == USBH_DEVSTATUS_CONFIGURED){
			usbh_device_descriptor_t const * desc = &device->devDesc;
			return (unsigned short int)desc->idVendor;
		}
		return 0;
	}
	return 0;
}

unsigned short Info::NativeGetPID( HRESULT &hr )
{
    (void)hr;

	if(usbh->status == USBH_STATUS_STARTED)
	{
		usbh_device_t * device = &usbh->rootport.device;
		if(device->status == USBH_DEVSTATUS_CONFIGURED){
			usbh_device_descriptor_t const * desc = &device->devDesc;
			return (unsigned short int)desc->idProduct;
		}
		return 0;
	}
	return 0;
}

const char* Info::NativeGetSerialNumber( HRESULT &hr )
{	
	(void)hr;

	if(usbh->status == USBH_STATUS_STARTED)
	{
		usbh_device_t * device = &usbh->rootport.device;
		if(device->status == USBH_DEVSTATUS_CONFIGURED){
			usbh_device_descriptor_t const * desc = &device->devDesc;
			usbhDeviceReadString(device, str, sizeof(str), desc->iSerialNumber, device->langID0);
			return str;
		}
		return 0;
	}
	return 0;
}

const char* Info::NativeGetManufacturerString( HRESULT &hr )
{
	(void)hr;

	if(usbh->status == USBH_STATUS_STARTED)
	{
		usbh_device_t * device = &usbh->rootport.device;
		if(device->status == USBH_DEVSTATUS_CONFIGURED){
			usbh_device_descriptor_t const * desc = &device->devDesc;
			usbhDeviceReadString(device, str, sizeof(str), desc->iManufacturer, device->langID0);
			
			return str;
			}
		return 0;
	}
	return 0;
}

const char* Info::NativeGetProductString( HRESULT &hr )
{
	(void)hr;

	if(usbh->status == USBH_STATUS_STARTED)
	{
		usbh_device_t * device = &usbh->rootport.device;
		if(device->status == USBH_DEVSTATUS_CONFIGURED){
			usbh_device_descriptor_t const * desc = &device->devDesc;
			usbhDeviceReadString(device, str, sizeof(str), desc->iProduct, device->langID0);
			
			return str;
		}
		return 0;
	}
	return 0;
}

