<template>
	<div class="contain">
		<el-row :gutter="20">
			<el-col :span="6">
				<statistics
					:targetText="'学员数'"
					:targetNumber="999"
					:iconName="'mdi:people'"
					:iconColor="'#40C9C6'"
					:hoverIconColor="'white'"
					:hoverBgColor="'#40C9C6'"
				/>
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
	</div>
</template>
<script setup lang="ts">
import statistics from "@/components/statistics/statistics.vue";
</script>
<style lang="css" scoped></style>
