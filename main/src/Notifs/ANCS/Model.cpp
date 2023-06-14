#include "Model.h"
#include <unordered_map>
#include <cstdint>

namespace ANCS {

	// const std::unordered_set<NotificationAttributeID> AttrNeedLen = { Title, Subtitle, Message };

	static const std::unordered_map<uint16_t, const char*> ErrString = {
			{ ANCS::Error::Unknown_command,   "Unknown command" },
			{ ANCS::Error::Invalid_command,   "Invalid command" },
			{ ANCS::Error::Invalid_parameter, "Invalid parameter" },
			{ ANCS::Error::Action_failed,     "Action failed" }
	};

	static const std::unordered_map<uint8_t, const char*> EventString = {
			{ ANCS::EventID::NotificationAdded,    "New notification" },
			{ ANCS::EventID::NotificationModified, "Modified notification" },
			{ ANCS::EventID::NotificationRemoved,  "Removed notification" }
	};

	static const std::unordered_map<uint8_t, const char*> CategoryString = {
			{ ANCS::CategoryID::Other,              "Other" },
			{ ANCS::CategoryID::IncomingCall,       "IncomingCall" },
			{ ANCS::CategoryID::MissedCall,         "MissedCall" },
			{ ANCS::CategoryID::Voicemail,          "Voicemail" },
			{ ANCS::CategoryID::Social,             "Social" },
			{ ANCS::CategoryID::Schedule,           "Schedule" },
			{ ANCS::CategoryID::Email,              "Email" },
			{ ANCS::CategoryID::News,               "News" },
			{ ANCS::CategoryID::HealthAndFitness,   "HealthAndFitness" },
			{ ANCS::CategoryID::BusinessAndFinance, "BusinessAndFinance" },
			{ ANCS::CategoryID::Location,           "Location" },
			{ ANCS::CategoryID::Entertainment,      "Entertainment" }
	};
}

const char* ANCS::labelError(ANCS::Error error){
	auto label = ErrString.find(error);
	if(label == ErrString.end()) return "Unknown error";
	return label->second;
}

const char* ANCS::labelEvent(ANCS::EventID evt){
	auto label = EventString.find(evt);
	if(label == EventString.end()) return "Unknown EventID";
	return label->second;
}

const char* ANCS::labelCategory(ANCS::CategoryID cat){
	auto label = CategoryString.find(cat);
	if(label == CategoryString.end()) return "Unknown CategoryID";
	return label->second;
}
