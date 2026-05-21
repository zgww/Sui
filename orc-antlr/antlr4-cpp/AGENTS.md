# AGENTS.md

## 工程定位

这个仓库不是一个单一用途的小型 demo，而是一个“上游 ANTLR4 C++ Runtime + 自定义 Orc 语言工具链”的复合工程。

- 根目录主体仍然是 `antlr4-cpp runtime`，负责提供 ANTLR4 的 C++ 运行时库、CMake 构建、安装与测试能力。
- `demo/` 已经被扩展为 Orc 语言实验场，不只是 ANTLR 示例，而是包含：
  - Orc 语法定义
  - 语法生成产物
  - 基于 Visitor 的符号分析、类型分析与代码生成
  - 一个 Windows 优先的命令行编译器 / LSP 服务器 `orcc`
- `demo/Windows/antlr4-cpp-demo` 是当前最核心、最活跃、最接近“产品代码”的目录。
- `fssense/` 更像独立的文件监听实验区，不是主流程的一部分。

结论：如果后续要继续维护此仓库，应把它理解为“ANTLR4 C++ Runtime 仓库里嵌入了一个 Orc 语言编译与编辑器支持原型”，而不是纯 runtime 镜像。

## 顶层目录职责

### `runtime/`

ANTLR4 C++ runtime 主体源码。

- `runtime/src/`：ANTLR4 runtime 实现，按 `atn/`、`tree/`、`support/` 等子模块组织。
- `runtime/CMakeLists.txt`：构建 `antlr4_shared` / `antlr4_static`，并在启用测试时拉取 GoogleTest。
- `runtime/tests/`：runtime 单元测试，当前可见如 `Utf8Test.cpp`。
- `runtime/*.vcxproj`：Windows 下的 Visual Studio 工程文件。

该目录整体接近上游项目，不像 `demo/Windows/antlr4-cpp-demo` 那样带有明显的业务定制。

### `cmake/`

提供额外 CMake 脚本和打包支持。

- `ExternalAntlr4Cpp.cmake`
- `FindANTLR.cmake`
- `antlr4-runtime.cmake.in`
- `antlr4-generator.cmake.in`

主要服务于 runtime 的集成、安装和包导出。

### `demo/`

这个目录已经不是简单示例，而是 Orc 语言开发区。

- `Orc.g4`：主语法文件，定义 Orc 语言的词法/语法。
- `generated/`：ANTLR 生成的 C++ 解析器、Lexer、Visitor、Listener。
- `Windows/antlr4-cpp-demo/`：核心业务实现，包含编译器、符号系统、代码生成、LSP。
- `Linux/`、`Mac/`：较轻量的平台示例或历史构建入口。
- `generate-Orc.cmd` / `generate.sh`：语法生成脚本。
- `antlr-4.13.2-complete.jar`：生成语法所需 jar。

### `fssense/`

文件监听实验区。

- `filesense/filesense.cpp`：基于 Win32 `ReadDirectoryChangesW` 的监听原型。
- 与主工程中的 `FsWatcher.*` 有概念关联，但不是主编译链核心。

## 构建系统分析

## 根 CMake

根目录 `CMakeLists.txt` 仍然以 ANTLR runtime 为中心。

- 最低 CMake 版本：`3.15`
- C++ 标准：`C++17`
- 默认行为：
  - 构建 `runtime/`
  - 仅在 `WITH_DEMO=True` 时构建 `demo/`
- 若启用 demo，要求：
  - 已安装 Java
  - 显式指定 `ANTLR_JAR_LOCATION`

这说明：仓库的官方构建入口仍偏向 runtime，而 Orc 工具链更多依赖 `demo` 自己的脚本和 VS 工程。

## Demo CMake

`demo/CMakeLists.txt` 仍保留了更早期的 TLexer/TParser 示例逻辑，和当前 Orc 主线不完全一致。

- 它引用的是 `TLexer.g4` / `TParser.g4`
- Linux 可执行入口是 `demo/Linux/main.cpp`
- 当前 Windows 主项目实际上使用的是 Orc 语法和单独的 VS 方案

