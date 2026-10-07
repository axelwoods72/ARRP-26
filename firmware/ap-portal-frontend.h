#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ARRP-26</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: sans-serif;
      background: #111;
      color: #fff;
      text-align: center;
      padding: 40px 20px;
    }
    h1 { margin-bottom: 40px; }
    h2 {
      font-size: 14px;
      text-transform: uppercase;
      letter-spacing: 2px;
      color: #888;
      margin: 30px 0 15px 0;
    }
    .group {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 12px;
      max-width: 320px;
      margin: 0 auto;
    }
    button {
      padding: 18px;
      font-size: 16px;
      border: none;
      border-radius: 10px;
      color: #fff;
      cursor: pointer;
    }
    .btn-servo {
      background: #ff8c42;
    }
    .btn-servo:active { background: #cc6b29; }
    .btn-face {
      background: #5b8dd9;
    }
    .btn-face:active { background: #3a6bbf; }
  </style>
</head>
<body>
  <h1>ARRP-26</h1>

  <h2>Servo Commands</h2>
  <div class="group">
    <button class="btn-servo" onclick="pose('lay_down')">Lay Down</button>
    <button class="btn-servo" onclick="pose('stand_up')">Stand Up</button>
    <button class="btn-servo" onclick="pose('wave')">Wave</button>
  </div>

  <h2>OLED Face</h2>
  <div class="group">
    <button class="btn-face" onclick="face('happy')">Happy</button>
    <button class="btn-face" onclick="face('sad')">Sad</button>
    <button class="btn-face" onclick="face('sleepy')">Sleepy</button>
    <button class="btn-face" onclick="face('cute')">Cute</button>
  </div>

  <script>
    function pose(name) {
      fetch('/cmd?pose=' + name).catch(console.error);
    }
    function face(name) {
      fetch('/cmd?face=' + name).catch(console.error);
    }
  </script>
</body>
</html>
)rawliteral";
