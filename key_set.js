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
function set_key() {
    var key = document.getElementById("key").value;

    var xmlhttp = getXMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            //处理服务器的应答 xmlhttp.responseText
            var ret = xmlhttp.responseText;
            // alert(ret);
            if (ret == "ok") {
                alert("--秘钥设置成功--");
            }
            else if (ret == "erro") {
                alert("###秘钥设置失败###");
            }
            else if (ret == "repeat") { 
                alert("###秘钥重复###");
            }

        }
        else {
            // alert(xmlhttp.readyState + xmlhttp.status);
            return;
        }
    }
    var url = "./cgi-bin/set_key/set_key.cgi?";
    url += key;
    url += ":";
    alert("url" + url);
    xmlhttp.open("GET", url, true);
    //4、发送请求
    xmlhttp.send();
}