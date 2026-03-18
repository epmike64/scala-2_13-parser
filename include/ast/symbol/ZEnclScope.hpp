#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "ZEnclosingScopeFwd.hpp"
#include "../node/fAstProdSubTreeN.hpp"
#include "ast/leaf/fType.hpp"
#include "lex/kind/fVarianceE.hpp"
#include "util/fCommon.hpp"


namespace zebra::ast::symbol {

	using namespace zebra::ast::node;
	using namespace zebra::ast::leaf;
	using namespace zebra::lex::kind;
	using namespace zebra::util;

	class ZFullyQualifiedName {
		std::vector<std::string> simpleNames;
	public:

		ZFullyQualifiedName(std::vector<std::string> qualifiers) : simpleNames(qualifiers) {}

		std::string getSimpleName() {
			return simpleNames.empty() ? "" : simpleNames.back();
		}

		std::vector<std::string> getFullyQualifiedName() const {
			return simpleNames;
		}
	};

	class ZSymbol {
		sp<ZFullyQualifiedName> qualifiedName_;

	public:
		virtual ~ZSymbol() = default;
		// virtual std::string toString() const = 0;
	};

	class ZVariantTypeParam;

	class ZTypeParam {
	protected:
		const fToken* id_;
		std::vector<sp<ZVariantTypeParam>> variantTypeParams_;
		sp<fType> upperBound_, lowerBound_;
		sp<std::vector<sp<fType>>> contextBounds_;
		sp<fType> theType_;
	public:
		~ZTypeParam() = default;
	};

	class ZVariantTypeParam : public ZTypeParam {
		fVarianceE variance_;
	};

	class ZTrait: public ZSymbol {};

	class ZClass : public ZSymbol {
		sp<ZClass> parentClass_;
		sp<std::vector<sp<ZTrait>>> traits_;
		std::vector<sp<ZVariantTypeParam>> variantTypeParams_;
		public:
	};

	/**
	 *
	 */
	class ZEnclScope {
		const esc parentScope_;
		const fLangGrmrProdE parentScopeGrmrProd_;
		sp<std::vector<sp<fAstNod>>> polishCalcStack; //RPN - reverse polish notation
		// sp<std::unordered_map<std::string, sp<ZSymbol>>> symbolMap_;
		StrVecMap<ZSymbol> symbVecMap_;
	public:
		ZEnclScope(esc parentScope, fLangGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		fLangGrmrProdE getParentScopeGrmrProd() const;

		void setPolishSS(sp<std::vector<sp<fAstNod>>>&& astRPN) ;

		sp<std::vector<sp<fAstNod>>> getPolishSS() const;

		void addSymbol(const std::string& name, sp<ZSymbol> declr);
		PtrVec<ZSymbol> getSymbol(const std::string& name) const;
	};



	//esc
}
