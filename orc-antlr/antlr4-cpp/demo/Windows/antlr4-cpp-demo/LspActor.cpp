#include <format>
#include "LspActor.h"
#include "Symbol.h"
#include <unordered_map>
#include <functional>
#include "UrlUtil.h"
#include "CodeCompletion.h"
#include "SymbolActor.h"
#include "ProjectScanActor.h"
#include "ThreadUtil.h"
#include "./SymbolBuilderVisitor.h"
#include <mutex>

#include "TypeCheckerVisitor.h"


int newline = 1; // \n
static std::unordered_map<int, std::function<void(json&)>> onResponseMap;

SafeMap<std::string, std::shared_ptr<TextDocumentSymbolInfo>> textDocumentSymbolInfoMap;
std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();


void waitAndHandleTextDocumentSymbolInfoMapOnLspActor(std::string uri, std::function<void(std::shared_ptr<TextDocumentSymbolInfo>)> fn) {
	timerActor->setInterval(100, 100, [=]() {
		auto info = textDocumentSymbolInfoMap.get(uri);
		if (info) {
			fn(info);
			return true;
		}
		return false;

		}, lspActor.get());
}
bool documentSymbol(int id, std::string method, json& params) {
	if (method != "textDocument/documentSymbol") return false;

	json textDocument = params["textDocument"];
	auto ent = textDocument.get<TextDocumentWithUri>();

	ent.uri = decodeURIComponent(ent.uri);
	log(std::format("ent:{} \n", ent.uri));

	//	auto result = json::parse(R"(
	//[
	//{"name":"say", "kind":12, "location":{"uri":"Scene.orc", "range":{"start":{"line":5,"character":1}, "end":{"line":5,"character":4}   }}},
	//{"name":"nice", "kind":12, "location":{"uri":"Scene.orc", "range":{"start":{"line":8,"character":1}, "end":{"line":8,"character":4}   }}}
	//]
	//
	//)");

	auto mail = std::make_shared<ActorMail>();
	mail->cbHandle = [ent, id](ActorMail* mail, ActorByThread* actor) {
		auto info = textDocumentSymbolInfoMap.get(ent.uri);
		if (info) {
			log(std::format("buildDocumentSymbols. start\n"));
			//auto sis = info->buildSymbolInfomations();
			auto sis = info->buildDocumentSymbols();
			log(std::format("buildDocumentSymbols. cnt:{}\n", sis.size()));
			json result = sis;

			//log(std::format("buildDocumentSymbols. symbols:{}\n", result.dump(4)));
			writeResponse(result, id);
			return;
		}

		};

	symbolActor->pushNotification(mail);
	//waitAndHandleTextDocumentSymbolInfoMapOnLspActor(ent.uri, [=](std::shared_ptr<TextDocumentSymbolInfo> info) {
	//		if (0) {
	//			log(std::format("buildSymbolInfomations. start\n"));
	//			//auto sis = info->buildSymbolInfomations();
	//			auto sis = info->buildDocumentSymbols();
	//			log(std::format("buildSymbolInfomations. cnt:{}\n", sis.size()));
	//			json result = sis;

	//			log(std::format("buildSymbolInfomations. symbols:{}\n", result.dump(4)));
	//			writeResponse(result, id);
	//			return true;
	//		}

	//		if (1) {
	//			log(std::format("buildDocumentSymbols. start\n"));
	//			//auto sis = info->buildSymbolInfomations();
	//			auto sis = info->buildDocumentSymbols();
	//			log(std::format("buildDocumentSymbols. cnt:{}\n", sis.size()));
	//			json result = sis;

	//			//log(std::format("buildDocumentSymbols. symbols:{}\n", result.dump(4)));
	//			writeResponse(result, id);
	//			return true;
	//		}


	//		SymbolInformation a;
	//		a.kind = SymbolKind_Function;
	//		a.name = "sdfs234234f2";
	//		a.location.uri = ent.uri;
	//		a.location.range.start.line = 5;
	//		a.location.range.start.character = 0;
	//		a.location.range.end.line = 5;
	//		a.location.range.end.character = 10;

	//		json result2 = json::array({ a });

	//		writeResponse(result2, id);
	//		return true;
	//	});

	return true;
}


