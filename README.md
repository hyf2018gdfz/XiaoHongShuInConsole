这不是一个小红书。

我把这个玩意定义为有发帖功能的社交平台，然而目前因为没有服务器，所以如果多个人之间需要交流，可能需要线下互相传数据（一个人在他的机子上写了点东西，然后把所有的数据打包给另一个人以实现数据通信）。

这个玩意的评论显示是参考Codeforces。

如果你能帮忙开发，我将非常感谢你。（然而我还没有写开发文档）

## 未来

未来将细致地实现scene.cpp。我认为这里的交互界面由“界面”（有点类似于浏览器的网页）构成，一个“界面”包含它的内容以及一个“目录”，通过选择目录的选项可以跳转到其他的“界面”或者“目录”。

在目前的实现中，我是用函数递归来描述“界面”的跳转，用函数返回来描述“界面”的“回到上一级”。实际上这构成了一个栈的关系：跳转就是把一个新的界面进栈，返回就是出栈。所以我期望单独拎出来一个函数控制这个栈的关系，这样可以尽可能减少递归带来的风险。

未来还将细致实现点赞、反对、编辑、删除等操作。

未来一定会支持多行文字的输入。

未来一定会支持用上下左右键实现选择选项/要回复的评论。

未来会使用cmake，但我现在还不很会这个。

未来会将部分写好的很少会再动的文件做成lib或dll，减少编译时间（现在编译一次要差不多十五秒钟真是太慢了吧）。

未来可能会支持多语言。

未来可能会搭建服务器以及抛弃控制台界面。

## 使用的外部库情况

使用了jsoncpp，未来将使用Crypto++对密码、手机号等个人数据进行加密。

## 协议

协议应该是MIT License，晚点我看看把协议写上去。

## 其他

头文件放在include中，源文件在source中，生成程序以及程序需要的数据放在out中，代码格式化细节在.clang-format里，编译指令参考.vscode里的tasks.json。
