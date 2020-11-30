<template>
  <Menubar :model="items">
    <template #start>
      <router-link to="/" class="brand-logo" tag="a">
        <img alt="logo" src="../assets/logo.svg" height="40" class="p-mr-2" />
      </router-link>
    </template>
  </Menubar>
</template>

<script>
import { Auth } from '@/firebase';
export default {
  data() {
    return {
      user: null,
      items: [
        { label: 'Profile', icon: 'pi pi-fw pi-user', to: '/profile' },
        { label: 'Login', icon: 'pi pi-fw pi-unlock', to: '/login' },
        {
          label: 'Logout',
          icon: 'pi pi-fw pi-power-off',
          command: () => this.logOut(),
        },
        { label: 'About', icon: 'pi pi-fw pi-book', to: '/about' },
      ],
    };
  },
  created() {
    Auth.onAuthStateChanged(user => {
      this.user = user;
    });
  },
  methods: {
    logOut(e) {
      e.stopPropagation();
      Auth.signOut().then(() => {
        this.$router.push({ name: 'Login' });
      });
    },
  },
};
</script>
