<template>
  <Menubar :model="items">
    <template #start>
      <router-link to="/" class="brand-logo" tag="a">
        <img alt="logo" src="../assets/osw.png" height="40" class="p-mr-2" />
      </router-link>
    </template>
  </Menubar>
</template>

<script>
import AuthService from '@/services/AuthService';
import router from '../router';

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
        { label: 'Dashboard', icon: 'pi pi-fw pi-chart-bar', to: '/dashboard' },
        { label: 'Profile', icon: 'pi pi-fw pi-user', to: '/profile' },
        { label: 'About', icon: 'pi pi-fw pi-book', to: '/about' },
        {
          label: 'Logout',
          icon: 'pi pi-fw pi-power-off',
          command: () => this.logout()
        }
      ]
    };
  },
  created() {
    this.user = AuthService.currentUser;
  },
  methods: {
    logout() {
      AuthService.logout()
        .then(() => {
          setTimeout(() => {
            router.push('/login');
          }, 0);
        })
        .catch(err => {
          console.log(err);
        });
    }
  }
};
</script>
