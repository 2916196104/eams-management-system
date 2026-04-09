type TeacherRouteQueryValue = string | string[] | null | (string | null)[] | undefined;
type TeacherRouteQuery = Record<string, TeacherRouteQueryValue>;

type TeacherRouteLike = {
	name?: unknown;
	path?: unknown;
	query?: TeacherRouteQuery;
};

type BackTargetType = "tab" | "page";
type TeacherBackTarget = {
	name?: string;
	path?: string;
	type: BackTargetType;
	query?: Record<string, string>;
};
type TeacherBackTargetInput = {
	name?: unknown;
	path?: unknown;
	type?: unknown;
	query?: TeacherRouteQuery | Record<string, string>;
};

const TEACHER_TAB_ROUTE_NAMES = new Set(["home", "schedule", "class", "mine"]);
const TEACHER_BACK_STACK_QUERY_KEY = "__back_stack";
const MAX_TEACHER_BACK_STACK_SIZE = 8;

function readRouteStringValue(query: TeacherRouteQuery | undefined, key: string) {
	const value = query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

function isTeacherTabRouteName(name: string) {
	return TEACHER_TAB_ROUTE_NAMES.has(name);
}

function isTeacherBackInternalQueryKey(key: string) {
	return (
		key === TEACHER_BACK_STACK_QUERY_KEY ||
		key === "__back_name" ||
		key === "__back_path" ||
		key === "__back_type"
	);
}

function normalizeQueryValue(value: TeacherRouteQueryValue) {
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

function normalizeBusinessQuery(query?: TeacherRouteQuery) {
	if (!query) return undefined;

	const nextQuery = Object.entries(query).reduce<Record<string, string>>((result, [key, value]) => {
		if (isTeacherBackInternalQueryKey(key)) return result;

		const normalizedValue = normalizeQueryValue(value);
		if (!normalizedValue) return result;

		result[key] = normalizedValue;
		return result;
	}, {});

	return Object.keys(nextQuery).length ? nextQuery : undefined;
}

function normalizeBackTarget(target: TeacherBackTargetInput | null | undefined): TeacherBackTarget | null {
	const name = typeof target?.name === "string" ? target.name : "";
	const path = typeof target?.path === "string" ? target.path : "";
	const query = normalizeBusinessQuery(target?.query as TeacherRouteQuery | undefined);

	if (!name && !path) return null;

	return {
		name: name || undefined,
		path: path || undefined,
		type: target?.type === "tab" ? "tab" : "page",
		query,
	} satisfies TeacherBackTarget;
}

function buildCurrentRouteBackTarget(currentRoute: TeacherRouteLike) {
	const routeName = typeof currentRoute.name === "string" ? currentRoute.name : "";
	const routePath = typeof currentRoute.path === "string" ? currentRoute.path : "";
	const backType: BackTargetType = routeName && isTeacherTabRouteName(routeName) ? "tab" : "page";

	return normalizeBackTarget({
		name: routeName,
		path: routePath,
		type: backType,
		query: currentRoute.query,
	});
}

function serializeTeacherBackStack(backStack: TeacherBackTarget[]) {
	if (!backStack.length) return "";

	return encodeURIComponent(JSON.stringify(backStack.slice(0, MAX_TEACHER_BACK_STACK_SIZE)));
}

function buildTeacherBackQueryFromStack(backStack: TeacherBackTarget[]) {
	const legacyTarget = backStack[0];
	const query: Record<string, string | undefined> = {};
	const serializedBackStack = serializeTeacherBackStack(backStack);

	if (serializedBackStack) {
		query[TEACHER_BACK_STACK_QUERY_KEY] = serializedBackStack;
	}

	if (legacyTarget) {
		query.__back_name = legacyTarget.name || undefined;
		query.__back_path = legacyTarget.path || undefined;
		query.__back_type = legacyTarget.type;
	}

	return query;
}

function readTeacherBackStack(query?: TeacherRouteQuery) {
	const backStackValue = readRouteStringValue(query, TEACHER_BACK_STACK_QUERY_KEY);
	if (backStackValue) {
		try {
			const parsed = JSON.parse(decodeURIComponent(backStackValue));
			if (Array.isArray(parsed)) {
				return parsed
					.map((item) => normalizeBackTarget(item))
					.filter((item): item is TeacherBackTarget => Boolean(item))
					.slice(0, MAX_TEACHER_BACK_STACK_SIZE);
			}
		} catch {
			// Fallback to legacy back query fields below.
		}
	}

	const legacyTarget = normalizeBackTarget({
		name: readRouteStringValue(query, "__back_name"),
		path: readRouteStringValue(query, "__back_path"),
		type: readRouteStringValue(query, "__back_type") === "tab" ? "tab" : "page",
	});

	return legacyTarget ? [legacyTarget] : [];
}

export function withTeacherBackQuery(
	currentRoute: TeacherRouteLike,
	query: Record<string, string | number | undefined> = {},
) {
	const currentTarget = buildCurrentRouteBackTarget(currentRoute);
	const inheritedBackStack = readTeacherBackStack(currentRoute.query);
	const nextBackStack = currentTarget ? [currentTarget, ...inheritedBackStack] : inheritedBackStack;

	return {
		...query,
		...buildTeacherBackQueryFromStack(nextBackStack),
	};
}

export function hasTeacherNavigationHistory() {
	try {
		return getCurrentPages().length > 1;
	} catch {
		return false;
	}
}

export function navigateToTeacherBackTarget(router: any, query?: TeacherRouteQuery) {
	const backStack = readTeacherBackStack(query);
	const [target, ...restBackStack] = backStack;
	if (!target) return false;

	if (target.type === "tab") {
		if (target.name) {
			router.pushTab({ name: target.name });
			return true;
		}

		if (target.path) {
			uni.switchTab({ url: target.path });
			return true;
		}
	}

	const nextLocation: Record<string, any> = target.name ? { name: target.name } : { path: target.path };
	const nextQuery = {
		...(target.query || {}),
		...buildTeacherBackQueryFromStack(restBackStack),
	};
	if (Object.keys(nextQuery).length) nextLocation.query = nextQuery;

	router.replace(nextLocation);
	return true;
}
