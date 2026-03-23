package com.zeroone.eams.api.j26.user;

import com.zeroone.eams.common.core.domain.R;
import com.zeroone.eams.common.core.page.PageResult;
import com.zeroone.eams.domain.j26.user.dto.UserAccountDTO;
import com.zeroone.eams.domain.j26.user.dto.UserPasswordDTO;
import com.zeroone.eams.domain.j26.user.query.UserAccountQuery;
import com.zeroone.eams.domain.j26.user.vo.UserAccountVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

/**
 * 学员家长账号接口定义
 *
 * @author j26
 */
@Api(tags = "学员家长账号管理")
@RequestMapping("/user/account")
public interface UserAccountApi {

    /**
     * 获取账号列表
     *
     * @param query 查询条件
     * @return 账号列表分页数据
     */
    @ApiOperation(value = "获取账号列表", notes = "分页查询学员家长账号列表，支持按姓名、手机号、状态等条件筛选")
    @GetMapping("/list")
    R<PageResult<UserAccountVO>> getAccountList(UserAccountQuery query);

    /**
     * 获取账号详情
     *
     * @param id 用户ID
     * @return 账号详情
     */
    @ApiOperation(value = "获取账号详情", notes = "根据用户ID查询账号详细信息")
    @GetMapping("/{id}")
    R<UserAccountVO> getAccountDetail(
            @ApiParam(value = "用户ID", required = true, example = "1")
            @PathVariable("id") Long id);

    /**
     * 修改账号
     *
     * @param dto 账号信息
     * @return 修改结果
     */
    @ApiOperation(value = "修改账号", notes = "修改学员家长账号基本信息，包括姓名、手机号、邮箱等")
    @PutMapping("/update")
    R<Boolean> updateAccount(@Valid @RequestBody UserAccountDTO dto);

    /**
     * 修改密码
     *
     * @param dto 密码信息
     * @return 修改结果
     */
    @ApiOperation(value = "修改密码", notes = "修改学员家长账号密码，需验证原密码")
    @PutMapping("/password")
    R<Boolean> updatePassword(@Valid @RequestBody UserPasswordDTO dto);
}
