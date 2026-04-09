<template>
	<div>
		<el-tabs v-model="activeName" @tab-click="handleRedirect">
			<el-tab-pane
				v-for="(item, index) in list"
				:key="index"
				:label="item.label"
				:name="item.label"
				:url="item.url"
			></el-tab-pane>
		</el-tabs>
	</div>
</template>
<script>
export default {
	props: {
		list: {
			required: true,
			default: () => {
				return [{ label: "", url: "" }];
			},
		},
		active: {
			default: "",
		},
	},
	data() {
		return {};
	},
	computed: {
		activeName: {
			get: function () {
				return this.active;
			},
			set: function (val) {
				this.$emit("update:active", val);
			},
		},
	},
	methods: {
		handleRedirect(tab) {
			console.log("tab.attrs");
			console.log(tab.attrs);
			var params = [];
			for (var i in this.$route.query) {
				params.push(i + "=" + this.$route.query[i]);
			}
			this.$router.push(tab.$attrs.url + (params.length > 0 ? "?" + params.join("&") : ""));
		},
	},
};
</script>
