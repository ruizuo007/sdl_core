/**
 * \file device_adapter_listener_impl.h
 * \brief DeviceAdapterImpl class header file.
 *
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_DEVICE_ADAPTER_LISTENER_IMPL
#define SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_DEVICE_ADAPTER_LISTENER_IMPL

#include "transport_manager/device_adapter_listener.h"

namespace transport_manager
{

class DeviceAdapterListenerImpl :public DeviceAdapterListener
{
public:
	virtual ~DeviceAdapterListenerImpl();

	virtual void OnSearchDeviceDone(const DeviceAdapter* device_adapter);
	virtual void OnSearchDeviceFailed(const DeviceAdapter* device_adapter, const SearchDeviceError& error);

	virtual void OnDeviceConnectDone(const DeviceAdapter* device_adapter, DeviceHandle device_handle);
	virtual void OnDeviceConnectFailed(const DeviceAdapter* device_adapter, DeviceHandle device_handle, const ConnectDeviceError& error);

	virtual void OnDeviceDisconnecteDone(const DeviceAdapter* device_adapter, DeviceHandle device_handle);
	virtual void OnDeviceDisconnecteFailed(const DeviceAdapter* device_adapter, DeviceHandle device_handle, const DisconnectDeviceError& error);

	virtual void OnDataReceiveDone(const DeviceAdapter* device_adapter, DeviceHandle device_handle, const DataContainerSptr data_container);
	virtual void OnDataReceiveFailed(const DeviceAdapter* device_adapter, DeviceHandle device_handle, const DataReceiveError& error);

	virtual void OnDataSendDone(const DeviceAdapter* device_adapter, DeviceHandle device_handle, const DataContainerSptr data_container);
	virtual void OnDataSendFailed(const DeviceAdapter* device_adapter, DeviceHandle device_handle, const DataSendError& error);

	virtual void OnCommunicationError(const DeviceAdapter* device_adapter, CommunicationError& error);

private:
	/**
	* \brief For logging.
	*/
	static log4cxx::LoggerPtr logger_;

};
} // namespace transport_manager

#endif // SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_DEVICE_ADAPTER_LISTENER_IMPL