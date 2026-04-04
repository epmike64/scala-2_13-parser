#pragma once
#include "fParamType.hpp"
#include "ast/node/fAstProdSubTreeN.hpp"


namespace zebra::ast::leaf {
	using namespace ast::node;

	class fAnnotation : public fLangOprnd {
		const sp<fParamType> simpleType_;
		PVecP<fAstProdSubTreeN> argsExprs_;
	public:
		fAnnotation(sp<fParamType> simpleType) : simpleType_(std::move(simpleType)) {}

		 sp<fParamType> getSimpleType() const {
			return simpleType_;
		}

		void addArgExprs(sp<fAstProdSubTreeN> &&arg) {
			if (!argsExprs_) {
				argsExprs_ = ms<std::vector<sp<fAstProdSubTreeN>>>();
			}
			argsExprs_->push_back(std::move(arg));
		}

		void accept(std::shared_ptr<fAstNodVisitor> visitor, sbx s) override;
		std::string toString() const override;

		fLangOprndType getLangOprndType() override {
			return LOprndT::ANNOTATION;
		}
	};
}
