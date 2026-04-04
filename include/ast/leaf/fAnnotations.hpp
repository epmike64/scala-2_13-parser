#pragma once
#include "fAnnotation.hpp"
#include "fParamType.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace util;

	class fAnnotations: public fLangOprnd {
		PVecP<fAnnotation> annotations_;
		public:
		fAnnotations() = default;
		void addAnnotation(sp<fAnnotation> annotation) ;
		PVecP<fAnnotation> annotations();

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::ANNOTATIONS;
		}
	};
}
