import Vue from "vue";
import App from "./App.vue";

// 引入element-ui组件
import ElementUI from "element-ui";
import "./styles/element-variables.scss";
Vue.use(ElementUI);

// 注册打印组件
import Print from "vue-print-nb";
Vue.use(Print);

// 引入cui组件
import "./components/cui";
import "./components/cui/style/index.scss";

Vue.config.productionTip = false;

// 演示用路由
import Router from "vue-router";
Vue.use(Router);
import TablePage from "@/example/tablePage";
import FormPage from "@/example/formPage";

const router = new Router({
	routes: [
		{ path: "", component: TablePage },
		{ path: "/table-page-example", component: TablePage },
		{ path: "/form-page-example", component: FormPage },
	],
});

new Vue({
	router,
	render: (h) => h(App),
}).$mount("#app");
