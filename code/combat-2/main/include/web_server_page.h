#ifndef WEB_SERVER_PAGE_H
#define WEB_SERVER_PAGE_H

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

        /* .slider {
        -webkit-appearance: slider-vertical; 
        margin: 70px;
        width: 25px;
        height: 360px;
        background: #FFD65C;
        outline: none;
        -webkit-transition: .2s;
        transition: opacity .2s;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 35px;
            height: 35px;
            background: #003249;
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 35px;
            height: 35px;
            background: #003249;
            cursor: pointer;
        }

        */
    </style>
</head>

<body>
    <h2>Pilot do Rozkurwiatora3000</h2>
    <p><span id="textSliderValue1">%SLIDERVALUE1% </span>
        <space><span id="textSliderValue2"> %SLIDERVALUE2%</span>
    </p>
    <h3>L | R</h3>
    <p><input type="range" orient="vertical" style="-webkit-appearance: slider-vertical; 
        margin: 70px;
        width: 25px;
        height: 300px;
        margin-bottom: 0px;
        margin-top: 0px;" OnInput="updateSliderPWM(this, 'textSliderValue1')" id="pwmSlider1" min="0" max="255"
            value="%SLIDERVALUE1%" step="1" class="slider">

        <input type="range" orient="vertical" style="-webkit-appearance: slider-vertical; 
        margin: 70px;
        width: 25px;
        height: 300px;
        margin-bottom: 0px;
        margin-top: 0px;" OnInput="updateSliderPWM(this, 'textSliderValue2')" id="pwmSlider2" min="0" max="255"
            value="%SLIDERVALUE2%" step="1" class="slider">
    </p>
    <h3>Broń</h3>
    <p><span id="textSliderValue3">%SLIDERVALUE3% </span></p>
    <p>
        <input type="range" orient="horisontal" style="-webkit-appearance: slider-horizontal; 
        margin: 20px;width:360px; 
        height:25px; 
        margin-top: 0px;" id="pwmSlider3" OnInput="updateSliderPWM(this, 'textSliderValue3')" min="0" max="255"
            value="%SLIDERVALUE3%" step="1" class="slider">
    </p>
    <p><button type="button"><strong>Daj kurwie miodu</strong></button> <span class="dot"></span></p>
    <script>
        document.getElementById("pwmSlider1").addEventListener("touchend", function (event) { ResetSliderPWM(this, 'textSliderValue1'); }, true);
        document.getElementById("pwmSlider2").addEventListener("touchend", function (event) { ResetSliderPWM(this, 'textSliderValue2'); }, true);
        document.getElementById("pwmSlider1").addEventListener("pointerup", function (event) { ResetSliderPWM(this, 'textSliderValue1'); }, true);
        document.getElementById("pwmSlider2").addEventListener("pointerup", function (event) { ResetSliderPWM(this, 'textSliderValue2'); }, true);
        function updateSliderPWM(element, textSlider) {
            var sliderValue = element.value;
            document.getElementById(textSlider).innerHTML = sliderValue;
            Log(sliderValue, textSlider);
        }
        function ResetSliderPWM(element, textSlider) {
            var sliderValue = 50;
            element.value = sliderValue;
            document.getElementById(textSlider).innerHTML = sliderValue;
            Log(sliderValue, textSlider);
        }
        function Log(sliderValue, textSlider) {
            console.log(sliderValue);
            var xhr = new XMLHttpRequest();
            var id;
            if (textSlider == "textSliderValue1") {
                id = 1;
            } else {
                id = 2;
            }
            xhr.open("GET", "/slider" + id + "?value=" + sliderValue, true);
            xhr.send();
        }
    </script>
</body>

</html>
)rawliteral";

#endif