结论：`demo/CMakeLists.txt` 不能完全代表当前 Orc 主线构建方式，更多像历史示例构建脚本。

## Windows 主构建入口

当前最可信的主构建入口是：

- 解决方案：`demo/Windows/antlr4cpp-vs2022.sln`
- 主项目：`demo/Windows/antlr4-cpp-demo/antlr4-cpp-demo-vs2022.vcxproj`
- 产物名：`orcc`

特征：

- 依赖 `runtime/antlr4cpp-vs2022.vcxproj`
- 支持 `Debug/Release` + `DLL/Static` + `Win32/x64`
- x64 的 DLL 配置中甚至使用了 `ClangCL`
- 包含 `demo/generated` 与 `runtime/src` 下多组头文件目录

实际维护优先级应判断为：

1. `demo/Windows/antlr4cpp-vs2022.sln`
2. 根 `runtime` CMake
3. 其余 demo 平台目录

## Orc 语法与生成物

### 语法核心

`demo/Orc.g4` 定义的语言形态大致是“接近 C 语法，但加入面向对象、扩展、引用类型和闭包”的混合语言。

可见能力包括：

- `package`
- `include`
- `import`
- `struct`
- `enum`
- `class`
- `extension`
- 全局变量 / 全局函数
- `@` 引用类型
- `^` 闭包表达式与闭包类型
- `new`
- `.` / `->` 成员访问
- `if` / `for` / `while`
- 强制类型转换
- 函数指针
- scope 语句：`expr ~ {}` 或 `expr . {}`

这不是纯 C 语法，也不是 C++，而是一个自定义的面向对象脚本/系统语言。

### 语法生成方式

`demo/generate-Orc.cmd` 的实际命令是：

```bat
java -jar antlr-4.13.2-complete.jar -Dlanguage=Cpp -listener -visitor -o generated/ -package antlrcpptest Orc.g4
```

因此：

- `demo/generated/` 应视为生成目录
- 常规开发时不要手工修改 `generated/` 下文件
- 改语法应编辑 `demo/Orc.g4`，再重新运行生成脚本

## Windows 主工程架构

主代码位于 `demo/Windows/antlr4-cpp-demo/`。

可按职责拆为 7 层。

### 1. 入口与命令层

入口文件：`main.cpp`

程序行为：

- 无参数：默认启动 `OrcLsp::run()`，直接作为 LSP 服务器
- `lsp` / `-lsp`：显式启动 LSP
- `watch [dir]` / `w [dir]`：监听目录，文件变更时重编译
- `compile path` / `c path`：编译指定 `.orc`
- `recompileAll`：扫描并重编译全部 `.orc`
- `version` / `help`：输出版本或帮助

这说明 `orcc` 同时承担：

- 编译器前端
- 文件监听构建工具
- 语言服务器

### 2. 语义模型层

核心文件：

- `Symbol.h`
- `Symbol.cpp`

这是整个 Orc 工程最重要的领域模型层，定义了：

- 位置信息：`Position`、`Range`
- 类型系统：`SymbolType*`
  - 原始类型
  - 指针类型
  - 数组类型
  - `@` 引用类型
  - 函数类型
  - 闭包类型
- 符号定义：`SymbolDefinition*`
  - 类
  - 结构体
  - 枚举
  - 扩展
  - 函数
  - 变量
  - 方法
  - 字段
- 符号空间：`SymbolSpace`
- 符号加载器：`SymbolSpaceLoader`

这里不仅做“符号表”，还承担：

- JSON 序列化 / 反序列化
- import/include 依赖装载
- 类型转换辅助
- AST 辅助构造
- 跨文件符号解析

从体量和职责上看，`Symbol.*` 是 Orc 编译前端的“内核”。

### 3. AST 访问器层

代表文件：

- `SymbolBuilderVisitor.*`
- `TypeCheckerVisitor.*`
- `GenOrcCodeVisitor.*`
- `ReturnStringVisitor.*`
- 以及 `Symbol.cpp` 内部涉及的多个转换 Visitor

