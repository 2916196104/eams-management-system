<template>
	<span>
		<span v-if="editing" class="editable-input-box">
			<el-input v-if="editConf.type == 'input'" v-model="fieldValue" size="mini" clearable></el-input>
			<el-input v-if="editConf.type === 'textarea'" type="textarea" :rows="3" v-model="fieldValue"></el-input>
			<cui-select
				size="mini"
				v-if="editConf.type === 'select'"
				:code="editConf.code"
				:value.sync="fieldValue"
				:clearable="true"
				:filterable="true"
			></cui-select>
			<cui-select-enum
				size="mini"
				v-if="editConf.type === 'enum'"
				:code="editConf.code"
				:value.sync="fieldValue"
			></cui-select-enum>
			<cui-checkbox-enum
				size="mini"
				v-if="editConf.type === 'enumCheckbox'"
				:code="editConf.code"
				:value.sync="fieldValue"
			></cui-checkbox-enum>
			<cui-select-dict
				size="mini"
				v-if="editConf.type === 'dict'"
				:code="editConf.code"
				:value.sync="fieldValue"
			></cui-select-dict>
			<el-date-picker
				v-if="editConf.type === 'month'"
				v-model="fieldValue"
				type="month"
				placeholder="选择月"
				style="width: 100%"
				value-format="yyyy-MM-dd"
			></el-date-picker>
			<el-date-picker
				v-if="editConf.type == 'date' || editConf.type == 'daterange'"
				v-model="fieldValue"
				:type="type"
				:picker-options="{ firstDayOfWeek: 1 }"
				value-format="yyyy-MM-dd"
			></el-date-picker>
			<el-date-picker
				v-if="editConf.type == 'datetime'"
				v-model="fieldValue"
				:type="type"
				:picker-options="{ firstDayOfWeek: 1 }"
				value-format="yyyy-MM-dd HH:mm:ss"
				clearable
			></el-date-picker>

			<span class="editable-icon" @click="handleSave"><i class="el-icon-check">保存</i></span>
			<span class="editable-icon" @click="handleCancel"><i class="el-icon-close">取消</i></span>
		</span>
		<span v-else class="editable-text" @mouseenter="enter" @mouseleave="leave" @click="textClick">
			<slot />
			<i class="el-icon-edit" v-if="showIcon"></i>
		</span>
	</span>
</template>
<script>
/* 
可编辑文档，点击后可以输入，失去焦点后执行保存
*/
export default {
	name: "EditableText",
	props: {
		editConf: {
			type: Object,
			default: () => {
				return {
					type: "input",
					code: "",
					disabled: false,
				};
			},
		},
		disable: {
			type: Boolean,
			default: false,
		},
		type: {
			type: String,
			default: "input",
		},
		text: {
			type: String,
			default: "",
		},
		field: {
			type: String,
		},
		row: {
			type: Object,
		},
		editFunc: {
			type: Function,
		},
	},
	data() {
		return {
			editing: false,
			showIcon: false,
			fieldValue: this.row[this.field],
		};
	},
	created() {},
	methods: {
		handleSave() {
			this.editFunc(this.row, this.field, this.fieldValue);
			this.handleCancel();
		},
		handleCancel() {
			this.editing = false;
			this.leave();
		},
		textClick() {
			if (this.editConf && !this.editConf.disabled) this.editing = true;
		},
		enter() {
			if (this.editConf && !this.editConf.disabled) this.showIcon = true;
		},
		leave() {
			this.showIcon = false;
		},
	},
};
</script>
<style>
.editable-text:hover {
	color: blue !important;
	text-decoration: underline;
}
.editable-input-box .el-input__inner {
	padding-left: 5px !important;
	padding-right: 5px !important;
}
.editable-input-box .editable-icon {
	width: 80px;
	margin-right: 10px;
	cursor: pointer;
}
</style>
