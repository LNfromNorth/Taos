# boot of Duo

> this doc is for the boot process of the Milkv Duo
> reference to the SDK: https://github.com/milkv-duo/duo-buildroot-sdk

The SDK mainly contains the following parts:
- u-boot: 2021.10
- linux kernel: 5.10.4
- buildroot: 2021.05
- opensbi: 89182b2

SDK Directory Structure
```
├── build               // compilation scripts and board configs
├── build.sh            // one-click compilation script
├── buildroot-2021.05   // buildroot source code
├── freertos            // freertos system
├── fsbl                // fsbl firmware in prebuilt form
├── install             // temporary images stored here
├── isp_tuning          // camera effect parameters
├── linux_5.10          // linux kernel
├── middleware          // self-developed multimedia framework
├── device              // configuration files for milkv
├── opensbi             // opensbi library
├── out                 // final image for SD card
├── ramdisk             // prebuilt ramdisk
└── u-boot-2021.10      // u-boot source code
```

