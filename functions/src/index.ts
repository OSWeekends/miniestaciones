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
  });
  // Send back a message that we've succesfully written the message
  res.json({data});
});
