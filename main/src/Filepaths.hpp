#ifndef ARTEMIS_FIRMWARE_FILEPATHS_HPP
#define ARTEMIS_FIRMWARE_FILEPATHS_HPP

namespace File {
	[[maybe_unused]] constexpr const char* BackgroundBottom = "S:/bg_bot.bin";
	[[maybe_unused]] constexpr const char* Background = "S:/bg.bin";
	[[maybe_unused]] constexpr const char* ModalBackground = "S:/ModalBg.bin";

	namespace Theremin {
		[[maybe_unused]] constexpr const char* Dot = "S:/theremin/dot.bin";
		[[maybe_unused]] constexpr const char* Down = "S:/theremin/down.bin";
		[[maybe_unused]] constexpr const char* HorizontalBar = "S:/theremin/horizontalBar.bin";
		[[maybe_unused]] constexpr const char* VerticalBar = "S:/theremin/verticalBar.bin";
		[[maybe_unused]] constexpr const char* Left = "S:/theremin/left.bin";
		[[maybe_unused]] constexpr const char* Right = "S:/theremin/right.bin";
		[[maybe_unused]] constexpr const char* Up = "S:/theremin/up.bin";
	}

	namespace Level {
		[[maybe_unused]] constexpr const char* Background = "S:/level/bg.bin";
		[[maybe_unused]] constexpr const char* BubbleCenter = "S:/level/bubbleCenter.bin";
		[[maybe_unused]] constexpr const char* BubbleHorizontal = "S:/level/bubbleHorizontal.bin";
		[[maybe_unused]] constexpr const char* BubbleVertical = "S:/level/bubbleVertical.bin";
		[[maybe_unused]] constexpr const char* MarkingsCenter = "S:/level/markingsCenter.bin";
		[[maybe_unused]] constexpr const char* MarkingsHorizontal = "S:/level/markingsHorizontal.bin";
		[[maybe_unused]] constexpr const char* MarkingsVertical = "S:/level/markingsVertical.bin";
	}

	namespace Intro {
		[[maybe_unused]] constexpr const char* Artemis = "S:/intro/artemis.bin";
		[[maybe_unused]] constexpr const char* BlackBackground = "S:/intro/blackBg.bin";
		[[maybe_unused]] constexpr const char* CircuitMess = "S:/intro/cm.bin";
		[[maybe_unused]] constexpr const char* GeekClub = "S:/intro/geek.bin";
		[[maybe_unused]] constexpr const char* OrangeBackground = "S:/intro/orangeBg.bin";
		[[maybe_unused]] constexpr const char* Space = "S:/intro/space.bin";
	}

	namespace LockScreen {
		namespace Default {
			[[maybe_unused]] constexpr const char* Background = "S:/default/lock_screen/bg.bin";
		}

		namespace Theme1 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme1/lock_screen/bg.bin";
		}

