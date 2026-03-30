import type { CourseListVO } from "@/apis/academic/type";
import type { MyTableColumn } from "@/components/mytable/type";

export type ScheduleExportColumn = Pick<MyTableColumn, "prop" | "label">;

export function getScheduleExportColumns(
	columns: ScheduleExportColumn[],
	visibleColumns: Record<string, boolean>,
): ScheduleExportColumn[] {
	return columns.filter((column) => {
		if (!column.prop || column.prop === "action") return false;
		return visibleColumns[column.prop] !== false;
	});
}

export function formatScheduleExportValue(
	row: CourseListVO,
	prop: string,
	evaluationSummary: string,
	emptyText = "-",
): string {
	if (prop === "canReserve") {
		return row.canReserve === "1" ? "是" : "否";
	}

	if (prop === "evaluationSummary") {
		return evaluationSummary || emptyText;
	}

	const value = (row as Record<string, unknown>)[prop];
	if (value === undefined || value === null || value === "") {
		return emptyText;
	}

	return String(value);
}

export function buildScheduleExportRows(
	rows: CourseListVO[],
	columns: ScheduleExportColumn[],
	resolveEvaluationSummary: (row: CourseListVO) => string,
	emptyText = "-",
): Record<string, string>[] {
	return rows.map((row) => {
		const exportRow: Record<string, string> = {};

		columns.forEach((column) => {
			const label = column.label || column.prop || "";
			const prop = column.prop || "";
			exportRow[label] = formatScheduleExportValue(row, prop, resolveEvaluationSummary(row), emptyText);
		});

		return exportRow;
	});
}

export function buildScheduleExportFilename(now = new Date()) {
	const year = now.getFullYear();
	const month = String(now.getMonth() + 1).padStart(2, "0");
	const day = String(now.getDate()).padStart(2, "0");
	const hours = String(now.getHours()).padStart(2, "0");
	const minutes = String(now.getMinutes()).padStart(2, "0");
	const seconds = String(now.getSeconds()).padStart(2, "0");

	return `课程表导出_${year}${month}${day}_${hours}${minutes}${seconds}.xlsx`;
}
