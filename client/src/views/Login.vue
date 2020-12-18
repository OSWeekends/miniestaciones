<template>
  <Card style="width: 24rem;" class="p-jc-center">
    <template #content>
      <div class="p-grid p-jc-center">
        <div class="p-field p-col-12">
          <label for="user">Usuario</label>
          <InputText id="user" type="text" v-model="email" />
        </div>
        <div class="p-field p-col-12">
          <label for="password">Contraseña</label>
          <InputText id="password" type="password" v-model="password" />
        </div>
        <p v-if="error" class="error">
          Has introducido mal el email o la contraseña.
        </p>
        <Button label="Login" @click="login()" />
      </div>
    </template>
  </Card>
</template>

<script>
import AuthService from '@/services/AuthService';

export default {
  name: 'Login',
  data: () => ({
    email: '',
    password: '',
    error: false
  }),
  methods: {
    login: function() {
      AuthService.login(this.email, this.password)
        .then(result => {
          window.localStorage.setItem('user', JSON.stringify(result.user));
        })
        .catch(err => {
          this.error = err;
        });
    }
  }
};
</script>
