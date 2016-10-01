Installing from sources `[*nix]`

```bash
# Install g++4.9

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-4.9 g++-4.9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9
```

```bash
# Install OpenSSL 1.0.2g

wget https://github.com/openssl/openssl/archive/OpenSSL_1_0_2g.tar.gz -O OpenSSL_1_0_2g.tar.gz
tar -xf OpenSSL_1_0_2g.tar.gz && cd openssl-OpenSSL_1_0_2g
./config
make && sudo make install
cd .. && rm -rf openssl-OpenSSL_1_0_2g && rm -f OpenSSL_1_0_2g.tar.gz
```

```bash
# Install libcurl 7.48.0

wget https://github.com/curl/curl/archive/curl-7_48_0.tar.gz -O curl-7_48_0.tar.gz
tar -xf curl-7_48_0.tar.gz && cd curl-curl-7_48_0
mkdir build && cd build && cmake ..
make && sudo make install
cd ../.. && rm -rf curl-curl-7_48_0 && rm -f curl-7_48_0.tar.gz
```

```bash
# Install pugixml 1.7

wget https://github.com/zeux/pugixml/releases/download/v1.7/pugixml-1.7.tar.gz -O pugixml-1.7.tar.gz
tar -xf pugixml-1.7.tar.gz && cd pugixml-1.7
mkdir build && cd build && cmake ../scripts/ -DBUILD_SHARED_LIBS:BOOL=TRUE
make && sudo make install
cd ../.. && rm -rf pugixml-1.7 && rm -f pugixml-1.7.tar.gz
```

```bash
# Install webdavclient 0.9.8

wget https://github.com/designerror/webdav-client-cpp/archive/v0.9.8.tar.gz -O webdavclient-0.9.8.tar.gz
tar -xf webdavclient-0.9.8.tar.gz && cd webdav-client-cpp-0.9.8
mkdir build && cd build && cmake ..
make && sudo make install
cd ../.. && rm -rf webdav-client-cpp-0.9.8 && rm -f webdavclient-0.9.8.tar.gz
```