//代码完成
bool completion(int id, std::string method, json& params) {
	if (method != "textDocument/completion") return false;

	auto completionParams = params.get< CompletionParams>();

	completionParams.textDocument.uri = decodeURIComponent(completionParams.textDocument.uri);

	log(std::format("completion \n"));
	if (0) {
		std::vector< CompletionItem> items;
		for (int i = 0; i < 10; i++) {
			CompletionItem e;
			e.kind = 1;
			e.label = std::format("hi_{}", i);
			items.push_back(e);
		}
		json jo = items;
		writeResponse(jo, id);
		return true;
	}
	//如果存在
	auto document = textDocumentSymbolInfoMap.get(completionParams.textDocument.uri);
	if (document) {
		if (completionParams.context.triggerKind == TriggerKind_Invoked) {
			log("\n===================TriggerKind_invoked\n=======================\n");

			auto code = document->textDocument->text;
			CodeCompletion cc;
			cc.initByCode(code);
			AstBuilder b;
			Position pos = {
				.line = 7, .character = 12
			};
			pos = completionParams.position;
			auto se = cc.codeCompleteAtPosition_forDot(pos, b);
			log(std::format("type completion: [{}]\n", se->getText()));

			// ast已经构建过了，直接取就可以
			auto program = document->program;
			ContainPositionNodeStackVisitor vi;
			vi.position = pos;
			vi.visit(program);

			log(std::format("vi. nodeStack.size:{}\n", vi.nodeStack.size()));
			if (se) {
				auto candText = se->getText();
				if (vi.nodeStack.size() > 0) {
					auto last = vi.nodeStack.back();
					{ //如果在函数内部
						auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(last);
						if (fn) {
							std::vector< CompletionItem> items;
							int i = 0;

							std::unordered_set<std::string> dealSet;
							//提取本空间的符号
							auto relSpaces = document->symbolSpace->listSymbolSpace_includeSelfAndImports();
							for (auto space : relSpaces) {
								for (auto sym : space->symbols) {
									if (dealSet.contains(sym->name)) {
										continue;
									}
									dealSet.insert(sym->name);

									auto match = StrUtil::matchChars_withOrder(sym->name, candText);
									if (match) {
										CompletionItem e;
										e.kind = 1;
										e.label = sym->name;
										e.sortText = std::format("{}", i++);

										items.push_back(e);
									}
								}
							}

							json jo = items;
							writeResponse(jo, id);
							return true;
						}
					}
					{
						auto ctx = ast_findAncestorByType<OrcParser::ProgramContext>(last);
						if (ctx) {
							//提示类型
							std::vector< CompletionItem> items;
							int i = 0;

							int insertImportLine = document->findInsertImportLine_afteLastImport();
							std::unordered_set<std::string> dealSet;
							//提取本空间的符号
							auto relSpaces = document->symbolSpace->listSymbolSpace_includeSelfAndImports();
							for (auto space : relSpaces) {
								for (auto sym : space->symbols) {
									if (dealSet.contains(sym->name)) {
										continue;
									}
									dealSet.insert(sym->name);

									auto match = StrUtil::matchChars_withOrder(sym->name, candText);
									if (match) {
										CompletionItem e;
										e.kind = 1;
										e.label = sym->name;
										e.sortText = std::format("{}", i++);
										
										items.push_back(e);
									}
								}
							}

							//全局扫描的符号
							for (int i = 0, l = projectScanActor->symbolList.size(); i < l; i++) {
								auto sym = projectScanActor->symbolList.get(i);
								if (dealSet.contains(sym->name)) {
									continue;
								}
								dealSet.insert(sym->name);

								auto match = StrUtil::matchChars_withOrder(sym->name, candText);
								log(std::format("type completion. candText:{} name;{}\n", candText, sym->name));
								if (match) {
									CompletionItem e;
									e.kind = 1;
									e.label = sym->name;
									e.sortText = std::format("{}", i++);
									/*e.textEdit.range.start = completionParams.position;
									e.textEdit.range.end = completionParams.position;
									e.textEdit.newText = sym->name;*/
									/*e.command.title = "orclsp.importUri";
									e.command.command = "orclsp.importUri";*/

									//需要 import
									if (!document->symbolSpace->existsImport(sym->absPath)) {
										TextEdit te;
										te.range.set(insertImportLine, 0, insertImportLine, 0);
										auto relPath = SymbolSpace_mkImportRelativePathByAbsPath(document->symbolSpace, sym->absPath);
										te.newText = std::format("import * from \"{}\"\n", relPath);
										e.additionalTextEdits.push_back(te);
									}

									//ImportUriParams param;
									//param.curUri = completionParams.textDocument.uri;
									//param.importUri = decodeURIComponent(sym->uri);// sym->uri;
									//json joParam = param;
									//e.command.arguments.push_back(joParam);
									//e.label = std::format("hi_{}", i);
									items.push_back(e);
								}
							}

							json jo = items;
							writeResponse(jo, id);
							return true;
						}
					}
				}
				
			}
			return true;
		}
	}


	if (document && completionParams.context.triggerKind == TriggerKind_TriggerCharacter) {
		auto code = document->textDocument->text;
		CodeCompletion cc;
		cc.initByCode(code);
		AstBuilder b;
		Position pos = {
			.line = 7, .character = 12
		};
		pos = completionParams.position;
		auto se = cc.codeCompleteAtPosition_forDot(pos, b);
		log(std::format("tmp: [{}]\n", se->getText()));

		// ast已经构建过了，直接取就可以
		auto program = document->program;
		ContainPositionNodeStackVisitor vi;
		vi.position = pos;
		vi.visit(program);

		log(std::format("vi. nodeStack.size:{}\n", vi.nodeStack.size()));
		if (se && vi.nodeStack.size() > 0) {
			/*std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
			SymbolBuilderVisitor symBuilder;
			symBuilder.space->symbolSpaceLoader = symbolSpaceLoader;

			auto absPath = fileUri_toAbsPath(document->textDocument->uri);
			symBuilder.init(absPath);
			symBuilder.visit(program);*/

			//AstMake mk;
			//tree::ParseTreeTracker _tracker;
			//mk.tracker = &_tracker;

			////给方法添加self参数
			//AddSelfArgumentVisitor addSelfArgumentVisitor;
			//addSelfArgumentVisitor.mk = &mk;
			//addSelfArgumentVisitor.visit(program);
			//cost.stat("addSelfArgumentVisitor");

			//se挂到最近的ctx下
			se->parent = vi.nodeStack.back();
			try {
				auto symType = ast_calcSymbolTypeOfExpressionResult(se, document->symbolSpace);
				auto typePointer = std::dynamic_pointer_cast<SymbolTypePointer>(symType->type);
				auto typeRef = std::dynamic_pointer_cast<SymbolTypeRef>(symType->type);
				auto nakeTypeName = typePointer ? typePointer->getNakeTypeName()
					: typeRef ? typeRef->getNakeTypeName() : "";
				//log(std::format("symType:{}\n", long long(symType.get())));
				if (nakeTypeName != "") {
					auto def = symType->hostSpace->findSymbolDefinitionByName_includeImports(nakeTypeName);
					{
						auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(def);
						if (classDef) {
							std::vector< CompletionItem> items;
							int i = 0;
							for (auto mem : classDef->listAllMembers_includeSupers()) {
								log(std::format("code complete:{}  full={}\n", mem->name, mem->fullname));

								CompletionItem e;
								e.kind = 1;
								e.label = mem->name;
								e.sortText = std::format("{}", i++);
								//e.label = std::format("hi_{}", i);
								items.push_back(e);
							}

							json jo = items;
							writeResponse(jo, id);
							return true;
						}
					}
				}
			}
			catch (std::string s) {
				log(std::format("查找符号异常:{}", s));
			}

			json jo = json::array({});
			writeResponse(jo, id);
			return true;
		}


	}
	else {
		log(std::format("completion fail. no document found\n"));
	}

	json jo = json::array({});
	writeResponse(jo, id);
	return true;
}

