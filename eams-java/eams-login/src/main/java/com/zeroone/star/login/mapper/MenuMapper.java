package com.zeroone.star.login.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.login.entity.Menu;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * Menu mapper.
 */
@Mapper
public interface MenuMapper extends BaseMapper<Menu> {

    /**
     * Query menus by role codes with a single SQL statement.
     *
     * @param roleCodes current user role codes
     * @return menu list
     */
    List<Menu> selectByRoleCodes(@Param("roleCodes") List<String> roleCodes);

    /**
     * Query ancestor menus by ids.
     *
     * @param menuIds ancestor menu ids
     * @return ancestor menu list
     */
    List<Menu> selectByIds(@Param("menuIds") List<Integer> menuIds);
}
