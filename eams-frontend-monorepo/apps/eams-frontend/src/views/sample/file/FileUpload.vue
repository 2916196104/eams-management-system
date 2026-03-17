<template>
  <div class="root-container">
    <!-- 上传文件携带表单数据 -->
    <el-upload
      action="no-action"
      :show-file-list="false"
      :http-request="uploadUseFormData"
      @success="handleSuccess"
      @error="handleError"
    >
      <el-button size="small" type="primary">
        <el-icon style="vertical-align: middle">
          <icon-upload />
        </el-icon>
        <span style="vertical-align: middle">FormData上传文件</span>
      </el-button>
    </el-upload>
    <!-- 流方式上传文件 -->
    <el-upload
      ref="upload"
      action="no-action"
      :show-file-list="false"
      :http-request="uploadUseStream"
      @success="handleSuccess"
      @error="handleError"
    >
      <el-button size="small" type="primary">
        <el-icon style="vertical-align: middle">
          <icon-upload />
        </el-icon>
        <span style="vertical-align: middle">Stream上传文件</span>
      </el-button>
    </el-upload>
    <!-- 导出文件数据示例 -->
    <el-button type="primary" size="small" @click="exportFile">
      <el-icon style="vertical-align: middle">
        <icon-download />
      </el-icon>
      <span style="vertical-align: middle">导出报表</span>
    </el-button>
  </div>
</template>

<script setup lang="ts">
import { useHttp } from '@/plugins/http'
import { ElMessage } from 'element-plus'
// 获取http实例
const http = useHttp()
// 成功回调
function handleSuccess(response: any) {
  console.log(response)
  ElMessage.success('上传成功')
}

// 失败回调
function handleError(error: any) {
  console.log(error)
  ElMessage.error('上传失败')
}

// 使用FormData的方式上传文件
function uploadUseFormData(params: any) {
  return http.postWithFile<any>(
    '/file/upload',
    {
      fileType: '10001',
      saveType: '10002',
      file: params.file
    },
    {
      baseURL: 'http://localhost:8090',
      onUploadProgress: (progressEvent) => {
        console.log('上传', progressEvent.progress ? progressEvent.progress * 100 + '%' : '0%')
      }
    }
  )
}

// 使用Stream方式上传
function uploadUseStream(params: any) {
  return new Promise((resolve, reject) => {
    const suffix = params.file.name.split('.').pop()
    http.postFileStream(
      `/file/upload-stream?suffix=${suffix}`,
      params.file,
      (res: any) => {
        resolve(res)
      },
      (err: any) => {
        reject(err)
      },
      { baseURL: 'http://localhost:8090' }
    )
  })
}

// 下载文件
function downFile(blob: any, filename: string) {
  const link = document.createElement('a')
  link.href = window.URL.createObjectURL(blob) // 创建下载的链接
  link.download = filename // 下载后文件名
  link.style.display = 'none'
  document.body.appendChild(link)
  link.click() // 点击下载
  window.URL.revokeObjectURL(link.href) // 释放掉blob对象
  document.body.removeChild(link) // 下载完成移除元素
}

// 请求文件数据
function exportFile() {
  http
    .getFile(
      '/sample/export',
      {
        pageIndex: 1,
        pageSize: 10
      },
      {
        responseType: 'blob',
        baseURL: 'http://localhost:8090',
        onDownloadProgress: function (progressEvent) {
          console.log('下载', progressEvent.progress ? progressEvent.progress * 100 + '%' : '0%')
        }
      }
    )
    .then((res) => {
      if (res.data) {
        const headers = res.headers
        const contentType = headers['content-type']
        const blob = new Blob([res.data], { type: contentType })
        const contentDisposition = headers['content-disposition']
        let filename = 'tmp.xlsx'
        if (contentDisposition) {
          filename = window.decodeURI(contentDisposition.split('=')[1])
        }
        downFile(blob, filename)
        ElMessage.success('下载成功')
        return
      }
      console.warn(res)
      ElMessage.error('下载失败')
    })
    .catch((res) => {
      console.warn(res)
      ElMessage.error('下载失败')
    })
}
</script>

<style scoped>
.root-container {
  background-color: white;
  border-radius: 5px;
  padding: 20px;
  display: flex;
  flex-direction: row;
  justify-content: flex-start;
  gap: 15px;
}
.el-button {
  width: 240px;
}
</style>
