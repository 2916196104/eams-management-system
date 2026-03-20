// 这里导入你要使用的图标，保持原有 Element Plus 全局注册方式不变
import { Menu, Expand, Fold, HomeFilled } from "@element-plus/icons-vue";
import { Setting, Operation } from "@element-plus/icons-vue";
import { User } from "@element-plus/icons-vue";
import { Tickets } from "@element-plus/icons-vue";
import { UploadFilled, Download } from "@element-plus/icons-vue";
import { consola } from "consola";
import {
	Message,
	Plus,
	Edit,
	Delete,
	Search,
	Check,
	More,
	MoreFilled,
	Finished,
	Back,
	Close,
	CloseBold,
	FullScreen,
	Minus,
	ArrowUpBold,
	ArrowDownBold,
	RefreshRight,
} from "@element-plus/icons-vue";
import type { App } from "vue";
import { IconifyIconOffline, IconifyIconOnline } from "@/components/ReIcon";

export default {
	/**
	 * 插件安装函数
	 * @param app 应用实例
	 */
	install: (app: App) => {
		app.component("IconMenu", Menu);
		app.component("IconExpand", Expand);
		app.component("IconFold", Fold);
		app.component("IconHomeFilled", HomeFilled);
		app.component("IconSetting", Setting);
		app.component("IconOperation", Operation);
		app.component("IconUser", User);
		app.component("IconTickets", Tickets);
		app.component("IconUpload", UploadFilled);
		app.component("IconDownload", Download);

		// 表格与通用操作图标
		app.component("IconMessage", Message);
		app.component("IconPlus", Plus);
		app.component("IconEdit", Edit);
		app.component("IconDelete", Delete);
		app.component("IconSearch", Search);
		app.component("IconCheck", Check);
		app.component("IconMore", More);
		app.component("IconMoreFilled", MoreFilled);
		app.component("IconFinished", Finished);
		app.component("IconBack", Back);
		app.component("IconClose", Close);
		app.component("IconCloseBlod", CloseBold);
		app.component("IconFullScreen", FullScreen);
		app.component("IconMinus", Minus);
		app.component("IconArrowUpBold", ArrowUpBold);
		app.component("IconArrowDownBold", ArrowDownBold);
		app.component("IconReset", RefreshRight);

		// 新增 iconify 组件能力，不覆盖原有全局别名
		app.component("IconifyIconOffline", IconifyIconOffline);
		app.component("IconifyIconOnline", IconifyIconOnline);
		consola.success("[admin/icon] Element Plus global icons and Iconify components are ready");
	},
};
