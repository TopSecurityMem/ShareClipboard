import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import monaco from 'rollup-plugin-monaco-editor';


// https://vitejs.dev/config/
export default defineConfig({
    plugins: [
        vue(),
        monaco({
            languages: ['json', 'xml', 'C++'],
        })
    ],

})