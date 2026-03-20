import type { Component } from "vue";

export interface EamsNavSubItem {
	key: string;
	label: string;
	path: string;
}

export interface EamsNavItem {
	key: string;
	label: string;
	icon?: string | Component;
	path?: string;
	children?: EamsNavSubItem[];
}
