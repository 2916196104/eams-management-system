// 选课页分类结构
export interface SelectCategory {
	id: string;
	name: string;
}

// 选课页课程结构
export interface SelectCourse {
	id: string;
	categoryId: string;
	subject: string;
	title: string;
	subTitle: string;
	teacher: string;
	price: number;
	lessonCount: number;
	suitableFor: string;
	recommended?: boolean;
	coverColor: string;
	tags: string[];
	description: string;
	highlights: string[];
}

// 顶部分类与展开面板共用的数据
export const selectCategories: Array<SelectCategory> = [
	{ id: "recommend", name: "推荐" },
	{ id: "info", name: "信息" },
	{ id: "geography", name: "地理" },
	{ id: "politics", name: "政治" },
	{ id: "history", name: "历史" },
	{ id: "biology", name: "生物" },
	{ id: "chemistry", name: "化学" },
	{ id: "physics", name: "物理" },
	{ id: "math", name: "数学" },
	{ id: "chinese", name: "语文" },
	{ id: "english", name: "英语" },
	{ id: "sports", name: "体能" },
	{ id: "calligraphy", name: "书法" },
	{ id: "craft", name: "劳技" },
	{ id: "piano", name: "钢琴" },
	{ id: "pe", name: "体育" },
	{ id: "guqin", name: "古筝" },
	{ id: "music", name: "音乐" },
	{ id: "art", name: "美术" },
];

