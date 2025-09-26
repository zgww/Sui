#pragma once
#include "./ActorByThread.h"
#include <string>
#include "Symbol.h"
#include "LspActor.h"

/*

扫描项目， 得到各个.orc文件的导出符号信息(类、结构体、枚举、扩展、全局函数、全局变量)

TODO:
1. 全局符号提示，并auto import  [ok]
2. import [ok]
3. diagnostics 语法错误+符号错误+auto import [v]
4. import color
5. unused var color
6. include 头文件全局符号提示 [v]


# 全局符号提示
1. 扫描得到全局.orc文件列表 [v]
2. 加载符号表 [v]
3. 记录到全局符号列表中 [v]
5. completion时，返回匹配的符号列表 [v]
*/


class GlobalSymbol {
public:
	std::string uri; //文档uri
	std::string absPath; //文档uri
	std::string name;
	//class|struct|enum|enumItem|function|var|extensionFunction
	std::string type;
};

class ProjectScanActor :public ActorByThread
{
public:
	std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
	SafeVector<std::shared_ptr<GlobalSymbol>> symbolList;


	virtual void onStart() override;
	void loadSubtree(std::string dirpath);

	void loadSymbolOfOrcAbsPath(std::string orcAbsPath);

	void pushGlobalSymbol(std::shared_ptr<GlobalSymbol> gsym);

	std::shared_ptr<GlobalSymbol> findGlobalSymbolByName(std::string name);
};

