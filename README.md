# OS-CourseDesign
A group project in Operating System /Linux （CS356 SJTU）

Introduction:
ghost.sh为整合后的脚本文件

ghost文件下编写lkm相关的框架和文件，在cd到ghost目录下后 make 便会生成.ko后缀的内核模块，可直接插入4.15linux内核
aes-target 是aes加密的目标路径（default）
cpu.c 为手动占用cpu资源程序
poc.c 为CVE-2019-13272漏洞提权代码
monitor.sh 监视器
dispose.sh 配置挖矿环境
run.sh 运行挖矿程序


Reference:
[1]脚本监控进程 https://blog.csdn.net/xin_yu_xin/article/details/45629743
[2]基于Khook的Reptile https://github.com/f0rb1dd3n/Reptile
[3] Rootkit与后门隐藏技术 https://codingnote.cc/p/1811
[4]开机自启脚本 https://blog.csdn.net/marujunyy/article/details/8466255
[5]提权源码 https://github.com/bcoles/kernel-exploits/blob/master/CVE-2019-13272/poc.c
[6]挖矿部署源码 https://github.com/xmrig/xmrig
[7]漏洞提权代码 https://github.com/bcoles/kernel-exploits/blob/master/CVE-2019-13272
[8]AES加密算法 https://blog.csdn.net/zxh2075/article/details/80630296?tdsourcetag=s_pcqq_aiomsg
[9]AES 加密 https://segmentfault.com/a/1190000011658363
[10]文件遍历 https://www.cnblogs.com/niuniuniuniu/p/10650956.html

