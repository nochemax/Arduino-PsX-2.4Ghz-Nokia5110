Arduino-PsX-2.4Ghz-Nokia5110
============================
//////########EN COSTRUCCION DISCULPEN LAS MOLESTIAS ######################\\\\\\\\\\\\\\\\\

Esta versión de PsX arduino radio control, esta programado en C  
incluye varios modo de manejos, así como selección de canales, comprobación de la batería del mando y variables para gizmo de 3 ejes digital, el control del mando influye su modalidad, en los menú de pantalla que se explicara mas abajo. Por lo que empezaremos con los materiales necesarios para montar nuestro mando psXrC 

VIDEO DEL PROYECTO

///falta por subir 

tiempo realizado x

lenguaje de programación C 

diseño piezas 3D rediseñadas para el proyecto 

creación  new line robotic  https://www.facebook.com/newlinerobotic

colaboradores MrCuervoRC  https://www.youtube.com/user/MrCuervoRC 


MATERIALES NECESARIOS 

2 Arduinos nano V3
1 Arduino mini pro
1 pantalla Nokia5110 
2 condensadores de 10 uf
3 condensador 0,33uf y 0.1uf 
2 resistencias de 4k7
1 altavoz pizioelectrónico 
1 mando psx (sony 3.3v no sony 5.0v)”recomendado sony version2”
1 modulo de radio “recomendado con antena tipo este modelo:
4 tornillos de métrica 3 con rosca
1 metro de cable com serial " es igual quel usb pero con mas hilos "
1 termo retráctil 
1 ts7809 http://pdf1.alldatasheet.net/datasheet-pdf/view/123868/TSC/TS7809BCI.html
2 l7806 http://pdf.datasheetcatalog.com/datasheet_pdf/sgs-thomson-microelectronics/L7805CD2T_to_L7885CV.pdf
http://www.ebay.es/itm/like/251699886656?limghlpsr=true&hlpv=2&ops=true&viphx=1&hlpht=true&lpid=115 “
1 modulo de radio de placa el receptor no tiene por que llevarla 

LIBRERIAS

Modulo Nrf24l01
https://github.com/stanleyseow/arduino-nrf24l01

Mando psx
https://github.com/madsci1016/Arduino-PS2X

Pantalla nokia5110
http://www.henningkarlsen.com/electronics/library.php?id=44


PIEZAS 3D PARA MONTAR EL MANDO
http://www.thingiverse.com/thing:526993

Explicación del montaje del mando PsX 

Es realmente sencillo lo primero que tenemos que hacer son todas las conexiones, en el siguiente orden y empezando por el máster ya que lleva el mando PsX, y sera lo que mas tardemos junto la placa receptora, para ello dejo el tutorial el cual lo hice con algunos consejos extras. 

-http://www.billporter.info/2010/06/05/playstation-2-controller-arduino-library-v1-0/

primer consejo usar mando sony 3.3v y montar todo en protoboar para ver que todo esta correcto 

segundo consejo usar cable usb no intentar usar el de sony no es bueno a la hora de soldar 

tercer consejo y esto mas que un consejo es vital para que funcione hay que poner una resistencia 4k7 del positivo al data podéis dejarla dentro del mando una vez soldéis los cables usb 

cuarto consejo poner los cables de su color y hacerlo con cuidado requiere de soldador de punta fina  

-Cuando este listo aremos las conexiones al arduino nano v3 máster ver el sketch máster para ver la asignación de pines ;)


-Ahora pasaremos hacer la laconexion de cables de la pantalla 5110 y la pcb del receptor 

Conexion pantalla nokia5110
https://drive.google.com/?tab=mo&authuser=0#my-drive

Montaje de la placa rceptora

https://drive.google.com/?tab=mo&authuser=0#my-drive

////////@@@@@ Queda por montar tutorial @@@@ \\\\\\\\
                      en muy poco tiempo estará listo 

-Una vez lo tengamos realizado, pasaremos a la conexión de los condensadores de los módulos de radio 

http://i61.tinypic.com/2rc75zn.jpg

usaremos los condensadores de 10uf electrolítico 

positivo con positivo y negativo con negativo 

