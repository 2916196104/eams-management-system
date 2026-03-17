<template>
  <!-- 对话框激活按钮 -->
  <section class="root-container">
    <el-row :gutter="20">
      <el-col :span="8">
        <el-button color="#626aef" @click="formDialog?.openDialog()">表单对话框</el-button>
      </el-col>
      <el-col :span="8">
        <el-button color="#626aef" @click="cusdialog?.openDialog()">自定义对话框</el-button>
      </el-col>
      <el-col :span="8">
        <el-button color="#626aef" @click="dialog?.openDialog()">对话框事件支持</el-button>
      </el-col>
    </el-row>
  </section>

  <!-- 表单对话框 -->
  <my-form-dialog ref="formDialog" :="formDialogProps" @confirm="onSubmit">
    <template #itemdefault="{ item, model }">
      <!-- 处理头像使用文件上传组件 -->
      <el-upload
        v-if="item.prop === 'avatar'"
        class="avatar-uploader"
        action="https://jsonplaceholder.typicode.com/posts/"
        :show-file-list="false"
        :on-success="handleAvatarSuccess"
        :before-upload="beforeAvatarUpload"
        @change="model.avatar = imageUrl"
      >
        <img v-if="imageUrl" :src="imageUrl" class="avatar" />
        <el-icon v-else class="avatar-uploader-icon"><IconPlus /></el-icon>
      </el-upload>
    </template>
  </my-form-dialog>

  <!-- 自定义对话框 -->
  <my-dialog ref="cusdialog" :="cusprops">
    <!-- 定义标题栏 -->
    <template #header="{ close, fullscreen, title }">
      <section class="cus-dialog-title">
        <section>{{ title }}</section>
        <section>
          <el-button
            link
            type="primary"
            :icon="fullscreen ? 'IconMinus' : 'IconFullScreen'"
            @click="cusprops.fullscreen = !fullscreen"
          />
          <el-button link type="danger" icon="IconCloseBlod" @click="close()" />
        </section>
      </section>
    </template>
    <!-- 定义内容区 -->
    <template #default>
      <el-table :data="gridData" :height="cusprops?.fullscreen ? '85vh' : '100%'">
        <el-table-column property="name" label="Name" />
        <el-table-column property="date" label="Date" />
        <el-table-column property="address" label="Address" />
      </el-table>
    </template>
    <!-- 定义底部栏 -->
    <template #footer>
      <el-text class="cus-dialog-footer" type="success" tag="i">
        Self element set width 100px Squeezed by parent element The -webkit-line-clamp CSS property
        allows limiting of the contents of a block to the specified number of lines.
      </el-text>
    </template>
  </my-dialog>

  <!-- 自定义对话框事件支持 -->
  <my-dialog
    ref="dialog"
    :="props"
    :before-close="handleClose"
    @open="console.log('open')"
    @open-auto-focus="console.log('open-auto-focus')"
    @opened="console.log('opened')"
    @close="console.log('close')"
    @close-auto-focus="console.log('close-auto-focus')"
    @closed="console.log('closed')"
  />
</template>
<script setup lang="ts">
// #region 公用导入
import { reactive, ref } from 'vue'
import type { SampleFormData } from '@/apis/sample/type'
// #endregion

// #region 表单对话框
// 导入组件和类型
import MyFormDialog from '@/components/mydialog/MyFormDialog.vue'
import type { MyFormDialogProps } from '@/components/mydialog/type'
import type {
  MyFormItemAttr,
  MyFormInputProps,
  MyFormSelectProps,
  MyFormInputNumberProps,
  MyFormDatePickerProps
} from '@/components/myform/type'
import type { UploadProps } from 'element-plus'
// 定义对话框引用
const formDialog = ref()
// 定义对话框属性
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const formDialogProps = reactive<MyFormDialogProps<SampleFormData>>({
  // 表单数据
  data: reactive<SampleFormData>({}),
  // 表单域数据
  formitemdata: reactive<MyFormItemAttr[]>([
    {
      type: 'input',
      prop: 'name',
      label: '姓名',
      rules: [{ required: true, message: '请输入姓名', trigger: 'change' }],
      fprops: {
        placeholder: '请输入姓名',
        clearable: true
      } as MyFormInputProps
    },
    {
      type: 'select',
      prop: 'country',
      label: '国家',
      rules: [{ required: true, message: '请选择国家', trigger: 'change' }],
      fprops: {
        placeholder: '请选择国家',
        options: [
          {
            label: '中国',
            value: 'CN'
          },
          {
            label: '美国',
            value: 'US'
          },
          {
            label: '日本',
            value: 'JP',
            disabled: true
          }
        ]
      } as MyFormSelectProps
    },
    {
      type: 'input',
      prop: 'state',
      label: '省份',
      required: true,
      fprops: {
        placeholder: '请输入省份'
      }
    },
    {
      type: 'input',
      prop: 'city',
      label: '城市',
      fprops: {
        placeholder: '请输入城市'
      }
    },
    {
      type: 'number',
      prop: 'zip',
      label: '邮编',
      fprops: {
        width: '100%',
        placeholder: '请输入邮编',
        max: 999999,
        min: 100000,
        step: 100
      } as MyFormInputNumberProps
    },
    {
      type: 'date',
      prop: 'date',
      label: '生日',
      fprops: {
        width: '100%',
        placeholder: '请选择生日',
        type: 'date',
        'value-format': 'YYYY-MM-DD'
      } as MyFormDatePickerProps
    },
    {
      type: 'file',
      prop: 'avatar',
      label: '头像'
    }
  ]),
  // 表单属性
  formattr: {
    // 当这个值为true时表单元素全部禁止修改,对话框也不在显示提交和重置按钮
    disabled: false,
    'label-width': '80px'
  },
  title: '新增数据',
  width: '35vw',
  reset: true
})
/**
 * 提交修改
 * @param data 表单数据
 */