bool completion2(int id, std::string method, json& params) {
	if (method != "textDocument/completion") return false;

	auto completionParams = params.get< CompletionParams>();

	completionParams.textDocument.uri = decodeURIComponent(completionParams.textDocument.uri);

	log(std::format("completion \n"));
	if (0) {
		std::vector< CompletionItem> items;
		for (int i = 0; i < 10; i++) {
			CompletionItem e;
			e.kind = 1;
			e.label = std::format("hi_{}", i);
			items.push_back(e);
		}
		json jo = items;
		writeResponse(jo, id);
		return true;
	}

	//如果存在
	auto document = textDocumentSymbolInfoMap.get(completionParams.textDocument.uri);
	if (document && completionParams.context.triggerKind == TriggerKind_TriggerCharacter) {
		auto code = document->textDocument->text;
		CodeCompletion cc;
		cc.initByCode(code);
		AstBuilder b;
		Position pos = {
			.line = 7, .character = 12
		};
		pos = completionParams.position;
		auto se = cc.codeCompleteAtPosition_forDot(pos, b);
		log(std::format("tmp: [{}]\n", se->getText()));


		AstBuilder fullAst;
		fullAst.initByCode(code);
		auto program = fullAst.parser->program();
		ContainPositionNodeStackVisitor vi;
		vi.position = pos;
		vi.visit(program);

		log(std::format("vi. nodeStack.size:{}\n", vi.nodeStack.size()));
		if (se && vi.nodeStack.size() > 0) {
			std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
			SymbolBuilderVisitor symBuilder;
			symBuilder.space->symbolSpaceLoader = symbolSpaceLoader;

			auto absPath = fileUri_toAbsPath(document->textDocument->uri);
			symBuilder.init(absPath);
			symBuilder.visit(program);

			AstMake mk;
			tree::ParseTreeTracker _tracker;
			mk.tracker = &_tracker;

			//给方法添加self参数
			AddSelfArgumentVisitor addSelfArgumentVisitor;
			addSelfArgumentVisitor.mk = &mk;
			addSelfArgumentVisitor.visit(program);
			//cost.stat("addSelfArgumentVisitor");

			//se挂到最近的ctx下
			se->parent = vi.nodeStack.back();
			try {
				auto symType = ast_calcSymbolTypeOfExpressionResult(se, symBuilder.space);
				auto typePointer = std::dynamic_pointer_cast<SymbolTypePointer>(symType->type);
				auto typeRef = std::dynamic_pointer_cast<SymbolTypeRef>(symType->type);
				auto nakeTypeName = typePointer ? typePointer->getNakeTypeName()
					: typeRef ? typeRef->getNakeTypeName() : "";
				//log(std::format("symType:{}\n", long long(symType.get())));
				if (nakeTypeName != "") {
					auto def = symType->hostSpace->findSymbolDefinitionByName_includeImports(nakeTypeName);
					{
						auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(def);
						if (classDef) {
							std::vector< CompletionItem> items;
							for (auto mem : classDef->members) {
								log(std::format("code complete:{}  full={}\n", mem->name, mem->fullname));

								CompletionItem e;
								e.kind = 1;
								e.label = mem->name;
								//e.label = std::format("hi_{}", i);
								items.push_back(e);
							}

							json jo = items;
							writeResponse(jo, id);
							return true;
						}
					}
				}
			}
			catch (std::string s) {
				log(std::format("查找符号异常:{}", s));
			}

			json jo = json::array({});
			writeResponse(jo, id);
			return true;
		}


	}
	else {
		log(std::format("completion fail. no document found\n"));
	}

	json jo = json::array({});
	writeResponse(jo, id);
	return true;
}


bool hover(int id, std::string method, json& params) {
	if (method != "textDocument/hover") return false;

	std::shared_ptr<HoverParams> ent = std::make_shared<HoverParams>();
	params.get_to(*ent);
	ent->textDocument.uri = decodeURIComponent(ent->textDocument.uri);

	if (textDocumentSymbolInfoMap.contains(ent->textDocument.uri)) {

		auto info = textDocumentSymbolInfoMap.get(ent->textDocument.uri);
		auto code = info->textDocument->text;
		AstBuilder fullAst;
		fullAst.initByCode(code);
		auto program = fullAst.parser->program();
		ContainPositionNodeStackVisitor vi;
		vi.position = ent->position;
		vi.visit(program);
		if (vi.nodeStack.size() > 0) {
			auto back = vi.nodeStack.back();
			if (back) {
				auto expr = ast_findAncestorByType<OrcParser::SingleExpressionContext>(back);
				if (expr) { //表达式，可以求解符号

					std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
					SymbolBuilderVisitor symBuilder;
					symBuilder.space->symbolSpaceLoader = symbolSpaceLoader;
					auto absPath = fileUri_toAbsPath(ent->textDocument.uri);
					symBuilder.init(absPath);
					symBuilder.visit(program);


					AstMake mk;
					tree::ParseTreeTracker _tracker;
					mk.tracker = &_tracker;

					//给方法添加self参数
					AddSelfArgumentVisitor addSelfArgumentVisitor;
					addSelfArgumentVisitor.mk = &mk;
					addSelfArgumentVisitor.visit(program);

					try {
						auto symInfo = ast_calcSymbolTypeOfExpressionResult(expr, symBuilder.space);
						if (symInfo && symInfo->type) {
							log(std::format("hover Expression succ\n"));

							HoverResponse r;
							r.contents.value = std::string("sym:") +
								symInfo->type->toString();
							r.range.set(
								ent->position.line, expr->getStart()->getCharPositionInLine(),
								ent->position.line, expr->getStop()->getCharPositionInLine() + expr->getStop()->getText().size()
							);

							json jo = r;
							writeResponse(jo, id);
							return true;
						}
					}
					catch (std::string s) {
						log(std::format("hover calc symbol error:{}\n", s));
					}
				}

				log(std::format("hover succ\n"));

				HoverResponse r;
				r.contents.value = std::string("ast:") +
					back->getText().substr(0, 40);
				r.range.set(
					ent->position.line, ent->position.character,
					ent->position.line, ent->position.character + 3
				);

				json jo = r;
				writeResponse(jo, id);
				return true;
			}
		}
	}


	log(std::format("hover succ\n"));

	HoverResponse r;
	r.contents.value = "nothing recognized";
	r.range.set(
		ent->position.line, ent->position.character,
		ent->position.line, ent->position.character + 3
	);

	json jo = r;
	writeResponse(jo, id);
	return true;
}

