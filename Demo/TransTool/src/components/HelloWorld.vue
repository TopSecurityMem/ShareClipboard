<script setup>
import { ref } from 'vue'
import X2js from 'x2js'
import jQuery from 'jquery'

let content = ref("测试数据")

function formatXml(xml) {
    var formatted = '';
    var reg = /(>)(<)(\/*)/g;
    xml = xml.replace(reg, '$1\r\n$2$3');
    var pad = 0;
    jQuery.each(xml.split('\r\n'), function(index, node) {
        var indent = 0;
        if (node.match( /.+<\/\w[^>]*>$/ )) {
            indent = 0;
        } else if (node.match( /^<\/\w/ )) {
            if (pad != 0) {
                pad -= 1;
            }
        } else if (node.match( /^<\w[^>]*[^\/]>.*$/ )) {
            indent = 1;
        } else {
            indent = 0;
        }

        var padding = '';
        for (var i = 0; i < pad; i++) {
            padding += '  ';
        }

        formatted += padding + node + '\r\n';
        pad += indent;
    });

    return formatted;
}

function isJSON (str) {
  if (typeof str === 'string') {
    try {
      var obj = JSON.parse(str)
      if (typeof obj === 'object' && obj) {
        return true
      } else {
        return false
      }
    } catch (e) {
      return false
    }
  }
}

/*
 * 验证xml格式的正确性
 */
function validateXML(xmlContent)
{
    //errorCode 0是xml正确，1是xml错误，2是无法验证
    var xmlDoc,errorMessage,errorCode = 0;
    // code for IE
    if (window.ActiveXObject)
    {
        xmlDoc  = new ActiveXObject("Microsoft.XMLDOM");
        xmlDoc.async="false";
        xmlDoc.loadXML(xmlContent);

        if(xmlDoc.parseError.errorCode!=0)
        {
            errorMessage="错误code: " + xmlDoc.parseError.errorCode + "\n";
            errorMessage=errorMessage+"错误原因: " + xmlDoc.parseError.reason;
            errorMessage=errorMessage+"错误位置: " + xmlDoc.parseError.line;
            errorCode = 1;
        }
        else
        {
            errorMessage = "格式正确";
        }
    }
    // code for Mozilla, Firefox, Opera, chrome, safari,etc.
    else if (document.implementation.createDocument)
    {
        var parser=new DOMParser();
        xmlDoc = parser.parseFromString(xmlContent,"text/xml");
        var error = xmlDoc.getElementsByTagName("parsererror");
        if (error.length > 0)
        {
               if(xmlDoc.documentElement.nodeName=="parsererror"){
                errorCode = 1;
                errorMessage = xmlDoc.documentElement.childNodes[0].nodeValue;
            } else {
                errorCode = 1;
                errorMessage = xmlDoc.getElementsByTagName("parsererror")[0].innerHTML;
            }
        }
        else
        {
            errorMessage = "格式正确";
        }
    }
    else
    {
        errorCode = 2;
        errorMessage = "浏览器不支持验证，无法验证xml正确性";
    }
    return {
        "msg":errorMessage, 
        "error_code":errorCode
    };
}


const  OnXml2Json = () => {
  if(validateXML(content.value).error_code === 0) {
    let x2js = new X2js()
    let jscontent = x2js.xml2js(content.value)
    content.value = JSON.stringify(jscontent, null, 2)
  }
}

const OnJson2Xml = () => {
  if(isJSON(content.value)) {
    let x2js = new X2js()
    let xmlcontent = x2js.js2xml(JSON.parse(content.value))
    content.value = formatXml(xmlcontent)
  }
}

const FormatString = () => {
  if(isJSON(content.value)) {
    content.value = JSON.stringify(content.value)
  } else if (validateXML(content.value).error_code === 0) {
    content.value = formatXml(content.value)
  }
}

</script>

<template>

  <textarea v-model="content" style="width:100%; height:500px;" />

  <div>
    <button id="tjson2xml" @click="OnJson2Xml">json转xml</button>
    <button id="txml2json" @click="OnXml2Json">xml转json</button>
    <button id="tcpp">转代码</button>
    <button id="tcformat" @click="FormatString">格式化xml和json</button>
  </div>
  
</template>