consejo mirar la versión del dispositivo algunos de antena no lo necesitan 

-Ahora realizaremos las conexiones para ello mirar el sketch maestro para la asignación de pines del modulo de radio

para comprender el dispositivo y su protocolo de comunicación ver los siguiente links 
https://itechnofrance.wordpress.com/2013/05/24/utilisation-du-module-nrf24l01-avec-larduino/

bus isp
http://tronixstuff.com/2011/05/13/tutorial-arduino-and-the-spi-bus/

-sacaremos una ultima conexión del pin analógico A1, para la medición de la batería del mando ajustar sketch y resistencia según voltaje, recomendado 9,6 v 800ma 

tutorial arduino su divisor de tensión 
http://arduinohome.com/wp-content/uploads/2012/10/divisorTension.png
- Y ya el ultimo paso para terminar con el máster por ahora ya. Que cuando conectemos la pantalla al arduino mini pro tendremos que poner 3 conexiones mas, de la siguiente manera :

arduino nano  |  arduino mini pro
        rx    |             tx
        tx    |             rx
      gnd     |             gnd

http://scratchpad.majenko.co.uk/SimpleComm.png

consejo no cargar los sktch con la conexión serial entre arduinos, por eso debe ser el ultimo paso a realizar antes de la prueba 


-Y  ya pasaremos al ultimo paso, montar los pin del arduino mini pro para cargar el programa del siguiente modo  


 http://besoft.com.es/tutorial-arduino/tutorial-programar-arduino-pro-mini-con-otro-arduino/


primer consejo tener mucho cuidado es muy frágil si no estáis familiarizado mucho con la electrónica podéis cambiarlo por un arduino nano v3 

segundo consejo no olvidarse del pin BLK o DTR situado en la esquina de arduino mini pro al reset  de arduino 

luego conectaremos la pantalla nokia5110  al arduino mini pro para ver pin de conexión mirar sktch pantalla, para saber mas sobre el protocolo mirar el siguiente link

http://arduino.alhin.de/index.php?n=23

-Por ultimo cargar los sktch, y ver que todo va como tiene que ir podéis de seleccionar des comentando algunos println del receptor para ver que todos los datos son correctos en todas sus modalidades y tenemos que montar el mando con sus piezas imprimidas en 3D de la siguiente
manera :

1º Montaremos la tapa.stl  a la pieza principal.stl con el tornillo y una tuerca, consejo usar algo de pegamento 

https://drive.google.com/?tab=mo&authuser=0#my-drive

2º Pegar visera.stl a cajanokia.stl como se ve en la siguiente imagen 

https://drive.google.com/?tab=mo&authuser=0#my-drive

3º Montamos la pantalla en su caja y cerramos la tapa sacando los cables de la pantalla para fuera podemos usar pegamento caliente de pistola para fijarla bien por la ranura y retirando lo sobrante  

 https://drive.google.com/?tab=mo&authuser=0#my-drive


4º Pasaremos el cable del mando PsX por la pieza  principal.slt, pasaremos los tornillos de cogida y pondremos atornillada la pieza de taco.stl a uno de los agujeros 
https://drive.google.com/?tab=mo&authuser=0#my-drive
https://drive.google.com/?tab=mo&authuser=0#my-drive

5º montaremos los conectores a las cajas de los arduino pieza base.stl y realizaremos todas las soldaduras y conexiones para ya solo atornillarla a la pieza principal.stl pinchar nuestro arduino y cerrar con la tapaA.stl 

https://drive.google.com/?tab=mo&authuser=0#my-drive
https://drive.google.com/?tab=mo&authuser=0#my-drive
https://drive.google.com/?tab=mo&authuser=0#my-drive
https://drive.google.com/?tab=mo&authuser=0#my-drive

6ª Motar el conector de la radio y soldarlos a los pines de arduino 

https://drive.google.com/?tab=mo&authuser=0#my-drive
https://drive.google.com/?tab=mo&authuser=0#my-drive
https://drive.google.com/?tab=mo&authuser=0#my-drive

7º montaremos la base de arduino atornillando al taco 

https://drive.google.com/?tab=mo&authuser=0#my-drive



