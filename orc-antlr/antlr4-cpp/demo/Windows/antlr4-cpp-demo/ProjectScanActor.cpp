#include "ProjectScanActor.h"
#include "FsUtil.h"
#include "UrlUtil.h"
#include "LspActor.h"

void ProjectScanActor::onStart()
{
	log(std::format("\n\nProjectScanActor::onStart. cwd:{}   exe:{}", FsUtil::getcwd(), FsUtil::getExecutionPath()));
	loadSubtree("./");
}

void ProjectScanActor::loadSubtree(std::string dirpath)
{
	Path p(dirpath);
	auto paths = p.listSubtree();
	log("\nProjectScanActor::loadSubtree");
	symbolList.clear();
	for (auto& p : paths) {
		if (p.ends_with(".orc")) {
			Path curpath(p);
			auto orcAbsPath = curpath.getAbsolute();
			loadSymbolOfOrcAbsPath(orcAbsPath.path());
		}
	}


}

void ProjectScanActor::loadSymbolOfOrcAbsPath(std::string orcAbsPath)
{
	auto uri = UrlUtil::absPath_toFileUri(orcAbsPath);

	log(std::format("abs:{}  uri:{}\n", orcAbsPath, uri));

	auto space = symbolSpaceLoader->load_orcModule(orcAbsPath);

	if (space) {
		for (auto &sym : space->symbols) {
			auto extensionDef = std::dynamic_pointer_cast<SymbolDefinitionExtension>(sym);
			if (extensionDef) {

				for (auto& extFn : extensionDef->members) {
					auto info = std::make_shared<GlobalSymbol>();

					auto funcDef = std::dynamic_pointer_cast<SymbolDefinitionFunction>(sym);
					if (funcDef) {
						info->name = funcDef->name;
						info->type = "extensionFunction";

						pushGlobalSymbol(info);
					}

					info->uri = uri;
					info->absPath = orcAbsPath;
				}
				continue;
			}


			auto info = std::make_shared<GlobalSymbol>();
			info->name = sym->name;
			info->uri = uri;
			info->absPath = orcAbsPath;

			auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(sym);
			if (classDef) {
				info->type = "class";
			}
			auto structDef = std::dynamic_pointer_cast<SymbolDefinitionStruct>(sym);
			if (structDef) {
				info->type = "struct";
			}
			auto enumItemDef = std::dynamic_pointer_cast<SymbolDefinitionEnumItem>(sym);
			if (enumItemDef) {
				info->type = "enumItem";
			}
			auto funcDef = std::dynamic_pointer_cast<SymbolDefinitionFunction>(sym);
			if (funcDef) {
				info->type = "function";
			}
			auto varDef = std::dynamic_pointer_cast<SymbolDefinitionVar>(sym);
			if (varDef) {
				info->type = "var";
			}

			pushGlobalSymbol(info);
		}
	}
}

void ProjectScanActor::pushGlobalSymbol(std::shared_ptr<GlobalSymbol> gsym)
{
	symbolList.push_back(gsym);

	log(std::format("\npushGlobalSymbol. name={}  type={} uri={}\n", 
		gsym->name, gsym->type, gsym->uri
	));
}

std::shared_ptr<GlobalSymbol> ProjectScanActor::findGlobalSymbolByName(std::string name)
{
	for (int i = 0; i < symbolList.size(); i++) {
		auto sym = symbolList.get(i);
		if (sym->name == name) {
			return sym;
		}
	}
	return nullptr;
}
