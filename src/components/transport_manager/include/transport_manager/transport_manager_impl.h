/**
 * \file transport_manager_impl.h
 * \brief Class transport_manager_implr header.
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

#ifndef SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_TRANSPORT_MANAGER_IMPL
#define SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_TRANSPORT_MANAGER_IMPL

#include <queue>
#include "transport_manager.h"
#include "device_adapter.h"

namespace transport_manager
{
	/**
	 * @brief Interface of transport manager.
	 * @interface TransportManager
	 **/
class TransportManagerImpl : public TransportManager
{
public:
	/**
	 * @brief provide default instance of transport manager
	 *
	 * @see @ref components_transportmanager_client_device_management
	 **/
	static TransportManagerImpl *instance(void);

	/**
	 * @brief Destructor.
	 **/
	virtual ~TransportManagerImpl(void);

	/**
	 * @brief Start scanning for new devices.
	 *
	 * @see @ref components_transportmanager_client_device_management
	 **/
	virtual void searchDevices(void) const;

	/**
	 * @brief Connect to all applications discovered on device.
	 *
	 * @param DeviceHandle Handle of device to connect to.
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	virtual void connectDevice(const SessionID session_id);

	/**
	 * @brief Disconnect from all applications connected on device.
	 *
	 * @param DeviceHandle Handle of device to disconnect from.
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	virtual void disconnectDevice(const SessionID session_id);

	/**
	 * @brief post new mesage into TM's queue
	 *
	 * @param new message container
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	virtual void postMessage(const protocol_handler::RawMessage message);

	/**
	 * @brief adds new call back function for specified event type
	 *
	 * @param event type, function address
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	virtual void addDeviceAdapterListener(DeviceAdapterListener *listener);

	/**
	 * @brief add new device adapter
	 *
	 * @param device adapter
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	virtual void addDeviceAdapter(DeviceAdapter *device_adapter);

protected:

	/**
	 * @brief type for mesage queue
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	typedef std::vector<protocol_handler::RawMessage> MessageQueue;

	/**
	 * @brief type for
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	typedef std::vector<SessionID>  SessionList;

	/**
	 * @brief type for
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	typedef struct{
		DeviceAdapter *device_adapter;
		DeviceHandle device_handle;
	} ConnectionHandle;

	/**
	 * @brief default constructor
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	TransportManagerImpl();

	/**
	 * @brief constructor used to create new TM with device adapter
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	TransportManagerImpl::TransportManagerImpl(DeviceAdapter *device_adapter);

	/**
	 * @brief constructor used to create new TM with device adapter
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	TransportManagerImpl::TransportManagerImpl(std::vector<DeviceAdapter *> device_adapter_list);

	/**
	 * @brief scan message's queue and pull messages according to priority and serial number
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 */
	static void *processQueue(void *);

	/**
	 * @brief whait until event happens
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 */
	static void *deviceListener(void *);

	/**
	 * @brief initialize TM
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 */
	void initialize(void);

	/**
	 * @brief return device adapter corresponding to defined session id
	 *
	 * @param session id
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 */
	ConnectionHandle *getConnectionHandler(SessionID session_id);


	/**
	* \brief For logging.
	*/
	static log4cxx::LoggerPtr logger_;

	/**
	 * @brief store messages
	 *
	 * @param
	 *
	 * @see @ref components_transportmanager_client_connection_management
	 **/
	MessageQueue queue_;

	/**
	 * @brief Mutex restricting access to messages.
	 **/
	mutable pthread_mutex_t queue_mutex_;

	/**
	 * @brief flag that indicates that thread must be terminated
	 **/
	mutable bool all_thread_active_;

	/**
	 * @brief Device adapters.
	 **/
	std::vector<DeviceAdapter *> device_adapters_;

	/**
	 * @brief Device adapter listener.
	 **/
	std::vector<DeviceAdapterListener *> device_adapter_listener_;

	/**
	 * @brief ID of message queue processing thread
	 **/
	pthread_t messsage_queue_thread_;

	/**
	 * @brief conditional event thread
	 **/
	pthread_t event_thread_;

	/**
	 * @brief condition variable to wake up event
	 **/
	pthread_cond_t event_thread_wakeup_;

	/**
	 * @brief Mutex restricting access to events.
	 **/
	mutable pthread_mutex_t event_thread_mutex_;
};
}

#endif