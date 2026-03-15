#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;
	using namespace ast::symbol;

	class fTypeParam : public fAstOprndNod {
		const fToken* typeParamName_;
		sp<std::vector<sp<fVariantTypeParam>>> variantTypeParam_;
		sp<fType> upperBound_, lowerBound_;
		sp<std::vector<sp<fType>>> types_;
		sp<std::vector<sp<fType>>> contextBounds_;

	public:
		fTypeParam() = default;
		virtual ~fTypeParam();

		void setTypeParamName(const fToken* typeParamName);

		 const fToken* getTypeParamName() const ;

		void setVariantTypeParam(std::vector<sp<fVariantTypeParam>> &&variantTypeParam);


		void setVariantTypeParams(std::vector<sp<fVariantTypeParam> > &&variantTypeParam) ;

		sp<std::vector<sp<fVariantTypeParam>>> getVariantTypeParam() const;

		 void addType(sp<fType> &&types) ;

		 sp<std::vector<sp<fType>>> getTypes() const;

		void addContextBound(sp<fType> &&contextBound) ;

		sp<std::vector<sp<fType>>> getContextBounds() const;

		 void setUpperBound(sp<fType> &&upperBound) ;

		 sp<fType> getUpperBound() const ;

		 void setLowerBound(sp<fType> &&lowerBound);

		 sp<fType> getLowerBound() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}