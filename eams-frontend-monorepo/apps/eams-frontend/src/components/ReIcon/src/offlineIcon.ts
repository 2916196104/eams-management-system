import type { App, Component } from "vue";
import { markRaw } from "vue";
import EpArrowDownBold from "~icons/ep/arrow-down-bold";
import EpArrowUpBold from "~icons/ep/arrow-up-bold";
import EpBack from "~icons/ep/back";
import EpCalendar from "~icons/ep/calendar";
import EpCheck from "~icons/ep/check";
import EpClose from "~icons/ep/close";
import EpCloseBold from "~icons/ep/close-bold";
import EpDelete from "~icons/ep/delete";
import EpDownload from "~icons/ep/download";
import EpEdit from "~icons/ep/edit";
import EpEditPen from "~icons/ep/edit-pen";
import EpExpand from "~icons/ep/expand";
import EpFinished from "~icons/ep/finished";
import EpFold from "~icons/ep/fold";
import EpFullScreen from "~icons/ep/full-screen";
import EpHomeFilled from "~icons/ep/home-filled";
import EpList from "~icons/ep/list";
import EpMenu from "~icons/ep/menu";
import EpMessage from "~icons/ep/message";
import EpMinus from "~icons/ep/minus";
import EpMore from "~icons/ep/more";
import EpMoreFilled from "~icons/ep/more-filled";
import EpOpen from "~icons/ep/open";
import EpOperation from "~icons/ep/operation";
import EpPlus from "~icons/ep/plus";
import EpPrinter from "~icons/ep/printer";
import EpRefresh from "~icons/ep/refresh";
import EpRefreshRight from "~icons/ep/refresh-right";
import EpSearch from "~icons/ep/search";
import EpSetting from "~icons/ep/setting";
import EpTickets from "~icons/ep/tickets";
import EpUploadFilled from "~icons/ep/upload-filled";
import EpUser from "~icons/ep/user";
import EpVideoPause from "~icons/ep/video-pause";
import EpVideoPlay from "~icons/ep/video-play";
import RiApps2Line from "~icons/ri/apps-2-line";
import RiBookOpenLine from "~icons/ri/book-open-line";
import RiBuilding2Line from "~icons/ri/building-2-line";
import RiComputerLine from "~icons/ri/computer-line";
import RiDatabase2Line from "~icons/ri/database-2-line";
import RiMailLine from "~icons/ri/mail-line";
import RiShoppingBag3Line from "~icons/ri/shopping-bag-3-line";
import RiWallet3Line from "~icons/ri/wallet-3-line";

const offlineIcons = {
	"ep/arrow-down-bold": markRaw(EpArrowDownBold),
	"ep/arrow-up-bold": markRaw(EpArrowUpBold),
	"ep/back": markRaw(EpBack),
	"ep/calendar": markRaw(EpCalendar),
	"ep/check": markRaw(EpCheck),
	"ep/close": markRaw(EpClose),
	"ep/close-bold": markRaw(EpCloseBold),
	"ep/delete": markRaw(EpDelete),
	"ep/download": markRaw(EpDownload),
	"ep/edit": markRaw(EpEdit),
	"ep/edit-pen": markRaw(EpEditPen),
	"ep/expand": markRaw(EpExpand),
	"ep/finished": markRaw(EpFinished),
	"ep/fold": markRaw(EpFold),
	"ep/full-screen": markRaw(EpFullScreen),
	"ep/home-filled": markRaw(EpHomeFilled),
	"ep/list": markRaw(EpList),
	"ep/menu": markRaw(EpMenu),
	"ep/message": markRaw(EpMessage),
	"ep/minus": markRaw(EpMinus),
	"ep/more": markRaw(EpMore),
	"ep/more-filled": markRaw(EpMoreFilled),
	"ep/open": markRaw(EpOpen),
	"ep/operation": markRaw(EpOperation),
	"ep/plus": markRaw(EpPlus),
	"ep/printer": markRaw(EpPrinter),
	"ep/refresh": markRaw(EpRefresh),
	"ep/refresh-right": markRaw(EpRefreshRight),
	"ep/search": markRaw(EpSearch),
	"ep/setting": markRaw(EpSetting),
	"ep/tickets": markRaw(EpTickets),
	"ep/upload-filled": markRaw(EpUploadFilled),
	"ep/user": markRaw(EpUser),
	"ep/video-pause": markRaw(EpVideoPause),
	"ep/video-play": markRaw(EpVideoPlay),
	// 后台一级菜单会直接消费这些图标键，必须在这里注册，否则菜单配置里写了图标名也不会显示。
	"ri/apps-2-line": markRaw(RiApps2Line),
	"ri/book-open-line": markRaw(RiBookOpenLine),
	"ri/building-2-line": markRaw(RiBuilding2Line),
	"ri/computer-line": markRaw(RiComputerLine),
	"ri/database-2-line": markRaw(RiDatabase2Line),
	"ri/mail-line": markRaw(RiMailLine),
	"ri/shopping-bag-3-line": markRaw(RiShoppingBag3Line),
	"ri/wallet-3-line": markRaw(RiWallet3Line),
} satisfies Record<string, Component>;

const aliasIcons = {
	IconArrowDownBold: offlineIcons["ep/arrow-down-bold"],
	IconArrowUpBold: offlineIcons["ep/arrow-up-bold"],
	IconBack: offlineIcons["ep/back"],
	IconCheck: offlineIcons["ep/check"],
	IconClose: offlineIcons["ep/close"],
	IconCloseBlod: offlineIcons["ep/close-bold"],
	IconDelete: offlineIcons["ep/delete"],
	IconDownload: offlineIcons["ep/download"],
	IconEdit: offlineIcons["ep/edit"],
	IconExpand: offlineIcons["ep/expand"],
	IconFinished: offlineIcons["ep/finished"],
	IconFold: offlineIcons["ep/fold"],
	IconFullScreen: offlineIcons["ep/full-screen"],
	IconHomeFilled: offlineIcons["ep/home-filled"],
	IconMenu: offlineIcons["ep/menu"],
	IconMessage: offlineIcons["ep/message"],
	IconMinus: offlineIcons["ep/minus"],
	IconMore: offlineIcons["ep/more"],
	IconMoreFilled: offlineIcons["ep/more-filled"],
	IconOperation: offlineIcons["ep/operation"],
	IconPlus: offlineIcons["ep/plus"],
	IconReset: offlineIcons["ep/refresh-right"],
	IconSearch: offlineIcons["ep/search"],
	IconSetting: offlineIcons["ep/setting"],
	IconTickets: offlineIcons["ep/tickets"],
	IconUpload: offlineIcons["ep/upload-filled"],
	IconUser: offlineIcons["ep/user"],
} satisfies Record<string, Component>;

function normalizeOfflineIconName(icon: string): string {
	return icon.replace(/:/g, "/").trim();
}

export function resolveOfflineIcon(icon: string): Component | undefined {
	if (icon in aliasIcons) {
		return aliasIcons[icon as keyof typeof aliasIcons];
	}

	return offlineIcons[normalizeOfflineIconName(icon) as keyof typeof offlineIcons];
}

export function registerOfflineIcons(app: App) {
	for (const [name, component] of Object.entries(aliasIcons)) {
		app.component(name, component);
	}
}
