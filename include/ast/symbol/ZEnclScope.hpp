#pragma once

#include <string>
#include <vector>

#include "ZEnclScopeFwd.hpp"
#include "../node/fAstProdSubTreeN.hpp"
#include "ast/leaf/fType.hpp"
#include "util/fCommon.hpp"
#include "ZSymbol.hpp"


namespace zebra::ast::symbol {

	using namespace zebra::ast::node;
	using namespace zebra::ast::leaf;
	using namespace zebra::lex::kind;
	using namespace zebra::util;
	using symbol::ZSymbol;


	class ZSymbol;

	class ZFullyQualName {
		std::vector<std::string> simpleNames;
	public:

		ZFullyQualName(std::vector<std::string> qualifiers) : simpleNames(qualifiers) {}

		std::string getSimpleName() {
			return simpleNames.empty() ? "" : simpleNames.back();
		}

		std::vector<std::string> getFullyQualifiedName() const {
			return simpleNames;
		}
	};




	/**
	 *
	 */
	class ZEnclScope {
		const esc parentScope_;
		PVecP<fAstNod> polishCalcStack; //RPN - reverse polish notation

	protected:
		sp<ZUnit> zUnit = nullptr;
	public:

		ZEnclScope(esc parentScope, sp<ZUnit> zUnit);
		esc getParentScope() const;

		ZLangConstruct getLangConstruct() const;

		void setPolishSS(PVecP<fAstNod>&& astRPN) ;

		PVecP<fAstNod> getPolishSS() const;

		sp<ZUnit> getZUnit();
	};



	//esc
}
