



on ubuntu-usb
	sudo add-apt-repository universe
	

apt update
apt-get install -y --no-install-recommends python3 python3-pip python3-setuptools python3-wheel ninja-build build-essential openjdk-8-jdk-headless curl unzip bash nasm pkg-config make git
openjdk-11-jdk-headless

apt-get clean
rm -rf /var/lib/apt/lists/*
pip3 install meson==1.0.1

curl https://dl.google.com/android/repository/commandlinetools-linux-9477386_latest.zip --output /home/hersztu/android-sdk.zip
mkdir -p /home/hersztu/android-sdk
unzip -qq /home/hersztu/android-sdk.zip -d /home/hersztu/android-sdk
rm /home/hersztu/android-sdk.zip

chmod +x /home/hersztu/android-sdk/cmdline-tools/bin/sdkmanager

installAndroidComponent() { yes | /root/android-sdk/cmdline-tools/bin/sdkmanager --sdk_root=/root/android-sdk "$1" > /dev/null; }
/home/hersztu/android-sdk/cmdline-tools/bin/sdkmanager --sdk_root=/home/hersztu/android-sdk "ndk;25.2.9519653"
/home/hersztu/android-sdk/cmdline-tools/bin/sdkmanager --sdk_root=/home/hersztu/android-sdk "cmake;3.22.1"



apt-get --allow-releaseinfo-change update

export ANDROID_SDK_HOME=/home/hersztu/android-sdk
export ANDROID_NDK_HOME=/home/hersztu/android-sdk/ndk/25.2.9519653

git clone https://github.com/Javernaut/ffmpeg-android-maker.git



CC=cl PKG_CONFIG_PATH=../../installed/lib/pkgconfig ../../sources/ffmpeg/configure --prefix=../../installed \
--toolchain=msvc --target-os=win64 --arch=x86_64 --enable-yasm --enable-asm --disable-static --enable-shared \
--enable-libx264 --enable-gpl --enable-nonfree --enable-debug --disable-optimizations --extra-ldflags="-LIBPATH:../../installed/lib"\
 --extra-cxxflags="-I../../installed/include/ -MTd -Od -Zi" --extra-cflags="-I../../installed/include/ -MTd -Od -Zi" 


./configure --prefix=/home/hersztu/output --enable-cross-compile --target-os=android --arch=aarch64 --sysroot=/home/hersztu/android-sdk/ndk/25.2.9519653/toolchains/llvm/prebuilt/linux-x86_64 --cross-prefix=arm64-v8a --cc=/home/hersztu/android-sdk/ndk/25.2.9519653/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang --extra-cflags="-O3 -fPIC" --enable-shared  --disable-static 

