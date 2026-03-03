import { expect, describe, it, beforeAll, afterAll } from 'vitest'
import { withSetup } from '../test-apis-settings'
import { useHttp, HttpClient } from '@/plugins/http'
import type { PageDTO } from '@/apis/type'
import type { Article } from './type'

/**
 * 演示二次封装Axios使用
 * 测试指令 npm run test:unit http
 */
describe('http', () => {
  let app: any
  let http: HttpClient
  beforeAll(() => {
    app = withSetup(() => (http = useHttp()))[1]
  })
  afterAll(() => {
    app.unmount()
  })
  // 测试get请求
  it('getSync', async () => {
    http
      .get<PageDTO<Article>>('/article', {
        pageIndex: 1,
        pageSize: 2
      })
      .then((data) => {
        expect(data.code).toBe(10000)
        console.log(data.data?.rows)
      })
      .catch((error) => {
        expect(1).toBe(0)
        console.error(error)
      })
    //[x] [TEST_CODE]保证异步请求执行完成前测试案例不会结束
    await new Promise((resolve) => setTimeout(resolve, 1500))
  })
  // 测试get请求
  it('getAsync', async () => {
    const data = await http.get<PageDTO<Article>>('/article', {
      pageIndex: 1,
      pageSize: 2
    })
    expect(data.code).toBe(10000)
    console.log(data.data?.rows)
  })
  // 测试post请求
  it('post', async () => {
    const data = await http.post<Article>('/article', {
      title: '测试标题',
      keywords: '测试',
      summary: '测试摘要',
      content: '测试内容'
    })
    expect(data.code).toBe(10000)
    console.log(data.data)
  })
  // 测试put请求
  it('put', async () => {
    const data = await http.put<Article>('/article', {
      id: '1',
      title: '测试标题',
      keywords: '测试',
      summary: '测试摘要',
      content: '测试内容'
    })
    expect(data.code).toBe(10000)
    console.log(data.data)
  })
  // 测试delete请求
  it('delete', async () => {
    const data = await http.delete<Article>('/article/233')
    expect(data.code).toBe(10000)
    console.log(data.data)
  })
})
