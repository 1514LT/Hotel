function back() {
    window.location.href = "./index.html";
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
function get_card() { 
    var xmlhttp = getXMLHttpRequest();
    var card;
    //alert(xmlhttp);
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            //处理服务器的应答 xmlhttp.responseText
            var ret = xmlhttp.responseText;
            card = ret;
            alert("##" + ret + "##");
            document.getElementById("card").value=ret
        }

    }
    var url = "./cgi-bin/get_card/get_card.cgi?";
    //alert(url);
    url += "get_card:";
    alert(url);
    xmlhttp.open("GET", url, true);
    //4、发送请求
    xmlhttp.send();
}
function top_up() {
    var card = document.getElementById("card").value;
    var money = document.getElementById("money").value;
    //1、创建xmlhttp对象
    var xmlhttp = getXMLHttpRequest();
    //alert(xmlhttp);
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            //处理服务器的应答 xmlhttp.responseText
            var ret = xmlhttp.responseText;
            if (ret == "充值成功") {
                alert("----充值" + money + "成功----");
            }
            else if (ret == "充值失败") {
                alert("----充值失败---");
            }
            else if (ret == "0") { 
                alert("没有该账户");
            }
        }

    }
    var url = "./cgi-bin/top_up/top_up.cgi?";
    //alert(url);
    url += card;
    url += ":";
    url += money;
    alert(url);
    xmlhttp.open("GET", url, true);
    //4、发送请求
    xmlhttp.send();
}
