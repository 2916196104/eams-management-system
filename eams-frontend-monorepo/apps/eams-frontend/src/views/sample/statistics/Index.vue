<template>
	<el-row :gutter="20">
		<el-col :span="6">
			<statistics :targetText="'学员数'" :targetNumber="999" :hoverColor="'red'" />
		</el-col>
		<el-col :span="6">
			<statistics :targetText="'学员数'" :targetNumber="12345" :hoverColor="'green'" />
		</el-col>
		<el-col :span="6">
			<statistics :targetText="'学员数'" :targetNumber="99234569" :hoverColor="'black'" />
		</el-col>
		<el-col :span="6">
			<statistics :targetText="'学员数'" :targetNumber="13323" :hoverColor="'yellow'" />
		</el-col>
	</el-row>
</template>

<script setup lang="ts">
import statistics from "@/components/statistics/statistics.vue";
</script>