bool gotoDefinition(int id, std::string method, json& params) {
	if (method != "textDocument/definition") return false;

	std::shared_ptr<TextDocumentPositionParams> ent = std::make_shared<TextDocumentPositionParams>();
	params.get_to(*ent);

	ent->textDocument.uri = decodeURIComponent(ent->textDocument.uri);

	if (textDocumentSymbolInfoMap.contains(ent->textDocument.uri)) {
		auto info = textDocumentSymbolInfoMap.get(ent->textDocument.uri);
		auto code = info->textDocument->text;
		AstBuilder fullAst;
		fullAst.initByCode(code);
		auto program = fullAst.parser->program();
		ContainPositionNodeStackVisitor vi;
		vi.position = ent->position;
		vi.visit(program);
		if (vi.nodeStack.size() > 0) {
			auto back = vi.nodeStack.back();
			if (back) {
			auto expr = ast_findAncestorByType<OrcParser::SingleExpressionContext>(back);
			if (expr) { //表达式，可以求解符号

				std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
				SymbolBuilderVisitor symBuilder;
				symBuilder.space->symbolSpaceLoader = symbolSpaceLoader;
				auto absPath = fileUri_toAbsPath(ent->textDocument.uri);
				symBuilder.init(absPath);
				symBuilder.visit(program);

				AstMake mk;
				tree::ParseTreeTracker _tracker;
				mk.tracker = &_tracker;

				//给方法添加self参数
				AddSelfArgumentVisitor addSelfArgumentVisitor;
				addSelfArgumentVisitor.mk = &mk;
				addSelfArgumentVisitor.visit(program);

				try {
					//memberdot
					{

						auto dotExpr = dynamic_cast<OrcParser::MemberDotExpressionContext*>(expr);
						//取属性
						if (dotExpr) {
							auto symInfo = ast_calcSymbolTypeOfExpressionResult(dotExpr->singleExpression(), symBuilder.space);
							if (symInfo) {
								auto def = symInfo->findSymbolDefinition();
								//类
								auto classDef = dynamic_cast<SymbolDefinitionClass*>(def.get());
								if (classDef) {
									auto memberName = dotExpr->Id()->getText();
									auto member = classDef->findMemberByName_includeSupers(memberName);
									if (member) {
										log(std::format("gotoDefinition for member Expression succ\n"));
										LocationLink r;
										r.originSelectionRange.set(
											expr->getStart()->getLine() - 1, expr->getStart()->getCharPositionInLine(),
											expr->getStop()->getLine() - 1, expr->getStop()->getCharPositionInLine() + expr->getStop()->getText().size()
										);
										if (def) {
											r.targetRange = member->member->range;
										}
										else {
											r.targetRange.set(
												1, 0,
												1, 10
											);
										}
										r.targetSelectionRange = r.targetRange;
										r.targetUri = std::format("file:///{}", member->member->hostSpace->path);
										std::vector<LocationLink> links{ r };
										json jo = r;
										writeResponse(jo, id);
										return true;
									}
								}
							}
						}
					}




					auto symInfo = ast_calcSymbolTypeOfExpressionResult(expr, symBuilder.space);
					if (symInfo) {
						auto def = symInfo->findSymbolDefinition();
						log(std::format("hover Expression succ\n"));
						LocationLink r;
						r.originSelectionRange.set(
							expr->getStart()->getLine() - 1, expr->getStart()->getCharPositionInLine(),
							expr->getStop()->getLine() - 1, expr->getStop()->getCharPositionInLine() + expr->getStop()->getText().size()
						);
						if (def) {
							r.targetRange = def->range;
						}
						else {

							r.targetRange.set(
								1, 0,
								1, 10
							);
						}
						r.targetSelectionRange = r.targetRange;
						r.targetUri = std::format("file:///{}", symInfo->hostSpace->path);
						std::vector<LocationLink> links{ r };
						json jo = r;
						writeResponse(jo, id);
						return true;
					}
				}
				catch (std::string s) {
					log(std::format("hover calc symbol error:{}\n", s));
				}
			}
		}
		}
	}

	log(std::format("gotoDefinition succ\n"));

	LocationLink r;
	r.originSelectionRange.set(
		ent->position.line, ent->position.character,
		ent->position.line, ent->position.character + 3
	);
	r.targetRange.set(
		ent->position.line + 1, ent->position.character,
		ent->position.line + 1, ent->position.character + 3
	);
	r.targetSelectionRange.set(
		ent->position.line + 1, ent->position.character,
		ent->position.line + 1, ent->position.character + 3
	);
	r.targetUri = decodeURIComponent(ent->textDocument.uri);
	std::vector<LocationLink> links{ r };


	Location ret;
	ret.uri = decodeURIComponent(ent->textDocument.uri);
	ret.range.set(
		ent->position.line + 1, ent->position.character,
		ent->position.line + 1, ent->position.character + 3
	);

	json jo = links;
	//json jo = ret;
	writeResponse(jo, id);
	return true;
}

bool codeAction(int id, std::string method, json& params) {
	if (method != "textDocument/codeAction") return false;

	std::shared_ptr<CodeActionParams> ent = std::make_shared<CodeActionParams>();
	params.get_to(*ent);
	ent->textDocument.uri = decodeURIComponent(ent->textDocument.uri);

	log(std::format("codeAction succ\n"));

	CodeAction a;
	a.title = "import";
	a.kind = "refactor";
	a.isPrefered = true;
	a.command.title = "orclsp.import";
	a.command.command = "orclsp.import";

	a.command.arguments.push_back(*ent.get());


	std::vector<CodeAction> acts{ a };
	json jo = acts;
	writeResponse(jo, id);
	return true;
}

void applyEdit_insertLine(std::string uri, int line, std::string newline) {
	auto plainUri = decodeURIComponent(uri);
	TextEdit textEdit;
	textEdit.newText = newline;
	textEdit.range.set(line, 0, line, 0);

	std::vector<TextEdit> textEdits;
	textEdits.push_back(textEdit);

	ApplyWorkspaceEditParams p;
	p.label = "insertLine";
	p.edit.changes[plainUri] = textEdits;
	json params = p;
	writeRequest("workspace/applyEdit", params, nullptr);
}

// 判断符号空间里是否已经import了fileUri
bool SymbolSpace_existsByAbsPath(std::shared_ptr<SymbolSpace> space, std::string abspath) {
	//auto abspath = fileUri_toAbsPath(fileUri);
	if (space) {
		for (auto imp : space->imports) {
			if (imp->path == abspath || imp->abspath == abspath) {
				return true;
			}
		}
	}
	return false;
}
std::string SymbolSpace_mkImportRelativePathByAbsPath(std::shared_ptr<SymbolSpace> space, std::string abspath) {
	//auto abspath = fileUri_toAbsPath(fileUri);
	if (space) {
		Path p(space->path);
		Path imp(abspath);
		Path rel = imp.relativeToBaseDir(p.dirname());
		return rel.path();
	}
	return "";
}



