import { DB } from '@/services/FirebaseService';

const DBNames = ['hermes001'];

class DataService {
  db: any;
  currentID = '';

  getDevices() {
    return DBNames;
  }
  setDevice(id: string) {
    this.currentID = id;
    this.db = DB.ref(id);
  }

  getAll(prop = 'timestamp', limit = 1) {
    return this.db.orderByChild(prop).limitToLast(limit);
  }
}

export default new DataService();
