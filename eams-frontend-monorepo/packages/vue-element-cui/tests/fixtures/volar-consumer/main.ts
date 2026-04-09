import { createApp } from "vue";
import VueElementCui from "@eams-monorepo/vue-element-cui";
import "@eams-monorepo/vue-element-cui/styles";
import App from "./App.vue";

createApp(App).use(VueElementCui).mount("#app");
