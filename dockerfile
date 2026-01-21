FROM optimistic_allen
RUN apt-get update && apt-get install -y wget
RUN wget -q https://github.com/chipsalliance/verible/releases/download/v0.0-4023-gc1271a00/verible-v0.0-4023-gc1271a00-linux-static-x86_64.tar.gz
RUN tar -xzf verible-*.tar.gz
RUN cp -r verible/bin/* /usr/local/bin/
RUN rm -rf verible verible-*.tar.gz