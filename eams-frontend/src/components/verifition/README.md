# 验证码组件使用说明

相关参考链接地址

- 官方地址：https://ajcaptcha.beliefteam.cn/captcha-doc/
- `Vue`中使用：https://ajcaptcha.beliefteam.cn/captcha-doc/captchaDoc/vue.html

## 基础示例

```html
<template>
    <Verify
      ref="verify"
      mode="pop"
	  :captchaType="captchaType"
      :imgSize="{ width: '330px', height: '155px' }"
      @success="success">
    </Verify>
    <button @click="useVerify('clickWord')">登录</button>
</template>

<script setup lang="ts">
import { ref } from 'vue'
//引入组件
import Verify from '@/components/verifition/Verify.vue'
// 验证码组件引用
const verify = ref<InstanceType<typeof Verify> | null>(null)
// 验证码类型
const captchaType = ref('blockPuzzle')
/**
 * 弹出验证码框
 * @param type 验证码类型 blockPuzzle滑块验证 clickWord点击文字验证
 */
function useVerify(type: string) {
  captchaType.value = type
  if (verify.value) verify.value.show()
}
/**
 * 验证码验证通过执行登录二次验证逻辑
 * @param res 验证通过信息
 */
success(res: { captchaVerification: string }) {
  //验证码值获取通过 res.captchaVerification
}
</script>
```

***TIPS***

- mode为"pop"时,使用组件需要给组件添加ref值,并且手动调用show方法 例: `verify.show()`
- mode为"fixed"时,无需添加ref值,无需调用show()方法

## 回调事件

| 事件名            | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| `success(params)` | 验证码匹配成功后的回调函数,params为返回需回传服务器的二次验证参数 |
| `error`           | 验证码匹配失败后的回调函数                                   |
| `ready`           | 验证码初始化成功的回调函数                                   |

## 组件属性

| 属性名        | 类型   | 说明                                                         |
| ------------- | ------ | ------------------------------------------------------------ |
| `captchaType` | String | 1）滑动拼图 `blockPuzzle` 2）文字点选 `clickWord`            |
| `mode`        | String | 验证码的显示方式，弹出式pop，固定fixed，默认：mode : 'pop'   |
| `vSpace`      | String | 验证码图片和移动条容器的间隔，默认单位是`px`。如：间隔为`5px`，默认:`vSpace:5` |
| `explain`     | String | 滑动条内的提示，不设置默认是：'向右滑动完成验证'             |
| `imgSize`     | Object | 其中包含了width、height两个参数，分别代表图片的宽度和高度，支持百分比方式设置 如:`{width:'400px',height:'200px'}` |

## 默认接口

| 接口地址         | 请求方式 |
| ---------------- | -------- |
| `/captcha/get`   | post     |
| `/captcha/check` | post     |

### 获取验证码接口详情

请求地址如：http://xxx:xxx/captcha/get

```
组件内部默认请求服务器地址: import.meta.env.VITE_CAPTCHA_URL;是vue项目打包配置地址,方便分环境打包
```

请求参数：

```json
{
    // 验证码类型 clickWord
    "captchaType": "blockPuzzle",
    // 客户端UI组件id,组件初始化时设置一次，UUID（非必传参数）
    "clientUid": "唯一标识"
}
```

响应数据：

```json
{
    "repCode": "0000",
    "repData": {
        "originalImageBase64": "底图base64",
        "point": {//默认不返回的，校验的就是该坐标信息，允许误差范围
            "x": 205,
            "y": 5
        },
        "jigsawImageBase64": "滑块图base64",
        "token": "71dd26999e314f9abb0c635336976635", //一次校验唯一标识
        "result": false,
        "opAdmin": false
    },
    "success": true,
    "error": false
}
```

### 核对验证码接口详情

请求接口：http://xxx:xxx/captcha/check

```
组件内部默认请求服务器地址: import.meta.env.VITE_CAPTCHA_URL;是vue项目打包配置地址,方便分环境打包
```

请求参数：

```json
{
    "captchaType": "blockPuzzle",
    "pointJson": "QxIVdlJoWUi04iM+65hTow==",  //aes加密坐标信息
    "token": "71dd26999e314f9abb0c635336976635"  //get请求返回的token
}
```

响应数据：

```json
{
    "repCode": "0000",
    "repData": {
        "captchaType": "blockPuzzle",
        "token": "71dd26999e314f9abb0c635336976635",
        "result": true,
        "opAdmin": false
    },
    "success": true,
    "error": false
}
```