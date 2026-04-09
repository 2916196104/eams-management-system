<template>
	<cui-dialog :title="title" :visible.sync="dialogVisible" @submit="formSubmit" :width="width">
		<slot></slot>
		<cui-form ref="formRef" :config="formConfig" @update="formUpdate"></cui-form>
		<!-- 组件外数据：{{formData}} -->
		<template #btn>
			<slot name="btn"></slot>
		</template>
	</cui-dialog>
</template>
<script>
// 带表单的弹出窗
/*
    * 例子
    * 模板：
       <cui-dialog-form
          ref="cuiDialogForm"
          title="自定义标题"
          :formConfig="formConfig"
          :visible.sync="visible"
          @onSubmit="onSubmit">
          顶部内容
          <template #btn>
            取消和确认中间的按钮
          </template>
       </cui-dialog-form>
    *
    * 参数：
     data() {
      return {
        // 表单参数同 cui-form 组件
        formConfig: {
          fields: [
            {label: "学员姓名", name: "name", type: "input"},
          ],
          rules: {
            name: [{required: true, message: '请输入姓名'}],
          },
        },
        initData: {}, // 初始化数据
        visible: false, // 显示与隐藏
        }
       }
     }
    *
    * 调起显示
    *   this.visible = true
        setTimeout(() => {
          this.initData = {
            name: 'abcd'
          }
        }, 1000)
    *
    * 表单提交处理方法：
    *
    * onSubmit(test) {
        console.log(test)
        this.$refs.cuiDialogForm.onReset();
      },
    * */
export default {
	name: "CuiDialogForm",
	props: {
		formConfig: {
			type: Object,
			required: true,
		},
		visible: {
			type: Boolean,
			required: true,
		},
		title: {
			type: String,
			default: "信息窗口",
		},
		width: {
			type: String,
		},
	},
	data() {
		return {
			formData: {},
		};
	},
	computed: {
		dialogVisible: {
			get: function () {
				return !!this.visible;
			},
			set: function (val) {
				this.$emit("update:visible", val);
			},
		},
	},
	methods: {
		// 表单数据更新
		formUpdate(value) {
			this.formData = value;
		},

		// 提交
		formSubmit: async function () {
			const valid = await this.$refs.formRef.onValidate();
			if (valid === true) {
				this.$emit("update:visible", false);
				this.$emit("onSubmit", this.formData);
			}
		},

		// 设置默认值和回显
		initFormData(data) {
			setTimeout(() => {
				this.$refs.formRef.setInitData(data);
			}, 50);
		},

		// 调用的父级组件需要手动重置表单内容
		onReset() {
			setTimeout(() => {
				this.$refs.formRef.formReset();
			}, 50);
		},
	},
};
</script>
