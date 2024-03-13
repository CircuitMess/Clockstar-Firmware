#include "Notif.h"
#include <unordered_map>
#include "Filepaths.hpp"
#include "Settings/Settings.h"
#include "Util/Services.h"

const char* iconPath(const Notif& notif){
	Settings* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return "";
	}

	const Theme theme = settings->get().themeData.theme;

	const std::unordered_map<std::string, const char*> appMap = {
			{ "Messenger", THEMED_FILE(Icons, AppMess, theme) },
			{ "WhatsApp",  THEMED_FILE(Icons, AppWapp, theme) },
			{ "Messages",  THEMED_FILE(Icons, AppSms, theme) },
			{ "Instagram", THEMED_FILE(Icons, AppInst, theme) },
			{ "Snapchat",  THEMED_FILE(Icons, AppSnap, theme) },
			{ "TikTok",    THEMED_FILE(Icons, AppTiktok, theme) }
	};

	const std::unordered_map<Notif::Category, const char*> catMap = {
			{ Notif::Category::Other,              THEMED_FILE(Icons, CatOther, theme) },
			{ Notif::Category::IncomingCall,       THEMED_FILE(Icons, CallIn, theme) },
			{ Notif::Category::MissedCall,         THEMED_FILE(Icons, CallMiss, theme) },
			{ Notif::Category::Voicemail,          THEMED_FILE(Icons, CatOther, theme) },
			{ Notif::Category::Social,             THEMED_FILE(Icons, CatSoc, theme) },
			{ Notif::Category::Schedule,           THEMED_FILE(Icons, CatSched, theme) },
			{ Notif::Category::Email,              THEMED_FILE(Icons, CatEmail, theme) },
			{ Notif::Category::News,               THEMED_FILE(Icons, CatNews, theme) },
			{ Notif::Category::HealthAndFitness,   THEMED_FILE(Icons, CatHealth, theme) },
			{ Notif::Category::BusinessAndFinance, THEMED_FILE(Icons, CatFin, theme) },
			{ Notif::Category::Location,           THEMED_FILE(Icons, CatLoc, theme) },
			{ Notif::Category::Entertainment,      THEMED_FILE(Icons, CatEntert, theme) },
			{ Notif::Category::OutgoingCall,       THEMED_FILE(Icons, CallOut, theme) }
	};

	auto itApp = appMap.find(notif.appID);
	if(itApp != appMap.end()){
		return itApp->second;
	}

	auto itCat = catMap.find(notif.category);
	if(itCat != catMap.end()){
		return itCat->second;
	}

	return THEMED_FILE(Icons, CatOther, theme);
}
