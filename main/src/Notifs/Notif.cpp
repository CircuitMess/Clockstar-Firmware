#include "Notif.h"
#include <unordered_map>
#include "Filepaths.hpp"

static const std::unordered_map<std::string, const char*> appMap = {
		{ "Messenger", File::Icons::Theme1::AppMess },
		{ "WhatsApp",  File::Icons::Theme1::AppWapp },
		{ "Messages",  File::Icons::Theme1::AppSms },
		{ "Instagram", File::Icons::Theme1::AppInst },
		{ "Snapchat",  File::Icons::Theme1::AppSnap },
		{ "TikTok",    File::Icons::Theme1::AppTiktok }
};

static const std::unordered_map<Notif::Category, const char*> catMap = {
		{ Notif::Category::Other,              File::Icons::Theme1::CatOther },
		{ Notif::Category::IncomingCall,       File::Icons::Theme1::CallIn },
		{ Notif::Category::MissedCall,         File::Icons::Theme1::CallMiss },
		{ Notif::Category::Voicemail,          File::Icons::Theme1::CatOther },
		{ Notif::Category::Social,             File::Icons::Theme1::CatSoc },
		{ Notif::Category::Schedule,           File::Icons::Theme1::CatSched },
		{ Notif::Category::Email,              File::Icons::Theme1::CatEmail },
		{ Notif::Category::News,               File::Icons::Theme1::CatNews },
		{ Notif::Category::HealthAndFitness,   File::Icons::Theme1::CatHealth },
		{ Notif::Category::BusinessAndFinance, File::Icons::Theme1::CatFin },
		{ Notif::Category::Location,           File::Icons::Theme1::CatLoc },
		{ Notif::Category::Entertainment,      File::Icons::Theme1::CatEntert },
		{ Notif::Category::OutgoingCall,       File::Icons::Theme1::CallOut }
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

	return File::Icons::Theme1::CatOther;
}
