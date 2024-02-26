#include "Notif.h"
#include <unordered_map>

static const std::unordered_map<std::string, const char*> appMap = {
		{ "Messenger", "S:/default/icon/app_mess.bin" },
		{ "WhatsApp",  "S:/default/icon/app_wapp.bin" },
		{ "Messages",  "S:/default/icon/app_sms.bin" },
		{ "Instagram", "S:/default/icon/app_inst.bin" },
		{ "Snapchat",  "S:/default/icon/app_snap.bin" },
		{ "TikTok",    "S:/default/icon/app_tiktok.bin" }
};

static const std::unordered_map<Notif::Category, const char*> catMap = {
		{ Notif::Category::Other,              "S:/default/icon/cat_other.bin" },
		{ Notif::Category::IncomingCall,       "S:/default/icon/call_in.bin" },
		{ Notif::Category::MissedCall,         "S:/default/icon/call_miss.bin" },
		{ Notif::Category::Voicemail,          "S:/default/icon/cat_other.bin" },
		{ Notif::Category::Social,             "S:/default/icon/cat_soc.bin" },
		{ Notif::Category::Schedule,           "S:/default/icon/cat_sched.bin" },
		{ Notif::Category::Email,              "S:/default/icon/cat_email.bin" },
		{ Notif::Category::News,               "S:/default/icon/cat_news.bin" },
		{ Notif::Category::HealthAndFitness,   "S:/default/icon/cat_health.bin" },
		{ Notif::Category::BusinessAndFinance, "S:/default/icon/cat_fin.bin" },
		{ Notif::Category::Location,           "S:/default/icon/cat_loc.bin" },
		{ Notif::Category::Entertainment,      "S:/default/icon/cat_entert.bin" },
		{ Notif::Category::OutgoingCall,       "S:/default/icon/call_out.bin" }
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
