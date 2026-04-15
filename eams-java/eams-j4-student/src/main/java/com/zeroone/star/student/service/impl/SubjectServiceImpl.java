package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.student.entity.SubjectDO;
import com.zeroone.star.student.mapper.SubjectMapper;
import com.zeroone.star.student.service.ISubjectService;
import org.springframework.stereotype.Service;

@Service
public class SubjectServiceImpl extends ServiceImpl<SubjectMapper, SubjectDO> implements ISubjectService {
}
