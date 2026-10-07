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
    button {
      display: block;
      width: 200px;
      margin: 15px auto;
      padding: 18px;
      font-size: 18px;
      border: none;
      border-radius: 10px;
      background: #ff8c42;
      color: #fff;
      cursor: pointer;
    }
    button:active { background: #cc6b29; }
  </style>
</head>
<body>
  <h1>ARRP-26</h1>
  <button onclick="cmd('lay_down')">Lay Down</button>
  <button onclick="cmd('stand_up')">Stand Up</button>
  <button onclick="cmd('wave')">Wave</button>
  <script>
    function cmd(name) {
      fetch('/cmd?pose=' + name).catch(console.error);
    }
  </script>
</body>
</html>
)rawliteral";
