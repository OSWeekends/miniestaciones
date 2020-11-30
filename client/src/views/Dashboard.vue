<template>
  <Panel header="Dashboard" class="p-shadow-3">
    <div class="p-grid">
      <Card class="p-col-5 p-m-2">
        <template #content class="p-d-flex p-flex-column p-flex-md-row">
          <LineRTChart title="Temperatura" :data="dataTemp"></LineRTChart>
        </template>
      </Card>
      <Card class="p-col-5 p-m-2">
        <template #content class="p-d-flex p-flex-column p-flex-md-row">
          <LineRTChart title="Humedad" :data="dataHum"></LineRTChart>
        </template>
      </Card>
    </div>
  </Panel>
</template>

<script>
import { Auth } from '@/firebase';
import LineRTChart from '@/components/LineRTChart';

import DataService from '../services/DataService';

export default {
  name: 'Dashboard',
  components: {
    LineRTChart,
  },
  data() {
    return {
      user: null,
      dataTemp: [],
      dataHum: [],
    };
  },
  created() {
    Auth.onAuthStateChanged(user => {
      if (user) {
        this.user = user;
      } else {
        this.user = null;
      }
    });
  },
  mounted() {
    const fetcher = DataService.getAll()
      .orderByChild('timestamp')
      .limitToLast(10);

    fetcher.once('value').then(snapshot => {
      const data = snapshot.val();
      const tempList = [];
      const humList = [];
      Object.values(data).forEach(element => {
        const date = new Date(element.timestamp * 1000);
        tempList.push([date, element.temp]);
        humList.push([date, element.hum]);
        // const formatDate = date.toLocaleString('es', { timeZone: 'UTC' })
        // data1.push({ x: formatDate, y: element.temp });
      });
      this.dataTemp = tempList;
      this.dataHum = humList;
    });

    // fetcher.on('value').then(snapshot => {
    //   const data = snapshot.val();
    //   Object.values(data).forEach(element => {
    //     const date = new Date(element.timestamp * 1000);
    //     // const formatDate = date.toLocaleString('es', { timeZone: 'UTC' })
    //     // data1.push({ x: formatDate, y: element.temp });
    //     this.dataTemp.push([date, element.temp]);
    //     this.dataHum.push([date, element.hum]);
    //   });
    //   console.log(this.dataTemp);
    // });
  },
  methods: {},

  // intervals: () => {
  //   setTimeout(() => {
  //     chartRef.updateSeries(
  //       [
  //         {
  //           data: data1.slice(),
  //         },
  //       ],
  //       false,
  //       true,
  //     );
  //   }, 2000);
  //   window.setInterval(() => {
  //     getNewSeries(lastDate, this.temperature());

  //     console.log(data1);

  //     chartRef.updateSeries([
  //       {
  //         data: data1,
  //       },
  //     ]);
  //   }, 10000);

  //   // every 60 seconds, we reset the data to prevent memory leaks
  //   window.setInterval(() => {
  //     resetData();

  //     chartRef.updateSeries(
  //       [
  //         {
  //           data1,
  //         },
  //       ],
  //       false,
  //       true,
  //     );
  //   }, 60000);
  // },
};
</script>
