#include "back/tree/ZVisitPSubTreeHelp.hpp"

#include <iostream>
#include <stack>

#include "ast/leaf/fClassParam.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/leaf/fParamType.hpp"
#include "util/fUtil.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast;


	sp<ZProdSubTreeN> ZVisitPSubTreeHelp::visitIntoSubTree(sp<fAstNod> node, esc prnSc, sp<fAstNodVisitor> visitor) {
		sp<ZProdSubTreeN> tr = ms<ZProdSubTreeN>();
		esc trSc = ms<ZEnclScope>(prnSc, tr);
		node->accept(visitor, trSc);
		return tr;
	}

	// void ZVisitPSubTreeHelp::treePostOrderPush(sp<fAstNod> n, esc prnSc) {
	// 	sp<ZProdSubTreeN> prnt = std::dynamic_pointer_cast<ZProdSubTreeN>(prnSc->getZSymbol());
	// 	if (prnt) {
	// 		prnt->getTreePostOrderSS()->push_back(n);
	// 		std::cout << "Pushed: " + n->toString() << std::endl;
	// 		std::cout << prnt->getTreePostOrderSS()->toString() << std::endl;
	// 		std::cout << "" << std::endl;
	// 	} else {
	// 		std::cout << "" << std::endl;
	// 	}
	// }

	sp<fAstNod> ZVisitPSubTreeHelp::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTr) {
		while (true) {
			sp<fAstNod> subTRight = subTr->getRootOpNod()->getAstRightN();
			sp<fAstProdSubTreeN> subTRight_SubTr = std::dynamic_pointer_cast<fAstProdSubTreeN>(subTRight);
			if (!subTRight_SubTr) {
				return subTRight;
			}
			subTr = subTRight_SubTr;
		}
	}

	void ZVisitPSubTreeHelp::traverseProdSubTree(sp<fAstProdSubTreeN> subTr, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << subTr->toString() << std::endl;

		sp<fAstNod> psubT = getAstPSTreeRightN(subTr);
		if (!psubT) {
			return;
		}

		sp<ZProdSubTreeN> prnt = std::dynamic_pointer_cast<ZProdSubTreeN>(prnSc->getZSymbol());
		zaccert(prnt != nullptr, "Parent symbol in scope must be a production subtree node");


		std::stack<sp<fAstStackItem> > ss;
		ss.push(ms<fAstStackItem>(psubT));

		while (!ss.empty()) {
			sp<fAstStackItem> currItem = ss.top();
			sp<fAstNod> currNode = currItem->getNode();
			if (currNode == nullptr) {
				throw std::runtime_error("Current node in AST stack cannot be null");
			}

			if (!currItem->isLeftVisited()) {
				currItem->setLeftVisited();
				if (currNode->getAstLeftN()) {
					sp<fAstProdSubTreeN> leftSubTr = std::dynamic_pointer_cast<fAstProdSubTreeN>(currNode->getAstLeftN());
					if (leftSubTr) {
						sp<fAstNod> pst = getAstPSTreeRightN(leftSubTr);
						if (pst) {
							ss.push(ms<fAstStackItem>(pst));
						}
					} else {
						ss.push(ms<fAstStackItem>(currNode->getAstLeftN()));
					}
					continue;
				}
			}

			if (!currItem->isRightVisited()) {
				currItem->setRightVisited();
				if (currNode->getAstRightN()) {
					sp<fAstProdSubTreeN> rightSubTr = std::dynamic_pointer_cast<fAstProdSubTreeN>(currNode->getAstRightN());
					if (rightSubTr) {
						sp<fAstNod> pst = getAstPSTreeRightN(rightSubTr);
						if (pst) {
							ss.push(ms<fAstStackItem>(pst));
						}
					} else {
						ss.push(ms<fAstStackItem>(currNode->getAstRightN()));
					}
					continue;
				}
			}

			ss.pop();
			if (!currNode->isOperator()) {
				switch (dynSp<ast::fLangOprnd>(currNode)->getLangOprndType()) {
					case LOprndT::LITERAL: case LOprndT::STABLE_ID: case LOprndT::ID: case LOprndT::UNDERSCORE: {
						prnt->getTreePostOrderSS()->push_back(ms<ZAstNWrap>(currNode));
						break;
					}
					case LOprndT::TYPE: {
						sp<ZType> zType = ms<ZType>();
						esc typeScp = ms<ZEnclScope>(prnSc, zType);
						currNode->accept(visitor, typeScp);
						prnt->getTreePostOrderSS()->push_back(zType);
						break;
					}
					case LOprndT::TYPE_ARGS: {
							sp<ZTypeList> zTypeList = ms<ZTypeList>();
							esc typeArgsScp = ms<ZEnclScope>(prnSc, zTypeList);
							currNode->accept(visitor, typeArgsScp);
							prnt->getTreePostOrderSS()->push_back(zTypeList);
							break;
					}
					case LOprndT::CLASS_TEMPLATE: {
						sp<ZClassTemplate> zClassTemplate = ms<ZClassTemplate>();
						esc classTemplateScp = ms<ZEnclScope>(prnSc, zClassTemplate);
						currNode->accept(visitor, classTemplateScp);
						prnt->getTreePostOrderSS()->push_back(zClassTemplate);
						break;
					}
					case LOprndT::IF: {
						sp<ZIf> zIf = ms<ZIf>();
						esc ifScp = ms<ZEnclScope>(prnSc, zIf);
						currNode->accept(visitor, ifScp);
						prnt->getTreePostOrderSS()->push_back(zIf);
						break;
					}
					case LOprndT::BLOCK: {
						sp<ZBlock> zBlock = ms<ZBlock>();
						esc blockScp = ms<ZEnclScope>(prnSc, zBlock);
						currNode->accept(visitor, blockScp);
						prnt->getTreePostOrderSS()->push_back(zBlock);
						break;
					}
					default:
						std::cout << fLangOprndType2String(dynSp<ast::fLangOprnd>(currNode)->getLangOprndType()) << std::endl;
						throw std::runtime_error("Unsupported language operand type in production subtree: " + fLangOprndType2String(dynSp<ast::fLangOprnd>(currNode)->getLangOprndType()));
				}

			} else {
				prnt->getTreePostOrderSS()->push_back(ms<ZAstNWrap>(currNode));
			}
		}

		std::cout << subTr->toString() + " END" << std::endl;
	}


	esc ZVisitPSubTreeHelp::getWrapScope(esc prnSc, ZLangConstruct lc) {
		assert(prnSc != nullptr);
		while (prnSc->getLangConstruct() != lc) {
			prnSc = prnSc->getParentScope();
			if (prnSc == nullptr) {
				throw std::runtime_error("No enclosing scope found for language construct: " + std::to_string(lc));
			}
		}
		return prnSc;
	}
}
