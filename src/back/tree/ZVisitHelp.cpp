#include "back/tree/ZVisitHelp.hpp"

#include <iostream>
#include <stack>

#include "ast/leaf/fClassParam.hpp"
#include "ast/symbol/ZEnclScope.hpp"
#include "ast/leaf/fClassParamClauses.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;

	esc ZVisitHelp::getWrapScope(esc prnSc, ZLangConstruct lc) {
		assert(prnSc != nullptr);
		while (prnSc->getLangConstruct() != lc) {
			prnSc = prnSc->getParentScope();
			if (prnSc == nullptr) {
				throw std::runtime_error("No enclosing scope found for language construct: " + std::to_string(lc));
			}
		}
		return prnSc;
	}

	void ZVisitHelp::treePostOrderPush(sp<fAstNod> n, esc prnSc) {
		sp<ZProdSubTreeN> prnt = std::dynamic_pointer_cast<ZProdSubTreeN>(prnSc->getZSymbol());
		if (prnt) {
			prnt->getTreePostOrderSS()->push_back(n);
			std::cout << "Pushed: " + n->toString() << std::endl;
			std::cout << prnt->getTreePostOrderSS()->toString() << std::endl;
			std::cout <<  "" << std::endl;
		} else {
			std::cout << "" << std::endl;
		}
	}

	sp<fAstNod> ZVisitHelp::getAstPSTreeRightN(sp<fAstProdSubTreeN> subTr) {
		while (true) {
			sp<fAstNod> subTRight = subTr->getRootOpNod()->getAstRightN();
			sp<fAstProdSubTreeN> subTRight_SubTr = std::dynamic_pointer_cast<fAstProdSubTreeN>(subTRight);
			if (!subTRight_SubTr) {
				return subTRight;
			}
			subTr = subTRight_SubTr;
		}
	}

	void ZVisitHelp::traverseProdSubTree(sp<fAstProdSubTreeN> subTr, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << subTr->toString() << std::endl;

		sp<fAstNod> psubT = getAstPSTreeRightN(subTr);
		if (!psubT) {
			return;
		}

		sp<ZProdSubTreeN> prnt = std::dynamic_pointer_cast<ZProdSubTreeN>(prnSc->getZSymbol());
		if (prnt == nullptr) {
			throw std::runtime_error("Parent symbol in scope must be a production subtree node");
		}

		std::stack<sp<fAstStackItem>> ss;
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
			currNode->accept(visitor, prnSc);
		}

		std::cout << subTr->toString() + " END" << std::endl;
	}

	void ZVisitHelp::visitClassParamClauses(sp<fClassParamClauses> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		for (const auto& classParamList : n->getClassParamLists()) {
			for (const auto& classParam : classParamList) {
				classParam->accept(visitor, prnSc);
			}
		}
		for (const auto& implicitClassParam : n->getImplicitClassParamList()) {
			implicitClassParam->accept(visitor, prnSc);
		}
	}
}
