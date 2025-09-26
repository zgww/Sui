#pragma once
#include "./ActorByThread.h"
#include <string>
#include "Symbol.h"
#include "LspActor.h"

/*

ɨ����Ŀ�� �õ�����.orc�ļ��ĵ���������Ϣ(�ࡢ�ṹ�塢ö�١���չ��ȫ�ֺ�����ȫ�ֱ���)

TODO:
1. ȫ�ַ�����ʾ����auto import  [ok]
2. import [ok]
3. diagnostics �﷨����+���Ŵ���+auto import [v]
4. import color
5. unused var color
6. include ͷ�ļ�ȫ�ַ�����ʾ [v]


# ȫ�ַ�����ʾ
1. ɨ��õ�ȫ��.orc�ļ��б� [v]
2. ���ط��ű� [v]
3. ��¼��ȫ�ַ����б��� [v]
5. completionʱ������ƥ��ķ����б� [v]
*/


class GlobalSymbol {
public:
	std::string uri; //�ĵ�uri
	std::string absPath; //�ĵ�uri
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

