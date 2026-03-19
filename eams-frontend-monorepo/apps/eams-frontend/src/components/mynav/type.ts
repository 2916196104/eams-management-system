export interface EamsNavMenuItem {
	id: string | number
	text: string
	icon?: string
	path?: string
	href?: string
	disabled?: boolean
	children?: EamsNavMenuItem[]
}

export interface EamsNavProps {
	menus: EamsNavMenuItem[]
	appName?: string
	logoSrc?: string
	userText?: string
	collapse?: boolean
	defaultActive?: string
	menuWidth?: string
	headerHeight?: string
	showHome?: boolean
	homeText?: string
	homePath?: string
	homeIcon?: string
	defaultIcon?: string
	backgroundColor?: string
	textColor?: string
	activeTextColor?: string
	uniqueOpened?: boolean
	router?: boolean
	collapseTransition?: boolean
}
