
#include "back/tree/ZVisitClassHelp.hpp"

#include <iostream>

#include "ast/leaf/fAccessModifier.hpp"
#include "ast/leaf/fClassDef.hpp"
#include "ast/leaf/fModifiers.hpp"
#include "ast/leaf/fTemplate.hpp"

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
			cls->getTypeParamClause()->accept(visitor, clsDefScp);
		}

		if (cls->getClassParamClauses()) {
			cls->getClassParamClauses()->accept(visitor, clsDefScp);
		}

		if (cls->getExtendsTemplate()) {
			cls->getExtendsTemplate()->accept(visitor, clsDefScp);
		}
	}

}
