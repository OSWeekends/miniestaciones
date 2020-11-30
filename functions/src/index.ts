import * as functions from "firebase-functions";

import admin from "firebase-admin";
// The Firebase Admin SDK to access Cloud Firestore.
admin.initializeApp();

let data = {};

export const helloWorld = functions.https.onRequest((request, response) => {
  functions.logger.info("Hello logs!", { structuredData: true });
  response.send("Hello from Firebase!");
});
exports.getSensor = functions.https.onRequest(async (req, res) => {
  // Grab the text parameter.
  const sensorId = req.query.id;
  // Push the new message into Cloud Firestore using the Firebase Admin SDK.
  const db = await admin.database();
  const newRef = db.ref(String(sensorId));
  const flowData = newRef.orderByChild("timestamp").limitToLast(100);

  flowData.on('value', (snapshot) => {
    data = snapshot.val();
    console.log(data);
  });
  // Send back a message that we've succesfully written the message
  res.json({data});
});

// exports.setTimestampValue = functions.database
//   .ref('{deviceID}/{dataType}/{messageId}')
//   .onCreate((snapshot: any, context) => {
//     if (!snapshot && !snapshot.ref) return;
//     // Grab the current value of what was written to the Realtime Database.
//     const original = snapshot.val();
//     console.log("Data", context.params, original);
//     // You must return a Promise when performing asynchronous tasks inside a Functions such as
//     // writing to the Firebase Realtime Database.
//     return snapshot.ref.parent.child('uppercase').set(original);
//   });
