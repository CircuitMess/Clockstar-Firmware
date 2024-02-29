#include "Notif.h"
#include <unordered_map>
#include "Filepaths.hpp"

static const std::unordered_map<std::string, const char*> appMap = {
		{ "Messenger", File::Icons::Default::AppMess },
		{ "WhatsApp",  File::Icons::Default::AppWapp },
		{ "Messages",  File::Icons::Default::AppSms },
		{ "Instagram", File::Icons::Default::AppInst },
		{ "Snapchat",  File::Icons::Default::AppSnap },
		{ "TikTok",    File::Icons::Default::AppTiktok }
};

static const std::unordered_map<Notif::Category, const char*> catMap = {
		{ Notif::Category::Other,              File::Icons::Default::CatOther },
		{ Notif::Category::IncomingCall,       File::Icons::Default::CallIn },
		{ Notif::Category::MissedCall,         File::Icons::Default::CallMiss },
		{ Notif::Category::Voicemail,          File::Icons::Default::CatOther },
		{ Notif::Category::Social,             File::Icons::Default::CatSoc },
		{ Notif::Category::Schedule,           File::Icons::Default::CatSched },
		{ Notif::Category::Email,              File::Icons::Default::CatEmail },
		{ Notif::Category::News,               File::Icons::Default::CatNews },
		{ Notif::Category::HealthAndFitness,   File::Icons::Default::CatHealth },
		{ Notif::Category::BusinessAndFinance, File::Icons::Default::CatFin },
		{ Notif::Category::Location,           File::Icons::Default::CatLoc },
		{ Notif::Category::Entertainment,      File::Icons::Default::CatEntert },
		{ Notif::Category::OutgoingCall,       File::Icons::Default::CallOut }
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

	return File::Icons::Default::CatOther;
}
