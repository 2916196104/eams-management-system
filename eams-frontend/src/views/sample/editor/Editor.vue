<template>
  <div class="root-container">
    <Toolbar
      style="border-bottom: 1px solid #ccc"
      :editor="editorRef"
      :defaultConfig="toolbarConfig"
      :mode="mode"
    />
    <Editor
      style="min-height: 500px"
      v-model="valueHtml"
      :defaultConfig="editorConfig"
      :mode="mode"
      @onCreated="handleCreated"
      @onChange="handleChange"
    />
  </div>
</template>
<style scoped>
.root-container {
  background-color: white;
  border: 1px solid #ccc;
  border-radius: 5px;
  padding: 20px;
  display: flex;
  flex-direction: column;
  gap: 15px;
}
</style>
<script setup lang="ts">
import '@wangeditor/editor/dist/css/style.css' // 引入 css
import { onBeforeUnmount, ref, shallowRef, onMounted } from 'vue'
import { Editor, Toolbar } from '@wangeditor/editor-for-vue'
import { ElMessage } from 'element-plus'
import { useUserStore } from '@/stores/user'
import { pinyin } from 'pinyin-pro'
// 编辑器实例，必须用 shallowRef
const editorRef = shallowRef()
const mode = 'default' // 或 'simple'
// 内容HTML
const valueHtml = ref(`<p>你好，富文本编辑器</p>`)
// 模拟ajax异步获取内容
onMounted(() => {
  setTimeout(() => {
    valueHtml.value = `<p>模拟异步结果：${pinyin('你好，富文本编辑器', { toneType: 'none' })}</p>`
  }, 1500)
})
// 组件销毁时，也及时销毁编辑器
onBeforeUnmount(() => {
  const editor = editorRef.value
  if (editor == null) return
  editor.destroy()
})

// 获取登录凭证
const store = useUserStore()
const token = store.getToken

// 组件相关配置
const toolbarConfig = {}
const editorConfig = {
  placeholder: '请输入内容...',
  MENU_CONF: {
    // 配置图片上传服务器
    uploadImage: {
      // 服务端地址
      server: 'http://localhost:8090/file/editor-upload-image',
      // 文件上传对应的表单名称，默认值：wangeditor-uploaded-image
      fieldName: 'file',
      // 设置请求头
      headers: {
        Authorization: 'Bearer ' + token
      },
      // 单个文件上传失败
      onFailed(file: any, res: any) {
        console.log(file, res)
        ElMessage.error('图片上传失败')
      },
      // 上传错误，或者触发 timeout 超时
      onError(file: any, err: any, res: any) {
        console.log(file, res, err)
        ElMessage.error('图片上传失败')
      },
      // 自定义插入图片
      customInsert(res: any, insertFn: any) {
        // 服务端的返回结果
        if (res.code === 10000) insertFn(res.data.url, res.data.alt, res.data.href)
        else ElMessage.error('图片上传失败')
      }
    }
  }
}
// 编辑器创建回调
const handleCreated = (editor: any) => {
  editorRef.value = editor // 记录 editor 实例，重要！
}
// 编辑器内容发生变化
const handleChange = (editor: any) => {
  console.log(editor.getHtml())
  console.log(editor.getText())
}
</script>
