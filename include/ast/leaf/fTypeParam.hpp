#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTypeParam : public fAstOprndNod {
		const fToken* typeParamName_;
		sp<std::vector<sp<fVariantTypeParam>>> variantTypeParam_;
		sp<fType> type_, upperBound_, lowerBound_;
		public:

		fTypeParam(const fToken* name) ;

		 const fToken* getTypeParamName() const ;

		void setVariantTypeParam(std::vector<sp<fVariantTypeParam>> &&variantTypeParam);


		void setVariantTypeParams(std::vector<sp<fVariantTypeParam> > &&variantTypeParam) ;

		sp<std::vector<sp<fVariantTypeParam>>> getVariantTypeParam() const;

		 void setType(sp<fType> &&type) ;

		 sp<fType> getType() const;

		 void setUpperBound(sp<fType> &&upperBound) ;

		 sp<fType> getUpperBound() const ;

		 void setLowerBound(sp<fType> &&lowerBound);

		 sp<fType> getLowerBound() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}