function onSubmit(data: SampleFormData) {
  // 提交数据
  console.log(data)
  // 关闭对话框
  formDialog.value.closeDialog()
}
// 图片地址
const imageUrl = ref('')
/**
 * 上传成功逻辑
 * @param response 响应数据
 * @param uploadFile 上传的文件
 */
const handleAvatarSuccess: UploadProps['onSuccess'] = (response, uploadFile) => {
  imageUrl.value = URL.createObjectURL(uploadFile.raw!)
  console.log(response)
}

/**
 * 上传前执行逻辑
 * @param rawFile 选择的文件
 */
const beforeAvatarUpload: UploadProps['beforeUpload'] = (rawFile) => {
  if (rawFile.type !== 'image/jpeg') {
    ElMessage.error('Avatar picture must be JPG format!')
    return false
  } else if (rawFile.size / 1024 / 1024 > 2) {
    ElMessage.error('Avatar picture size can not exceed 2MB!')
    return false
  }
  return true
}
// #endregion

// #region 自定义对话框
// 导入组件和类型
import MyDialog from '@/components/mydialog/MyDialog.vue'
import type { MyDialogProps } from '@/components/mydialog/type'
// 定义对话框引用
const cusdialog = ref()
// 定义对话框属性
const cusprops = reactive<MyDialogProps<string>>({
  data: '',
  title: '自定义对话框',
  draggable: true
})
// 定义测试表格数据
const gridData = [
  {
    name: 'John Smith',
    date: '2016-05-02',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  },
  {
    name: 'John Smith',
    date: '2016-05-04',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  },
  {
    name: 'John Smith',
    date: '2016-05-01',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  },
  {
    name: 'John Smith',
    date: '2016-05-03',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  }
]
// #endregion

// #region 自定义对话框事件支持
import { ElMessage } from 'element-plus'
// 定义对话框引用
const dialog = ref()
// 定义对话框属性
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const props = reactive<MyDialogProps<string>>({
  data: '',
  title: '对话框事件支持演示',
  'show-close': true
})
/**
 * 模拟操作失败阻止关闭
 */
let i = 0
function handleClose(done: () => void) {
  i++
  if (i % 2 === 0) done()
  else ElMessage.warning('操作失败，请重试')
}
// #endregion
</script>
<style scoped>
.root-container {
  background-color: white;
  border-radius: 5px;
  padding: 20px;
  display: flex;
  flex-direction: column;
  gap: 15px;
}
.el-col .el-button {
  width: 100%;
  /* margin-bottom: 20px; */
}
.cus-dialog-title {
  display: flex;
  justify-content: space-between;
  align-items: center;
  font-size: 20px;
  .el-button {
    font-size: 20px;
  }
}
.cus-dialog-footer {
  display: flex;
  justify-content: center;
  align-items: center;
  font-size: 17px;
  text-align: center;
}
</style>
<style>
.avatar-uploader .avatar {
  width: 96px;
  height: 96px;
  display: block;
}
.avatar-uploader .el-upload {
  border: 1px dashed var(--el-border-color);
  border-radius: 6px;
  cursor: pointer;
  position: relative;
  overflow: hidden;
  transition: var(--el-transition-duration-fast);
}
.avatar-uploader .el-upload:hover {
  border-color: var(--el-color-primary);
}
.el-icon.avatar-uploader-icon {
  font-size: 28px;
  color: #8c939d;
  width: 96px;
  height: 96px;
  text-align: center;
}
</style>
