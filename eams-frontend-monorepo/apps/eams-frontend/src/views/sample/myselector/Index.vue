<template>
	<section class="root-container">
		<el-card class="demo-card">
			<template #header>
				<div class="card-header">
					<span>人员选择器组件示例</span>
				</div>
			</template>

			<!-- 基础使用 -->
			<div class="demo-section">
				<h3>基础使用</h3>
				<p class="demo-desc">最简单的使用方式，使用静态数据源</p>
				<my-person-selector v-model="selectedPerson1" :data="staticData" placeholder="请选择人员" />
				<el-alert
					v-if="selectedPerson1"
					:title="`选中的人员：${selectedPerson1.name} - ${selectedPerson1.department} - ${selectedPerson1.phone}`"
					type="success"
					:closable="false"
					style="margin-top: 15px"
				/>
			</div>

			<el-divider />

			<!-- 动态加载数据 -->
			<div class="demo-section">
				<h3>动态加载数据</h3>
				<p class="demo-desc">通过 dataLoader 函数从API动态加载数据</p>
				<my-person-selector
					v-model="selectedPerson2"
					:data-loader="loadDynamicData"
					placeholder="请选择人员（动态加载）"
					panel-width="600px"
					table-height="450px"
				/>
				<el-alert
					v-if="selectedPerson2"
					:title="`选中的人员：${selectedPerson2.name} - ${selectedPerson2.department}`"
					type="success"
					:closable="false"
					style="margin-top: 15px"
				/>
			</div>

			<el-divider />

			<!-- 自定义分页 -->
			<div class="demo-section">
				<h3>自定义分页选项</h3>
				<p class="demo-desc">自定义每页显示条数选项和默认值</p>
				<my-person-selector
					v-model="selectedPerson3"
					:data="staticData"
					placeholder="请选择人员"
					:page-sizes="[5, 10, 20, 30]"
					:default-page-size="5"
					@select="handleSelect"
				/>
				<el-alert
					v-if="selectedPerson3"
					:title="`选中的人员：${selectedPerson3.name}`"
					type="success"
					:closable="false"
					style="margin-top: 15px"
				/>
			</div>

			<el-divider />

			<!-- 自定义样式 -->
			<div class="demo-section">
				<h3>自定义样式</h3>
				<p class="demo-desc">自定义面板宽度和表格高度</p>
				<my-person-selector
					v-model="selectedPerson4"
					:data="staticData"
					placeholder="请选择人员"
					panel-width="700px"
					table-height="500px"
				/>
				<el-alert
					v-if="selectedPerson4"
					:title="`选中的人员：${selectedPerson4.name}`"
					type="success"
					:closable="false"
					style="margin-top: 15px"
				/>
			</div>

			<el-divider />

			<!-- 手动控制 -->
			<div class="demo-section">
				<h3>手动控制选择器</h3>
				<p class="demo-desc">通过组件引用手动控制选择器的打开和关闭</p>
				<my-person-selector ref="selectorRef" v-model="selectedPerson5" :data="staticData" placeholder="请选择人员" />
				<div class="button-group">
					<el-button type="primary" @click="openSelector">打开选择器</el-button>
					<el-button @click="closeSelector">关闭选择器</el-button>
					<el-button type="success" @click="reloadData">重新加载数据</el-button>
				</div>
				<el-alert
					v-if="selectedPerson5"
					:title="`选中的人员：${selectedPerson5.name}`"
					type="success"
					:closable="false"
					style="margin-top: 15px"
				/>
			</div>

			<el-divider />

			<!-- 表单中使用 -->
			<div class="demo-section">
				<h3>表单中使用</h3>
				<p class="demo-desc">在表单中使用人员选择器</p>
				<el-form :model="formData" label-width="100px">
					<el-form-item label="姓名">
						<el-input v-model="formData.name" placeholder="请输入姓名" />
					</el-form-item>
					<el-form-item label="部门">
						<my-person-selector v-model="formData.departmentPerson" :data="staticData" placeholder="请选择部门人员" />
					</el-form-item>
					<el-form-item label="备注">
						<el-input v-model="formData.remark" type="textarea" placeholder="请输入备注" />
					</el-form-item>
					<el-form-item>
						<el-button type="primary" @click="submitForm">提交</el-button>
						<el-button @click="resetForm">重置</el-button>
					</el-form-item>
				</el-form>
			</div>
		</el-card>
	</section>
</template>

<script setup lang="ts">
import { ref, reactive } from "vue";
import { ElMessage } from "element-plus";
import MyPersonSelector from "@/components/myselector/MyPersonSelector.vue";
import type { PersonData } from "@/components/myselector/type";