void doImport(std::shared_ptr<CodeActionParams> ent) {


	if (textDocumentSymbolInfoMap.contains(ent->textDocument.uri)) {
		auto info = textDocumentSymbolInfoMap.get(ent->textDocument.uri);
		auto code = info->textDocument->text;
		AstBuilder fullAst;
		fullAst.initByCode(code);
		auto program = fullAst.parser->program();
		ContainPositionNodeStackVisitor vi;
		vi.position = ent->range.start;
		vi.visit(program);
		auto back = vi.nodeStack.back();
		if (back) {
			auto typeContext = ast_findAncestorByType<OrcParser::TypeContext>(back);
			auto varDecl = ast_findAncestorByType<OrcParser::VarDeclarationContext>(back);
			if (varDecl) {
				typeContext = varDecl->type();
			}

			if (typeContext) { //光标在类型上
				auto nakeName = ast_getNakeTypeName_fromTypeContext(typeContext);
				if (!nakeName.empty()) {
					auto globalSym = projectScanActor->findGlobalSymbolByName(nakeName);
					if (globalSym) {
						auto impPath = SymbolSpace_mkImportRelativePathByAbsPath(info->symbolSpace, globalSym->absPath);
						if (impPath.empty()) {
							log(std::format("do import fail. mkRelativePath fail:{} {}", info->symbolSpace->path, globalSym->absPath));
						}
						else {
							int line = info->findInsertImportLine_afteLastImport();
							applyEdit_insertLine(ent->textDocument.uri, line, std::format(
								"import * from \"{}\"\n", impPath
							));
						}
					}
				}
				return;
			}

			auto expr = ast_findAncestorByType<OrcParser::SingleExpressionContext>(back);
			if (expr) { //表达式，可以求解符号

				std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
				SymbolBuilderVisitor symBuilder;
				symBuilder.space->symbolSpaceLoader = symbolSpaceLoader;
				auto absPath = fileUri_toAbsPath(ent->textDocument.uri);
				symBuilder.init(absPath);
				symBuilder.visit(program);

				AstMake mk;
				tree::ParseTreeTracker _tracker;
				mk.tracker = &_tracker;

				//给方法添加self参数
				AddSelfArgumentVisitor addSelfArgumentVisitor;
				addSelfArgumentVisitor.mk = &mk;
				addSelfArgumentVisitor.visit(program);

				try {
					auto symInfo = ast_calcSymbolTypeOfExpressionResult(expr, symBuilder.space);
					if (symInfo) {
						auto def = symInfo->findSymbolDefinition(); //错误了。 符号要从整个项目的缓存中查找才对
						if (def) {

							log(std::format("doImport Expression succ: import * from '{}'\n", def->hostSpace->path));

							if (false && SymbolSpace_existsByAbsPath(symBuilder.space, def->hostSpace->path)) {
								log(std::format("do import fail. exists: {} {}", symBuilder.space->path, def->hostSpace->path));
							}
							else {
								auto impPath = SymbolSpace_mkImportRelativePathByAbsPath(symBuilder.space, def->hostSpace->path);
								if (impPath.empty()) {
									log(std::format("do import fail. mkRelativePath fail:{} {}", symBuilder.space->path, def->hostSpace->path));
								}
								else {
									int line = info->findInsertImportLine_afteLastImport();
									applyEdit_insertLine(ent->textDocument.uri, line, std::format(
										"import * from \"{}\"\n", impPath
									));
								}
							}
						}
						return;
					}
				}
				catch (std::string s) {
					log(std::format("hover calc symbol error:{}\n", s));
				}
			}
			
			//todo 用所在的id当类型名?
		}
	}
	showMessage("import fail.");
}

void doImportUri(std::shared_ptr<ImportUriParams> ent) {


	if (textDocumentSymbolInfoMap.contains(ent->curUri)) {
		auto info = textDocumentSymbolInfoMap.get(ent->curUri);
		if (info) {
			auto importUriAbsPath = fileUri_toAbsPath(ent->curUri);
			if (info->symbolSpace->existsImport(importUriAbsPath)) { // do nothing
				log(std::format("import ignore.  exists.: {}", importUriAbsPath));
				return;
			}
			//do import
			auto impPath = SymbolSpace_mkImportRelativePathByAbsPath(info->symbolSpace, importUriAbsPath);
			if (impPath.empty()) {
				log(std::format("do import fail. mkRelativePath fail:{} {}", info->symbolSpace->path, importUriAbsPath));
			}
			else {
				applyEdit_insertLine(ent->curUri, 2, std::format(
					"import * from \"{}\"\n", impPath
				));
			}
		}
	}
}


bool executeCommand(int id, std::string method, json& params) {
	if (method != "workspace/executeCommand") return false;

	std::shared_ptr<ExecuteCommandParams> ent = std::make_shared<ExecuteCommandParams>();
	params.get_to(*ent);

	if (ent->command == "orclsp.import") {
		log(std::format("\n orclp.import: hi!!!!!!!!!!!!!!\n"));

		std::shared_ptr<CodeActionParams> codeActionParams = std::make_shared<CodeActionParams>();
		if (ent->arguments.size() > 0) {
			ent->arguments[0].get_to(*codeActionParams);
			doImport(codeActionParams);
		}

	}
	if (ent->command == "orclsp.importUri") {
		log(std::format("\n orclp.importUri: hi!!!!!!!!!!!!!!\n"));

		std::shared_ptr<ImportUriParams> cmdParams = std::make_shared<ImportUriParams>();
		if (ent->arguments.size() > 0) {
			ent->arguments[0].get_to(*cmdParams);
			doImportUri(cmdParams);
		}

	}

	log(std::format("executeCommand succ\n"));

	json jo = json::object();
	writeResponse(jo, id);
	return true;
}

void LspMail::handle(std::shared_ptr<ActorByThread> actor)
{

	auto id = json_getInt(jo, "id");
	auto method = json_getString(jo, "method");

	if (method == "") { //说明是响应
		json result = jo.contains("result") ? jo["result"] : json::object();
		log(std::format("\nroute. id:{}, json:{}, hasOnResponse:{}\n", id,
			jo.dump(4),

			onResponseMap.contains(id) ? 1 : 0));
		if (id != 0) {
			if (onResponseMap.contains(id)) {
				auto fn = onResponseMap[id];
				//log("call onResponse\n");
				fn(result);

				onResponseMap.erase(onResponseMap.find(id));
				log(std::format("remain onResponseMap size:{}\n", onResponseMap.size()));
			}
		}
		return;
	}

	json params = jo.contains("params") ? jo["params"] : json::object();
	log(std::format("route. id:{}, method:{}, params:{}\n", id, method, params.dump(4)));

	if (initialize(id, method, params)) return;
	if (initialized(id, method, params)) return;
	if (didOpen(id, method, params)) return;
	if (documentSymbol(id, method, params)) return;
	if (completion(id, method, params)) return;
	if (didChange(id, method, params)) return;
	if (hover(id, method, params)) return;
	if (gotoDefinition(id, method, params)) return;
	if (codeAction(id, method, params)) return;
	if (executeCommand(id, method, params)) return;


	{
		json result = json::object();
		writeResponse(result, id);
	}

}


void printOnLspActor(std::string str) {
	lspActor->runOnThisActor([=]() {

		printf(str.c_str());
		fflush(stdout);
		
		});
}

void writeResponse(json& result, int id) {
	//if (id == 0) return;
	json resp;
	resp["jsonrpc"] = "2.0";
	resp["id"] = id;
	resp["result"] = result;

	auto text = resp.dump();
	auto out = std::format("Content-Length: {}{}{}", text.size(), newline == 1 ? "\n\n" : "\r\n\r\n", text); //为啥跟规范不一样。  规范不是\r\n吗
	//log(std::format("\tresponse:{}", out.c_str()));
	log(std::format("\nresponse:{}\n", out));
	
	printOnLspActor(out);
}

