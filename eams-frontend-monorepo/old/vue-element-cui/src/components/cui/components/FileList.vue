<template>
	<a :href="fileinfo.url" target="_blank" style="font-size: 12px">{{ fileinfo.fileName }}</a>
</template>
<script>
import { getFileInfo } from "@/api/common";
export default {
	name: "FileList",
	props: ["fileId", "isImg"],
	data() {
		return {
			fileinfo: {
				url: "###",
				fileName: "加载中...",
			},
		};
	},
	created() {
		this.getFileNameByUrl(this.fileId);
	},
	methods: {
		getFileNameByUrl: function (id) {
			if (id) {
				this.fileinfo = {};
			}
		},
	},
};
</script>
