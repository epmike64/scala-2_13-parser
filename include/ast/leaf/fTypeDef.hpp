#pragma once

#include <vector>

#include "ast/node/fAstOprndNod.hpp"
#include "ast/node/fAstNodVisitor.hpp"
#include "util/fCommon.hpp"

namespace zebra::ast::leaf {
	using namespace ast::node;

	class fTypeDef : public fAstOprndNod {
		const fToken* _typeDefName;
		std::vector<sp<fVariantTypeParam>> typeParams_;
		sp<fType> assignedType_;
		public:

		fTypeDef(const fToken* typeDefName) ;

		 const fToken* getTypeDefName() const;

		 void setTypeParams(std::vector<sp<fVariantTypeParam>> &&typeParams) ;

		 std::vector<sp<fVariantTypeParam>> getTypeParams() const ;

		 void setAssignedType(sp<fType> &&assignedType);
		 sp<fType> getAssignedType() const ;

		void accept(std::shared_ptr<fAstNodVisitor> visitor, esc s) override;
		std::string toString() const override;
	};
}