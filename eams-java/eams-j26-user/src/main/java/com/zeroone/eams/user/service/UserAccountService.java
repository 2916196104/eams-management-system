package com.zeroone.eams.user.service;

import com.zeroone.eams.common.core.page.PageResult;
import com.zeroone.eams.domain.j26.user.dto.UserAccountDTO;
import com.zeroone.eams.domain.j26.user.query.UserAccountQuery;
import com.zeroone.eams.domain.j26.user.vo.UserAccountVO;

/**
 * 学员家长账号Service接口
 *
 * @author j26
 */
public interface UserAccountService {

    /**
     * 获取账号列表
     *
     * @param query 查询条件
     * @return 分页结果
     */
    PageResult<UserAccountVO> getAccountList(UserAccountQuery query);

    /**
     * 获取账号详情
     *
     * @param id 用户ID
     * @return 账号详情
     */
    UserAccountVO getAccountDetail(Long id);

    /**
     * 修改账号
     *
     * @param dto 账号信息
     * @return 是否成功
     */
    boolean updateAccount(UserAccountDTO dto);

    /**
     * 检查手机号是否重复
     *
     * @param userId 用户ID（排除自身）
     * @param mobile 手机号
     * @return true-重复，false-不重复
     */
    boolean checkMobileDuplicate(Long userId, String mobile);

    /**
     * 验证原密码
     *
     * @param userId      用户ID
     * @param oldPassword 原密码
     * @return true-正确，false-错误
     */
    boolean verifyOldPassword(Long userId, String oldPassword);

    /**
     * 修改密码
     *
     * @param userId      用户ID
     * @param newPassword 新密码
     * @return 是否成功
     */
    boolean updatePassword(Long userId, String newPassword);
}
