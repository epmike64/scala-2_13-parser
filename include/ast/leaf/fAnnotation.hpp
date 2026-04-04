#pragma once
#include "fParamType.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace util;

	class fAnnotation : public fLangOprnd {
		const sp<fParamType> simpleType_;
		PVecP<fAstProdSubTreeN> argsExprs_;
	public:
		fAnnotation(sp<fParamType> simpleType);

		 sp<fParamType> getSimpleType() const ;

		void addArgExprs(sp<fAstProdSubTreeN> &&arg);
		PVecP<fAstProdSubTreeN> getArgsExprs();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::ANNOTATION;
		}
	};
}
