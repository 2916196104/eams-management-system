<template>
	<el-row :gutter="20">
		<el-col :span="6">
			<statistics :targetText="'学员数1'" :targetNumber="999" :hoverColor="'red'" />
		</el-col>
		<el-col :span="6">
			<statistics :targetText="'学员数2'" :targetNumber="12345" :hoverColor="'green'" />
		</el-col>
		<el-col :span="6">
			<statistics :targetText="'学员数3'" :targetNumber="99234569" :hoverColor="'black'" />
		</el-col>
		<el-col :span="6">
			<statistics :targetText="'学员数4'" :targetNumber="13323" :hoverColor="'yellow'" />
		</el-col>
	</el-row>
</template>
<script setup lang="ts">
// 引入组件和类型
import statistics from '@/components/statistics/statistics.vue'
</script>
