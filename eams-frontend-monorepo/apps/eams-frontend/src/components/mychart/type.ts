//图表组件接口定义
//图表数据接口
//基础数据属性
export interface ChartSeriesData {
	name: string;
	data: Array<number | null>;
	color?: string;
}

//图表通用属性
export interface ChartCommonProps {
	title?: string;
	height?: number | string;
	width?: number | string;
	theme?: "light" | "dark";
}

//折线图属性
export interface LineChartProps extends ChartCommonProps {
	xAxisData: Array<string | number>; //x轴数据
	seriesData: ChartSeriesData[]; //折线数据
	smooth?: boolean; //是否平滑折线
	showSymbol?: boolean; //是否显示数据点
	showArea?: boolean; //是否显示区域
	showLabel?: boolean; //是否显示数据标签
}

//柱状图属性
export interface BarChartProps extends ChartCommonProps {
	xAxisData: Array<string | number>; //x轴数据
	seriesData: ChartSeriesData[]; //柱状数据
	horizontal?: boolean; //是否水平柱状图
	showLabel?: boolean; //是否显示数据标签
}

//饼图属性
export interface PieChartProps extends ChartCommonProps {
	seriesData: Array<{
		//饼图数据
		name: string;
		value: number;
		color?: string;
	}>;
	radius?: string | [string, string]; //饼图半径
	roseType?: boolean | "area"; //是否玫瑰图
	showLabel?: boolean; //是否显示数据标签
}
//图表事件接口
export interface ChartEvents {
	(event: "chart-ready", chart: any): void; //图表初始化完成事件
	(event: "click", params: any): void; //点击事件
}