void log(std::string s) {
	static FILE* f;
	if (!f) {
		f = fopen("stdin.log", "w+");
	}
	fwrite(s.c_str(), 1, s.length(), f);
	fflush(f);
}


bool initialize(int id, std::string method, json& params) {
	if (method != "initialize") return false;
	json result = json::parse(R"(
{
	"capabilities": {
		"colorProvider": {},
		"completion":{},
		"formatting":{},
		"textDocumentSync":{
			"openClose": true,
			"willSave":true,
			"save":true,
			"change":1
		},
		"completionProvider":{
			"triggerCharacters": [".", ">"],
			"allCommitCharacters": [
				"import",
				"include",
				"class",
				"extends",
				"extension",
				"from",
				"while",
				"switch",
				"default",
				"break",
				"return",
				"continue",
				"type"
			],
			"completionItem":{
				"labelDetailsSupport": true
			},
			"resolveProvider": false
		},
		"executeCommandProvider":{
			"commands": [
				"orclsp.import",
				"orclsp.importUri",
				"orclsp.say"
			]
		},
		"documentSymbolProvider":{
		},
		"hoverProvider":{},
		"codeActionProvider":{},
		"documentLinkProvider":{},
		"documentHighlightProvider":{},
		"typeHierarchyProvider":{},
		"callHierarchyProvider":{},
		"referencesProvider":{},
		"definitionProvider":{},
		"declarationProvider":{},
		"typeDefinitionProvider":{},
		"diagnosticProvider":{
			"interFileDependencies": true,
			"workspaceDiagnostics":true
		},
		"implementationProvider":{}
	},
	"serverInfo":{
		"name":"orcc -lsp",
		"version": "0.0.2"
	}
}

)");
	writeResponse(result, id);
	return true;
}


bool initialized(int id, std::string method, json& params) {
	if (method != "initialized") return false;

//	std::thread t([]() {
//		std::this_thread::sleep_for(std::chrono::seconds(3));
//		json result = json::parse(R"(
//{
//		"type":3,
//		"message": "hi",
//		"actions": [
//			{"title":"retry"},
//			{"title":"open log"}
//		]
//}
//)");
//		writeRequest(std::string("window/showMessageRequest"), result, [](json& result) {
//			log(std::format("recv reply:{}\n", result.dump(4)));
//			});
//		});
//	t.detach();

	return true;
}
void writeNotification(std::string method, json& params) {
	json resp;
	resp["jsonrpc"] = "2.0";

	resp["method"] = method;
	resp["params"] = params;

	auto text = resp.dump();
	auto out = std::format("Content-Length: {}{}{}", text.size(), newline == 1 ? "\n\n" : "\r\n\r\n", text); //为啥跟规范不一样。  规范不是\r\n吗
	//log(std::format("\nserver=>client request:{}", out));
	log(std::format("\nserver=>client notification:{}\n", out));

	//printf(out.c_str());
	//fflush(stdout);


	printOnLspActor(out);

}

int writeRequest(std::string method, json& params, std::function<void(json&)> onResponse) {
	static int id = 1000;
	id++;
	json resp;
	resp["jsonrpc"] = "2.0";
	resp["id"] = id;
	resp["method"] = method;
	resp["params"] = params;

	auto text = resp.dump();
	auto out = std::format("Content-Length: {}{}{}", text.size(), newline == 1 ? "\n\n" : "\r\n\r\n", text); //为啥跟规范不一样。  规范不是\r\n吗
	//log(std::format("\nserver=>client request:{}", out));
	log(std::format("\nserver=>client request:{}\n", out));

	//printf(out.c_str());
	//fflush(stdout);
	printOnLspActor(out);

	if (onResponse) {
		//log2(std::format("\nbind id => onResponse\n"));
		onResponseMap[id] = onResponse;
	}
	return id;
}




void TextDocumentSymbolInfo::buildSymbolInfomations_bySymbols(std::vector<std::shared_ptr<SymbolDefinition>>& symbols,
	std::vector<SymbolInformation>& ret) {
	static int line = 0;


	for (auto& sym : symbols) {
		line++;
		log(std::format("buildSymbolInfomations_bySymbols. sym.name:{} \n", sym->name));
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionClass>(sym);
			if (def) {
				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Class;
				si.kind = SymbolKind_Function;
				//si.setLocation(this->textDocument->uri, line, 0, line, 10);
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);

				buildSymbolInfomations_bySymbols(def->members, ret);
				continue;
			}
		}

		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionStruct>(sym);
			if (def) {
				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Struct;
				si.kind = SymbolKind_Function;
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);
				continue;
			}
		}

		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionFunction>(sym);
			if (def) {
				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Function;
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);
				continue;
			}
		}

		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionEnum>(sym);
			if (def) {

				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Enum;
				si.kind = SymbolKind_Function;
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);
				continue;
			}
		}
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionMethod>(sym);
			if (def) {
				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Method;
				si.kind = SymbolKind_Function;
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);
				continue;
			}
		}
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionClassField>(sym);
			if (def) {
				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Field;
				si.kind = SymbolKind_Function;
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);
				continue;
			}
		}
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionVar>(sym);
			if (def) {
				SymbolInformation si;
				si.name = def->name;
				si.kind = SymbolKind_Variable;
				si.kind = SymbolKind_Function;
				si.setLocation("ViewBuilder.orc", line, 0, line, 10);
				ret.push_back(si);
				continue;
			}
		}
	}
}
std::vector<SymbolInformation> TextDocumentSymbolInfo::buildSymbolInfomations() {
	std::vector<SymbolInformation> ret;

	//遍历符号表
	if (symbolSpace) {
		log(std::format("buildSymbolInfomations_bySymbols. start\n"));
		buildSymbolInfomations_bySymbols(symbolSpace->symbols, ret);
	}

	return ret;
}

