import VueElementCui from "@eams-monorepo/vue-element-cui";
import "@eams-monorepo/vue-element-cui/styles";
import ElementPlus from "element-plus";
import "element-plus/dist/index.css";

export default defineNuxtPlugin((nuxtApp) => {
	nuxtApp.vueApp.use(ElementPlus);
	nuxtApp.vueApp.use(VueElementCui);
});
