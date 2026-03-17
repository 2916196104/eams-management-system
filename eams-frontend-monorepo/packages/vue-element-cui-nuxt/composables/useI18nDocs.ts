import type { NavItem } from "@ztl-uwu/nuxt-content";
import type { SearchResult } from "minisearch";

export function useI18nDocs() {
	const { navigation, next, prev } = useContent();
	const locale = computed(() => "zh-CN");
	const locales = computed(() => [{ code: "zh-CN", name: "简体中文" }]);
	const availableLocales = computed(() => ["zh-CN"]);
	const defaultLocale = "zh-CN";
	const otherLocales = computed((): string[] => []);

	return {
		i18nEnabled: false,
		locale,
		locales,
		defaultLocale,
		availableLocales,
		otherLocales,
		navigation: computed(() => navigation.value as NavItem[]),
		prev,
		next,
		localePath: (path: string) => path,
		localizeSearchResult: (result: SearchResult[]) => result,
		switchLocalePath: () => useRoute().path,
	};
}
