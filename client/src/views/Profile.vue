<template>
  <Panel header="Profile" class="p-shadow-3">
    <Card style="width: 25rem; margin-bottom: 2em">
      <template #header>
        <img :src="user.photoURL || 'https://upload.wikimedia.org/wikipedia/commons/thumb/9/96/Generic-person.svg/240px-Generic-person.svg.png'" />
      </template>
      <template #title>
        {{ user.displayName || user.email }}
      </template>
      <template #content>
        <p>
          name:
          <strong>{{ user.displayName || 'N/A' }}</strong>
          <br />email:
          <strong>{{ user.email }}</strong>
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
        providerData: [{ providerId: '' }]
      }
    };
  },
  created() {
    if (AuthService.currentUser) {
      this.user = AuthService.currentUser;
    }
  }
};
</script>