职责划分大致为：

- `SymbolBuilderVisitor`
  - 扫描 AST
  - 建立包、导入、类、结构体、扩展、函数、变量等符号定义
  - 填充 `SymbolSpace`
- `TypeCheckerVisitor`
  - 提供类型兼容性检查
  - 收集 `TypeError`
  - 但在磁盘编译主流程中当前被 `if (0)` 禁用
- `GenOrcCodeVisitor`
  - 将 AST 回生成为 Orc 文本，偏调试/中间输出用途
- 其他 Visitor
  - `AddSelfArgumentVisitor`
  - `ClosureCollectCaptureInfoVisitor`
  - `AddOutRefArgumentVisitor`
  - `TranslateVisitor`
  - `GenHeadCodeVisitor`
  - `GenCodeVisitor`

可以看出，真正的“编译”不是一次性完成，而是多阶段 AST 重写与再生成。

### 4. 编译流水线

磁盘编译主流程入口：`Project::compile()` -> `SymbolSpace::startBuild()`

`startBuild()` 的关键步骤如下：

1. 解析源码生成 AST
2. `fulfillFullname`
   - 先补全节点全名
3. `SymbolBuilderVisitor`
   - 建立符号空间
4. `AddSelfArgumentVisitor`
   - 为类方法 / 扩展方法显式补 `self` 参数
5. `ClosureCollectCaptureInfoVisitor`
   - 收集闭包捕获信息
6. `closureVi.translate()`
   - 做闭包相关 AST 转换
7. `AddOutRefArgumentVisitor`
   - 处理输出引用参数相关转换
8. `TranslateVisitor`
   - 做更通用的语义到目标形式的转译
9. `GenHeadCodeVisitor`
   - 生成 `*_orc.h`
10. `GenCodeVisitor`
    - 生成 `*_orc.c`
11. 将结果落盘到源文件同目录

产物规则：

- `Foo.orc` -> `Foo_orc.h`
- `Foo.orc` -> `Foo_orc.c`

这说明 Orc 当前目标语言是 C，而不是直接解释执行。

### 5. 符号缓存与增量装载

`SymbolSpaceLoader` 提供跨文件符号复用能力。

关键机制：

- `.orc` 文件对应一个 `SymbolSpace`
- 会将符号表落盘到 `_orc/*.symbols.json`
- 文件名使用 `MD5(absPath)`，避免同名文件冲突
- 若源文件 `mtime` 未更新，则优先复用缓存的符号 JSON

这套机制被用于：

- import 解析
- 工程扫描
- LSP 的跨文件补全 / 跳转基础

因此 `_orc/` 目录应理解为“索引缓存目录”，不是手工维护目录。

### 6. 项目管理与文件监听

核心文件：

- `Project.h/.cpp`
- `FsWatcher.h/.cpp`
- `fssense/filesense.cpp`（实验版）

`Project` 的职责：

- 监听目录下 `.orc` 文件变更
- 延迟去抖后触发 `build` / `unload`
- 编译成功后刷新 `SymbolSpaceLoader`
- 生成符号缓存文件
- Windows 下通过托盘气泡提示编译结果

这说明它不仅是“项目对象”，本质上还是一个简化版后台构建服务。

### 7. LSP 服务层

核心文件：

- `OrcLsp.h/.cpp`
- `LspActor.h/.cpp`
- `ProjectScanActor.h/.cpp`
- `SymbolActor.h/.cpp`
- `CodeCompletion.h/.cpp`
- `CodeCompletionCore.cpp/.hpp`

#### LSP 启动方式

`OrcLsp::run()`：

- 初始化多个 actor 线程
- 持续从 `stdin` 读取 JSON-RPC
- 解析 `Content-Length`
- 将消息转为 `LspMail`
- 投递给 `LspActor`

#### Actor 划分

当前 actor 设计包括：

- `lspActor`
  - 负责路由 LSP 请求
- `symbolActor`
  - 负责文档符号相关异步任务
