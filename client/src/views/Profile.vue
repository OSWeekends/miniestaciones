<template>
  <Panel header="Profile" class="p-shadow-3">
    <Card style="width: 25rem; margin-bottom: 2em">
      <template #header>
        <img alt="user avatar" :src="user.photoURL" />
      </template>
      <template #title>
        {{ user.displayName }}
      </template>
      <template #content>
        <p>
          name:
          <strong>{{ user.displayName }}</strong>
          <br />email:
          <strong>{{ user.email }}</strong>
          <br />uid:
          <strong>{{ user.uid }}</strong>
          <br />provider:
          <strong class="teal-text">{{
            user.providerData[0].providerId
          }}</strong>
        </p>
      </template>
    </Card>
  </Panel>
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
        providerData: [{ providerId: '' }],
      },
    };
  },
  created() {
    if (AuthService.currentUser) {
      this.user = AuthService.currentUser;
    }
  },
};
</script>
