#ifndef CLOCKSTAR_FIRMWARE_MODEL_H
#define CLOCKSTAR_FIRMWARE_MODEL_H

#include <unordered_set>
#include <map>
#include <string>

namespace ANCS {
	enum Error {
		Unknown_command = (0xA0), // The commandID was not recognized by the NP.
		Invalid_command = (0xA1), // The command was improperly formatted.
		Invalid_parameter = (0xA2), // One of the parameters (for example, the NotificationUID) does not refer to an existing object on the NP.
		Action_failed = (0xA3), // The action was not performed
	};

	enum CommandID {
		GetNotificationAttributes = 0,
		GetAppAttributes = 1,
		PerformNotificationAction = 2,
		// Reserved CommandID values = 3–255
	};

	enum EventID {
		NotificationAdded = 0,
		NotificationModified = 1,
		NotificationRemoved = 2,
		//Reserved EventID values = 3–255
	};

	enum AttributeID {
		AppIdentifier = 0,
		Title = 1, // (Needs to be followed by a 2-bytes max length parameter)
		Subtitle = 2, // (Needs to be followed by a 2-bytes max length parameter)
		Message = 3, // (Needs to be followed by a 2-bytes max length parameter)
		MessageSize = 4,
		Date = 5,
		PositiveActionLabel = 6,
		NegativeActionLabel = 7,
		// Reserved NotificationAttributeID values = 8–255
		COUNT
	};
	static const std::unordered_set<AttributeID> AttrNeedLen = { Title, Subtitle, Message }; // Attributes that require max length specified when requesting data

	enum ActionID {
		ActionIDPositive = 0,
		ActionIDNegative = 1,
		// Reserved ActionID values = 2–255
	};

	enum CategoryID {
		Other = 0,
		IncomingCall = 1,
		MissedCall = 2,
		Voicemail = 3,
		Social = 4,
		Schedule = 5,
		Email = 6,
		News = 7,
		HealthAndFitness = 8,
		BusinessAndFinance = 9,
		Location = 10,
		Entertainment = 11,
		// Reserved CategoryID values = 12–255
	};

	static const std::map<std::string, std::string> AppIDMap = {
			{ "com.apple.MobileSMS",      "Messages" },
			{ "com.facebook.Messenger",   "Messenger" },
			{ "net.whatsapp.WhatsApp",    "WhatsApp" },
			{ "com.burbn.instagram",      "Instagram" },
			{ "com.toyopagroup.picaboo",  "Snapchat" },
			{ "com.zhiliaoapp.musically", "TikTok" }
	};

	const char* labelError(Error error);
	const char* labelEvent(EventID evt);
	const char* labelCategory(CategoryID cat);
}

#endif //CLOCKSTAR_FIRMWARE_MODEL_H
