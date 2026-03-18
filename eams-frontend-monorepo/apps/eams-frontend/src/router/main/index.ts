import type { RouteRecordRawArray } from '@/types/Route'
import { useRoute, type RouteRecordRaw } from 'vue-router'
import { defineComponent, h } from 'vue'
import { eamsNavItems } from '@/components/mynav/nav-data'
import type { EamsNavItem } from '@/components/mynav/types'

const routes = [
	{
		path: '/home',
		name: 'Home',
		redirect: { name: 'Dashboard' },
		component: () => import('@/views/HomeView.vue'),
		children: [
			{
				path: '/dashboard',
				name: 'Dashboard',
				component: () => import('@/views/dashboard/Dashboard.vue')
			}
		] as RouteRecordRaw[]
	}
]

const NavPlaceholder = defineComponent({
	name: 'NavPlaceholder',
	setup() {
		const route = useRoute()
		return () =>
			h(
				'div',
				{
					style: {
						background: '#ffffff',
						borderRadius: '6px',
						margin: '12px',
						padding: '16px'
					}
				},
				[
					h('div', { style: { fontSize: '18px', fontWeight: '600', marginBottom: '10px' } }, [
						String(route.meta.label ?? route.path)
					]),
					h('div', { style: { color: '#666' } }, [`当前路由：${route.path}`])
				]
			)
	}
})

function collectNavRoutes(items: EamsNavItem[]): RouteRecordRaw[] {
	const res: RouteRecordRaw[] = []
	for (const group of items) {
		if (group.path) {
			res.push({
				path: group.path,
				name: `Nav_${group.key}`,
				meta: { label: group.label },
				component: NavPlaceholder
			})
		}
		for (const child of group.children ?? []) {
			res.push({
				path: child.path,
				name: `Nav_${child.key}`,
				meta: { label: child.label },
				component: NavPlaceholder
			})
		}
	}
	return res
}

// 读取子目录下面菜单设置为二级路由
const secondRouter = import.meta.glob<RouteRecordRawArray>('./**/index.ts', { eager: true })
for (const path in secondRouter) {
	routes[0].children.push(...secondRouter[path].default)
}

routes[0].children.push(...collectNavRoutes(eamsNavItems))

export default routes
