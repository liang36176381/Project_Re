function Load() {
    setInterval(function () { updateTime(); }, 100);
    setInterval(function () { StatusRequest(); }, 3000);
}

let StatusRequest = async () => {
    let response = await fetch("/data/get/");
    let json = await response.json();
    console.log(json);
    let humid = json["value"]["humid"];
    let temp = json["value"]["temp"];
    let light = json["value"]["light"];
    if (humid != "null") {
        document.getElementById("humid_p").innerText = humid;
    }
    if (temp != "null") {
        document.getElementById("temp_p").innerText = temp;
    }
    if (light != "null") {
        document.getElementById("light_p").innerText = light;
    }
}
let SendRequest = async (type) => {
    // 根據傳入的 type 參數，獲取對應的 HTML 元素
    let value;
    value =
        type === "LED" ?
            document.querySelector('input[type="radio"][name="rd"]:checked').value :
            value = document.getElementById(type.toLowerCase()).checked ? "on" : "off";
    // 發送請求
    let response = await fetch(`/arduino/${type}/${value}/`);
    console.log(`/arduino/${type}/${value}/`);
    if (response.ok == false) {
        toastr["error"](`${response.status}`, "Error");
    }
}

function updateTime() {
    let date = new Date();
    // 使用 padStart 方法自動補 0
    let year = date.getFullYear();
    let month = (date.getMonth() + 1).toString().padStart(2, '0');
    let day = date.getDate().toString().padStart(2, '0');
    let hour = date.getHours().toString().padStart(2, '0');
    let minute = date.getMinutes().toString().padStart(2, '0');
    let sec = date.getSeconds().toString().padStart(2, '0');
    let dateStr = `${year}/${month}/${day} ${hour}:${minute}:${sec}`;
    document.getElementById("time").innerText = dateStr;
}
function openConfig() {
    document.querySelector('.popupWindow').style.display = 'flex';
    document.querySelector('#fade').style.display = 'block';
}
function closeConfig() {
    document.querySelector('.popupWindow').style.display = 'none';
    document.querySelector('#fade').style.display = 'none';
}
function addCardInputCreate() {
    const form = document.querySelector(".addForm");
    for (let i = 1; i < 5; i++) {
        let label = document.createElement("label");
        let input = document.createElement("input");
        let br = document.createElement("br");
        label.setAttribute("for", `v${i}`)
        label.innerText = `*value${i} 0x`;
        label.className = "RFLabel"
        input.id = `v${i}`;
        input.name = `v${i}`;
        input.className = "addCard";
        input.type = "text";
        input.autocomplete = "off"
        input.oninput = function () {
            /*正規表達式: 放在//中間
            []=>比對中括號內的字元
            [^]=>比對中括號裡面 "以外的任意自元"
            \d: 所有數字集合
            g: 全部比對(整個字串)
            */
            this.value = this.value.replace(/[^\da-fA-F]|[\u4e00-\u9fa5]/g, '').toUpperCase();
        }
        input.minLength = 2;
        input.maxLength = 2;
        form.appendChild(label);
        form.appendChild(input);
        form.appendChild(br);
    }
}
function toast() {
    toastr["error"]("Toast", "Test")
}
let CloseLED = async () => {
    ar.forEach(element => {
        element.checked = false;
    });
    let response = await fetch(`/arduino/LED/close/`);
    if (response.ok == false) {
        toastr["error"](`${response.status}`, "Error")
    }
    let ar = document.querySelectorAll('input[type="radio"][name="rd"]');
    
}