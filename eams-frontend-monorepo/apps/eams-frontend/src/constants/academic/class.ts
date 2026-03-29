/**
 * 班级状态枚举
 */
export const CLASS_STATUS = {
  /** 进行中 */
  ACTIVE: 0,
  /** 已结业 */
  FINISHED: 1,
} as const;

export type ClassStatus = typeof CLASS_STATUS[keyof typeof CLASS_STATUS];

/**
 * 班级状态映射
 */
export const CLASS_STATUS_MAP: Record<ClassStatus, string> = {
  [CLASS_STATUS.ACTIVE]: '进行中',
  [CLASS_STATUS.FINISHED]: '已结业',
};

/**
 * 班级状态标签类型
 */
export const CLASS_STATUS_TYPE_MAP: Record<ClassStatus, string> = {
  [CLASS_STATUS.ACTIVE]: 'success',
  [CLASS_STATUS.FINISHED]: 'info',
};