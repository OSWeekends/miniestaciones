<template>
  <div class="app-container">
    <navigation class="p-m-2"></navigation>
    <div class="p-grid p-formgrid p-fluid">
      <div class="p-col p-m-2">
        <router-view />
      </div>
    </div>
  </div>
</template>

<script>
import navigation from '@/components/NavBar';
export default {
  name: 'App',
  components: {
    navigation,
  },
};
</script>

<style scoped>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
