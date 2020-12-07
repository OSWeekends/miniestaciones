import { DB } from '@/firebase';

const DBNames = ['hermes001'];

class DataService {
  db = null;
  currentID;

  getDevices() {
    return DBNames;
  }
  setDevice(id) {
    this.currentID = id;
    this.db = DB.ref(id);
  }

  getAll(prop = 'timestamp', limit = 1) {
    return this.db.orderByChild(prop).limitToLast(limit);
  }

  create(tutorial) {
    return this.db.push(tutorial);
  }

  update(key, value) {
    return this.db.child(key).update(value);
  }

  delete(key) {
    return this.db.child(key).remove();
  }

  deleteAll() {
    return this.db.remove();
  }
}

export default new DataService();
