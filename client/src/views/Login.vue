<template>
  <Panel header="Login">
    <section id="firebaseui-auth-container"></section>
  </Panel>
</template>

<script>
import { UI, uiConfig } from '@/firebase';

export default {
  name: 'Login',
  data() {
    return {};
  },
  mounted() {
    UI.start('#firebaseui-auth-container', uiConfig);
  },
};
</script>
