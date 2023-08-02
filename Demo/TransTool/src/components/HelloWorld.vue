<script setup>
import { ref } from 'vue'
import X2js from 'x2js'

let content = ref("测试数据")

const  OnXml2Json = () => {
  
  let x2js = new X2js()
  let jscontent = x2js.xml2js(content.value)
  
  content.value = JSON.stringify(jscontent, null, 2)
}

const OnJson2Xml = () => {
  let x2js = new X2js()
  let xmlcontent = x2js.js2xml(content.value)
  
  content.value = xmlcontent
}

</script>

<template>

  <textarea v-model="content" style="width:100%; height:500px;" />

  <div>
    <button id="tjson2xml" @click="OnJson2Xml">json转xml</button>
    <button id="txml2json" @click="OnXml2Json">xml转json</button>
    <button id="tcpp">转代码</button>
  </div>
  
</template>