void TextDocumentSymbolInfo::buildDocumentSymbols_bySymbols(std::vector<std::shared_ptr<SymbolDefinition>>& symbols,
	std::vector<DocumentSymbol>& ret) {
	static int line = 0;


	for (auto& sym : symbols) {
		line++;
		log(std::format("buildSymbolInfomations_bySymbols. sym.name:{} ret:{}\n", sym->name, ret.size()));
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionClass>(sym);
			if (def) {
				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Class;
				si.kind = SymbolKind_Function;
				//si.setLocation(this->textDocument->uri, line, 0, line, 10);
				si.setRangeByRange(def->range);

				buildDocumentSymbols_bySymbols(def->members, si.children);
				ret.push_back(si);
				continue;
			}
		}

		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionStruct>(sym);
			if (def) {
				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Struct;
				si.kind = SymbolKind_Function;
				si.setRangeByRange(def->range);
				ret.push_back(si);
				continue;
			}
		}

		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionFunction>(sym);
			if (def) {
				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Function;
				si.setRangeByRange(def->range);
				ret.push_back(si);
				continue;
			}
		}

		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionEnum>(sym);
			if (def) {

				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Enum;
				si.kind = SymbolKind_Function;
				si.setRangeByRange(def->range);
				ret.push_back(si);
				continue;
			}
		}
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionMethod>(sym);
			if (def) {
				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Method;
				si.kind = SymbolKind_Function;
				si.setRangeByRange(def->range);
				ret.push_back(si);
				continue;
			}
		}
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionClassField>(sym);
			if (def) {
				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Field;
				si.kind = SymbolKind_Function;
				si.setRangeByRange(def->range);
				ret.push_back(si);
				continue;
			}
		}
		{
			auto def = std::dynamic_pointer_cast<SymbolDefinitionVar>(sym);
			if (def) {
				DocumentSymbol si;
				si.name = def->name;
				si.kind = SymbolKind_Variable;
				si.kind = SymbolKind_Function;
				si.setRangeByRange(def->range);
				ret.push_back(si);
				continue;
			}
		}
	}
}
std::vector<DocumentSymbol> TextDocumentSymbolInfo::buildDocumentSymbols() {
	std::vector<DocumentSymbol> ret;

	//遍历符号表
	if (symbolSpace) {
		log(std::format("buildSymbolInfomations_bySymbols. start\n"));
		buildDocumentSymbols_bySymbols(symbolSpace->symbols, ret);
	}

	return ret;
}

int TextDocumentSymbolInfo::findLastImportLine()
{
	if (symbolSpace && symbolSpace->imports.size() > 0) {
		return symbolSpace->imports.back()->line;
	}
	return -1;
}

int TextDocumentSymbolInfo::findInsertImportLine_afteLastImport() {
	int at = findLastImportLine();
	if (at >= 0) {
		return at + 1;
	}
	//要在package之后
	auto lines = StrUtil::split_by_re(this->textDocument->text, "\n");
	for (int i = 0; i < lines.size(); i++) {
		auto line = lines[i];
		line = StrUtil::trim(line);
		if (line.starts_with("package ")) {
			return i + 1;
		}
	}
	return 0;
}


class SyntaxErrorInfo {
public:
	Token* offendingSymbol;
	size_t line;
	size_t charPositionInLine;
	std::string msg;
};
class ErrorListener : public BaseErrorListener {
public:
	std::vector< SyntaxErrorInfo> infos;
	virtual void syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line, size_t charPositionInLine,
		const std::string& msg, std::exception_ptr e) override {
		SyntaxErrorInfo info;
		info.offendingSymbol = offendingSymbol;
		info.line = line;
		info.charPositionInLine = charPositionInLine;
		info.msg = msg;

		infos.push_back(info);
	}
};
class ErrorNodeVisitor : public OrcBaseVisitor {
public:
	std::vector<tree::ErrorNode*> errorNodes;
	virtual std::any visitChildren(tree::ParseTree* node) override {
		auto err = dynamic_cast<tree::ErrorNode*>(node);
		if (err) {
			errorNodes.push_back(err);
		}
		return OrcBaseVisitor::visitChildren(node);
	}
};
void doDiagnostic(std::string uri) {
	if (textDocumentSymbolInfoMap.contains(uri)) {
		PublishDiagnosticsParams p;
		p.uri = uri;

		auto info = textDocumentSymbolInfoMap.get(uri);

		AstBuilder fullAst;
		fullAst.initByCode(info->textDocument->text);

		ErrorListener errListener;
		fullAst.parser->removeErrorListeners(); //阻止往控制台打印。因为控制台是lsp的通信通道
		fullAst.parser->addErrorListener(&errListener);

		auto program = fullAst.parser->program();
		int errNum = fullAst.parser->getNumberOfSyntaxErrors();
		//语法错误识别
		if (errNum > 0) {
			if (1) {
				if (errListener.infos.size() > 0) {

					for (auto& info : errListener.infos) {
						int l = info.line - 1;
						int c = info.charPositionInLine;
						std::string symText = "";
						if (info.offendingSymbol) {
							symText = info.offendingSymbol->getText();
						}

						Diagnostic diag;
						diag.range.set(l, c, l, c + (info.offendingSymbol ? info.offendingSymbol->getText().size() : 2));
						diag.severity = 1;
						diag.message = std::format("syntax error. symbol:{}, msg:{}", symText, info.msg);
						p.diagnostics.push_back(diag);
					}
				}
			
			}
			/*if (0) {
				ErrorNodeVisitor vi;
				vi.visit(program);
				if (vi.errorNodes.size() > 0) {
					PublishDiagnosticsParams p;
					p.uri = uri;

					for (auto errNode : vi.errorNodes) {
						int l = errNode->getSymbol()->getLine();
						int c = errNode->getSymbol()->getCharPositionInLine();

						Diagnostic diag;
						diag.range.set(l, c, l, c + errNode->getText().size());
						diag.severity = 1;
						diag.message = std::format("syntax error:{}", errNode->getText());
						p.diagnostics.push_back(diag);
					}
					json jo = p;
					writeNotification("textDocument/publishDiagnostics", jo);
				}
			}*/
		}
	

		//符号错误识别
		{
			TypeCheckerVisitor vi;
			vi.space = info->symbolSpace;
			vi.doCheck(info->program);


			for (auto& info : vi.typeErrors) {
				Diagnostic diag;
				diag.range = info.range;
				diag.severity = 1;
				diag.message = std::format("type error. {}", info.message);
				p.diagnostics.push_back(diag);
			}
		}

		json jo = p;
		writeNotification("textDocument/publishDiagnostics", jo);
	}
}

bool didOpen(int id, std::string method, json& params) {
	if (method != "textDocument/didOpen") return false;

	json textDocument = params["textDocument"];

	std::shared_ptr<TextDocumentDidOpen> ent = std::make_shared<TextDocumentDidOpen>();
	textDocument.get_to(*ent);
	ent->uri = decodeURIComponent(ent->uri);


	auto tid = ThreadUtil::getThisThreadIdString();
	log(std::format("=========>didOpen. tid:{}\n", tid));

	auto mail = std::make_shared<ActorMail>();
	mail->cbHandle = [ent](ActorMail *mail, ActorByThread *actor) {
		auto tid = ThreadUtil::getThisThreadIdString();
		log(std::format("thread:{} ent:{} {} {} {}\n", tid, ent->languageId, ent->uri, ent->text.size(), ent->version));

		updateTextDocumentSymbolInfo(ent);
		log(std::format("updateTextDocumentSymbolInfo succ\n"));

		//发个诊断
		{
			diagnosticsActor->runOnThisActor([=]() {
				doDiagnostic(ent->uri);
			});
		}
	};

	symbolActor->pushNotification(mail);

	return true;
}

