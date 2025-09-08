#include "WebHandlers.h"
#include "MotorControl.h"

WebServer server(80);

const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html>
<html lang="vi">
<head>
<meta charset="UTF-8">

<meta name="viewport" content="width=device-width, initial-scale=1">
<title>FireTruck Controller</title>
<style>
  body { font-family: system-ui, sans-serif; margin: 20px; text-align:center; }
  .grid { display:grid; grid-template-columns:repeat(3, 1fr); gap:12px; max-width:420px; margin:0 auto; }
  button { padding:16px; font-size:18px; border-radius:12px; border:1px solid #ddd; }
  .wide { grid-column: span 3; }
  .speed { margin-top:18px; }
  .badge { margin:8px 0; font-size:14px; color:#555;}
</style>
</head>
<body>
  <h2>🚒 Điều khiển xe</h2>
  <div class="badge">Chạm & giữ để chạy, thả để dừng</div>
  <div class="grid">
    <div></div>
    <button id="btnF">Tiến</button>
    <div></div>
    <button id="btnL">Trái</button>
    <button id="btnS" class="stop">Dừng</button>
    <button id="btnR">Phải</button>
    <div></div>
    <button id="btnB">Lùi</button>
    <div></div>
    <button id="btnStopWide" class="wide">DỪNG KHẨN</button>
  </div>

  <div class="speed">
    <p>Tốc độ: <span id="sp"></span></p>
    <input id="spd" type="range" min="0" max="255" value="200">
  </div>

<script>
function press(endpoint){ fetch(endpoint).catch(()=>{}); }
function bindHold(btnId, endpoint){
  const el = document.getElementById(btnId);
  const start = ()=>press(endpoint);
  const stop  = ()=>press('/s');
  ['mousedown','touchstart'].forEach(ev=>el.addEventListener(ev, e=>{e.preventDefault(); start();}));
  ['mouseup','mouseleave','touchend','touchcancel'].forEach(ev=>el.addEventListener(ev, e=>{e.preventDefault(); stop();}));
}
bindHold('btnF','/f');
bindHold('btnB','/b');
bindHold('btnL','/l');
bindHold('btnR','/r');
document.getElementById('btnS').addEventListener('click', ()=>press('/s'));
document.getElementById('btnStopWide').addEventListener('click', ()=>press('/s'));
const sp = document.getElementById('sp');
const sl = document.getElementById('spd');
sp.textContent = sl.value;
let t=null;
sl.addEventListener('input', ()=>{
  sp.textContent = sl.value;
  if(t) clearTimeout(t);
  t = setTimeout(()=>fetch('/speed?v='+sl.value).catch(()=>{}), 120);
});
</script>
</body>
</html>
)HTML";

void handleRoot(){ server.send_P(200, "text/html", INDEX_HTML); }
void handleForward(){ forward(); server.send(200,"text/plain","OK"); }
void handleBackward(){ backward(); server.send(200,"text/plain","OK"); }
void handleLeft(){ left(); server.send(200,"text/plain","OK"); }
void handleRight(){ right(); server.send(200,"text/plain","OK"); }
void handleStop(){ stopAll(); server.send(200,"text/plain","OK"); }
void handleSpeed(){
  if (server.hasArg("v")) {
    int v = server.arg("v").toInt();
    v = constrain(v, 0, 255);
    speedValue = v;
    applySpeed();
    server.send(200,"text/plain",String(speedValue));
  } else {
    server.send(400,"text/plain","missing v");
  }
}
void handleNotFound(){ server.send(404, "text/plain", "Not found"); }
