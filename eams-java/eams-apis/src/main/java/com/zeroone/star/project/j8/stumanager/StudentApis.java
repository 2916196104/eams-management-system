package com.zeroone.star.project.j8.stumanager;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.project.dto.StudentAvatarDTO;
import com.zeroone.star.project.query.StudentQuery;
import com.zeroone.star.project.vo.StudentVO;

public interface StudentApis {

//    获取学员汇总列表
    IPage<StudentVO> getStudentList(StudentQuery query);

//    获取学员详情
    StudentVO getStudentDetail(Long studentId);

//    修改学员头像
    Boolean updateStudentAvatar(StudentAvatarDTO dto);
}