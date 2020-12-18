<template>
  <apexchart
    type="line"
    height="350"
    ref="chart"
    :options="chartOptions"
    :series="series"
  ></apexchart>
</template>

<script>
import VueApexCharts from 'vue3-apexcharts';

import ChartOptions from './chartRTConfig';

export default {
  name: 'LineRTChart',
  components: {
    apexchart: VueApexCharts,
  },
  props: {
    title: String,
    values: Object,
  },
  data: () => {
    return {
      chartOptions: ChartOptions,
      series: [],
    };
  },
  watch: {
    values: function() {
      this.updateSeriesLine();
    },
  },
  created() {
    const customConfig = {
      id: 'chart' + this.title,
      title: { text: this.title },
    };
    this.chartOptions = Object.assign({}, ChartOptions, customConfig);
  },
  beforeUpdate() {
    this.updateSeriesLine();
  },
  methods: {
    updateSeriesLine() {
      const me = this;
      me.$refs.chart.chart.updateSeries([
        {
          data: this.values,
        },
      ]);
    },
  },
};
</script>

<style scoped></style>
