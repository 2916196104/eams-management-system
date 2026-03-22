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
    default List<StaffDO> queryPage(StaffQuery condition) {
        LambdaQueryWrapper<StaffDO> queryWrapper = new LambdaQueryWrapper<>();
        if (condition.getName() != null && !condition.getName().isEmpty()) {
            queryWrapper.like(StaffDO::getName, condition.getName());
        }
        if (condition.getId() != null) {
            queryWrapper.eq(StaffDO::getId, condition.getId());
        }
        if (condition.getAccount() != null) {
            queryWrapper.eq(StaffDO::getMobile, condition.getAccount());
        }
        if (condition.getStatue() != null) {
            queryWrapper.eq(StaffDO::getState, condition.getStatue());
        }
        return this.selectList(queryWrapper);
    }

    default StaffDO queryStaff(StaffQuery condition){
        LambdaQueryWrapper<StaffDO> queryWrapper = new LambdaQueryWrapper<>();
        if (condition.getId() != null) {
            queryWrapper.eq(StaffDO::getId, condition.getId());
        }
        queryWrapper.eq(StaffDO::getDeleted, 0);

        return this.selectOne(queryWrapper);
    };

    default Long saveStaff(StaffDTO condition){
        StaffDO staff = new StaffDO();
        BeanUtils.copyProperties(condition,staff);
        if (condition.getId() == null) {
            // 新增：调用 MP 的 insert 方法，会自动回填主键到 staffDO
            this.insert(staff);
            // 返回新生成的主键 id
            return staff.getId();
        }
            else{
                this.updateById(staff);
                return staff.getId();
            }
    }

   default Long  removeStaff(List<Long> ids){
       long result = this.deleteBatchIds(ids);
       return result;
   }

   default Long updateStaffStatus(StaffUpdateDTO condition){
        StaffDO staff = new StaffDO();
       List<Long> ids = condition.getIds();
       Integer status = condition.getStatus();
       BeanUtils.copyProperties(condition,staff);
       // 2. 构建更新条件
       LambdaUpdateWrapper<StaffDO> wrapper = Wrappers.lambdaUpdate();
       wrapper.in(StaffDO::getId, ids) // 批量匹配ID
               .set(StaffDO::getState, status); // 设置目标状态
       // 3. 执行批量更新
       int updateCount = this.update(new StaffDO(), wrapper);
       return (long)updateCount;
   }
}
