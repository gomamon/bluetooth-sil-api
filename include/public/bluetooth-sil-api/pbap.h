// Copyright (c) 2015-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef BLUETOOTH_SIL_PBAP_H_
#define BLUETOOTH_SIL_PBAP_H_

#ifndef BLUETOOTH_SIL_H_
	#error This header file should only be included by bluetooth-sil-api.h
#endif

const std::string BLUETOOTH_PROFILE_ID_PBAP = "PBAP";

typedef uint64_t BluetoothPbapAccessRequestId;
const BluetoothPbapAccessRequestId BLUETOOTH_PBAP_ACCESS_REQUEST_ID_INVALID = 0;

/**
 * @brief This interface is the base to implement an observer for the PBAP profile.
 */
class BluetoothPbapStatusObserver
{
public:
	/**
	 * @brief The method is called when the device has to display a request for PBAP access confirmation
	 *        dialog for a specific device. The user has to confirm that the acception or
	 *        rejection the same on both devices.
	 *
	 * @param accessRequestId Id of the incoming access request
	 * @param address Address of the device
	 * @param deviceName deviceName of the device
	*/
	virtual void accessRequested(BluetoothPbapAccessRequestId accessRequestId, const std::string &address,
	        const std::string &deviceName) { }
};

/**
 * @brief Interface to abstract the operations for the PBAP bluetooth profile.
 */
class BluetoothPbapProfile
{
public:
	BluetoothPbapProfile() { }

	virtual ~BluetoothPbapProfile() { }

	/**
	 * @brief Register a observer for the PBAP profile. The observer will be notified about
	 *        results from requested operations or any events.
	 *
	 * @param observer Observer instance to register.
	 */
	void registerObserver(BluetoothPbapStatusObserver *observer)
	{
		this->observer = observer;
	}

	/**
	 * @brief Accept the PBAP access request with a remote device or reject the request. Should
	 *        be only called after the SIL asked for it by calling the displayAccessRequest
	 *        method of the registered observer which is the BluetoothPbapStatusObserver class.
	 *        The displayAccessRequest is the signal of phonebook access.
	 *
	 *        This method is only for the service side of PBAP to support incoming requests.
	 *
	 * @param accessRequestId Id of the access request
	 * @param accept True to accept the PBAP access request or False to reject.
	 * @param callback Callback function which is called when the operation is done or
	 *        has failed.
	 */
	virtual void supplyAccessConfirmation(BluetoothPbapAccessRequestId accessRequestId, bool accept, BluetoothResultCallback callback) = 0;

protected:
	/**
	 * @brief Retrieve the PBAP status observer
	 *
	 *        If no observer was registered with registerObserver before a NULL object
	 *        instance will be returned which is usable but will doing nothing when
	 *        called.
	 *
	 * @return The PBAP status observer
	 */
	BluetoothPbapStatusObserver *getPbapObserver()
	{
		static BluetoothPbapStatusObserver nullObserver;

		if (!observer)
			return &nullObserver;

		return observer;
	}

private:
	BluetoothPbapStatusObserver *observer;

};

#endif //BLUETOOTH_SIL_PBAP_H_
