<template>
  <div class="f1-table">
    <el-table
      :data="F1TableConfig.tableList"
      v-bind="F1TableConfig.tableProperties"
      style="width: 100%"
    >
      <template v-for="item in F1TableConfig.tableList" :key="item.prop">
        <template v-if="item.type === 'index'">
          <el-table-column align="center" v-bind="item" />
        </template>
        <template v-else-if="item.type === 'selection'">
          <el-table-column align="center" v-bind="item" />
        </template>
        <!-- 拓展用插槽 -->
        <template v-else-if="item.type === 'custom'">
          <el-table-column align="center" v-bind="item">
            <template #default="scope">
              <slot :name="item.slotName" v-bind="scope"></slot>
            </template>
          </el-table-column>
        </template>
        <template v-else>
          <el-table-column align="center" v-bind="item" />
        </template>
      </template>
    </el-table>
    <!-- 分页功能 -->
    <div class="pagination">
      <el-pagination
        v-model:current-page="currentPage"
        v-model:page-size="pageSize"
        :page-sizes="[10, 20, 50, 100]"
        size="small"
        layout="total, sizes, prev, pager, next, jumper"
        :total="10"
      />
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { F1TableConfig } from './tableTest'

const pageSize = ref(10)
const currentPage = ref(1)
</script>

<style scoped>
.pagination {
  background: #fff;
}
</style>
