// vite.config.ts
import process from "node:process";
import Uni from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+plugin-uni@0.1._760abeaae0973b16e63d90be4bbb43de/node_modules/@uni-helper/plugin-uni/src/index.js";
import { isMpWeixin } from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+uni-env@0.2.0/node_modules/@uni-helper/uni-env/dist/index.js";
import UniHelperComponents from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+vite-plugin-uni-components@0.2.10_rollup@4.59.0/node_modules/@uni-helper/vite-plugin-uni-components/dist/index.mjs";
import { WotResolver } from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+vite-plugin-uni-components@0.2.10_rollup@4.59.0/node_modules/@uni-helper/vite-plugin-uni-components/dist/resolvers.mjs";
import UniHelperLayouts from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+vite-plugin-uni_da8262252ac373abe7e054723d89f2ca/node_modules/@uni-helper/vite-plugin-uni-layouts/dist/index.mjs";
import UniHelperManifest from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+vite-plugin-uni_b16bc92adbcee69a3a58f84bfbac7466/node_modules/@uni-helper/vite-plugin-uni-manifest/dist/index.mjs";
import UniHelperPages from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-helper+vite-plugin-uni_47bce620316159ebcf432ff854bf37a9/node_modules/@uni-helper/vite-plugin-uni-pages/dist/index.mjs";
import Optimization from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-ku+bundle-optimizer@2._165b6e5a6671932ee5ea374334b4917f/node_modules/@uni-ku/bundle-optimizer/dist/index.mjs";
import UniKuRoot from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/@uni-ku+root@1.4.1_vite@5.4_929dcb7454bd8aef800e9810f23cf857/node_modules/@uni-ku/root/dist/index.mjs";
import { UniEchartsResolver } from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/uni-echarts@2.5.1_echarts@6.0.0_vue@3.4.38_typescript@5.5.4_/node_modules/uni-echarts/dist-resolver/index.mjs";
import { UniEcharts } from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/uni-echarts@2.5.1_echarts@6.0.0_vue@3.4.38_typescript@5.5.4_/node_modules/uni-echarts/dist-vite/index.mjs";
import UnoCSS from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/unocss@66.0.0_postcss@8.5.8_014def9a5e5a4479635ad58267cf54a1/node_modules/unocss/dist/vite.mjs";
import AutoImport from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/unplugin-auto-import@0.18.6_31aa37beddbc65cb6db3c52a79a3120b/node_modules/unplugin-auto-import/dist/vite.js";
import { defineConfig } from "file:///E:/VSCode/Projects/zero-one-eams2603/eams-frontend-monorepo/node_modules/.pnpm/vite@5.4.21_@types+node@20._cb9131cbbb3fa1fe8ac3cbbc2d3ce024/node_modules/vite/dist/node/index.js";
var vite_config_default = defineConfig({
  base: "./",
  optimizeDeps: {
    exclude: process.env.NODE_ENV === "development" ? ["wot-design-uni", "uni-echarts"] : []
  },
  plugins: [
    // https://github.com/uni-helper/vite-plugin-uni-manifest
    UniHelperManifest(),
    // https://github.com/uni-helper/vite-plugin-uni-pages
    UniHelperPages({
      dts: "src/uni-pages.d.ts",
      subPackages: ["src/subPages"],
      /**
       * 排除的页面，相对于 dir 和 subPackages
       * @default []
       */
      exclude: ["**/components/**/*.*"]
    }),
    // https://github.com/uni-helper/vite-plugin-uni-layouts
    UniHelperLayouts(),
    // https://github.com/uni-helper/vite-plugin-uni-components
    UniHelperComponents({
      resolvers: [WotResolver(), UniEchartsResolver()],
      dts: "src/components.d.ts",
      dirs: ["src/components", "src/business"],
      directoryAsNamespace: true
    }),
    // https://github.com/uni-ku/root
    UniKuRoot(),
    // https://uni-echarts.xiaohe.ink
    UniEcharts(),
    // https://uni-helper.cn/plugin-uni
    Uni(),
    // https://github.com/uni-ku/bundle-optimizer
    Optimization({
      enable: isMpWeixin,
      logger: false
    }),
    // https://github.com/antfu/unplugin-auto-import
    AutoImport({
      imports: [
        "vue",
        "@vueuse/core",
        "pinia",
        "uni-app",
        {
          from: "@wot-ui/router",
          imports: ["createRouter", "useRouter", "useRoute"]
        },
        {
          from: "wot-design-uni",
          imports: ["useToast", "useMessage", "useNotify", "CommonUtil"]
        },
        {
          from: "alova/client",
          imports: ["usePagination", "useRequest"]
        }
      ],
      dts: "src/auto-imports.d.ts",
      dirs: ["src/composables", "src/store", "src/utils", "src/api"],
      vueTemplate: true
    }),
    // https://github.com/antfu/unocss
    // see unocss.config.ts for config
    UnoCSS()
  ]
});
export {
  vite_config_default as default
};
//# sourceMappingURL=data:application/json;base64,ewogICJ2ZXJzaW9uIjogMywKICAic291cmNlcyI6IFsidml0ZS5jb25maWcudHMiXSwKICAic291cmNlc0NvbnRlbnQiOiBbImNvbnN0IF9fdml0ZV9pbmplY3RlZF9vcmlnaW5hbF9kaXJuYW1lID0gXCJFOlxcXFxWU0NvZGVcXFxcUHJvamVjdHNcXFxcemVyby1vbmUtZWFtczI2MDNcXFxcZWFtcy1mcm9udGVuZC1tb25vcmVwb1xcXFxhcHBzXFxcXGVhbXMtZnJvbnR0ZWFcIjtjb25zdCBfX3ZpdGVfaW5qZWN0ZWRfb3JpZ2luYWxfZmlsZW5hbWUgPSBcIkU6XFxcXFZTQ29kZVxcXFxQcm9qZWN0c1xcXFx6ZXJvLW9uZS1lYW1zMjYwM1xcXFxlYW1zLWZyb250ZW5kLW1vbm9yZXBvXFxcXGFwcHNcXFxcZWFtcy1mcm9udHRlYVxcXFx2aXRlLmNvbmZpZy50c1wiO2NvbnN0IF9fdml0ZV9pbmplY3RlZF9vcmlnaW5hbF9pbXBvcnRfbWV0YV91cmwgPSBcImZpbGU6Ly8vRTovVlNDb2RlL1Byb2plY3RzL3plcm8tb25lLWVhbXMyNjAzL2VhbXMtZnJvbnRlbmQtbW9ub3JlcG8vYXBwcy9lYW1zLWZyb250dGVhL3ZpdGUuY29uZmlnLnRzXCI7aW1wb3J0IHByb2Nlc3MgZnJvbSBcIm5vZGU6cHJvY2Vzc1wiO1xuaW1wb3J0IFVuaSBmcm9tIFwiQHVuaS1oZWxwZXIvcGx1Z2luLXVuaVwiO1xuaW1wb3J0IHsgaXNNcFdlaXhpbiB9IGZyb20gXCJAdW5pLWhlbHBlci91bmktZW52XCI7XG5pbXBvcnQgVW5pSGVscGVyQ29tcG9uZW50cyBmcm9tIFwiQHVuaS1oZWxwZXIvdml0ZS1wbHVnaW4tdW5pLWNvbXBvbmVudHNcIjtcbmltcG9ydCB7IFdvdFJlc29sdmVyIH0gZnJvbSBcIkB1bmktaGVscGVyL3ZpdGUtcGx1Z2luLXVuaS1jb21wb25lbnRzL3Jlc29sdmVyc1wiO1xuaW1wb3J0IFVuaUhlbHBlckxheW91dHMgZnJvbSBcIkB1bmktaGVscGVyL3ZpdGUtcGx1Z2luLXVuaS1sYXlvdXRzXCI7XG5pbXBvcnQgVW5pSGVscGVyTWFuaWZlc3QgZnJvbSBcIkB1bmktaGVscGVyL3ZpdGUtcGx1Z2luLXVuaS1tYW5pZmVzdFwiO1xuaW1wb3J0IFVuaUhlbHBlclBhZ2VzIGZyb20gXCJAdW5pLWhlbHBlci92aXRlLXBsdWdpbi11bmktcGFnZXNcIjtcbmltcG9ydCBPcHRpbWl6YXRpb24gZnJvbSBcIkB1bmkta3UvYnVuZGxlLW9wdGltaXplclwiO1xuaW1wb3J0IFVuaUt1Um9vdCBmcm9tIFwiQHVuaS1rdS9yb290XCI7XG5pbXBvcnQgeyBVbmlFY2hhcnRzUmVzb2x2ZXIgfSBmcm9tIFwidW5pLWVjaGFydHMvcmVzb2x2ZXJcIjtcbmltcG9ydCB7IFVuaUVjaGFydHMgfSBmcm9tIFwidW5pLWVjaGFydHMvdml0ZVwiO1xuaW1wb3J0IFVub0NTUyBmcm9tIFwidW5vY3NzL3ZpdGVcIjtcbmltcG9ydCBBdXRvSW1wb3J0IGZyb20gXCJ1bnBsdWdpbi1hdXRvLWltcG9ydC92aXRlXCI7XG5pbXBvcnQgeyBkZWZpbmVDb25maWcgfSBmcm9tIFwidml0ZVwiO1xuLy8gaHR0cHM6Ly92aXRlanMuZGV2L2NvbmZpZy9cbmV4cG9ydCBkZWZhdWx0IGRlZmluZUNvbmZpZyh7XG5cdGJhc2U6IFwiLi9cIixcblx0b3B0aW1pemVEZXBzOiB7XG5cdFx0ZXhjbHVkZTogcHJvY2Vzcy5lbnYuTk9ERV9FTlYgPT09IFwiZGV2ZWxvcG1lbnRcIiA/IFtcIndvdC1kZXNpZ24tdW5pXCIsIFwidW5pLWVjaGFydHNcIl0gOiBbXSxcblx0fSxcblx0cGx1Z2luczogW1xuXHRcdC8vIGh0dHBzOi8vZ2l0aHViLmNvbS91bmktaGVscGVyL3ZpdGUtcGx1Z2luLXVuaS1tYW5pZmVzdFxuXHRcdFVuaUhlbHBlck1hbmlmZXN0KCksXG5cdFx0Ly8gaHR0cHM6Ly9naXRodWIuY29tL3VuaS1oZWxwZXIvdml0ZS1wbHVnaW4tdW5pLXBhZ2VzXG5cdFx0VW5pSGVscGVyUGFnZXMoe1xuXHRcdFx0ZHRzOiBcInNyYy91bmktcGFnZXMuZC50c1wiLFxuXHRcdFx0c3ViUGFja2FnZXM6IFtcInNyYy9zdWJQYWdlc1wiXSxcblx0XHRcdC8qKlxuXHRcdFx0ICogXHU2MzkyXHU5NjY0XHU3Njg0XHU5ODc1XHU5NzYyXHVGRjBDXHU3NkY4XHU1QkY5XHU0RThFIGRpciBcdTU0OEMgc3ViUGFja2FnZXNcblx0XHRcdCAqIEBkZWZhdWx0IFtdXG5cdFx0XHQgKi9cblx0XHRcdGV4Y2x1ZGU6IFtcIioqL2NvbXBvbmVudHMvKiovKi4qXCJdLFxuXHRcdH0pLFxuXHRcdC8vIGh0dHBzOi8vZ2l0aHViLmNvbS91bmktaGVscGVyL3ZpdGUtcGx1Z2luLXVuaS1sYXlvdXRzXG5cdFx0VW5pSGVscGVyTGF5b3V0cygpLFxuXHRcdC8vIGh0dHBzOi8vZ2l0aHViLmNvbS91bmktaGVscGVyL3ZpdGUtcGx1Z2luLXVuaS1jb21wb25lbnRzXG5cdFx0VW5pSGVscGVyQ29tcG9uZW50cyh7XG5cdFx0XHRyZXNvbHZlcnM6IFtXb3RSZXNvbHZlcigpLCBVbmlFY2hhcnRzUmVzb2x2ZXIoKV0sXG5cdFx0XHRkdHM6IFwic3JjL2NvbXBvbmVudHMuZC50c1wiLFxuXHRcdFx0ZGlyczogW1wic3JjL2NvbXBvbmVudHNcIiwgXCJzcmMvYnVzaW5lc3NcIl0sXG5cdFx0XHRkaXJlY3RvcnlBc05hbWVzcGFjZTogdHJ1ZSxcblx0XHR9KSxcblx0XHQvLyBodHRwczovL2dpdGh1Yi5jb20vdW5pLWt1L3Jvb3Rcblx0XHRVbmlLdVJvb3QoKSxcblx0XHQvLyBodHRwczovL3VuaS1lY2hhcnRzLnhpYW9oZS5pbmtcblx0XHRVbmlFY2hhcnRzKCksXG5cdFx0Ly8gaHR0cHM6Ly91bmktaGVscGVyLmNuL3BsdWdpbi11bmlcblx0XHRVbmkoKSxcblx0XHQvLyBodHRwczovL2dpdGh1Yi5jb20vdW5pLWt1L2J1bmRsZS1vcHRpbWl6ZXJcblx0XHRPcHRpbWl6YXRpb24oe1xuXHRcdFx0ZW5hYmxlOiBpc01wV2VpeGluLFxuXHRcdFx0bG9nZ2VyOiBmYWxzZSxcblx0XHR9KSxcblx0XHQvLyBodHRwczovL2dpdGh1Yi5jb20vYW50ZnUvdW5wbHVnaW4tYXV0by1pbXBvcnRcblx0XHRBdXRvSW1wb3J0KHtcblx0XHRcdGltcG9ydHM6IFtcblx0XHRcdFx0XCJ2dWVcIixcblx0XHRcdFx0XCJAdnVldXNlL2NvcmVcIixcblx0XHRcdFx0XCJwaW5pYVwiLFxuXHRcdFx0XHRcInVuaS1hcHBcIixcblx0XHRcdFx0e1xuXHRcdFx0XHRcdGZyb206IFwiQHdvdC11aS9yb3V0ZXJcIixcblx0XHRcdFx0XHRpbXBvcnRzOiBbXCJjcmVhdGVSb3V0ZXJcIiwgXCJ1c2VSb3V0ZXJcIiwgXCJ1c2VSb3V0ZVwiXSxcblx0XHRcdFx0fSxcblx0XHRcdFx0e1xuXHRcdFx0XHRcdGZyb206IFwid290LWRlc2lnbi11bmlcIixcblx0XHRcdFx0XHRpbXBvcnRzOiBbXCJ1c2VUb2FzdFwiLCBcInVzZU1lc3NhZ2VcIiwgXCJ1c2VOb3RpZnlcIiwgXCJDb21tb25VdGlsXCJdLFxuXHRcdFx0XHR9LFxuXHRcdFx0XHR7XG5cdFx0XHRcdFx0ZnJvbTogXCJhbG92YS9jbGllbnRcIixcblx0XHRcdFx0XHRpbXBvcnRzOiBbXCJ1c2VQYWdpbmF0aW9uXCIsIFwidXNlUmVxdWVzdFwiXSxcblx0XHRcdFx0fSxcblx0XHRcdF0sXG5cdFx0XHRkdHM6IFwic3JjL2F1dG8taW1wb3J0cy5kLnRzXCIsXG5cdFx0XHRkaXJzOiBbXCJzcmMvY29tcG9zYWJsZXNcIiwgXCJzcmMvc3RvcmVcIiwgXCJzcmMvdXRpbHNcIiwgXCJzcmMvYXBpXCJdLFxuXHRcdFx0dnVlVGVtcGxhdGU6IHRydWUsXG5cdFx0fSksXG5cdFx0Ly8gaHR0cHM6Ly9naXRodWIuY29tL2FudGZ1L3Vub2Nzc1xuXHRcdC8vIHNlZSB1bm9jc3MuY29uZmlnLnRzIGZvciBjb25maWdcblx0XHRVbm9DU1MoKSxcblx0XSxcbn0pO1xuIl0sCiAgIm1hcHBpbmdzIjogIjtBQUEwYSxPQUFPLGFBQWE7QUFDOWIsT0FBTyxTQUFTO0FBQ2hCLFNBQVMsa0JBQWtCO0FBQzNCLE9BQU8seUJBQXlCO0FBQ2hDLFNBQVMsbUJBQW1CO0FBQzVCLE9BQU8sc0JBQXNCO0FBQzdCLE9BQU8sdUJBQXVCO0FBQzlCLE9BQU8sb0JBQW9CO0FBQzNCLE9BQU8sa0JBQWtCO0FBQ3pCLE9BQU8sZUFBZTtBQUN0QixTQUFTLDBCQUEwQjtBQUNuQyxTQUFTLGtCQUFrQjtBQUMzQixPQUFPLFlBQVk7QUFDbkIsT0FBTyxnQkFBZ0I7QUFDdkIsU0FBUyxvQkFBb0I7QUFFN0IsSUFBTyxzQkFBUSxhQUFhO0FBQUEsRUFDM0IsTUFBTTtBQUFBLEVBQ04sY0FBYztBQUFBLElBQ2IsU0FBUyxRQUFRLElBQUksYUFBYSxnQkFBZ0IsQ0FBQyxrQkFBa0IsYUFBYSxJQUFJLENBQUM7QUFBQSxFQUN4RjtBQUFBLEVBQ0EsU0FBUztBQUFBO0FBQUEsSUFFUixrQkFBa0I7QUFBQTtBQUFBLElBRWxCLGVBQWU7QUFBQSxNQUNkLEtBQUs7QUFBQSxNQUNMLGFBQWEsQ0FBQyxjQUFjO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQSxNQUs1QixTQUFTLENBQUMsc0JBQXNCO0FBQUEsSUFDakMsQ0FBQztBQUFBO0FBQUEsSUFFRCxpQkFBaUI7QUFBQTtBQUFBLElBRWpCLG9CQUFvQjtBQUFBLE1BQ25CLFdBQVcsQ0FBQyxZQUFZLEdBQUcsbUJBQW1CLENBQUM7QUFBQSxNQUMvQyxLQUFLO0FBQUEsTUFDTCxNQUFNLENBQUMsa0JBQWtCLGNBQWM7QUFBQSxNQUN2QyxzQkFBc0I7QUFBQSxJQUN2QixDQUFDO0FBQUE7QUFBQSxJQUVELFVBQVU7QUFBQTtBQUFBLElBRVYsV0FBVztBQUFBO0FBQUEsSUFFWCxJQUFJO0FBQUE7QUFBQSxJQUVKLGFBQWE7QUFBQSxNQUNaLFFBQVE7QUFBQSxNQUNSLFFBQVE7QUFBQSxJQUNULENBQUM7QUFBQTtBQUFBLElBRUQsV0FBVztBQUFBLE1BQ1YsU0FBUztBQUFBLFFBQ1I7QUFBQSxRQUNBO0FBQUEsUUFDQTtBQUFBLFFBQ0E7QUFBQSxRQUNBO0FBQUEsVUFDQyxNQUFNO0FBQUEsVUFDTixTQUFTLENBQUMsZ0JBQWdCLGFBQWEsVUFBVTtBQUFBLFFBQ2xEO0FBQUEsUUFDQTtBQUFBLFVBQ0MsTUFBTTtBQUFBLFVBQ04sU0FBUyxDQUFDLFlBQVksY0FBYyxhQUFhLFlBQVk7QUFBQSxRQUM5RDtBQUFBLFFBQ0E7QUFBQSxVQUNDLE1BQU07QUFBQSxVQUNOLFNBQVMsQ0FBQyxpQkFBaUIsWUFBWTtBQUFBLFFBQ3hDO0FBQUEsTUFDRDtBQUFBLE1BQ0EsS0FBSztBQUFBLE1BQ0wsTUFBTSxDQUFDLG1CQUFtQixhQUFhLGFBQWEsU0FBUztBQUFBLE1BQzdELGFBQWE7QUFBQSxJQUNkLENBQUM7QUFBQTtBQUFBO0FBQUEsSUFHRCxPQUFPO0FBQUEsRUFDUjtBQUNELENBQUM7IiwKICAibmFtZXMiOiBbXQp9Cg==
