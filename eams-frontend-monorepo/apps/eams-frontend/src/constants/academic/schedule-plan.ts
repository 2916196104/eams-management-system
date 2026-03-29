/**
 * 排课计划状态枚举
 */
export const PLAN_STATE = {
  PENDING: 0,
  GENERATED: 1,
  CONFLICT: 2,
} as const;

export type PlanState = typeof PLAN_STATE[keyof typeof PLAN_STATE];

export const PLAN_STATE_MAP: Record<PlanState, string> = {
  [PLAN_STATE.PENDING]: '待生成',
  [PLAN_STATE.GENERATED]: '已生成',
  [PLAN_STATE.CONFLICT]: '冲突',
};

export const PLAN_STATE_TYPE_MAP: Record<PlanState, string> = {
  [PLAN_STATE.PENDING]: 'info',
  [PLAN_STATE.GENERATED]: 'success',
  [PLAN_STATE.CONFLICT]: 'danger',
};

export const WEEK_MAP: Record<string, string> = {
  '1': '周一',
  '2': '周二',
  '3': '周三',
  '4': '周四',
  '5': '周五',
  '6': '周六',
  '7': '周日',
};