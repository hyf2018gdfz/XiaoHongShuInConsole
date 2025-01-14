这不是一个小红书。

我把这个定义为有发帖功能的社交平台，其中帖子显示参考知乎，评论显示参考Codeforces。

如果你能帮忙开发，我将非常感谢你。（然而我还没有写开发文档）

## 未来

未来将细致地实现scene.cpp。我期望把这些函数的调用关系做成一个栈，栈内元素是函数指针，这样可以尽可能减少递归带来的风险。

未来还将细致实现点赞、反对、编辑、删除等操作。

未来一定会支持多行文字的输入。

未来一定会支持用上下左右键实现选择选项/要回复的评论。

未来会使用cmake，但我现在还不很会这个。

未来会将部分写好的很少会再动的文件做成lib，减少编译时间（现在编译一次要差不多十五秒钟真是太慢了吧）。

未来可能会支持多语言。

未来可能会搭建服务器以及抛弃控制台界面。

## 使用的外部库情况

使用了jsoncpp，未来将使用Crypto++对密码、手机号等个人数据进行加密。

## 协议

协议应该是MIT License，晚点我看看把协议写上去。

## 其他

代码格式化细节在.clang-format里，编译指令参考.vscode里的tasks.json。