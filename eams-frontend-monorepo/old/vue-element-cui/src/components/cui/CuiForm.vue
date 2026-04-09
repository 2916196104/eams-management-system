<template>
	<div>
		<el-form :model="formValue" :rules="rules" ref="formBuilder" :label-width="config.labelWidth || null" size="mini">
			<el-row :gutter="20">
				<template v-for="(item, index) in config.fields">
					<el-col :span="item.span ? item.span : 24" :key="index">
						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'static'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							{{ formValue[item.name] || "" }}
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'input'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-input
								:placeholder="item.placeholder"
								v-model="formValue[item.name]"
								style="width: 100%"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							>
								<template v-if="item.append" #append>{{ item.append }}</template>
							</el-input>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'number'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-input
								type="number"
								:placeholder="item.placeholder"
								v-model="formValue[item.name]"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							>
								<template v-if="item.append" #append>{{ item.append }}</template>
							</el-input>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'money'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-input
								type="number"
								:placeholder="item.placeholder"
								v-model="formValue[item.name]"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							>
								<template #append>元</template>
							</el-input>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'textarea'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-input
								type="textarea"
								:rows="3"
								:placeholder="item.placeholder"
								v-model="formValue[item.name]"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							>
								<template v-if="item.append" #append>{{ item.append }}</template>
							</el-input>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'selectBox'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<cui-select-box
								:code="item.code"
								:value.sync="formValue[item.name]"
								:visible.sync="selectorVisible[item.name]"
								:limit="item.limit || 0"
								:condition="item.condition || {}"
							/>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'select'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<cui-select :code="item.code" :value.sync="formValue[item.name]"></cui-select>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'multiselect'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<cui-select :code="item.code" :multiple="true" :value.sync="formValue[item.name]"></cui-select>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'enum'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<cui-select-enum :code="item.code" :value.sync="formValue[item.name]"></cui-select-enum>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'dict'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<cui-select-dict :code="item.code" :value.sync="formValue[item.name]"></cui-select-dict>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'date'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-date-picker
								v-model="formValue[item.name]"
								type="date"
								value-format="yyyy-MM-dd"
								:placeholder="item.placeholder"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							></el-date-picker>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'datetime'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-date-picker
								v-model="formValue[item.name]"
								type="datetime"
								:placeholder="item.placeholder"
								value-format="yyyy-MM-dd HH:mm:ss"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							></el-date-picker>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type == 'time'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-time-picker
								v-model="formValue[item.name]"
								:picker-options="{ format: 'HH:mm' }"
								value-format="HH:mm"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							></el-time-picker>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'switch'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-switch
								v-model="formValue[item.name]"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							></el-switch>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'editor'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<tinymce v-model="formValue[item.name]" :height="300" />
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'rate'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-rate
								v-model="formValue[item.name]"
								:disabled="!!item.cantEdit && formValue['id'] && formValue['id'] != ''"
							></el-rate>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'img'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<template v-for="(url, idx) in formValue[item.name]">
								<div
									:key="item.name + '' + idx"
									style="
										display: inline-block;
										margin-right: 10px;
										border-radius: 6px;
										over-flow: hidden;
										position: relative;
									"
								>
									<el-image style="width: 100px; height: 100px" :src="url" fit="fill"></el-image>
									<i
										class="el-icon-error"
										style="position: absolute; top: 5px; right: 5px; color: #ededed"
										@click="uploadRemove(item.name, idx)"
									></i>
								</div>
							</template>
							<fileUploader
								class="editor-upload-btn"
								@successCBK="uploadImgSuccess"
								:param="{ key: item.name, limit: item.limit || 1 }"
								:isImg="true"
								:acceptTypes="item.acceptTypes || '.jpg,.jpeg,.png,.gif,.JPG,.JPEG,.GIF,.PNG'"
							/>
							<span class="form-item-info" v-if="item.info">{{ item.info || "支持.jpg,.png,.gif的图片" }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'file'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<template v-for="(id, idx) in formValue[item.name]">
								<div :key="item.name + '' + idx" style="margin-right: 10px; position: relative">
									<fileList :key="id" :fileId="id" />
									<i
										class="el-icon-error"
										style="position: absolute; top: 5px; right: 5px; color: #ededed"
										@click="uploadRemove(item.name, idx)"
									></i>
								</div>
							</template>
							<fileUploader
								class="editor-upload-btn"
								@successCBK="uploadFileSuccess"
								:param="{ key: item.name, limit: item.limit || 1 }"
								:acceptTypes="item.acceptTypes || ''"
							/>
							<span class="form-item-info" v-if="item.info">{{ item.info }}</span>
						</el-form-item>

						<el-form-item
							:key="index"
							:label="item.label + ':'"
							v-if="item.type === 'region'"
							:prop="item.name"
							style="margin-bottom: 11px"
						>
							<el-cascader v-model="formValue[item.name]" :props="regionProps" style="width: 100%"></el-cascader>
						</el-form-item>
					</el-col>
				</template>
			</el-row>
		</el-form>
		<el-dialog :visible.sync="dialogVisible">
			<img width="100%" :src="dialogImageUrl" alt="" />
		</el-dialog>

		组件内数据：{{ formValue }}
	</div>
</template>

<script>
/*
* 参数示例：
*  formConfig: {
      fields: [],
      rules: {
        name: [{required: true, message: '请输入姓名'}],
        mobile: [
          {
            required: true, validator: async (rule, value) => {
              if (!isPhone(value)) {
                throw new Error('请输入手机号');
              }
            }
          },
        ],
        gender: [{required: true, message: '请选择性别'}],
      },
    },
*
*
*  默认值设置和回显方法：this.$refs.formRef.setInitData(initData);
*  提示: cui-select的回显使用字段加双下横线的形式
* */
import Tinymce from "@/components/Tinymce";
import fileUploader from "@/components/cui/components/FileUploader";
import fileList from "@/components/cui/components/FileList.vue";
import { loadRegionList } from "@/api/common";
let regionPid = 0;
export default {
	name: "CuiForm",
	components: {
		Tinymce,
		fileUploader,
		// 文件列表组件
		fileList,
	},
	props: {
		config: {
			type: Object,
			required: true,
			default: () => {
				return {
					fields: [], // 字段配置
					rules: {}, // 规则
				};
			},
		},
	},
	data() {
		return {
			formValue: {},
			fileArr: [],
			selectorVisible: {},

			// 上传参数
			dialogVisible: false,
			dialogImageUrl: "",

			regionProps: {
				lazy: true,
				lazyLoad: async function (node, resolve) {
					const { level } = node;
					const res = await loadRegionList(node.value || 0);
					const nodes = res.map((item) => ({
						value: item.id,
						label: item.name,
						leaf: level >= 2,
					}));
					resolve(nodes);
				},
			},
		};
	},
	watch: {
		// 更新新值并给父级
		formValue: function (val) {
			this.$emit("update", val);
		},
		"formValue.img": function (val) {
			console.log("11", val);
		},
	},
	computed: {
		fields: function () {
			return this.config.fields || [];
		},
		rules: function () {
			return this.config.rules || {};
		},
	},
	mounted() {
		// 加载后通过配置里的name构建初始属性
		for (const item of this.config.fields) {
			if (item.type == "selectBox") {
				this.$set(this.selectorVisible, item.name, "false");
			}
			// if (item.type == 'img' || item.type == 'file') {
			//   this.$set(this.formValue, item.name, null)
			// } else {
			this.$set(this.formValue, item.name, null);
			// }
		}
		// 初始化时防止触发验证
		this.resetFields();
	},
	methods: {
		formReset() {
			this.resetFields();
			const value = {};
			for (const i in this.formValue) {
				value[i] = null;
			}
			this.formValue = value;
		},
		onValidate: async function () {
			try {
				return await this.$refs.formBuilder.validate();
			} catch (error) {
				this.$message("表单未填写完整");
			}
		},
		resetFields() {
			// this.uploadFiles = []
			this.$refs.formBuilder.resetFields();
		},
		/**
		 * 设置和回显默认值方法
		 * force为 false 时只接受表单里配置里的值和属性id的值
		 * */
		setInitData(initData, force = false) {
			this.resetFields();
			if (initData) {
				// console.log('初始化formValue前', this.formValue, initData)
				for (var i in initData) {
					if (force) {
						this.$set(this.formValue, i, initData[i]);
					} else {
						for (var ii in this.formValue) {
							if (i == ii || i == "id") {
								// this.formValue[i] = initData[i]
								this.$set(this.formValue, i, initData[i]);
							}
						}
					}
				}
				// console.log('初始化formValue后', this.formValue)
			}
		},
		// 文件上传处理
		// handlePictureCardPreview(file) {
		//   this.dialogImageUrl = file.url;
		//   this.dialogVisible = true;
		// },
		uploadRemove(key, idx) {
			let values = { ...this.formValue };
			var data = values[key];
			data.splice(idx, 1);
			this.$set(this.formValue, key, data);
		},
		uploadFileSuccess(arr, param) {
			this.formValue[param.key] = [];
			for (var file of arr) {
				if (this.formValue[param.key].length < param.limit) {
					this.formValue[param.key].push(file.attaId);
				}
			}
		},
		uploadImgSuccess(arr, param) {
			this.formValue[param.key] = [];
			for (var file of arr) {
				if (this.formValue[param.key].length < param.limit) {
					this.formValue[param.key].push(file.url);
				}
			}
		},
	},
};
</script>
<style scoped>
.form-item-info {
	font-size: 12px;
	color: gray;
}
</style>