void DiagnosticsActor::doRun()  {

	ActorByThread::doRun();
}
void DiagnosticsActor::route(std::shared_ptr<ActorMail>& mail)
{
	ActorByThread::route(mail);
}
//更新textDocument的符号表
void updateTextDocumentSymbolInfo(std::shared_ptr<TextDocumentDidOpen> textDocument) {
	//如果存在
	auto old = textDocumentSymbolInfoMap.get(textDocument->uri);
	if (old != nullptr) {
		//如果版本一样,不用更新
		if (old->textDocument->version == textDocument->version) {
			log(std::format("uri {}. version is same:{}\n", textDocument->uri, textDocument->version));
			return;
		}
	} 
	//总是创建新实例
	auto info = std::make_shared<TextDocumentSymbolInfo>();
	log(std::format("create new TextDocumentSymbolInfo for uri {}. \n", textDocument->uri));

	info->textDocument = textDocument;

	//构建符号表
	info->symbolSpace = buildSymbolSpace_byTextDocument(info, textDocument);
	textDocumentSymbolInfoMap.set(textDocument->uri, info);

	log(std::format("buildSymbolSpace_byTextDocument  for uri {}. version:%d \n", textDocument->uri, textDocument->version));
}


std::shared_ptr<SymbolSpace> buildSymbolSpace_byTextDocument(std::shared_ptr<TextDocumentSymbolInfo> info, std::shared_ptr<TextDocumentDidOpen> textDocument) {
	CostUs cost;
	auto absPath = fileUri_toAbsPath(textDocument->uri);

	log(std::format("buildSymbolSpace_byTextDocument. uri:{}, absPath:{}\n", textDocument->uri, absPath));

	//std::shared_ptr<ANTLRInputStream> input;
	//std::shared_ptr<OrcLexer> lexer;
	//std::shared_ptr<CommonTokenStream> tokens;
	//std::shared_ptr<OrcParser> parser;

	//input = std::make_shared<ANTLRInputStream>(textDocument->text);
	//lexer = std::make_shared<OrcLexer>(input.get());
	//tokens = std::make_shared<CommonTokenStream>(lexer.get());
	//parser = std::make_shared<OrcParser>(tokens.get());
	info->fullAst.initByCode(textDocument->text);

	log(std::format("buildSymbolSpace_byTextDocument. mk parser\n"));
	info->fullAst.parser->removeErrorListeners();
	auto tree = info->fullAst.parser->program();
	info->program = dynamic_cast<OrcRuleContext*>(tree);
	if (!info->program) {
		throw std::string("parse program error");
	}
	if (info->fullAst.parser->getNumberOfSyntaxErrors() > 0) {
		throw std::string("has syntax error");
	}
	log(std::format("buildSymbolSpace_byTextDocument. program\n"));

	auto space = std::make_shared<SymbolSpace>();
	space->symbolSpaceLoader = symbolSpaceLoader;
	space->path = absPath;
	log(std::format("buildSymbolSpace_byTextDocument. mkSpace\n"));

	SymbolBuilderVisitor vi;

	vi.init(absPath);
	log(std::format("buildSymbolSpace_byTextDocument. init symbol builder v isitor\n"));
	vi.space = space;
	vi.visit(tree);
	log(std::format("buildSymbolSpace_byTextDocument. SymbolBuilderVisitor.visit\n"));


	info->mk.tracker = &info->_tracker;

	//给方法添加self参数
	AddSelfArgumentVisitor addSelfArgumentVisitor;
	addSelfArgumentVisitor.mk = &info->mk;
	addSelfArgumentVisitor.visit(tree);

	return space;
	//space->startBuild(absPath, tree, parser, cost);
	////注册缓存
	//symbolSpaceLoader->lib[absPath] = space;
	////保存符号文件
	//symbolSpaceLoader->saveSymbolFile_forOrc(absPath, space.get());
}

bool didChange(int id, std::string method, json& params) {
	if (method != "textDocument/didChange") return false;

	std::shared_ptr<TextDocumentDidChange> ent = std::make_shared<TextDocumentDidChange>();
	params.get_to(*ent);

	ent->textDocument.uri = decodeURIComponent(ent->textDocument.uri);
	log(std::format("didChange:{} {} {} \n", ent->textDocument.uri, ent->contentChanges[0].text.size(), ent->textDocument.version));


	auto old = textDocumentSymbolInfoMap.get(ent->textDocument.uri);
	if (old != nullptr) {
		//文本变更立即生效，不然可能completion会拿到旧值,导致识别异常
		old->textDocument->text = ent->contentChanges[0].text;
	}
	
	auto mail = std::make_shared<ActorMail>();
	mail->cbHandle = [ent](ActorMail* mail, ActorByThread* actor) {
		updateTextDocumentCodeAndSymbolInfo(ent->textDocument.uri, ent->textDocument.version, ent->contentChanges[0].text);
		log(std::format("didChange succ\n"));

		{
			diagnosticsActor->runOnThisActor([=]() {
				doDiagnostic(ent->textDocument.uri);
			});
		}
	};

	symbolActor->pushNotification(mail);
	return true;
}


//更新textDocument的符号表
void updateTextDocumentCodeAndSymbolInfo(std::string uri, int version, std::string code) {
	//如果存在
	auto old = textDocumentSymbolInfoMap.get( uri);
	if (old != nullptr) {
		//如果版本一样,不用更新
		if (old->textDocument->version == version) {
			log(std::format("uri {}. version is same:{}\n", uri, version));
			return;
		}
	}
	else { //不存在就创建新实例
		return;
		/*auto info = std::make_shared<TextDocumentSymbolInfo>();
		textDocumentSymbolInfoMap[uri] = info;
		log(std::format("create new TextDocumentSymbolInfo for uri {}. \n", uri));*/

	}

	//总是创建新实例
	auto info = std::make_shared<TextDocumentSymbolInfo>();
	//auto info = textDocumentSymbolInfoMap.get(uri);
	info->textDocument = std::make_shared<TextDocumentDidOpen>();
	if (old) {
		info->textDocument->languageId = old->textDocument->languageId;
	}
	info->textDocument->uri = uri;
	info->textDocument->version = version;
	info->textDocument->text = code;

	//构建符号表
	info->symbolSpace = buildSymbolSpace_byTextDocument(info, info->textDocument);
	textDocumentSymbolInfoMap.set(uri, info);

	log(std::format("buildSymbolSpace_byTextDocument  for uri {}. version:%d \n", uri, version));
}


void showMessage(std::string msg, int type) {
	ShowMessageParams p;
	p.type = type;
	p.message = msg;


	lspActor->runOnThisActor([=]() {
		json jo = p;
		writeNotification("window/showMessage", jo);
	});
}