FROM nginx:latest

COPY wasm/index.html /usr/share/nginx/html/index.html
COPY wasm/nginx.conf /etc/nginx/conf.d/default.conf
COPY build.wasm/gb_ostrich.js /usr/share/nginx/html/gb_ostrich.js
COPY build.wasm/gb_ostrich.worker.js /usr/share/nginx/html/gb_ostrich.worker.js
COPY build.wasm/gb_ostrich.wasm /usr/share/nginx/html/gb_ostrich.wasm