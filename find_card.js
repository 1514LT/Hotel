function cancel() {
    document.getElementById("input").value = "";
    document.getElementById("pwd").value = "";
}
function back() {
    window.location.href = "./total.html";
}
function showdata(str) {
    s1 = str.split('.');
    var row = parseInt(s1[0]);
    var table = document.getElementById("table");
    //alert("table="+table);
    var tmplen = table.rows.length;
    //alert("tmplen="+tmplen);
    for (var i = 1; i < tmplen; i++) {
        table.deleteRow(i);
    }
    var tmpstr = new Array();
    tmpstr = s1[1].split(" ");
    if (str.length > 0) {
        for (var i = 0; i < row; i++) {
            var x = table.insertRow(table.rows.length)
            var y = x.insertCell(0);
            var z = x.insertCell(1);
            var q = x.insertCell(2);
            y.innerHTML = tmpstr[i * 3];
            z.innerHTML = tmpstr[i * 3 + 1];
            q.innerHTML = tmpstr[i * 3 + 2];
        }

    }
}
function getXMLHttpRequest() {
    var xmlhttp = null;
    if (window.XMLHttpRequest)//自动检测当前浏览器的版本，如果是 IE5.0 以上的高版本的浏览器
    {// code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp = new XMLHttpRequest();//创建请求对象
    }
    else////如果浏览器是底版本的
    {// code for IE6, IE5
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");//创建请求对象
    }
    return xmlhttp;//返回请求对象
}
function find_card() {
    var input = document.getElementById("input").value;
    var pwd = document.getElementById("pwd").value;
    const radios = document.querySelectorAll('input[name="choice"]');
    let selectedValue;

    radios.forEach((radio) => {
        if (radio.checked) {
            selectedValue = radio.value;
        }
    });


    // card = document.getElementById("usercard").value;
    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            //处理服务器的应答 xmlhttp.responseText
            var ret = xmlhttp.responseText;
            if (ret != "0") {
                document.getElementById('div').innerHTML = ret;
            }
            else if (ret == "0") {
                alert("----查找失败---");
                document.getElementById('div').innerHTML = ret;
            }
            else if (ret == "pwd_erro")
                alert("##账户密码错误##");
        }
    }
    var url = "./cgi-bin/find/find.cgi?";
    url += input;
    url += ":";
    url += selectedValue + ":" + pwd;
    alert(url);
    xmlhttp.open("GET", url, true);
    //4、发送请求
    xmlhttp.send();
}
