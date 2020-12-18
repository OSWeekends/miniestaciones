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
import AuthService from '@/services/AuthService';
export default {
  data() {
    return {
      user: {
        uid: '',
        email: '',
        displayName: '',
        photoURL: '',
        providerData: [{ providerId: '' }]
      },
      items: [
        { label: 'Profile', icon: 'pi pi-fw pi-user', to: '/profile' },
        // { label: 'Login', icon: 'pi pi-fw pi-unlock', to: '/login' },
        { label: 'About', icon: 'pi pi-fw pi-book', to: '/about' },
        {
          label: 'Logout',
          icon: 'pi pi-fw pi-power-off',
          command: () => this.logOut()
        }
      ]
    };
  },
  created() {
    this.user = AuthService.currentUser;
  },
  methods: {
    logOut() {
      AuthService.logOut()
        .then(() => {
          this.$router.push({ name: 'Login' });
        })
        .catch(err => {
          console.log(err);
        });
    }
  }
};
</script>
