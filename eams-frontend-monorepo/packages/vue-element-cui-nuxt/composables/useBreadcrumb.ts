interface BreadcrumbItem {
	title: string;
	href: string;
}

export function useBreadcrumb(url: string): BreadcrumbItem[] {
	const { navigation } = useContent();

	const breadcrumbItems: BreadcrumbItem[] = [];
	const segments = url.split(/[/#]/g).filter((segment) => segment !== "");

	let href = "";
	let nav = navigation.value;

	if (!nav) {
		return [];
	}

	for (const rawSegment of segments) {
		const segment = rawSegment.replace(".html", "");
		href += `/${segment}`;

		const page = nav.find((item) => item._path === href);
		nav = page?.children ?? [];
		breadcrumbItems.push({ title: page?.title ?? segment, href });
	}

	return breadcrumbItems;
}
