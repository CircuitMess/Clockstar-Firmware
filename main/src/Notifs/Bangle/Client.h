#ifndef CLOCKSTAR_FIRMWARE_CLIENT_H
#define CLOCKSTAR_FIRMWARE_CLIENT_H

#include "Notifs/NotifSource.h"
#include "BLE/Server.h"
#include "BLE/UART.h"

namespace Bangle {

class Client : public NotifSource, private Threaded {
public:
	Client(BLE::Server* server);
	virtual ~Client();

	void actionPos(uint32_t uid) override;
	void actionNeg(uint32_t uid) override;

private:
	BLE::UART uart;

	void loop() override;

	// command handlers
	void handle_isGpsActive();

};

}


#endif //CLOCKSTAR_FIRMWARE_CLIENT_H