		namespace Theme2 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme2/lock_screen/bg.bin";
		}

		namespace Theme3 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme3/lock_screen/bg.bin";
		}

		namespace Theme4 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme4/lock_screen/bg.bin";
		}

		namespace Theme5 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme5/lock_screen/bg.bin";
		}

		namespace Theme6 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme6/lock_screen/bg.bin";
		}

		namespace Theme7 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme7/lock_screen/bg.bin";
		}

		namespace Theme8 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme8/lock_screen/bg.bin";
		}

		namespace Theme9 {
			[[maybe_unused]] constexpr const char* Background = "S:/theme9/lock_screen/bg.bin";
		}
	}

	namespace Clock {
		namespace Default {
			[[maybe_unused]] constexpr const char* Num0 = "S:/default/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/default/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/default/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/default/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/default/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/default/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/default/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/default/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/default/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/default/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/default/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/default/clock/space.bin";
		}

		namespace Theme1 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme1/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme1/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme1/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme1/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme1/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme1/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme1/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme1/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme1/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme1/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme1/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme1/clock/space.bin";
		}

		namespace Theme2 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme2/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme2/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme2/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme2/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme2/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme2/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme2/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme2/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme2/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme2/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme2/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme2/clock/space.bin";
		}

		namespace Theme3 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme3/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme3/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme3/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme3/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme3/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme3/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme3/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme3/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme3/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme3/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme3/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme3/clock/space.bin";
		}

		namespace Theme4 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme4/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme4/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme4/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme4/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme4/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme4/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme4/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme4/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme4/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme4/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme4/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme4/clock/space.bin";
		}

		namespace Theme5 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme5/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme5/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme5/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme5/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme5/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme5/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme5/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme5/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme5/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme5/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme5/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme5/clock/space.bin";
		}

		namespace Theme6 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme6/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme6/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme6/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme6/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme6/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme6/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme6/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme6/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme6/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme6/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme6/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme6/clock/space.bin";
		}

		namespace Theme7 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme7/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme7/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme7/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme7/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme7/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme7/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme7/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme7/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme7/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme7/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme7/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme7/clock/space.bin";
		}

		namespace Theme8 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme8/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme8/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme8/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme8/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme8/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme8/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme8/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme8/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme8/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme8/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme8/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme8/clock/space.bin";
		}

		namespace Theme9 {
			[[maybe_unused]] constexpr const char* Num0 = "S:/theme9/clock/0.bin";
			[[maybe_unused]] constexpr const char* Num1 = "S:/theme9/clock/1.bin";
			[[maybe_unused]] constexpr const char* Num2 = "S:/theme9/clock/2.bin";
			[[maybe_unused]] constexpr const char* Num3 = "S:/theme9/clock/3.bin";
			[[maybe_unused]] constexpr const char* Num4 = "S:/theme9/clock/4.bin";
			[[maybe_unused]] constexpr const char* Num5 = "S:/theme9/clock/5.bin";
			[[maybe_unused]] constexpr const char* Num6 = "S:/theme9/clock/6.bin";
			[[maybe_unused]] constexpr const char* Num7 = "S:/theme9/clock/7.bin";
			[[maybe_unused]] constexpr const char* Num8 = "S:/theme9/clock/8.bin";
			[[maybe_unused]] constexpr const char* Num9 = "S:/theme9/clock/9.bin";
			[[maybe_unused]] constexpr const char* Colon = "S:/theme9/clock/colon.bin";
			[[maybe_unused]] constexpr const char* Space = "S:/theme9/clock/space.bin";
		}
	}

	namespace Icons {
		namespace Default {
			[[maybe_unused]] constexpr const char* AppInst = "S:/default/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/default/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/default/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/default/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/default/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/default/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/default/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/default/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/default/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/default/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/default/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/default/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/default/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/default/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/default/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/default/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/default/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/default/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/default/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/default/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/default/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/default/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/default/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/default/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/default/icon/trash_sel.bin";
		}

		namespace Theme1 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme1/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme1/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme1/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme1/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme1/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme1/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme1/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme1/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme1/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme1/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme1/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme1/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme1/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme1/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme1/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme1/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme1/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme1/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme1/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme1/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme1/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme1/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme1/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme1/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme1/icon/trash_sel.bin";
		}

		namespace Theme2 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme2/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme2/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme2/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme2/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme2/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme2/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme2/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme2/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme2/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme2/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme2/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme2/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme2/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme2/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme2/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme2/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme2/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme2/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme2/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme2/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme2/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme2/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme2/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme2/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme2/icon/trash_sel.bin";
		}

		namespace Theme3 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme3/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme3/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme3/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme3/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme3/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme3/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme3/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme3/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme3/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme3/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme3/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme3/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme3/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme3/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme3/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme3/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme3/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme3/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme3/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme3/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme3/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme3/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme3/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme3/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme3/icon/trash_sel.bin";
		}

		namespace Theme4 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme4/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme4/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme4/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme4/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme4/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme4/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme4/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme4/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme4/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme4/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme4/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme4/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme4/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme4/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme4/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme4/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme4/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme4/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme4/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme4/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme4/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme4/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme4/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme4/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme4/icon/trash_sel.bin";
		}

		namespace Theme5 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme5/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme5/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme5/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme5/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme5/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme5/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme5/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme5/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme5/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme5/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme5/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme5/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme5/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme5/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme5/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme5/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme5/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme5/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme5/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme5/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme5/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme5/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme5/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme5/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme5/icon/trash_sel.bin";
		}

		namespace Theme6 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme6/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme6/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme6/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme6/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme6/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme6/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme6/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme6/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme6/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme6/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme6/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme6/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme6/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme6/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme6/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme6/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme6/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme6/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme6/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme6/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme6/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme6/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme6/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme6/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme6/icon/trash_sel.bin";
		}

		namespace Theme7 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme7/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme7/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme7/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme7/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme7/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme7/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme7/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme7/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme7/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme7/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme7/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme7/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme7/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme7/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme7/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme7/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme7/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme7/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme7/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme7/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme7/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme7/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme7/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme7/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme7/icon/trash_sel.bin";
		}

		namespace Theme8 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme8/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme8/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme8/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme8/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme8/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme8/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme8/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme8/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme8/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme8/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme8/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme8/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme8/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme8/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme8/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme8/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme8/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme8/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme8/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme8/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme8/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme8/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme8/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme8/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme8/icon/trash_sel.bin";
		}

		namespace Theme9 {
			[[maybe_unused]] constexpr const char* AppInst = "S:/theme9/icon/app_inst.bin";
			[[maybe_unused]] constexpr const char* AppMess = "S:/theme9/icon/app_mess.bin";
			[[maybe_unused]] constexpr const char* AppSms = "S:/theme9/icon/app_sms.bin";
			[[maybe_unused]] constexpr const char* AppSnap = "S:/theme9/icon/app_snap.bin";
			[[maybe_unused]] constexpr const char* AppTiktok = "S:/theme9/icon/app_tiktok.bin";
			[[maybe_unused]] constexpr const char* AppWapp = "S:/theme9/icon/app_wapp.bin";
			[[maybe_unused]] constexpr const char* Back = "S:/theme9/icon/back.bin";
			[[maybe_unused]] constexpr const char* BackSel = "S:/theme9/icon/back_sel.bin";
			[[maybe_unused]] constexpr const char* CallIn = "S:/theme9/icon/call_in.bin";
			[[maybe_unused]] constexpr const char* CallMiss = "S:/theme9/icon/call_miss.bin";
			[[maybe_unused]] constexpr const char* CallOut = "S:/theme9/icon/call_out.bin";
			[[maybe_unused]] constexpr const char* CatEmail = "S:/theme9/icon/cat_email.bin";
			[[maybe_unused]] constexpr const char* CatEntert = "S:/theme9/icon/cat_entert.bin";
			[[maybe_unused]] constexpr const char* CatFin = "S:/theme9/icon/cat_fin.bin";
			[[maybe_unused]] constexpr const char* CatHealth = "S:/theme9/icon/cat_health.bin";
			[[maybe_unused]] constexpr const char* CatLoc = "S:/theme9/icon/cat_loc.bin";
			[[maybe_unused]] constexpr const char* CatNews = "S:/theme9/icon/cat_news.bin";
			[[maybe_unused]] constexpr const char* CatOther = "S:/theme9/icon/cat_other.bin";
			[[maybe_unused]] constexpr const char* CatSched = "S:/theme9/icon/cat_sched.bin";
			[[maybe_unused]] constexpr const char* CatSoc = "S:/theme9/icon/cat_soc.bin";
			[[maybe_unused]] constexpr const char* Etc = "S:/theme9/icon/etc.bin";
			[[maybe_unused]] constexpr const char* LockClosed = "S:/theme9/icon/lock_closed.bin";
			[[maybe_unused]] constexpr const char* LockOpen = "S:/theme9/icon/lock_open.bin";
			[[maybe_unused]] constexpr const char* Trash = "S:/theme9/icon/trash.bin";
			[[maybe_unused]] constexpr const char* TrashSel = "S:/theme9/icon/trash_sel.bin";
		}
	}

	namespace Menu {
		namespace Default {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/default/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/default/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/default/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/default/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/default/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/default/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/default/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/default/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/default/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/default/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/default/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/default/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/default/menu/theremin.bin";
		}

		namespace Theme1 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme1/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme1/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme1/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme1/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme1/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme1/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme1/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme1/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme1/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme1/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme1/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme1/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme1/menu/theremin.bin";
		}

		namespace Theme2 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme2/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme2/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme2/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme2/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme2/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme2/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme2/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme2/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme2/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme2/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme2/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme2/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme2/menu/theremin.bin";
		}

		namespace Theme3 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme3/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme3/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme3/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme3/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme3/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme3/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme3/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme3/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme3/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme3/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme3/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme3/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme3/menu/theremin.bin";
		}

		namespace Theme4 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme4/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme4/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme4/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme4/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme4/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme4/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme4/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme4/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme4/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme4/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme4/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme4/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme4/menu/theremin.bin";
		}

		namespace Theme5 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme5/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme5/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme5/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme5/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme5/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme5/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme5/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme5/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme5/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme5/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme5/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme5/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme5/menu/theremin.bin";
		}

		namespace Theme6 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme6/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme6/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme6/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme6/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme6/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme6/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme6/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme6/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme6/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme6/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme6/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme6/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme6/menu/theremin.bin";
		}

		namespace Theme7 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme7/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme7/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme7/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme7/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme7/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme7/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme7/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme7/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme7/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme7/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme7/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme7/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme7/menu/theremin.bin";
		}

		namespace Theme8 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme8/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme8/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme8/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme8/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme8/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme8/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme8/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme8/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme8/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme8/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme8/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme8/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme8/menu/theremin.bin";
		}

		namespace Theme9 {
			[[maybe_unused]] constexpr const char* BatteryEmpty = "S:/theme9/menu/batteryEmpty.bin";
			[[maybe_unused]] constexpr const char* BatteryFull = "S:/theme9/menu/batteryFull.bin";
			[[maybe_unused]] constexpr const char* BatteryLow = "S:/theme9/menu/batteryLow.bin";
			[[maybe_unused]] constexpr const char* BatteryMid = "S:/theme9/menu/batteryMid.bin";
			[[maybe_unused]] constexpr const char* BigLowBattery = "S:/theme9/menu/bigLowBattery.bin";
			[[maybe_unused]] constexpr const char* Phone = "S:/theme9/menu/phone.bin";
			[[maybe_unused]] constexpr const char* PhoneDisconnected = "S:/theme9/menu/phoneDc.bin";
			[[maybe_unused]] constexpr const char* Background = "S:/theme9/menu/bg.bin";
			[[maybe_unused]] constexpr const char* Connection = "S:/theme9/menu/connection.bin";
			[[maybe_unused]] constexpr const char* Find = "S:/theme9/menu/find.bin";
			[[maybe_unused]] constexpr const char* Level = "S:/theme9/menu/level.bin";
			[[maybe_unused]] constexpr const char* Settings = "S:/theme9/menu/settings.bin";
			[[maybe_unused]] constexpr const char* Theremin = "S:/theme9/menu/theremin.bin";
		}
	}
}

#define THEMED_FILE(Category, Filename, theme) 									\
	theme == Theme::Default ? File::Category::Default::Filename : 				\
	theme == Theme::Theme1 ? File::Category::Theme1::Filename : 				\
	theme == Theme::Theme2 ? File::Category::Theme2::Filename : 				\
	theme == Theme::Theme3 ? File::Category::Theme3::Filename : 				\
	theme == Theme::Theme4 ? File::Category::Theme4::Filename : 				\
	theme == Theme::Theme5 ? File::Category::Theme5::Filename : 				\
	theme == Theme::Theme6 ? File::Category::Theme6::Filename : 				\
	theme == Theme::Theme7 ? File::Category::Theme7::Filename : 				\
	theme == Theme::Theme8 ? File::Category::Theme8::Filename : 				\
	theme == Theme::Theme9 ? File::Category::Theme9::Filename : ""				\

#endif //ARTEMIS_FIRMWARE_FILEPATHS_HPP
