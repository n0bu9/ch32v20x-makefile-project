# Linux环境下的CH32V203 makefile最小工程
### 基于 https://github.com/IOsetting/ch32v208-template/ 修改

## 工程目录结构
```
wch_risc_development/          # 基于MounRiverStudio_Linux_X64_V230
├── OpenOCD/                   # openocd工具
└── Toolchain/                 # gcc工具链

min_project/
├── user/                      # 用户应用代码
│   ├── main.c                 # 主程序入口
│   ├── my_button.c/h          # 按键驱动示例
│   ├── ch32v20x_it.c/h        # 中断处理函数
│   ├── ch32v20x_conf.h        # 外设配置头文件
│   └── system_ch32v20x.c/h    # 系统初始化
│
├── libraries/                 # 库文件
│   ├── Core/                  # RISC-V核心支持
│   ├── Debug/                 # 调试支持库
│   ├── Peripheral/            # CH32V20x外设驱动库
│   │   ├── inc/               # 外设头文件
│   │   └── src/               # 外设源文件
│   ├── FreeRTOS/              # FreeRTOS实时操作系统
│   ├── NetLib/                # 以太网库
│   ├── Startup/               # 启动文件
│   └── Ld/                    # 链接脚本
│
├── scripts/                   # 烧录脚本
│   ├── program.sh             # 烧录程序
│   ├── erase_all.sh           # 擦除芯片
│   ├── verify.sh              # 验证程序
│   └── wch-riscv.cfg          # OpenOCD配置
│
├── makefile                   # 主Makefile
└── rules.mk                   # 编译规则
```

### 开始
克隆仓库并进入最小工程文件夹
```
git clone https://github.com/n0bu9/ch32v20x-makefile-project.git && cd ch32v20x-makefile-project/min_project
```
### 编译
```
make
```
### 烧录
插上WCH-LINK
```
make flash
```

