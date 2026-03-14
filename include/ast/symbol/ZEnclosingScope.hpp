#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "ZEnclosingScopeFwd.hpp"
#include "../node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::symbol {

	using namespace zebra::ast::node;

	class ZNameQualifier {
		std::vector<std::string> qualifiers_;
	public:

		ZNameQualifier(std::vector<std::string> qualifiers) : qualifiers_(qualifiers) {}

		std::string getSimpleName() {
			return qualifiers_.empty() ? "" : qualifiers_.back();
		}

		std::vector<std::string> getQualifiedName() const {
			return qualifiers_;
		}
	};

	class ZSymbol {
		sp<ZNameQualifier> qualifier_;

	public:
		virtual ~ZSymbol() = default;
		virtual std::string toString() const = 0;
	};


	class ZTypeParam : public ZSymbol {

	};

	class ZClass : public ZSymbol {

		public:
	};

	/**
	 *
	 */
	class ZEnclosingScope {
		const esc parentScope_;
		const fLangGrmrProdE parentScopeGrmrProd_;
		sp<std::vector<sp<fAstNod>>> polishCalcStack; //RPN - reverse polish notation
		sp<std::unordered_map<std::string, sp<ZSymbol>>> symbolMap_;
	public:
		ZEnclosingScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setPolishSS(sp<std::vector<sp<fAstNod>>>&& astRPN) ;

		sp<std::vector<sp<fAstNod>>> getPolishSS() const;

		void addSymbol(const std::string& name, sp<ZSymbol> declr);
		sp<ZSymbol> getSymbol(const std::string& name) const;
	};



	//esc
}
