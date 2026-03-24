package com.zeroone.star.project.j8.stumanager;

import cn.hutool.db.PageResult;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.UserAccountDTO;
import com.zeroone.star.project.dto.j8.stumanager.UserPasswordDTO;
import com.zeroone.star.project.query.j8.stumanager.UserAccountQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.UserAccountVO;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;

import javax.validation.Valid;

/**
 * 家长账号
 */
public interface ParentAccountApis {
    /**
     * 获取账号列表
     *
     * @param query 查询条件
     * @return 账号列表分页数据
     */
    @ApiOperation(value = "获取账号列表", notes = "分页查询学员家长账号列表，支持按姓名、手机号、状态等条件筛选")
    @GetMapping("/list")
    JsonVO<PageDTO<UserAccountVO>> getAccountList(UserAccountQuery query);

//    /**
//     * 获取账号详情
//     *
//     * @param id 用户ID
//     * @return 账号详情
//     */
//    @ApiOperation(value = "获取账号详情", notes = "根据用户ID查询账号详细信息")
//    @GetMapping("/{id}")
//    JsonVO<UserAccountVO> getAccountDetail(
//            @ApiParam(value = "用户ID", required = true, example = "1")
//            @PathVariable("id") Long id);

    /**
     * 修改账号
     *
     * @param dto 账号信息
     * @return 修改结果
     */
    @ApiOperation(value = "修改账号", notes = "修改学员家长账号基本信息，包括姓名、手机号、邮箱等")
    @PutMapping("/update")
    JsonVO<Boolean> updateAccount(@Valid @RequestBody UserAccountDTO dto);

    /**
     * 修改密码
     *
     * @param dto 密码信息
     * @return 修改结果
     */
    @ApiOperation(value = "修改密码", notes = "修改学员家长账号密码，需验证原密码")
    @PutMapping("/password")
    JsonVO<Boolean> updatePassword(@Valid @RequestBody UserPasswordDTO dto);
}
