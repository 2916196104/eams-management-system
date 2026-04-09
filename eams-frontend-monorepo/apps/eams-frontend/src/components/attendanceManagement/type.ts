export default interface ActionItem {
	label: string;
	type?: "primary" | "success" | "default" | "warning" | "danger";
	onClick: (rows: any[]) => void;
}
