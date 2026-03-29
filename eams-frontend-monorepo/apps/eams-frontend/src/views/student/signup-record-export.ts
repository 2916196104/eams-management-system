import type { SignupRecordItemDTO } from "@/apis/student/type";
import type { MyTableColumn } from "@/components/mytable/type";

/**
 * 获取报名记录导出列（根据可见列过滤）
 */
export function getSignupRecordExportColumns(
	baseColumns: MyTableColumn[],
	visibleColumns: Record<string, boolean>,
): MyTableColumn[] {
	return baseColumns.filter((col) => visibleColumns[col.prop as keyof typeof visibleColumns] !== false);
}

/**
 * 构建报名记录导出行数据
 */
export function buildSignupRecordExportRows(
	rows: SignupRecordItemDTO[],
	visibleColumns: MyTableColumn[],
): Record<string, any>[] {
	return rows.map((row) => {
		const exportRow: Record<string, any> = {};
		visibleColumns.forEach((col) => {
			let value = (row as any)[col.prop];
			
			// 特殊字段处理
			if (col.prop === "verifyState") {
				const stateMap: Record<number, string> = {
					0: "待审核",
					1: "已通过",
					2: "已拒绝",
				};
				value = stateMap[value] || "未知";
			} else if (col.prop === "addTime") {
				// 格式化时间，去掉秒
				if (value) {
					value = value.substring(0, 16);
				}
			} else if (col.prop === "amount") {
				// 金额保留两位小数
				value = Number(value).toFixed(2);
			}
			
			exportRow[col.label] = value ?? "-";
		});
		return exportRow;
	});
}

/**
 * 构建报名记录导出文件名
 */
export function buildSignupRecordExportFilename(): string {
	const now = new Date();
	const timestamp = now.toISOString().replace(/[:.]/g, "-").substring(0, 19);
	return `报名记录_${timestamp}.xlsx`;
}
