# Miniestaciones calidad del aire en interiores
(Un proyecto gestionado por el Guild de Open Hardware)

Mini estaciones DIY para medir diferentes gases y contaminantes presentes en el aire en tiempo real.

## Motivación

* Preocupación sobre la calidad del aire en las ciudades. Conciencia medioambiental. Porque el aire que respiramos es un bien común que tenemos que necesitamos y debemos cuidar.

* Datos abiertos sobre la calidad del aire del ayuntamiento de Madrid. Estaciones limitadas y datos incompletos. Grandes zonas sin monitorización.

* Falta de datos de calidad del aire dentro de los edificios.

* Construir tus propios equipos de medición de bajo coste y tener una plataforma que open source colaborativa donde almacenar/procesar/visualizar información relacionada con la calidad del aire. 

* Es un proyecto que hay que modularizar por su naturaleza multidisciplinar
* Falta investigación más a fondo sobre las magnitudes físicas y químicas que queremos medir y como influyen en la calidad de vida de los habitantes de edificios
	- ¿Qué tipos de gases se encuentran en mayor concentración dentro de los edificios y que niveles son nocivos para los seres vivos?
	- ¿Cómo se distribuyen y se comportan esos gases en un espacio indoor?
	- ¿Qué tipo de sensores económicos hay y como medir de forma eficiente estos compuestos dentro de un edificio?
		* Sensores centralizados o distribuidos
	- ¿Qué tipo de alertas y en qué situaciones/concentraciones se pueden activar?
		* Interfaces usuario, etc.
	- ¿Cómo gestionar los datos que se recogen por las estaciones y con que datos externos se pueden cruzar?


## Referencias y estudios

* EPA - Publications about Indoor Air Quality (IAQ) - https://www.epa.gov/indoor-air-quality-iaq/publications-about-indoor-air-quality
* https://onlinelibrary.wiley.com/doi/full/10.1034/j.1600-0668.2003.00153.x

## Proyectos Open Source relacionados
  - Proyecto inspiracional Firebase IoT (https://github.com/kaizoku-oh/firebase-iot-demo)
  - ESP8266 +  Firebase (https://github.com/mobizt/Firebase-ESP8266)
  - https://github.com/UlisesGascon/Calidad-del-Aire
  - http://www.instructables.com/id/Air-Pollution-Detector/
  - http://www.instructables.com/id/AtmoScan/
  - http://www.instructables.com/id/Air-Quality-Monitoring-Device-Using-Arduino/
  - http://www.instructables.com/id/Precise-Air-Quality-Monitoring-System/
  - http://www.instructables.com/id/Air-Quality-Test-Box/
  - http://www.instructables.com/id/IoT-Air-Quality-Sensor/
  - http://www.instructables.com/id/Raspberry-Pi-Air-Quality-Monitor/
  - https://www.hackster.io/edwios/air-quality-monitor-3f422f

## Equipo

Aún por definir

## Tecnologías

### Hardware
* PlatformIO IDE - Integrado con VSCode (https://platformio.org/)
* Arduino IDE (https://www.arduino.cc/en/software)
* Generar JSON desde C++ (https://github.com/bblanchon/ArduinoJson/)
* Librerias Firebase para Arduino (https://github.com/FirebaseExtended/firebase-arduino)
* Librerías para NTP (https://github.com/arduino-libraries/NTPClient)

### Software
* Firebase SDK (https://firebase.google.com/docs/)
* Vue3 (https://v3.vuejs.org/)
* Librería de componentes para Vue3 (https://primefaces.org/primevue/)
* Librería de gráficos y diagramas integrada con Vue (https://apexcharts.com/)
* App Web/Android?

