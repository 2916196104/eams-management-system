package com.zeroone.star.education.service;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.education.entity.Staff;
import com.zeroone.star.education.mapper.StaffMapper;
import org.springframework.stereotype.Service;

@Service
public class StaffServiceImpl extends ServiceImpl<StaffMapper, Staff> implements StaffService{
}
