package com.zeroone.star.project.j1.org.staff.mapper;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.zeroone.star.project.DO.StaffDO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;

import com.zeroone.star.project.dto.j1.org.StaffUpdateDTO;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.BeanUtils;

import java.util.List;

@Mapper
public interface StaffMapper extends BaseMapper<StaffDO> {

}
