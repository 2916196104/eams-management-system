import { expect, describe, it, beforeAll, afterAll } from 'vitest'
import { withSetup } from '../test-apis-settings'
import { login } from '@/apis/login'

/**
 * 登录测试
 * 测试指令 npm run test:unit login
 */
describe('login', () => {
  let app: any
  beforeAll(() => {
    app = withSetup()[1]
  })
  afterAll(() => {
    app.unmount()
  })
  // 测试调用登录接口
  it('login', async () => {
    await login(
      {
        username: 'admin',
        password: '123456'
      },
      () => {
        expect(1).toBe(1)
      },
      () => {
        expect(0).toBe(1)
      }
    )
  })
})