// 选中的人员数据
const selectedPerson1 = ref<PersonData | null>(null);
const selectedPerson2 = ref<PersonData | null>(null);
const selectedPerson3 = ref<PersonData | null>(null);
const selectedPerson4 = ref<PersonData | null>(null);
const selectedPerson5 = ref<PersonData | null>(null);

// 组件引用
const selectorRef = ref();

// 表单数据
const formData = reactive({
	name: "",
	departmentPerson: null as PersonData | null,
	remark: "",
});

// 生成模拟数据
function generateMockData(): PersonData[] {
	const departments = ["技术部", "产品部", "市场部", "销售部", "人力资源部", "财务部", "运营部"];
	const names = [
		"张三",
		"李四",
		"王五",
		"赵六",
		"钱七",
		"孙八",
		"周九",
		"吴十",
		"郑十一",
		"冯十二",
		"陈十三",
		"褚十四",
		"卫十五",
		"蒋十六",
		"沈十七",
		"韩十八",
		"杨十九",
		"朱二十",
		"秦二十一",
		"尤二十二",
		"许二十三",
		"何二十四",
		"吕二十五",
		"施二十六",
		"张二十七",
		"孔二十八",
		"曹二十九",
		"严三十",
		"华三十一",
		"金三十二",
		"魏三十三",
		"陶三十四",
		"姜三十五",
		"戚三十六",
		"谢三十七",
		"邹三十八",
		"喻三十九",
		"柏四十",
		"水四十一",
		"窦四十二",
		"章四十三",
		"云四十四",
		"苏四十五",
		"潘四十六",
		"葛四十七",
		"奚四十八",
		"范四十九",
		"彭五十",
		"鲁五十一",
		"韦五十二",
		"昌五十三",
		"马五十四",
		"苗五十五",
		"凤五十六",
		"花五十七",
		"方五十八",
		"俞五十九",
		"任六十",
		"袁六十一",
		"柳六十二",
		"酆六十三",
		"鲍六十四",
		"史六十五",
		"唐六十六",
	];

	const data: PersonData[] = [];
	for (let i = 0; i < 64; i++) {
		data.push({
			id: i + 1,
			name: names[i],
			department: departments[Math.floor(Math.random() * departments.length)],
			phone: `138${String(Math.floor(Math.random() * 100000000)).padStart(8, "0")}`,
		});
	}
	return data;
}

// 静态数据
const staticData = ref<PersonData[]>(generateMockData());

// 动态加载数据函数
async function loadDynamicData(): Promise<PersonData[]> {
	// 模拟API调用
	return new Promise((resolve) => {
		setTimeout(() => {
			resolve(generateMockData());
		}, 300);
	});
}

// 选择事件处理
function handleSelect(person: PersonData) {
	ElMessage.success(`选中了：${person.name} - ${person.department}`);
	console.log("选中的人员信息:", person);
}

// 打开选择器
function openSelector() {
	selectorRef.value?.openSelector();
	ElMessage.info("打开选择器");
}

// 关闭选择器
function closeSelector() {
	selectorRef.value?.closeSelector();
	ElMessage.info("关闭选择器");
}

// 重新加载数据
function reloadData() {
	selectorRef.value?.loadData();
	ElMessage.success("重新加载数据");
}

// 提交表单
function submitForm() {
	console.log("表单数据:", formData);
	if (formData.departmentPerson) {
		ElMessage.success(
			`提交成功！选中的人员：${formData.departmentPerson.name} - ${formData.departmentPerson.department}`,
		);
	} else {
		ElMessage.warning("请选择部门人员");
	}
}

// 重置表单
function resetForm() {
	formData.name = "";
	formData.departmentPerson = null;
	formData.remark = "";
	ElMessage.info("表单已重置");
}
</script>

<style scoped>
.root-container {
	padding: 20px;
	display: flex;
	justify-content: center;
}

.root-container .demo-card {
	width: 100%;
	max-width: 1200px;
}

.root-container .demo-card .card-header {
	display: flex;
	justify-content: space-between;
	align-items: center;
	font-size: 18px;
	font-weight: bold;
}

.root-container .demo-card .demo-section {
	padding: 20px 0;
}

.root-container .demo-card .demo-section h3 {
	margin-bottom: 10px;
	color: #303133;
	font-size: 16px;
}

.root-container .demo-card .demo-section .demo-desc {
	margin-bottom: 15px;
	color: #909399;
	font-size: 14px;
}

.root-container .demo-card .demo-section .button-group {
	margin-top: 15px;
	display: flex;
	gap: 10px;
}
</style>
