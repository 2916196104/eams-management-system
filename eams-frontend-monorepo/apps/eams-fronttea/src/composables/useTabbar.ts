export interface TabbarItem {
	name: string;
	value: number | null;
	active: boolean;
	title: string;
	icon: string;
	activeColor: string;
}

const tabbarItems = ref<TabbarItem[]>([
	{
		name: "home",
		value: null,
		active: true,
		title: "工作台",
		icon: "i-carbon:home",
		activeColor: "#4c7cff",
	},
	{
		name: "schedule",
		value: null,
		active: false,
		title: "课表",
		icon: "i-carbon:calendar",
		activeColor: "#20c9c3",
	},
	{
		name: "class",
		value: null,
		active: false,
		title: "班级",
		icon: "i-carbon:group",
		activeColor: "#ff7b5d",
	},
]);

export function useTabbar() {
	const tabbarList = computed(() => tabbarItems.value);

	const activeTabbar = computed(() => {
		const item = tabbarItems.value.find((item) => item.active);
		return item || tabbarItems.value[0];
	});

	const getTabbarItemValue = (name: string) => {
		const item = tabbarItems.value.find((item) => item.name === name);
		return item && item.value ? item.value : null;
	};

	const setTabbarItem = (name: string, value: number) => {
		const tabbarItem = tabbarItems.value.find((item) => item.name === name);
		if (tabbarItem) {
			tabbarItem.value = value;
		}
	};

	const setTabbarItemActive = (name: string) => {
		tabbarItems.value.forEach((item) => {
			item.active = item.name === name;
		});
	};

	return {
		tabbarList,
		activeTabbar,
		getTabbarItemValue,
		setTabbarItem,
		setTabbarItemActive,
	};
}
