import { defineStore } from 'pinia'
import type { TabRoute } from '@/types/Route'

//FIXME 如果主界面首页路径不是/dashboard则需要修改此变量的值
const INDEX_PATH = '/dashboard'

export const useTabStore = defineStore('tab', {
  state: () => ({
    /**  已经打开的标签页 */
    tabs: [] as Array<TabRoute>,
    /** 当前激活的标签页 */
    activeIndex: INDEX_PATH,
    /** 首页的标签路径 */
    indexPath: INDEX_PATH
  }),
  getters: {
    /** 获取已经打开的标签页 */
    getTabs: (state) => state.tabs,
    /** 获取当前激活的标签页 */
    getActiveIndex: (state) => state.activeIndex,
    /** 获取指定标签页索引值 */
    getTabIndex: (state) => (path: string) => {
      return state.tabs.findIndex((item) => item.path === path)
    }
  },
  actions: {
    /** 添加标签页 */
    addTab(data: TabRoute) {
      // 首页不添加
      if (data.path === this.indexPath) return
      else this.tabs.push(data)
    },
    /** 删除标签页 */
    remTab(path: string) {
      const index = this.getTabIndex(path)
      if (index == -1) return
      this.tabs.splice(index, 1)
    },
    /** 删除指定标签页前面的标签页 */
    remBeforeTab(path: string) {
      if (path === this.indexPath) return
      const index = this.getTabIndex(path)
      if (index == -1) return
      this.tabs.splice(0, index)
    },
    /** 删除指定标签页后面的标签页 */
    remAfterTab(path: string) {
      if (path === this.indexPath) {
        this.reset()
        return
      }
      const index = this.getTabIndex(path)
      if (index == -1) return
      this.tabs.splice(index + 1)
    },
    /** 设置当前激活的标签页 */
    setActiveIndex(index: string) {
      this.activeIndex = index
    },
    /** 重置数据 */
    reset() {
      this.tabs = []
      this.activeIndex = INDEX_PATH
    }
  }
})
