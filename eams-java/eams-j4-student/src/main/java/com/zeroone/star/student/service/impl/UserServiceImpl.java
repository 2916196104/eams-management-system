package com.zeroone.star.student.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.j4.student.UserQueryDTO;
import com.zeroone.star.project.dto.j4.student.UserUpdateDTO;
import com.zeroone.star.project.dto.j4.student.UserUpdatePwdDTO;
import com.zeroone.star.project.vo.j4.student.UserVO;
import com.zeroone.star.student.entity.User;
import com.zeroone.star.student.mapper.UserMapper;
import com.zeroone.star.student.service.IUserService;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

/**
 * <p>
 * 家长端用户表 服务实现类
 * </p>
 *
 * @author zrt
 * @since 2026-03-16
 */
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements IUserService {

    /**
     * 1. 获取账号列表（条件+分页）
     */
    @Override
    public Page<UserVO> listUser(UserQueryDTO query) {
        // 1. 构建分页条件
        Page<User> page = new Page<>(query.getPageNum(), query.getPageSize());

        // 2. 构建查询条件
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        // 姓名模糊查询
        if (StringUtils.hasText(query.getName())) {
            wrapper.like(User::getName, query.getName());
        }
        // 手机号模糊查询
        if (StringUtils.hasText(query.getMobile())) {
            wrapper.like(User::getMobile, query.getMobile());
        }
        // 状态精确查询
        if (query.getState() != null) {
            wrapper.eq(User::getState, query.getState());
        }
        // 学校ID精确查询
        if (query.getSchoolId() != null) {
            wrapper.eq(User::getSchoolId, query.getSchoolId());
        }
        // 按创建时间倒序
        wrapper.orderByDesc(User::getAddTime);

        // 3. 分页查询
        long count = this.count(wrapper);
        List<User> records = this.list(wrapper);
        Page<User> userPage = new Page<>(page.getCurrent(), page.getSize(), count);
        userPage.setRecords(records);

        // 4. 转换为VO
        Page<UserVO> voPage = new Page<>(userPage.getCurrent(), userPage.getSize(), userPage.getTotal());
        voPage.setRecords(
                userPage.getRecords().stream()
                        .map(user -> BeanUtil.copyProperties(user, UserVO.class))
                        .collect(Collectors.toList())  // JDK8 正确写法
        );

        return voPage;
    }

    /**
     * 2. 修改账号信息
     */
    @Override
    public void updateUser(UserUpdateDTO dto) {
        // 1. 校验账号是否存在
        User user = this.getById(dto.getId());
        if (user == null) {
            throw new RuntimeException("账号不存在");
        }

        // 2. 校验手机号是否被其他账号占用
        if (!user.getMobile().equals(dto.getMobile())) {
            LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
            wrapper.eq(User::getMobile, dto.getMobile());
            wrapper.ne(User::getId, dto.getId());
            if (this.count(wrapper) > 0) {
                throw new RuntimeException("手机号已被其他账号使用");
            }
        }

        // 3. 更新信息
        BeanUtil.copyProperties(dto, user);
        this.updateById(user);
    }

    /**
     * 3. 修改密码
     */
    @Override
    public void updatePassword(UserUpdatePwdDTO dto) {
        // 1. 校验账号是否存在
        User user = this.getById(dto.getId());
        if (user == null) {
            throw new RuntimeException("账号不存在");
        }

        // 2. 校验两次新密码是否一致
        if (!dto.getNewPassword().equals(dto.getConfirmPassword())) {
            throw new RuntimeException("两次输入的新密码不一致");
        }

        // 3. 校验旧密码是否正确（这里用明文对比，实际项目建议用MD5加密）
        if (!user.getPassword().equals(dto.getOldPassword())) {
            throw new RuntimeException("旧密码错误");
        }

        // 4. 更新密码
        user.setPassword(dto.getNewPassword());
        this.updateById(user);
    }
}