- `diagnosticsActor`
  - 负责诊断任务调度
- `projectScanActor`
  - 扫描工程中的 `.orc` 文件并装载全局符号
- `timerActor`
  - 定时任务基础设施

但要注意：

- `SymbolActor` 本身非常薄，当前几乎只是占位类型
- 真实业务逻辑仍大量写在 `LspActor.cpp`

也就是说，这套 actor 架构“方向明确，但还未完全解耦”。

#### 当前已实现的 LSP 能力

从 `LspActor.cpp` 可确认已经路由并实现：

- `initialize`
- `initialized`
- `textDocument/didOpen`
- `textDocument/didChange`
- `textDocument/documentSymbol`
- `textDocument/completion`
- `textDocument/hover`
- `textDocument/definition`
- `textDocument/codeAction`
- `workspace/executeCommand`

`initialize` 返回的 capability 还声明了：

- completion
- formatting
- documentSymbol
- hover
- codeAction
- definition
- declaration
- typeDefinition
- references
- implementation
- diagnosticProvider

但“声明支持”不等于“全部实现完备”。从当前代码可确认最实的能力仍是：

- 文档符号
- 补全
- 悬停
- 跳转定义
- 诊断
- import 相关 code action / executeCommand

#### LSP 文档分析链路

LSP 与磁盘编译是两条不同链路。

LSP 侧文档打开 / 修改时，流程是：

1. `didOpen` / `didChange`
2. 更新 `textDocumentSymbolInfoMap`
3. `buildSymbolSpace_byTextDocument()`
   - 基于内存中文本重新解析 AST
   - `SymbolBuilderVisitor` 建立文档级符号空间
   - `AddSelfArgumentVisitor` 做最小必要 AST 调整
4. `doDiagnostic()`
   - 先做语法错误诊断
   - 再叠加类型 / 语义诊断能力

注意差异：

- LSP 文档链路目前不会像磁盘编译那样完整执行所有转译和代码生成步骤
- 它更偏向“快速语义索引 + 编辑器反馈”

这是合理设计，也意味着“LSP 看到的语义结果”和“真正编译产物”之间可能存在边缘差异。

## 重要目录与产物的真实语义

### `demo/generated/`

ANTLR 自动生成目录。

- 来源：`Orc.g4`
- 作用：解析 Orc 源码
- 建议：不要手改

### `demo/Windows/antlr4-cpp-demo/orc/`

这是 Orc 示例源码与生成 C 代码的混合目录。

里面同时存在：

- `*.orc`：输入样例
- `*_orc.c` / `*_orc.h`：对应生成产物
- `a.ast.json`、`amath-symbol.json` 等中间文件

因此它既是测试样例目录，又是编译输出目录。修改时要区分“源文件”和“生成物”。

### `demo/Windows/antlr4-cpp-demo/_orc/`

符号缓存目录。

- 存放 `*.symbols.json`
- 用于 import/load_orcModule/LSP 等快速装载
- 文件名与绝对路径绑定

可删除后重建，不应手工编辑。

## 测试与验证现状

### Runtime 侧

有正式测试。

- `runtime/tests/*.cpp`
- `runtime/CMakeLists.txt` 通过 `FetchContent` 获取 GoogleTest

说明 runtime 部分具备比较标准的工程化基础。

### Orc / LSP 侧

自动化测试明显不足。

- `main.cpp` 中保留了大量手工测试函数
- 样例 `.orc` 文件承担了回归样本角色
- 缺少系统化单元测试 / 集成测试

这意味着：

- 修改 Orc 语义或 LSP 行为时，需要更谨慎地做人工回归
- `orc/` 样例目录本质上就是很重要的回归资产

## 关键风险与现实判断

### 1. 工程是“双中心结构”

- `runtime/` 是相对标准的上游工程
- `demo/Windows/antlr4-cpp-demo/` 是高度定制业务工程

后续改动时不要把两者混为一谈。

### 2. 主维护平台明显偏 Windows

