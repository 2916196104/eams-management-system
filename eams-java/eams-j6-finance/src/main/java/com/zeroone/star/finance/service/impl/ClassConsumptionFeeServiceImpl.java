package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.finance.service.ClassConsumptionFeeService;
import com.zeroone.star.finance.mapper.ClassConsumptionFeeMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.ClassConsumptionFeeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.ClassConsumptionFeeVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ClassConsumptionFeeServiceImpl implements ClassConsumptionFeeService {

    @Autowired
    private ClassConsumptionFeeMapper classConsumptionFeeMapper;


    @Override
    public JsonVO<PageDTO<ClassConsumptionFeeVO>> listClassConsumptionFees(ClassConsumptionFeeQuery condition) {
        // 1. 使用 MyBatis-Plus 的分页插件进行分页查询
        Page<ClassConsumptionFeeVO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        // 2. 执行查询并获取分页结果
        Page<ClassConsumptionFeeVO> resultPage = classConsumptionFeeMapper.queryClassConsumptionFees(page, condition);

        // 3. 将分页结果转换为 PageDTO
        PageDTO<ClassConsumptionFeeVO> pageDTO = PageDTO.create(resultPage);

        // 4. 返回结果
        return JsonVO.success(pageDTO);
    }
}
