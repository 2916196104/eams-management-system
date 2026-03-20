import FcDesigner from "@form-create/designer";
import ElementPlus from "element-plus";
import zhCn from "element-plus/es/locale/lang/zh-cn";
import "element-plus/es/components/message/style/css";
import "element-plus/es/components/message-box/style/css";
import { createPinia } from "pinia";
import { createApp } from "vue";
import App from "./App.vue";
import "./assets/main.css";

// 安装http插件
import http from "./plugins/http";

// 安装ElIcon
import icon from "./plugins/icon";
import router from "./router";

const app = createApp(App);

app.use(createPinia());
app.use(router);

// 使用ElementPlus和FcDesigner
app.use(ElementPlus, { locale: zhCn });
app.use(FcDesigner);

// 安装http插件
app.use(http, { router });

// 安装ElIcon
app.use(icon);

app.mount("#app");
