import { DataUpType, useHttp } from '@/plugins/http'

// 定义一个功能模块基础url，方便替换
const currBaseUrl = import.meta.env.VITE_CAPTCHA_PREFIX

//获取验证图片以及token
export function reqGet(data) {
  return useHttp()
    .getInstance()
    .request({
      method: 'post',
      url: currBaseUrl + '/get',
      data: data,
      upType: DataUpType.json,
      baseURL: import.meta.env.VITE_CAPTCHA_URL
    })
}

//滑动或者点选验证
export function reqCheck(data) {
  return useHttp()
    .getInstance()
    .request({
      method: 'post',
      url: currBaseUrl + '/check',
      data: data,
      upType: DataUpType.json,
      baseURL: import.meta.env.VITE_CAPTCHA_URL
    })
}
