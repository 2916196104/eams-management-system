<template>
	<div id="app">
		<el-row class="tac">
			<el-col :span="4">
				<h5>CUI示例代码</h5>
				<el-menu @select="handleSelect" :router="true">
					<el-menu-item v-for="(item, index) in menu" :index="item" :key="index">
						<span slot="title">{{ item }}</span>
					</el-menu-item>
				</el-menu>
			</el-col>
			<el-col :span="20">
				<div style="padding: 20px">
					<router-view />
				</div>
			</el-col>
		</el-row>
	</div>
</template>

<script>
export default {
	name: "App",
	components: {},
	data() {
		return {
			menu: ["table-page-example", "form-page-example"],
		};
	},
	methods: {
		handleSelect(key, keyPath) {
			console.log(this.menu[key]);
		},
	},
};
</script>

<style>
#app {
	font-family: Avenir, Helvetica, Arial, sans-serif;
	color: #2c3e50;
}
</style>