// 选课页 mock 课程数据
export const selectCourses: Array<SelectCourse> = [
	{
		id: "geo-001",
		categoryId: "geography",
		subject: "地理",
		title: "地理提分班",
		subTitle: "区域地理与综合题突破",
		teacher: "林老师",
		price: 699,
		lessonCount: 12,
		suitableFor: "2027级",
		recommended: true,
		coverColor: "linear-gradient(135deg, #32c8a8 0%, #1fba97 100%)",
		tags: ["热门", "小班", "提分"],
		description: "围绕区域地理、自然与人文综合题型展开训练，帮助学生建立稳定的答题框架。",
		highlights: ["知识图谱梳理", "地图判读训练", "综合题模板精讲"],
	},
	{
		id: "politics-001",
		categoryId: "politics",
		subject: "政治",
		title: "政治时政冲刺班",
		subTitle: "高频考点快速梳理",
		teacher: "周老师",
		price: 599,
		lessonCount: 10,
		suitableFor: "2027级",
		recommended: true,
		coverColor: "linear-gradient(135deg, #ff9c51 0%, #ff7d4d 100%)",
		tags: ["冲刺", "时政", "答题"],
		description: "结合热点时政与教材核心知识，提升选择题和主观题的审题与表达能力。",
		highlights: ["热点专题整理", "主观题答题句式", "阶段测评反馈"],
	},
	{
		id: "info-001",
		categoryId: "info",
		subject: "信息",
		title: "信息学启蒙营",
		subTitle: "图形化编程与逻辑思维",
		teacher: "陈老师",
		price: 799,
		lessonCount: 16,
		suitableFor: "2028级",
		recommended: true,
		coverColor: "linear-gradient(135deg, #5b7cff 0%, #3c63ff 100%)",
		tags: ["编程", "思维", "入门"],
		description: "通过图形化编程任务培养孩子的逻辑表达与问题拆解能力。",
		highlights: ["项目式学习", "趣味闯关", "阶段作品展示"],
	},
	{
		id: "history-001",
		categoryId: "history",
		subject: "历史",
		title: "历史主线梳理班",
		subTitle: "时间轴与材料题精练",
		teacher: "许老师",
		price: 560,
		lessonCount: 8,
		suitableFor: "2027级",
		coverColor: "linear-gradient(135deg, #7b8a9a 0%, #4d5f75 100%)",
		tags: ["基础", "材料题"],
		description: "按照朝代演进和重大主题梳理历史知识，强化材料题和时序题的应对能力。",
		highlights: ["时间线构建", "史料阅读训练", "考点归纳复盘"],
	},
	{
		id: "biology-001",
		categoryId: "biology",
		subject: "生物",
		title: "生物实验专题班",
		subTitle: "图表分析与实验探究",
		teacher: "白老师",
		price: 620,
		lessonCount: 10,
		suitableFor: "2027级",
		coverColor: "linear-gradient(135deg, #38c172 0%, #24a65d 100%)",
		tags: ["实验", "图表"],
		description: "聚焦实验设计与图表分析题，帮助学生建立生物学科思维。",
		highlights: ["实验变量分析", "图表题专项", "错题讲评"],
	},
	{
		id: "chemistry-001",
		categoryId: "chemistry",
		subject: "化学",
		title: "化学方程式强化班",
		subTitle: "常见反应与计算专项",
		teacher: "吕老师",
		price: 680,
		lessonCount: 12,
		suitableFor: "2027级",
		coverColor: "linear-gradient(135deg, #8c6cff 0%, #6c52f4 100%)",
		tags: ["计算", "强化"],
		description: "围绕化学方程式、实验现象和基础计算题开展分层训练。",
		highlights: ["反应规律总结", "实验现象辨析", "计算题拆解"],
	},
	{
		id: "physics-001",
		categoryId: "physics",
		subject: "物理",
		title: "物理模型突破班",
		subTitle: "力学与电学双模块进阶",
		teacher: "尹老师",
		price: 760,
		lessonCount: 14,
		suitableFor: "2027级",
		coverColor: "linear-gradient(135deg, #00b8d9 0%, #0097b8 100%)",
		tags: ["力学", "电学", "进阶"],
		description: "聚焦中考高频模型题，帮助学生建立规范的受力分析与电路分析能力。",
		highlights: ["模型分类精讲", "实验题归纳", "公式运用训练"],
	},
	{
		id: "math-001",
		categoryId: "math",
		subject: "数学",
		title: "数学压轴训练营",
		subTitle: "函数与几何综合突破",
		teacher: "沈老师",
		price: 899,
		lessonCount: 18,
		suitableFor: "2027级",
		recommended: true,
		coverColor: "linear-gradient(135deg, #ff6b8b 0%, #ff4f6f 100%)",
		tags: ["压轴", "函数", "几何"],
		description: "针对函数、几何证明和综合压轴题展开系统训练，帮助学生提升高分题把握能力。",
		highlights: ["典型压轴题拆解", "图形辅助线思路", "限时训练与讲评"],
	},
	{
		id: "english-001",
		categoryId: "english",
		subject: "英语",
		title: "英语阅读表达班",
		subTitle: "阅读理解与写作同步提升",
		teacher: "叶老师",
		price: 640,
		lessonCount: 10,
		suitableFor: "2028级",
		coverColor: "linear-gradient(135deg, #17c1e8 0%, #0b99d5 100%)",
		tags: ["阅读", "写作"],
		description: "通过主题阅读和句式训练提升学生的阅读速度、信息提取能力与表达完整度。",
		highlights: ["主题阅读精练", "写作句式积累", "错题回炉复盘"],
	},
	{
		id: "art-001",
		categoryId: "art",
		subject: "美术",
		title: "创意美术体验课",
		subTitle: "造型基础与色彩表达",
		teacher: "顾老师",
		price: 399,
		lessonCount: 6,
		suitableFor: "2029级",
		coverColor: "linear-gradient(135deg, #ffb341 0%, #ff9041 100%)",
		tags: ["体验", "创意", "基础"],
		description: "适合低龄学生建立绘画兴趣，通过不同媒材完成创意主题作品。",
		highlights: ["色彩搭配启蒙", "造型观察训练", "主题作品完成"],
	},
];

// 根据课程 ID 获取课程详情
export function getSelectCourseById(id: string) {
	return selectCourses.find(item => item.id === id) || null;
}
