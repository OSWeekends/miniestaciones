import firebase from 'firebase/app';
import 'firebase/auth';
import 'firebase/database';

import * as firebaseui from 'firebaseui';
import 'firebaseui/dist/firebaseui.css';

import { firebaseConfig } from './config.js';

const App = firebase.initializeApp(firebaseConfig);
const Auth = App.auth();
const DB = App.database();

const uiConfig = {
  signInSuccessUrl: '/profile', // This redirect can be achived by route using callback.
  signInFlow: 'popup',
  signInOptions: [
    // firebase.auth.FacebookAuthProvider.PROVIDER_ID,
    // firebase.auth.GoogleAuthProvider.PROVIDER_ID,
    firebase.auth.EmailAuthProvider.PROVIDER_ID,
  ],
};

let UI = firebaseui.auth.AuthUI.getInstance();
if (!UI) {
  UI = new firebaseui.auth.AuthUI(Auth);
}
export { App, Auth, DB, UI, uiConfig };
