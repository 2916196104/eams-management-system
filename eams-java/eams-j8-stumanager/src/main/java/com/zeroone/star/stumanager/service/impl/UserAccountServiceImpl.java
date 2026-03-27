package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.UserAccountDTO;
import com.zeroone.star.project.query.j8.stumanager.UserAccountQuery;
import com.zeroone.star.project.vo.j8.stumanager.UserAccountVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.User;
import com.zeroone.star.stumanager.mapper.StudentMapper;
import com.zeroone.star.stumanager.mapper.UserMapper;
import com.zeroone.star.stumanager.service.UserAccountService;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.BeanUtils;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;

import java.util.List;
import java.util.stream.Collectors;

/**
 * 学员家长账号Service实现
 *
 * @author j26
 */
@Service
@RequiredArgsConstructor
public class UserAccountServiceImpl implements UserAccountService {

    private final UserMapper userMapper;
    private final StudentMapper studentMapper;
    private final BCryptPasswordEncoder passwordEncoder;

    @Override
    public PageDTO<UserAccountVO> getAccountList(UserAccountQuery query) {
        Page<User> page = new Page<>(query.getPageNum(), query.getPageSize());

        // 构建查询条件，指定需要的字段，避免select *
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        wrapper.select(User::getId, User::getName, User::getMobile, User::getEmail,
                       User::getState, User::getLoginTimes, User::getLatestLoginTime,
                       User::getLatestLoginIp, User::getAddTime, User::getRemark,
                       User::getSchoolId, User::getOrgId)
               .like(StringUtils.hasText(query.getName()), User::getName, query.getName())
               .like(StringUtils.hasText(query.getMobile()), User::getMobile, query.getMobile())
               .eq(query.getState() != null, User::getState, query.getState())
               .eq(query.getSchoolId() != null, User::getSchoolId, query.getSchoolId())
               .eq(query.getOrgId() != null, User::getOrgId, query.getOrgId())
               .orderByDesc(User::getAddTime);

        Page<User> userPage = userMapper.selectPage(page, wrapper);

        List<UserAccountVO> voList = userPage.getRecords().stream()
                .map(this::convertToVO)
                .collect(Collectors.toList());

        PageDTO<UserAccountVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(page.getCurrent());
        pageDTO.setPageSize(page.getSize());
        pageDTO.setTotal(userPage.getTotal());
        pageDTO.setPages(userPage.getPages());
        pageDTO.setRows(voList);

        return pageDTO;
    }

    @Override
    public UserAccountVO getAccountDetail(Long id) {
        User user = userMapper.selectById(id);
        if (user == null) {
            return null;
        }
        return convertToVO(user);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean updateAccount(UserAccountDTO dto) {
        User user = new User();
        BeanUtils.copyProperties(dto, user);
        return userMapper.updateById(user) > 0;
    }

    @Override
    public boolean checkMobileDuplicate(Long userId, String mobile) {
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(User::getMobile, mobile)
               .ne(User::getId, userId);
        return userMapper.selectCount(wrapper) > 0;
    }

    @Override
    public boolean verifyOldPassword(Long userId, String oldPassword) {
        // 只查询密码字段，避免select *
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        wrapper.select(User::getPassword)
               .eq(User::getId, userId);
        User user = userMapper.selectOne(wrapper);
        if (user == null || user.getPassword() == null) {
            return false;
        }
        return passwordEncoder.matches(oldPassword, user.getPassword());
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean updatePassword(Long userId, String newPassword) {
        User user = new User();
        user.setId(userId);
        user.setPassword(passwordEncoder.encode(newPassword));
        return userMapper.updateById(user) > 0;
    }

    /**
     * 转换为VO对象
     */
    private UserAccountVO convertToVO(User user) {
        UserAccountVO vo = new UserAccountVO();
        BeanUtils.copyProperties(user, vo);

        // 查询关联学生，只选择需要的字段，避免select *
        LambdaQueryWrapper<Student> studentWrapper = new LambdaQueryWrapper<>();
        studentWrapper.select(Student::getId, Student::getName, Student::getFamilyRel, Student::getAsDefault)
                      .eq(Student::getUserId, user.getId())
                      .eq(Student::getDeleted, 0);
        List<Student> students = studentMapper.selectList(studentWrapper);

        List<UserAccountVO.StudentSimpleVO> studentVOList = students.stream().map(s -> {
            UserAccountVO.StudentSimpleVO studentVO = new UserAccountVO.StudentSimpleVO();
            studentVO.setId(s.getId());
            studentVO.setName(s.getName());
            studentVO.setFamilyRel(s.getFamilyRel());
            studentVO.setAsDefault(s.getAsDefault() == Boolean.TRUE);
            return studentVO;
        }).collect(Collectors.toList());

        vo.setStudents(studentVOList);
        return vo;
    }
}
