import { Auth } from './FirebaseService';
import router from '../router'

export interface IUser {
  uid?: string;
  email: string;
  name?: string;
  displayName?: string;
  photoURL?: string;
  providerData?: Object[];
}

class AuthService {
  currentUser: any = null;
  constructor() {
    const me = this;
    Auth.onAuthStateChanged(user => {
      if (user) {
        me.currentUser = user;
        setTimeout(() => {
          router.push('/');
        }, 0);
      }
    });
  }
  login(email: string, password: string): Promise<any> {
    return Auth.signInWithEmailAndPassword(email, password);
  }
  logout(): Promise<any> {
    this.clearData();
    return Auth.signOut();
  }
  clearData() {
    this.currentUser = null;
    window.localStorage.removeItem('user');
  }
}

export default new AuthService();
