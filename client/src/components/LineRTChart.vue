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

// function getNewSeries(baseval, yrange) {
//   var newDate = baseval + 86400000;
//   lastDate = newDate;
//   data1.push({
//     x: newDate,
//     y: Math.floor(Math.random() * (yrange.max - yrange.min + 1)) + yrange.min,
//   });
//   // data2.push({
//   //   x: newDate,
//   //   y: Math.floor(Math.random() * (yrange.max - yrange.min + 1)) + yrange.min
//   // });
// }

// function resetData() {
//   data1 = data1.slice(data1.length - 10, data1.length);
//   // data2 = data2.slice(data2.length - 10, data2.length);
// }

function createDebounce() {
  let timeout = null;
  return function(fnc, delayMs) {
    clearTimeout(timeout);
    timeout = setTimeout(() => {
      fnc();
    }, delayMs || 500);
  };
}

export default {
  name: 'LineRTChart',
  components: {
    apexchart: VueApexCharts,
  },
  props: {
    title: String,
    data: Object,
  },
  // computed: {
  //   series() {
  //     return [
  //       {
  //         data: this.data,
  //       },
  //     ];
  //   },
  // },
  data() {
    return {
      chartOptions: ChartOptions,
      series: [],
    };
  },
  mounted() {
    const customConfig = {
      id: 'chart' + this.title,
      title: { text: this.title },
    };
    this.chartOptions = Object.assign({}, ChartOptions, customConfig);
    this.setDataLineChart();
  },
  methods: {
    setDataLineChart() {
      const ref = createDebounce();
      ref(this.updateSeriesLine, 1000);
    },
    updateSeriesLine() {
      const me = this;
      console.log();
      me.$refs.chart.chart.updateSeries([
        {
          data: this.data,
        },
      ]);
    },
  },
};
</script>

<style scoped></style>