虽然仓库保留 Linux/macOS 目录和根 CMake，但 Orc 主线实现大量依赖：

- `Windows.h`
- 托盘气泡
- Win32 路径与编码处理
- Visual Studio 工程

因此当前真实的“一等公民平台”是 Windows。

### 3. CMake 与真实主流程并不完全同步

根 CMake 和 `demo/CMakeLists.txt` 更像 runtime / 老 demo 入口，而当前 Orc 主线更依赖：

- `generate-Orc.cmd`
- VS 解决方案
- `demo/Windows/antlr4-cpp-demo`

新增功能时不要默认“改完 CMake 就等于改完构建链”。

### 4. LSP 能力声明大于真实实现成熟度

`initialize` 中对外声明的 capability 很多，但实际稳定度主要集中在：

- diagnostics
- completion
- hover
- definition
- documentSymbol
- import code action

不要假定所有声明能力都已完整可用。

### 5. 类型检查当前未完全接入正式编译链

`TypeCheckerVisitor` 存在，但在 `SymbolSpace::startBuild()` 中被 `if (0)` 包裹。

这说明：

- 类型系统设计已经有较强意图
- 但“编译必须经过严格类型检查”目前还不是硬约束

修改类型相关逻辑时，要留意“LSP 诊断”和“磁盘编译”可能不同步。

## 建议的维护视角

如果后续继续开发此仓库，建议按下面的优先级理解与修改：

1. 把 `demo/Windows/antlr4-cpp-demo` 当作主产品代码
2. 把 `demo/Orc.g4` 当作语言规范入口
3. 把 `Symbol.*` 当作语义内核
4. 把 `Project.cpp` 当作磁盘编译入口
5. 把 `LspActor.cpp` 当作编辑器体验入口
6. 把 `runtime/` 当作相对独立、尽量少动的基础依赖

## 对后续开发者/Agent 的直接建议

### 修改语法时

- 先改 `demo/Orc.g4`
- 再运行 `demo/generate-Orc.cmd`
- 再检查 `demo/generated/`
- 最后回归 `orcc` 编译链和 LSP 行为

### 修改语义时

优先关注：

- `Symbol.h/.cpp`
- `SymbolBuilderVisitor.*`
- `TypeCheckerVisitor.*`
- `TranslateVisitor` 相关逻辑

因为这些文件决定“语法节点如何变成可解析的类型和符号”。

### 修改代码生成时

优先关注：

- `GenHeadCodeVisitor`
- `GenCodeVisitor`
- `GenOrcCodeVisitor`
- `SymbolSpace::startBuild()`

并用 `demo/Windows/antlr4-cpp-demo/orc/*.orc` 做回归。

### 修改 LSP 时

优先关注：

- `OrcLsp.cpp`
- `LspActor.cpp`
- `CodeCompletion.*`
- `ProjectScanActor.*`

并明确区分：

- 基于磁盘缓存的全局符号
- 基于内存文档的即时 AST / SymbolSpace

### 清理产物时

通常可以安全重建的内容包括：

- `demo/generated/`（重新生成）
- `demo/Windows/antlr4-cpp-demo/_orc/`（符号缓存）
- `demo/Windows/antlr4-cpp-demo/orc/*_orc.c`
- `demo/Windows/antlr4-cpp-demo/orc/*_orc.h`

但在删除前仍应确认这些文件不是当前用户刻意保留的结果样本。

## 最终结论

这个仓库最有价值、也最需要重点理解的，不是 ANTLR runtime 本身，而是建立在其上的 Orc 工具链：

- 它实现了一个自定义语言的语法定义
- 通过 Visitor 构建符号和类型系统
- 将 Orc 转译为 C 代码
- 同时提供文件监听与 LSP 编辑器支持

从成熟度上看：

- runtime 部分较稳定、工程化程度高
- Orc 部分功能完整度已经不低，但仍带明显原型和演进中痕迹
- Windows 是当前事实上的主战场

如果把这份工程当作“一个 Orc 语言前端 + C 代码生成器 + LSP 原型”，整体结构就会非常清晰。
