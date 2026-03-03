import { useHttp, type RequestCallback } from '@/plugins/http'
import type { PageDTO, SelectItem } from '../type'
import type { SampleFormData, SampleFormQuery } from './type'

// 定义一个功能模块基础url，方便替换
const currBaseUrl = '/smytale'

/**
 * 分页查询数据
 * @param data 查询数据条件
 * @param success 成功回调
 * @param fail 失败回调
 */
export const listall = async (
  data: SampleFormQuery,
  success: RequestCallback,
  fail: RequestCallback
) => {
  try {
    const http = useHttp()
    // 发送请求
    const res = await http.get<PageDTO<SampleFormData>>(currBaseUrl + '/query-all', data, {
      showLoading: true
    })
    // 处理请求结果
    if (res.data) {
      // 执行成功回调
      success(res.data)
      return
    }
    // 执行失败回调
    fail(res)
  } catch (err) {
    // 执行失败回调
    fail(err)
  }
}

/**
 * 获取省市县数据
 * @param type 数据类型
 * @returns 返回异步对象
 */
export const getAddress = (type: 'province' | 'city' | 'county') => {
  const http = useHttp()
  return http.get<Array<SelectItem>>('/address', { code: type })
}
