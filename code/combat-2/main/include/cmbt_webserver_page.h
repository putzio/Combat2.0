#ifndef CMBT_WEBSERVER_PAGE_H
#define CMBT_WEBSERVER_PAGE_H

const char index_html[] = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP Web Server</title>
    <style>
        html {
            font-family: Arial;
            display: inline-block;
            text-align: center;
            touch-action: none;
        }

        h2 {
            font-size: 2.3rem;
            margin-bottom: 0px;
        }

        p {
            font-size: 1.9rem;
            margin-bottom: 0px;
            margin-top: 0px;
        }

        body {
            max-width: 400px;
            margin: 0px auto;
            padding-bottom: 5px;
        }

        .dot {
            height: 25px;
            width: 25px;
            background-color: #00FF00;
            border-radius: 50%;
            display: inline-block;
        }
    </style>
</head>

<body>
    <h2>Pilot do Rozkurwiatora3000</h2>
    <p><span id="textSliderLeft">%SLIDERVALUE1% </span>
        <space><span id="textSliderRight"> %SLIDERVALUE2%</span>
    </p>
    <h3>L | R</h3>
    <p><input type="range" orient="vertical" style="-webkit-appearance: slider-vertical; 
        margin: 70px;
        width: 25px;
        height: 300px;
        margin-bottom: 0px;
        margin-top: 0px;" OnInput="updateSliderPWM(this, 'textSliderLeft')" id="pwmSliderLeft" min="-255" max="255"
            value="%SLIDERVALUE1%" step="1" class="slider">

        <input type="range" orient="vertical" style="-webkit-appearance: slider-vertical; 
        margin: 70px;
        width: 25px;
        height: 300px;
        margin-bottom: 0px;
        margin-top: 0px;" OnInput="updateSliderPWM(this, 'textSliderRight')" id="pwmSliderRight" min="-255" max="255"
            value="%SLIDERVALUE2%" step="1" class="slider">
    </p>
    <h3>Bron</h3>
    <p><button type="button" onclick="toggleWeapon()"><strong>Daj kurwie miodu</strong></button> <span
            class="dot"></span>
        <label class="switch">
            <input type="checkbox" id="toggleButtonWeaponOn">
            <span class="slider round"></span>
        </label>
    </p>
    <p><label id="output" value=0,0,0,off></label></p>
    <script>
        document.getElementById("pwmSliderLeft").addEventListener("touchend", function (event) { ResetSliderPWM(this, 'textSliderLeft'); }, true);
        document.getElementById("pwmSliderRight").addEventListener("touchend", function (event) { ResetSliderPWM(this, 'textSliderRight'); }, true);
        document.getElementById("pwmSliderLeft").addEventListener("pointerup", function (event) { ResetSliderPWM(this, 'textSliderLeft'); }, true);
        document.getElementById("pwmSliderRight").addEventListener("pointerup", function (event) { ResetSliderPWM(this, 'textSliderRight'); }, true);
        var cnt = 0;
        setInterval(UpdateServer, 50);
        function UpdateServer() {
            var sliderValue1 = document.getElementById("pwmSliderLeft").value;
            var sliderValue2 = document.getElementById("pwmSliderRight").value;
            var weaponOn = document.getElementById("toggleButtonWeaponOn").checked;
            var out = cnt.toString() + "," + sliderValue1.toString() + "," + sliderValue2.toString() + "," + weaponOn.toString();
            cnt++;
            document.getElementById("output").innerHTML = out;
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/updatedData=" + out, true);
            xhr.send();
        }
        function toggleWeapon() {
            document.getElementById("toggleButtonWeaponOn").checked = !(document.getElementById("toggleButtonWeaponOn").checked);
        }
        function updateSliderPWM(element, textSlider) {
            var sliderValue = element.value;
            document.getElementById(textSlider).innerHTML = sliderValue;
            Log(sliderValue, textSlider);
        }
        function ResetSliderPWM(element, textSlider) {
            var sliderValue = 0;
            element.value = sliderValue;
            document.getElementById(textSlider).innerHTML = sliderValue;
        }
    </script>
</body>

</html>
)rawliteral";

#endif