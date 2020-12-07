import '@/firebase.js';
import { createApp } from 'vue';

import Dialog from 'primevue/dialog';
import InputText from 'primevue/inputtext';
import Button from 'primevue/button';
import Toast from 'primevue/toast';
import Menubar from 'primevue/menubar';
import Card from 'primevue/card';
import Panel from 'primevue/panel';
import Dropdown from 'primevue/dropdown';
import Fieldset from 'primevue/fieldset';

// import ToastService from 'primevue/toastservice';
import 'primeflex/primeflex.css';
import 'primevue/resources/themes/saga-blue/theme.css';
import 'primevue/resources/primevue.min.css';
import 'primeicons/primeicons.css';

import router from './router';
import App from './App.vue';

const app = createApp(App);
app.use(router);

// Submodules loading
app.component('Dialog', Dialog);
app.component('InputText', InputText);
app.component('Button', Button);
app.component('Toast', Toast);
app.component('Menubar', Menubar);
app.component('Card', Card);
app.component('Panel', Panel);
app.component('Dropdown', Dropdown);
app.component('Fieldset', Fieldset);

app.mount('#app');
