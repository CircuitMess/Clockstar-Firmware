#include "Notif.h"
#include <unordered_map>

static const std::unordered_map<std::string, const char*> appMap = {
		{ "Messenger", "S:/icon/app_mess.bin" },
		// TODO
};

static const std::unordered_map<Notif::Category, const char*> catMap = {
		{ Notif::Category::Other,              "S:/icon/cat_other.bin" },
		{ Notif::Category::MissedCall,         "S:/icon/call_miss.bin" },
		{ Notif::Category::Voicemail,          "S:/icon/cat_other.bin" },
		{ Notif::Category::Social,             "S:/icon/cat_soc.bin" },
		{ Notif::Category::Schedule,           "S:/icon/cat_sched.bin" },
		{ Notif::Category::Email,              "S:/icon/cat_email.bin" },
		{ Notif::Category::News,               "S:/icon/cat_news.bin" },
		{ Notif::Category::HealthAndFitness,   "S:/icon/cat_health.bin" },
		{ Notif::Category::BusinessAndFinance, "S:/icon/cat_fin.bin" },
		{ Notif::Category::Location,           "S:/icon/cat_loc.bin" },
		{ Notif::Category::Entertainment,      "S:/icon/cat_entert.bin" }
};

const char* iconPath(const Notif& notif){
	auto itApp = appMap.find(notif.appID);
	if(itApp != appMap.end()){
		return itApp->second;
	}

	auto itCat = catMap.find(notif.category);
	if(itCat != catMap.end()){
		return itCat->second;
	}

	return "S:/icon/cat_other.bin";
}
