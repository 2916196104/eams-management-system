/**
 * 预约审核状态枚举
 */
export const APPOINTMENT_STATE = {
  /** 待审核 */
  PENDING: 0,
  /** 已确认 */
  CONFIRMED: 1,
  /** 已取消 */
  CANCELLED: 2,
} as const;

export type AppointmentState = typeof APPOINTMENT_STATE[keyof typeof APPOINTMENT_STATE];

/**
 * 预约状态映射
 */
export const APPOINTMENT_STATE_MAP: Record<AppointmentState, string> = {
  [APPOINTMENT_STATE.PENDING]: '待审核',
  [APPOINTMENT_STATE.CONFIRMED]: '已确认',
  [APPOINTMENT_STATE.CANCELLED]: '已取消',
};

/**
 * 预约状态标签类型
 */
export const APPOINTMENT_STATE_TYPE_MAP: Record<AppointmentState, string> = {
  [APPOINTMENT_STATE.PENDING]: 'warning',
  [APPOINTMENT_STATE.CONFIRMED]: 'success',
  [APPOINTMENT_STATE.CANCELLED]: 'info',
};