
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
} function getuser() {
    //1、创建xmlhttp对象
    var xmlhttp = getXMLHttpRequest();
    //alert(xmlhttp);
    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            //处理服务器的应答 xmlhttp.responseText
            var ret = xmlhttp.responseText;
            document.getElementById('getuser').innerHTML = ret;
            
        }   
    }
    var url = "./cgi-bin/getuser/getuser.cgi?11";
    xmlhttp.open("GET", url, true);
    //4、发送请求
    xmlhttp.send();
}