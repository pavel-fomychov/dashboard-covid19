<h2>Мониторинг Covid-19 на ESP8266</h2>

<img src="https://raw.githubusercontent.com/pavel-fomychov/dashboard-covid19/main/IMG_20201129_163819_1.jpg" height="300">

<p>Проект устройства для мониторинга за ситуацией с Covid-19 на базе микроконтроллера ESP8266 выполненый в виде настольного виджета.</p>

<h3>Перечень элементов:</h3>
<div>1) ESP32 / ESP8266</div>
<div>2) OLED дисплей 0.96" 128х64</div>
<div>3) Тактовая кнопка (опционально)</div>
<div>4) Зуммер (опционально)</div>

<h3>Подключение OLED дисплея</h3>
<h4>OLED&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ESP8266</h4>
<div>SCL&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;D1 (GPIO5)</div>
<div>SDA&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;D2 (GPIO4)</div>
<div>Vcc&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;5V</div>
<div>GND&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;GND</div>

<h3>Подключение кнопки</h3>
<h4>Кнопка&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ESP8266</h4>
<div>PIN1&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;D7 (GPIO13)</div>
<div>PIN2&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;GND</div>

<h3>Подключение зуммера</h3>
<h4>Зуммер&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ESP8266</h4>
<div>PIN+&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;A0</div>
<div>PIN-&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->&nbsp;&nbsp;&nbsp;&nbsp;GND</div>
