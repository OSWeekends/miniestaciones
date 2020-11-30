<template>
  <Panel header="Bienvenid@" class="p-shadow-3">
    <p>
      Proyecto Miniestaciones OSW
    </p>
    <img alt="Vue logo" src="../assets/logo.png" />
    <p>
      Please, log in into dashboard
    </p>
  </Panel>
</template>

<script>
import { Auth } from '@/firebase';

export default {
  name: 'Home',
  created() {
    Auth.onAuthStateChanged(user => {
      if (user) {
        this.user = user;
        this.$router.push('/dashboard');
      }
    });
  },
};
</script>
