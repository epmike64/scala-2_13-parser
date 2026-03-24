
#include "back/tree/ZVisitClassHelp.hpp"

#include <iostream>

#include "ast/leaf/fAccessModifier.hpp"
#include "ast/leaf/fClassDef.hpp"
#include "ast/leaf/fClassParents.hpp"
#include "ast/leaf/fClassTemplate.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fObjectDef.hpp"
#include "ast/leaf/fTemplate.hpp"
#include "ast/leaf/fTemplateBody.hpp"
#include "back/tree/ZVisitTypeParamHelp.hpp"

namespace zebra::back::tree {
	using namespace ast::symbol;
	using namespace ast::leaf;
	using namespace util;

	void ZVisitClassHelp::visitClassDef(sp<fClassDef> cls, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting "<< (cls->isCaseClass()? "Case ": "") <<"ClassDef "  << cls->getIdentName()  << std::endl;

		sp<ZClassDef> zClsDef = ms<ZClassDef>(cls->getIdentName());
		esc clsDefScp = ms<ZEnclScope>(prnSc, zClsDef);

		if (cls->getModifiers()) {
			cls->getModifiers()->accept(visitor, clsDefScp);
		}

		if (cls->getConstrAccessModifier()) {
			cls->getConstrAccessModifier()->accept(visitor, clsDefScp);
		}

		if (cls->getTypeParamClause()) {
			zClsDef->setVariantTypeParamList(ms<ZVariantTypeParamList>());
			esc vtpListScp = ms<ZEnclScope>(clsDefScp, zClsDef->getVariantTypeParamList());
			ZVisitTypeParamHelp::buildVariantTypeParamClause(cls->getTypeParamClause(), zClsDef->getVariantTypeParamList(), vtpListScp,visitor);
		}

		if (cls->getClassParamClauses()) {
			cls->getClassParamClauses()->accept(visitor, clsDefScp);
		}

		if (cls->getExtendsTemplate()) {
			cls->getExtendsTemplate()->accept(visitor, clsDefScp);
		}
	}
	
	
	void ZVisitClassHelp::visitObjectDef(sp<fObjectDef> obj, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting "<< (obj->isCaseClass()? "Case ": "") <<"Object"  << obj->getIdentName()  << std::endl;

		sp<ZObjectDef> zObjDef = ms<ZObjectDef>(obj->getIdentName());
		esc objDefScp = ms<ZEnclScope>(prnSc, zObjDef);

		if (obj->getModifiers()) {
			obj->getModifiers()->accept(visitor, objDefScp);
		}

		if (obj->getExtendsTemplate()) {
			obj->getExtendsTemplate()->accept(visitor, objDefScp);
		}
	}
	
	///////////////
	

	void ZVisitClassHelp::visitClassTemplate(sp<fClassTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Class Template" << std::endl;
		if (n->getClassParents()) {
			n->getClassParents()->accept(visitor, prnSc);
		}
		if (n->getTemplateBody()) {
			n->getTemplateBody()->accept(visitor, prnSc);
		}
	}

	void ZVisitClassHelp::visitTemplate(sp<fTemplate> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template" << std::endl;
		n->getTemplateBody()->accept(visitor, prnSc);
	}

	void ZVisitClassHelp::visitTemplateBody(sp<fTemplateBody> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Template Body" << std::endl;
		sp<ZTemplateBody> zTB = ms<ZTemplateBody>();
		esc tbScp = ms<ZEnclScope>(prnSc,  zTB);
		for (const auto& stmt : n->getStmts()) {
			stmt->accept(visitor, tbScp);
		}
	}
	void ZVisitClassHelp::visitTraitDef(sp<fTraitDef> n, esc prnSc, sp<fAstNodVisitor> visitor) {
		std::cout << "Visiting Trait Definition: " << std::endl;
		if (n->getModifiers()) {
			n->getModifiers()->accept(visitor, prnSc);
		}
		if (n->getTypeParamClause()) {
			n->getTypeParamClause()->accept(visitor, prnSc);
		}
		if (n->getExtendsTemplate()) {
			n->getExtendsTemplate()->accept(visitor, prnSc);
		}
	}

}
