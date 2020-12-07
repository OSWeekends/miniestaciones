<template>
  <Panel header="Dashboard" class="p-shadow-3">
    <div class="p-grid">
      <Dropdown
        v-model="selectedDBName"
        @change="selectDBNameHandler"
        :options="DBNames"
        placeholder="Seleciona un dispositivo"
        class="p-col-1 p-m-2"
      />
      <Fieldset :legend="selectedDBName" v-if="selectedDBName" class="p-col-12">
        <div class="p-grid">
          <Card class="p-col-5 p-m-1">
            <template #content class="p-d-flex p-flex-column p-flex-md-row">
              <LineRTChart title="Temperatura (ªC)" :values="dataTemp"></LineRTChart>
            </template>
          </Card>
          <Card class="p-col-5 p-m-1">
            <template #content class="p-d-flex p-flex-column p-flex-md-row">
              <LineRTChart title="Humedad (% relativo)" :values="dataHum"></LineRTChart>
            </template>
          </Card>
        </div>
      </Fieldset>
    </div>
  </Panel>
</template>

<script>
import LineRTChart from '@/components/LineRTChart';
import DataService from '@/services/DataService';

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
      DBNames: [],
      selectedDBName: null,
    };
  },
  created() {
    this.DBNames = DataService.getDevices();
  },
  methods: {
    selectDBNameHandler: function(ev) {
      DataService.setDevice(ev.value);
      this.fetchInitialData();
    },
    fetchInitialData: function() {
      DataService.getAll(undefined, 10)
        .once('value')
        .then(snapshot => {
          const data = snapshot.val();
          const mapValues = this.assignValues(data, ['temp', 'hum']);
          this.dataTemp = mapValues.get('temp');
          this.dataHum = mapValues.get('hum');
        });
      this.subscribeRemoteData();
    },
    subscribeRemoteData: function() {
      // Only retrive last value for refresh data chart
      DataService.getAll(undefined, 1).on(
        'value',
        snapshot => {
          const data = snapshot.val();
          console.log('newData', data);
          const mapValues = this.assignValues(data, ['temp', 'hum']);
          const temp = mapValues.get('temp');
          const hum = mapValues.get('hum');
          let newArrTmp = this.slidingData(this.dataTemp);
          let newArrHum = this.slidingData(this.dataHum);
          // Format: [[date1, value1], [date2, value2], ...]
          this.dataTemp = [...newArrTmp, ...temp];
          this.dataHum = [...newArrHum, ...hum];
          console.log('newDataTemp', this.dataTemp);
          console.log('newDataHum', this.dataHum);
        },
        errorObject => {
          console.log('The read failed: ' + errorObject.code);
        },
      );
    },
    slidingData: (data, slideWindow = 1) => {
      return data.slice(slideWindow);
    },
    assignValues: (data, properties) => {
      // Initialize map
      const propertiesMap = new Map();
      properties.forEach(p => {
        propertiesMap.set(p, []);
      });
      Object.values(data).forEach(element => {
        // Format: [[date1, value1], [date2, value2], ...]
        const date = new Date(element.timestamp * 1000);
        properties.forEach(p => {
          const currentList = propertiesMap.get(p);
          propertiesMap.set(p, [...currentList, [date, element[p]]]);
        });
        // Other format handled by chart
        // const formatDate = date.toLocaleString('es', { timeZone: 'UTC' })
        // data1.push({ x: formatDate, y: element.temp });
      });
      return propertiesMap;
    },
  },
};
</script>
