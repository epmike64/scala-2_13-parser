#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "ZEnclosingScopeFwd.hpp"
#include "../node/fAstProdSubTreeN.hpp"
#include "ast/leaf/fType.hpp"
#include "ast/leaf/fVariantTypeParam.hpp"
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
		public:
		~ZSymbol() = default;
	};
	//
	// class ZSymbol {
	// 	sp<ZFullyQualifiedName> qualifiedName_;
	//
	// public:
	// 	virtual ~ZSymbol() = default;
	// 	// virtual std::string toString() const = 0;
	// };

	// class ZVariantTypeParam;

	// class ZVariantTypeParam: public ZSymbol {
	// protected:
	// 	sp<fVariantTypeParam> variantTypeParam_;
	// public:
	// 	explicit ZVariantTypeParam(sp<fVariantTypeParam> variantTypeParam) : variantTypeParam_(std::move(variantTypeParam)) {}
	//
	// 	sp<fVariantTypeParam> getVariantTypeParam() const {
	// 		return variantTypeParam_;
	// 	}
	// };

	// class ZTypeParam: public ZSymbol {
	//
	// };
	//
	// class ZTrait: public ZSymbol {};
	//
	// class ZClass : public ZSymbol {
	// 	sp<ZClass> parentClass_;
	// 	sp<std::vector<sp<ZTrait>>> traits_;
	// 	// std::vector<sp<ZVariantTypeParam>> variantTypeParams_;
	// 	public:
	// };

	/**
	 *
	 */
	class ZEnclScope {
		const esc parentScope_;
		const ZGrmrProdE parentScopeGrmrProd_;
		PVecP<fAstNod> polishCalcStack; //RPN - reverse polish notation
		// StrPVecPMap<ZTypeParam> typeParamMap_;
		StrPVecPMap<ZSymbol> symbolMap_;
	public:
		ZEnclScope(esc parentScope, ZGrmrProdE parentScopeGrmrProd);
		esc getParentScope() const;

		ZGrmrProdE getParentScopeGrmrProd() const;

		void setPolishSS(PVecP<fAstNod>&& astRPN) ;

		PVecP<fAstNod> getPolishSS() const;

		void addSymbol(const std::string& name, sp<ZSymbol> declr);
		PVecP<ZSymbol> getSymbol(const std::string& name) const;
	};



	//esc
}
