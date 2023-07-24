#ifndef CLOCKSTAR_FIRMWARE_BANGLE_H
#define CLOCKSTAR_FIRMWARE_BANGLE_H

#include "Notifs/NotifSource.h"
#include "BLE/Server.h"
#include "BLE/UART.h"
#include <map>

class Bangle : public NotifSource, private Threaded {
public:
	Bangle(BLE::Server* server);
	virtual ~Bangle();

	void actionPos(uint32_t uid) override;
	void actionNeg(uint32_t uid) override;

	void findPhoneStart();
	void findPhoneStop();

private:
	BLE::Server* server;
	BLE::UART uart;

	void loop() override;

	void handleCommand(const std::string& line);

	// command handlers
	void handle_isGpsActive();
	void handle_find(bool on);
	void handle_notify(const std::string& prop);
	void handle_notifyDel(uint32_t id);
	void handle_call(const std::string& line);

	static std::string getProperty(const std::string& line, std::string prop);

	enum class CallState : uint8_t {
		None, Incoming, Outgoing, IncomingAccepted, IncomingMissed
	};
	enum class CallCmd : uint8_t {
		Outgoing, End, Incoming, Start, Invalid, Any
	};

	struct CallInfo {
		const char* message;
		Notif::Category category;
	};

	static const std::map<std::pair<CallState, CallCmd>, CallState> CallTransitions;
	static const std::unordered_map<CallState, CallInfo> CallInfoMap;

	uint32_t currentCallId = -1;
	CallState currentCallState = CallState::None;

	std::unordered_set<uint32_t> missedCalls;

	float timeOffset = 0;
	uint64_t timeUnix = 0;

	void setTime();

	bool connected = false;
	void onConnect();
	void onDisconnect();

};


#endif //CLOCKSTAR_FIRMWARE_BANGLE_H
